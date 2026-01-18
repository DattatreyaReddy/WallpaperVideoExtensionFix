# WallpaperAerialsExtensionFix

**PROJECT STATUS: ABANDONED**

WallpaperAerialsExtensionFix is a lightweight application designed to automatically terminate the `WallpaperAerialsExtension` service each time you log in to macOS. If you've experienced issues with custom Aerial wallpapers, this tool might help. The app runs quietly in the background, without generating logs or indicators, ensuring a seamless experience.

Features
 - Runs silently, with no persistent UI or notifications.
 - Non-intrusive: no logs or visible indicators. You can confirm it’s active via Activity Monitor.

Issues with this fix
 - There will be a gray (or black) wallpaper when you login for around 2 seconds (cannot be fixed unless you use a different method)


# Installation

1. [Download the latest release](https://github.com/DattatreyaReddy/WallpaperVideoExtensionFix/releases) as a compiled binary or compile it yourself (execute `./build.sh`)

2. Extract the binary from the downloaded zip file.

3. Allow macOS to run the binary by executing:
```bash
chmod +x /path/to/WallpaperAerialsExtensionFix.app/Contents/MacOS/WallpaperAerialsExtensionFix
```

4. Run the app once and grant the necessary permissions.

5. Add the binary to your login items to ensure it launches automatically at login.

6. Log out, then log back in to start the utility.

7. (Optional) Confirm the app is running by opening Activity Monitor and searching for `WallpaperAerialsExtensionFix`.

# Why Was This Project Archived?

WallpaperAerialsExtensionFix was originally a part of a larger project named AerialUtil, which was later abandoned. Due to many people having issues with custom Aerials, this utility was published as a standalone tool to help those encountering issues with custom Aerials on macOS.

# Can I Fork This?

Yes, just credit Original Author (Proton0) & Me (DattatreyaReddy)
