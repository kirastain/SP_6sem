// ConsoleApplication1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "framework.h"
#include "Resourse.h"
#include "targetver.h"
#include <string>
#include <vector>
#include <fstream>
#include "ThreadLibrary.h"
#include <thread>
#include <windows.h>
#include <valarray>
#pragma comment(lib, "ThreadLibrary.lib")

using namespace std;

struct EventObjects {
	HANDLE evClose;
	int id;
};

struct Header
{
	int size;
	int threadNumber;
	int eventNumber;
};

extern "C"
{
	__declspec(dllimport) bool	__stdcall programConfirm();
	__declspec(dllimport) Header __stdcall getHeader();
}

UINT MyThread(LPVOID p)
{
	EventObjects* evStruct;
	evStruct = (struct EventObjects*)p;
	WaitForSingleObject(evStruct->evClose, INFINITE);
	CloseHandle(evStruct->evClose);

	return 0;
}


void start() {
	HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
	vector <HANDLE> vEventsClose;
	while (true) {
		Header header = getHeader();
		int evNum = header.eventNumber;
		switch (evNum) {
		case 0: {

			HANDLE handleClose = CreateEvent(NULL, false, false, NULL);
			vEventsClose.push_back(handleClose);

			EventObjects threadVar = { handleClose, vEventsClose.size()};

			AfxBeginThread(MyThread, &threadVar);

			cout << "Thread " << vEventsClose.size() << " created" << endl;
			break;
		}
		case 1: {
			if (vEventsClose.size() != 0) {
				SetEvent(vEventsClose.back());
				cout << "thread " << vEventsClose.size() << " done" << endl;
				vEventsClose.pop_back();
				break;
			}
		}
		case 2: {
			while (!programConfirm()) {}
			for (auto ev : vEventsClose)
				SetEvent(ev);
			return;
		}
		case 3: {
			DWORD dwRead;
			char* buff = new char[header.size + 1];
			if (!ReadFile(hIn, buff, header.size + 1, &dwRead, nullptr) || !dwRead) {
				break;
			}
			buff += 0;
			cout << "child: ";
			cout << buff << endl;
		}
		}
		programConfirm();
	}
}

int main()
{
	int nRetCode = 0;

	HMODULE hModule = ::GetModuleHandle(nullptr);

	if (hModule != nullptr)
	{

		// initialize MFC and print and error on failure
		if (!AfxWinInit(hModule, nullptr, ::GetCommandLine(), 0))
		{
			// TODO: code your application's behavior here.
			wprintf(L"Fatal Error: MFC initialization failed\n");
			nRetCode = 1;
		}
		else
		{
			start();
		}
	}
	else
	{
		// TODO: change error code to suit your needs
		wprintf(L"Fatal Error: GetModuleHandle failed\n");
		nRetCode = 1;
	}
	return nRetCode;
}