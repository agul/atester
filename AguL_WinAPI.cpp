#include "AguL_WinAPI.h"

FILE * fileLoader;

bool fileExists(string fileName) {
	fileLoader = fopen(fileName.c_str(), "r");
	if (fileLoader) {
		fclose(fileLoader);
		return true;
	}
	return false;
}

void setConsoleTextColor(COLOR color) {
	SetConsoleTextAttribute(hStdOut, (WORD)color);
}

void printColoredText(string text, COLOR color) {
	setConsoleTextColor(color);
	cout << text;
	setConsoleTextColor(DEFAULT_COLOR);
}

bool createDirectory(string directoryName) {
	return CreateDirectoryA(directoryName.c_str(), NULL) || CreateDirectoryA(directoryName.c_str(), NULL);
}

bool copyFile(string oldName, string newName) {
	bool isFail = false;
	return CopyFileA(oldName.c_str(), newName.c_str(), isFail) || CopyFileA(oldName.c_str(), newName.c_str(), isFail);
}

bool deleteDirectory(string directoryName, bool noRecycleBin = true) {
	int len = directoryName.length();
	TCHAR * pszFrom = new TCHAR[len + 2];
	for (int i = 0; i < len; ++i)
		pszFrom[i] = (TCHAR)(directoryName[i]);
	pszFrom[len] = 0;
	pszFrom[len + 1] = 0;
	SHFILEOPSTRUCT fileop;
	fileop.hwnd = NULL;
	fileop.wFunc = FO_DELETE;
	fileop.pFrom = pszFrom;
	fileop.pTo = NULL;
	fileop.fFlags = FOF_NOCONFIRMATION|FOF_SILENT;
	if(!noRecycleBin) fileop.fFlags |= FOF_ALLOWUNDO;
	fileop.fAnyOperationsAborted = FALSE;
	fileop.lpszProgressTitle = NULL;
	fileop.hNameMappings = NULL;
	int ret = SHFileOperation(&fileop);
	delete [] pszFrom;  
	return !ret;
}