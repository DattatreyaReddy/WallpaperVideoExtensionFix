#include <iostream>
#include <vector>
#include <string>
#include <signal.h>
#include <unistd.h>
#include <ApplicationServices/ApplicationServices.h>
#include <libproc.h>
#include <CoreFoundation/CoreFoundation.h>
#include <CoreServices/CoreServices.h>
const char* processName = "WallpaperAerialsExtension";
// Function to kill the process by name
void killWallpaper() {
    int numProcs = proc_listpids(PROC_ALL_PIDS, 0, NULL, 0);
    if (numProcs <= 0) {
        std::cerr << "Error retrieving process list" << std::endl;
        return;
    }

    std::vector<pid_t> pids(numProcs);
    numProcs = proc_listpids(PROC_ALL_PIDS, 0, pids.data(), pids.size() * sizeof(pid_t));

    for (int i = 0; i < numProcs; ++i) {
        if (pids[i] == 0) continue;

        char procNameBuffer[PROC_PIDPATHINFO_MAXSIZE];
        if (proc_name(pids[i], procNameBuffer, sizeof(procNameBuffer)) > 0) {
            if (std::string(procNameBuffer) == processName) {
                std::cout << "Killing " << processName << " (PID: " << pids[i] << ")" << std::endl;
                kill(pids[i], SIGKILL);
                break;
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
        std::cout << "unlock detected" << std::endl;
        killWallpaper();
    }
}

int main() {
    // Create a notification center
    CFNotificationCenterRef center = CFNotificationCenterGetDistributedCenter();
    if (!center) {
        std::cerr << "Failed to get notification center!" << std::endl;
        return -1;
    }

    // Register for screen unlock notifications
    CFNotificationCenterAddObserver(
            center,
            nullptr,
            systemEventCallback,
            CFSTR("com.apple.screenIsUnlocked"),
            nullptr,
            CFNotificationSuspensionBehaviorDeliverImmediately
    );

    std::cout << "Listening for unlock events..." << std::endl;

    // Run the main loop
    CFRunLoopRun();

    return 0;
}
