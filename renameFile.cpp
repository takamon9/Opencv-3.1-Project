#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int a = 1; 

int main() {

	while (a < 4) { //Change file with number from file.1 to file .4

		stringstream ssname;
		stringstream ssrenamed;

		ssname << "C:/Image/test" << a << ".jpg";

		string name = ssname.str();
		const char *cname = name.c_str();
		cout << cname << endl;

		ssrenamed << "C:/Image/test" << a << "renamed.jpg";

		string name2 = ssrenamed.str();
		const char *namerename = name2.c_str();
		cout << " to " << namerename << endl;

		rename(cname, namerename);

		a++;

	}

		system("pause");
	
	return 0;
}
