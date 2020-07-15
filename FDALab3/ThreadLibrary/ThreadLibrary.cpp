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


CSocket* Socket;
CSocket Server;
extern "C"
{
	int _afxForceUSRDLL;

	_declspec(dllexport) void _stdcall Init()
	{
		AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0);
		AfxSocketInit();
	}
	_declspec(dllexport) void _stdcall Connect()
	{
		Socket = new CSocket;
		Server.Listen();
		Server.Accept(*Socket);
	}
	_declspec(dllexport) void _stdcall launchClient() {
		STARTUPINFO si = { sizeof(si) };
		PROCESS_INFORMATION pi;
		CreateProcess(NULL, (LPSTR)"PezhemskyLab3.exe", NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);
		CloseHandle(pi.hThread);
		CloseHandle(pi.hProcess);
	}

	_declspec(dllexport) void _stdcall workWithClients() {
		AfxSocketInit();
		Server.Create(12345);
	}

	_declspec(dllexport) inline int _stdcall getInt() {
		int n;
		Socket->Receive(&n, sizeof(int));
		return n; 
	}

	_declspec(dllexport) inline void _stdcall sendInt(int n) {
		Socket->Send(&n, sizeof(int));
	}

	_declspec(dllexport) inline char* _stdcall getString() {
		int n;
		Socket->Receive(&n, sizeof(int));

		char* h = new char[n];
		Socket->Receive(h, n);
		return h;
	}

	_declspec(dllexport) inline void _stdcall sendString(char* str) {
		int nLength = strlen(str) + 1;
		Socket->Send(&nLength, sizeof(int));
		Socket->Send(str, nLength);
	}

	_declspec(dllexport) int _stdcall confirm() {
		while (true) {
			int response = getInt();
			if (response != 0) {
				return response;
			}
		}
	}

	_declspec(dllexport) inline void _stdcall connectToServer() {
		Socket = new CSocket;
		Socket->Create();

		Socket->Connect("192.168.1.23", 12345);
	}
	_declspec(dllexport) inline void _stdcall disconnect() {
		Socket->Close();
		delete Socket;
	}
	_declspec(dllexport) inline void _stdcall serverDisconnect() {
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
