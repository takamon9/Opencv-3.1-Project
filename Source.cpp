#include <iostream>
#include <fstream>
#include <Windows.h>
#include <time.h>
#include <string>
#include <tchar.h>

using namespace std;


HANDLE hSearch, hFile;
WIN32_FIND_DATA fd;
DWORD writeSize;
TCHAR filename[MAX_PATH + 10];
TCHAR str1[10] = _T("neg/");

int main(){

// Create new file
hFile = CreateFile(
_T("C:/cascade//neg//ng.txt"), GENERIC_WRITE, 0, NULL,
CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL
);

if (hFile == INVALID_HANDLE_VALUE)
{
return 0;
}

// Find all files
hSearch = FindFirstFile(_T("C:/cascade//neg//*.jpg"), &fd);
if (hSearch == INVALID_HANDLE_VALUE)
{
return 0;
}

while (TRUE)
{

	// Writting down files finded.
	_tcscpy(filename, fd.cFileName);
	// Copy file names
	_tcscat(filename, _T("\r\n"));
	_tcscat(filename, str1);

	// Input end line.
	WriteFile(
		hFile, filename, (DWORD)(_tcslen(filename) * sizeof(TCHAR)),
		&writeSize, NULL
	);

	if (!FindNextFile(hSearch, &fd))
	{
		if (GetLastError() == ERROR_NO_MORE_FILES)

			break;

		else

			break;
	}
}

FindClose(hSearch);
CloseHandle(hFile);

}
