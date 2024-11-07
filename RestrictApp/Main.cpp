#include "ClipboardMonitor.h"
#include "FileSystemMonitor.h"
#include "Validation.h"
#include "Notification.h"
#include <string>
#include <iostream>

int main() {
    // Change this to your desired local folder
    const std::string rootFolder ="C:\\Users\\mtcro\\Desktop\\New folder" ;

    std::cout << "Initializing Clipboard Monitor..." << std::endl;
    ClipboardMonitor clipboardMonitor(rootFolder);
    clipboardMonitor.StartMonitoring();

    std::cout << "Initializing File System Monitor..." << std::endl;
    FileSystemMonitor fileSystemMonitor(rootFolder);
    fileSystemMonitor.StartMonitoring();

    std::cout << "Application is running. Press Ctrl+C to exit." << std::endl;

    // Application message loop
    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
