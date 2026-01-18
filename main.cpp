#include <vector>
#include <syslog.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <libproc.h>
#include <CoreFoundation/CoreFoundation.h>

// Configuration
const char* TARGET_PROCESS = "WallpaperAerialsExtension";
const char* LOG_TAG = "WallpaperFix";

void killWallpaper() {
    // Get list of PIDs
    int numProcs = proc_listpids(PROC_ALL_PIDS, 0, NULL, 0);
    if (numProcs <= 0) {
        syslog(LOG_ERR, "%s: Error retrieving process list count", LOG_TAG);
        return;
    }

    // Allocate buffer
    std::vector<pid_t> pids(numProcs + 10);
    int actualCount = proc_listpids(PROC_ALL_PIDS, 0, pids.data(), pids.size() * sizeof(pid_t));

    if (actualCount <= 0) return;

    char procNameBuffer[PROC_PIDPATHINFO_MAXSIZE];

    for (int i = 0; i < actualCount; ++i) {
        if (pids[i] == 0) continue;
        if (proc_name(pids[i], procNameBuffer, sizeof(procNameBuffer)) > 0) {
            if (strcmp(procNameBuffer, TARGET_PROCESS) == 0) {
                syslog(LOG_NOTICE, "%s: Killing %s (PID: %d)", LOG_TAG, TARGET_PROCESS, pids[i]);
                kill(pids[i], SIGKILL);
            }
        }
    }
}

void systemEventCallback(CFNotificationCenterRef center,
                         void *observer,
                         CFStringRef name,
                         const void *object,
                         CFDictionaryRef userInfo) {
    if (CFStringCompare(name, CFSTR("com.apple.screenIsUnlocked"), 0) == kCFCompareEqualTo) {
        syslog(LOG_NOTICE, "%s: Unlock detected, scanning processes...", LOG_TAG);
        killWallpaper();
    }
}

int main() {
    // Initialize logging
    openlog(LOG_TAG, LOG_PID | LOG_CONS, LOG_USER);

    CFNotificationCenterRef center = CFNotificationCenterGetDistributedCenter();
    if (!center) {
        syslog(LOG_ERR, "%s: Failed to get distributed notification center!", LOG_TAG);
        return -1;
    }

    // Register observer
    CFNotificationCenterAddObserver(
            center,
            nullptr,
            systemEventCallback,
            CFSTR("com.apple.screenIsUnlocked"),
            nullptr,
            CFNotificationSuspensionBehaviorDeliverImmediately
    );

    syslog(LOG_NOTICE, "%s: Started successfully. Listening for unlock events...", LOG_TAG);

    // Run the main loop
    CFRunLoopRun();

    closelog();
    return 0;
}
