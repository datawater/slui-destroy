#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <Tlhelp32.h>
#include <tchar.h>
using namespace std;

bool IsProcessRunning(const TCHAR* const executableName) {
    PROCESSENTRY32 entry;
    entry.dwSize = sizeof(PROCESSENTRY32);

    const auto snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

    if (!Process32First(snapshot, &entry)) {
        CloseHandle(snapshot);
        return false;
    }

    do {
        if (!_tcsicmp(entry.szExeFile, executableName)) {
            CloseHandle(snapshot);
            return true;
        }
    } while (Process32Next(snapshot, &entry));

    CloseHandle(snapshot);
    return false;
}

int main() {
	::ShowWindow(::GetConsoleWindow(), SW_HIDE);
	while (true) {	
		if (IsProcessRunning("slui.exe") == 1) {
			int retval = ::_tsystem( _T("taskkill /IM slui.exe /F && exit") );
		}
		//cout << 'e' << '\\n';
		Sleep(50);
	}

	return 0;
}