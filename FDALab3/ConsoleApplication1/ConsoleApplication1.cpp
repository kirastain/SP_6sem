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
#include <afxsock.h>
#pragma comment(lib, "ThreadLibrary.lib")

using namespace std;

struct EventObjects {
	HANDLE evClose;
	int id;
};

extern "C"
{
	__declspec(dllimport) void __stdcall launchClient();
	__declspec(dllimport) void __stdcall workWithClients();
	__declspec(dllimport) inline int __stdcall getInt( );
	__declspec(dllimport) inline char* __stdcall getString();
	__declspec(dllimport) inline void __stdcall sendInt(int n);
	__declspec(dllimport) inline void __stdcall Connect();
	__declspec(dllimport) inline void __stdcall serverDisconnect();
}

UINT MyThread(LPVOID p)
{
	EventObjects* evStruct;
	evStruct = (struct EventObjects*)p;
	WaitForSingleObject(evStruct->evClose, INFINITE);
	CloseHandle(evStruct->evClose);

	return 0;
}


void start1() {
	vector <HANDLE> vEventsClose;

	while (true) {
		Connect();
		int evNum = getInt();
		switch (evNum) {
		case 0: {

			HANDLE handleClose = CreateEvent(NULL, false, false, NULL);
			vEventsClose.push_back(handleClose);

			EventObjects threadVar = { handleClose, vEventsClose.size() };

			AfxBeginThread(MyThread, &threadVar);

			cout << "Thread " << " created" << endl;
			break;
		}
		case 1: {
			if (vEventsClose.size() > 0) {
				SetEvent(vEventsClose.back());
				cout << "thread " << vEventsClose.size() << " done" << endl;
				vEventsClose.pop_back();
			}
			break;
		}
		case 3: {
			//sendInt(hPipe, vEventsClose.size());
			string message;
			message = getString();
			cout << message << endl;
		}
		}
		sendInt(vEventsClose.size());
		serverDisconnect();
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
			launchClient();
			workWithClients();
			start1();
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