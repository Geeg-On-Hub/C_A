#ifndef FILE_SYSTEM_MONITOR_H
#define FILE_SYSTEM_MONITOR_H

#include <windows.h>
#include <string>

class FileSystemMonitor {
public:
    static FileSystemMonitor* instance; // Declare instance
    FileSystemMonitor(const std::string& root);
    void StartMonitoring();
    static LRESULT CALLBACK ShellProc(int nCode, WPARAM wParam, LPARAM lParam);
    static LRESULT CALLBACK CallWndProc(int nCode, WPARAM wParam, LPARAM lParam);
private:
    std::string rootFolder;
    static HHOOK hShellHook;
    static HHOOK hCallWndProcHook;
};

#endif // FILE_SYSTEM_MONITOR_H
