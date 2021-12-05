#include <windows.h>
#include <string>
#include <iostream>

using namespace std;

void make() {system("1_make.bat");}

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
    			system("a.exe && exit");
    			return 0;
    		}
    	}
    }
   	return 0;
}
