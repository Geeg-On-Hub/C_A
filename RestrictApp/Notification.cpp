#include "Notification.h"
#include <windows.h>

void NotifyUser() {
    MessageBox(nullptr, TEXT("Operation restricted. You cannot copy, paste, or move files in or out of the specified folder."), TEXT("Restriction Alert"), MB_OK);
}
