#include "FileSystemMonitor.h"
#include "Validation.h" // Include validation header
#include "Notification.h" // Include notification header
#include <windows.h>
#include <iostream>

HHOOK FileSystemMonitor::hShellHook = nullptr;
HHOOK FileSystemMonitor::hCallWndProcHook = nullptr;
FileSystemMonitor* FileSystemMonitor::instance = nullptr; // Define instance

FileSystemMonitor::FileSystemMonitor(const std::string& root) : rootFolder(root) {
    instance = this; // Initialize instance
    std::cout << "FileSystemMonitor created with root folder: " << root << std::endl;
}

void FileSystemMonitor::StartMonitoring() {
    hShellHook = SetWindowsHookEx(WH_SHELL, ShellProc, nullptr, GetCurrentThreadId());
    if (!hShellHook) {
        std::cerr << "Failed to set shell hook" << std::endl;
        return;
    }
    hCallWndProcHook = SetWindowsHookEx(WH_CALLWNDPROC, CallWndProc, nullptr, GetCurrentThreadId());
    if (!hCallWndProcHook) {
        std::cerr << "Failed to set call window procedure hook" << std::endl;
        return;
    }
    std::cout << "File system monitor started." << std::endl;
}

LRESULT CALLBACK FileSystemMonitor::ShellProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HSHELL_WINDOWCREATED || nCode == HSHELL_WINDOWDESTROYED) {
        std::cout << "Shell window created or destroyed." << std::endl;
    }
    return CallNextHookEx(hShellHook, nCode, wParam, lParam);
}

LRESULT CALLBACK FileSystemMonitor::CallWndProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION) {
        CWPSTRUCT* pCwp = reinterpret_cast<CWPSTRUCT*>(lParam);
        if (pCwp->message == WM_DROPFILES) {
            HDROP hDrop = (HDROP)pCwp->wParam;
            UINT fileCount = DragQueryFile(hDrop, 0xFFFFFFFF, NULL, 0);
            TCHAR fileName[MAX_PATH];

            for (UINT i = 0; i < fileCount; ++i) {
                DragQueryFile(hDrop, i, fileName, MAX_PATH);

                // Convert TCHAR to std::string
#ifdef UNICODE
                std::wstring wideFileName(fileName);
                std::string fileNameStr(wideFileName.begin(), wideFileName.end());
#else
                std::string fileNameStr(fileName);
#endif

                // Check both incoming and outgoing operations
                if (IsWithinRootFolder(fileNameStr, FileSystemMonitor::instance->rootFolder) ||
                    IsOutsideRootFolder(fileNameStr, FileSystemMonitor::instance->rootFolder)) {
                    NotifyUser();
                    std::cout << "Drag and drop operation restricted." << std::endl;
                    return 1; // Prevent operation
                }
            }
        }
    }
    return CallNextHookEx(hCallWndProcHook, nCode, wParam, lParam);
}
