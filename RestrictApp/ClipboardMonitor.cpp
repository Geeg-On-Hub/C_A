#include "ClipboardMonitor.h"
#include "Validation.h"
#include "Notification.h"
#include <windows.h>
#include <iostream>
#include <string>

HWND ClipboardMonitor::nextClipboardViewer = nullptr;
ClipboardMonitor* ClipboardMonitor::instance = nullptr;

ClipboardMonitor::ClipboardMonitor(const std::string& root) : rootFolder(root) {
    instance = this;
    std::cout << "ClipboardMonitor created with root folder: " << root << std::endl;
}

void ClipboardMonitor::StartMonitoring() {
    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = ClipboardMonitor::WindowProc;
    wc.hInstance = GetModuleHandle(nullptr);
    wc.lpszClassName = TEXT("ClipboardMonitor");

    if (!RegisterClass(&wc)) {
        std::cerr << "Failed to register window class" << std::endl;
        return;
    }

    hwnd = CreateWindowEx(
        0, TEXT("ClipboardMonitor"), TEXT("Clipboard Monitor"),
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
        CW_USEDEFAULT, CW_USEDEFAULT, nullptr, nullptr,
        GetModuleHandle(nullptr), this);

    if (!hwnd) {
        std::cerr << "Failed to create window" << std::endl;
        return;
    }

    nextClipboardViewer = SetClipboardViewer(hwnd);
    std::cout << "Clipboard monitor started." << std::endl;

    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

LRESULT CALLBACK ClipboardMonitor::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_DRAWCLIPBOARD:
        std::cout << "Clipboard content changed." << std::endl;
        if (IsClipboardFormatAvailable(CF_HDROP)) {
            HDROP hDrop;
            UINT fileCount;
            TCHAR fileName[MAX_PATH];

            OpenClipboard(hwnd);
            hDrop = (HDROP)GetClipboardData(CF_HDROP);
            fileCount = DragQueryFile(hDrop, 0xFFFFFFFF, NULL, 0);

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
                if (IsWithinRootFolder(fileNameStr, ClipboardMonitor::instance->rootFolder) ||
                    IsOutsideRootFolder(fileNameStr, ClipboardMonitor::instance->rootFolder)) {
                    NotifyUser();
                    EmptyClipboard();
                    std::cout << "Clipboard cleared due to restriction." << std::endl;
                    break;
                }
            }
            CloseClipboard();
        }
        if (nextClipboardViewer) {
            SendMessage(nextClipboardViewer, uMsg, wParam, lParam);
        }
        return 0;
    case WM_CHANGECBCHAIN:
        if ((HWND)wParam == nextClipboardViewer) {
            nextClipboardViewer = (HWND)lParam;
        }
        else if (nextClipboardViewer != nullptr) {
            SendMessage(nextClipboardViewer, uMsg, wParam, lParam);
        }
        return 0;
    case WM_DESTROY:
        ChangeClipboardChain(hwnd, nextClipboardViewer);
        PostQuitMessage(0);
        return 0;
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}
