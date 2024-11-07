#ifndef CLIPBOARD_MONITOR_H
#define CLIPBOARD_MONITOR_H

#include <windows.h>
#include <string>

class ClipboardMonitor {
public:
    static ClipboardMonitor* instance;
    ClipboardMonitor(const std::string& root);
    void StartMonitoring();
    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
private:
    std::string rootFolder;
    HWND hwnd;
    static HWND nextClipboardViewer;
};

#endif // CLIPBOARD_MONITOR_H
