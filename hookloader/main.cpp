#include <Windows.h>
#include <iostream>
#include "skStr.h"
#include <vector>
#include <fstream>
#include <string>

using namespace std;

std::string tm_to_readable_time(tm ctx);
static std::time_t string_to_timet(std::string timestamp);
static std::tm timet_to_tm(time_t timestamp);
int INJECT()
{
	std::string url = "Your internal/cheat dll link";
	std::string path = "C:\\Windows\\System\\internal.dll";//change internal.dll to the name of your dll
	std::string command = "powershell -Command \"(New-Object System.Net.WebClient).DownloadFile('" + url + "', '" + path + "')\"";
	system(command.c_str());

	const wchar_t* dllName = L"C:\\Windows\\System\\internal.dll";//change internal.dll to the name of your dll
	if (GetFileAttributes(dllName) == INVALID_FILE_ATTRIBUTES) {
		cout << "[ ERROR: dll is not signed or link is outdated ]" << endl;
		system("pause");
		return 1;
	}

	HWND hwnd = FindWindowW(L"UnrealWindow", 0);
	if (hwnd == 0) {
		cout << "[ ERROR: Valorant is not running ]" << endl;
		system("pause");
		return 1;
	}

	DWORD pid = 0;
	DWORD tid = GetWindowThreadProcessId(hwnd, &pid);
	if (tid == 0) {
		cout << "[ ERROR: 3 ]" << endl;
		system("pause");
		return 1;
	}

	HMODULE dll = LoadLibraryEx(dllName, 0, DONT_RESOLVE_DLL_REFERENCES);
	if (dll == 0) {
		cout << "[ ERROR: 4 ]" << endl;
		system("pause");
		return 1;
	}

	HOOKPROC addr = (HOOKPROC)GetProcAddress(dll, "NextHook");
	if (addr == 0) {
		cout << "[ ERROR: 5 ]" << endl;
		system("pause");
		return 1;
	}

	HHOOK handle = SetWindowsHookEx(WH_GETMESSAGE, addr, dll, tid);
	if (handle == 0) {
		cout << "[ ERROR: 6 ]" << endl;
		system("pause");
		return 1;
	}

	PostThreadMessage(tid, 0x0000, 0, 0);
	cout << "[ SUCCESS ] Cheat successfully loaded." << endl;
}

int wmain(int argc, wchar_t* argv[], wchar_t* envp[]) {
	SetConsoleTitleA(skCrypt("Loader"));
	INJECT();
	
	system("pause > nul");
}

std::string tm_to_readable_time(tm ctx) {
	char buffer[80];

	strftime(buffer, sizeof(buffer), "%a %m/%d/%y %H:%M:%S %Z", &ctx);

	return std::string(buffer);
}

static std::time_t string_to_timet(std::string timestamp) {
	auto cv = strtol(timestamp.c_str(), NULL, 10); 

	return (time_t)cv;
}

static std::tm timet_to_tm(time_t timestamp) {
	std::tm context;

	localtime_s(&context, &timestamp);

	return context;
}