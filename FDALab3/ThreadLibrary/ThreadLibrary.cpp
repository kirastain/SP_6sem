// ThreadLibrary.cpp: определяет процедуры инициализации для библиотеки DLL.
//

#include "pch.h"
#include "framework.h"
#include "ThreadLibrary.h"
#include <afxsock.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include <thread>

struct Header
{
	int size;
	int eventNumber;
};

const BYTE SIZE_HEADER = sizeof(Header);

using namespace std;

HANDLE hRead = NULL;
HANDLE hWrite = NULL;
HANDLE hWriteConfirm = NULL;
HANDLE hReadConfirm = NULL;


//// Лаба 4
HANDLE hPipe;
extern "C"
{
	int _afxForceUSRDLL;

	_declspec(dllexport) void _stdcall Init()
	{

	}
	_declspec(dllexport) void _stdcall disconnect()
	{
		CloseHandle(hPipe);
	}
	_declspec(dllexport) void _stdcall connectToServer() {
		if (WaitNamedPipe("\\\\10.0.1.2\\pipe\\MyPipe", 5000))
		{
			hPipe = CreateFile("\\\\10.0.1.2\\pipe\\MyPipe", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
		}
	}

	_declspec(dllexport) void _stdcall launchClient() {
		STARTUPINFO si = { sizeof(si) };
		PROCESS_INFORMATION pi;
		CreateProcess(NULL, (LPSTR)"FDALab3.exe", NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);
		CloseHandle(pi.hThread);
		CloseHandle(pi.hProcess);
	}

	_declspec(dllexport) void _stdcall workWithClients() {
		hPipe = CreateNamedPipe("\\\\.\\pipe\\MyPipe",
			PIPE_ACCESS_DUPLEX, PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT, PIPE_UNLIMITED_INSTANCES,
			1024, 1024, 0, NULL);
	}

	_declspec(dllexport) inline int _stdcall getInt() {
		DWORD dwDone;
		int n;

		ReadFile(hPipe, &n, sizeof(int), &dwDone, NULL);
		return n;
	}

	_declspec(dllexport) inline void _stdcall sendInt(int n) {

		DWORD dwDone;
		WriteFile(hPipe, &n, sizeof(int), &dwDone, NULL);
		FlushFileBuffers(hPipe);
	}

	_declspec(dllexport) inline char* _stdcall getString() {
		DWORD dwDone;
		int n;

		ReadFile(hPipe, &n, sizeof(int), &dwDone, NULL);

		char* h = new char[n];
		ReadFile(hPipe, h, n, &dwDone, NULL);
		return h;
	}

	_declspec(dllexport) inline void _stdcall sendString(char* str) {
		DWORD dwDone;
		int n = strlen(str) + 1;
		WriteFile(hPipe, &n, sizeof(n), &dwDone, NULL);
		WriteFile(hPipe, str, n, &dwDone, NULL);
		FlushFileBuffers(hPipe);
	}

	_declspec(dllexport) inline int _stdcall confirm() {
		while (true) {
			int response = getInt();
			if (response != 0) {
				return response;
			}
		}
	}
	_declspec(dllexport) inline void _stdcall Connect() {
		ConnectNamedPipe(hPipe, NULL);
	}
	_declspec(dllexport) inline void _stdcall serverDisconnect() {
		DisconnectNamedPipe(hPipe);
	}
}




void Cleanup()
{
	CloseHandle(hRead);
	CloseHandle(hWrite);
	CloseHandle(hReadConfirm);
	CloseHandle(hWriteConfirm);
}

//
//TODO: если эта библиотека DLL динамически связана с библиотеками DLL MFC,
//		все функции, экспортированные из данной DLL-библиотеки, которые выполняют вызовы к
//		MFC, должны содержать макрос AFX_MANAGE_STATE в
//		самое начало функции.
//
//		Например:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// тело нормальной функции
//		}
//
//		Важно, чтобы данный макрос был представлен в каждой
//		функции до вызова MFC.  Это означает, что
//		должен стоять в качестве первого оператора в
//		функции и предшествовать даже любым объявлениям переменных объекта,
//		поскольку их конструкторы могут выполнять вызовы к MFC
//		DLL.
//
//		В Технических указаниях MFC 33 и 58 содержатся более
//		подробные сведения.
//

// CThreadLibraryApp

BEGIN_MESSAGE_MAP(CThreadLibraryApp, CWinApp)
END_MESSAGE_MAP()


// Создание CThreadLibraryApp

CThreadLibraryApp::CThreadLibraryApp()
{
	// TODO: добавьте код создания,
	// Размещает весь важный код инициализации в InitInstance
}


// Единственный объект CThreadLibraryApp

CThreadLibraryApp theApp;

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		Cleanup();
		break;
	}
	return TRUE;
}
// Инициализация CThreadLibraryApp

BOOL CThreadLibraryApp::InitInstance()
{
	CWinApp::InitInstance();
	setlocale(LC_ALL, "Russian");

	return TRUE;
}
