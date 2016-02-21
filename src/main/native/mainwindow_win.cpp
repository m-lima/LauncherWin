#include "../mainwindow.h"
#include "windows.h"

void MainWindow::forceFocus()
{
    activateWindow();
    HWND winID = (HWND) winId();

    if (IsIconic(winID)) {
        SendMessage(winID, WM_SYSCOMMAND, SC_RESTORE, 0);
    }

    DWORD foregroundThreadPID = GetWindowThreadProcessId(GetForegroundWindow(), NULL);
    DWORD threadPID = GetWindowThreadProcessId(winID, NULL);

    if (foregroundThreadPID != threadPID) {
        AttachThreadInput(foregroundThreadPID, threadPID, true);
        SetForegroundWindow(winID);
        AttachThreadInput(foregroundThreadPID, threadPID, false);
    } else {
        SetForegroundWindow(winID);
    }
}
