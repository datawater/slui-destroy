#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <iostream>
#include <ostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <chrono>

using namespace std;

void make() {system("make.bat");}


int main(int argc, char* argv[]) {

	string arg;

	cout << argc << "\n";

  	if (argc < 1 || argc == 1) {
    		cout << "Wasn't supplied any arguments, just building\n";
      		make();
      		return 0;
  	} else {
    	for (int i = 1; i < argc; ++i) {
    		//cout << argv[i] << "\n";
    		arg = argv[i];

    		if (arg == "run" || arg == "Run" || arg == "RUN") {
    			make();
    			system("if %errorlevel% == 0 (a.exe && exit) else (echo \"compalation error\" && exit)");
    			return 0;
    		}
    	}
    }
   	return 0;
}
