#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include <string>

#include <windows.h>
#include <stdlib.h>
#include <tchar.h>
#include <Tlhelp32.h>
#include <time.h>

#include "include/inipp.h"

#ifdef _WIN32
   #include <io.h> 
   #define access    _access_s
#else
   #include <unistd.h>
#endif

using namespace std;
using namespace inipp;

bool is_process_running(const TCHAR* const exec_name) {
    PROCESSENTRY32 entry;
    entry.dwSize = sizeof(PROCESSENTRY32);

    const auto snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

    if (!Process32First(snapshot, &entry)) {
        CloseHandle(snapshot);
        return false;
    }

    do {
        if (!_tcsicmp(entry.szExeFile, exec_name)) {
            CloseHandle(snapshot);
            return true;
        }
    } while (Process32Next(snapshot, &entry));

    CloseHandle(snapshot);
    return false;
}

bool file_exists( const std::string &Filename ) {
    return access( Filename.c_str(), 0 ) == 0;
}

int main(int argc, char* argv[]) {
    string exec_with_path = argv[0];
    string exec_name = exec_with_path.substr(exec_with_path.find_last_of("/\\") + 1);
    cout << "running\n";

    if (!file_exists("config.ini")) {
        cerr << "Error: \"config.ini\" Doesn't exist\n";
        system("pause");
        return 1;
    }

    Ini<char> ini;
    ifstream is("config.ini");
    ini.parse(is);

    ini.strip_trailing_comments();

    string run_on_startup, background_change, bg_file_config;
    get_value(ini.sections["CONFIG"], "run_on_startup", run_on_startup);
    get_value(ini.sections["CONFIG"], "background_change", background_change);
    get_value(ini.sections["CONFIG"], "background_file", bg_file_config);
    
    if (run_on_startup.size() == 0) {
        cerr << "Run On Startup Boolean Isn't Set In \"config.ini\"!\n";
        return 1;
    }

    if (background_change.size() == 0) {
        cerr << "Background Change Boolean Isn't Set In \"config.ini\"!\n";
        return 1;
    }

    if (background_change == "true" && bg_file_config.size() == 0) { 
        cerr << "Background Image Path Isn't Set In \"config.ini\"!\n";
        return 1;
    }

    stringstream ss;
    ss << getenv("appdata") << "\\Microsoft\\Windows\\Start Menu\\Programs\\Startup\\" << exec_name;

    stringstream _ss;
    _ss << getenv("appdata") << "\\Microsoft\\Windows\\Start Menu\\Programs\\Startup\\";

    //cout << _ss.str() << "\n";

    if (run_on_startup == "true" && !file_exists(ss.str())) {
        stringstream command; 
        command << "copy " << "\"" << exec_with_path << "\"" << " " << "\""  << _ss.str() << "\"";
        
        stringstream command_2;
        command_2 << "copy config.ini" << " " << "\""  << _ss.str() << "\"";

        cout << command.str() << "\n";
        cout << command_2.str() << "\n";
        system(command.str().c_str());
        system(command_2.str().c_str());
    }
    if (background_change == "true") {
        const wstring _config = wstring(bg_file_config.begin(), bg_file_config.end());
        const wchar_t *filenm = _config.c_str();
        try {
            SystemParametersInfoW(SPI_SETDESKWALLPAPER, 0,(void*)filenm,SPIF_UPDATEINIFILE);    
        }
        catch (string err) {
            cerr << err;
        }   
    }

	::ShowWindow(::GetConsoleWindow(), SW_HIDE);
	while (true) {
        if (is_process_running("slui.exe") == 1) {
            system( "taskkill /IM slui.exe /F && exit");
            cout << "woo";
            if (background_change == "true") {
                const wstring _config = wstring(bg_file_config.begin(), bg_file_config.end());
                const wchar_t *filenm = _config.c_str();
                try {
                    SystemParametersInfoW(SPI_SETDESKWALLPAPER, 0,(void*)filenm,SPIF_UPDATEINIFILE);    
                }
                catch (string err) {
                    cerr << err;
                }   
            }
        }
        Sleep(600);
	}
	
}