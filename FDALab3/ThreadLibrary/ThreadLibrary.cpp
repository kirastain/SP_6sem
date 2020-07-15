// ThreadLibrary.cpp: определяет процедуры инициализации для библиотеки DLL.
//

#include "pch.h"
#include "framework.h"
#include "ThreadLibrary.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

struct Header
{
	int size;
	int threadNumber;
	int eventNumber;
};

const BYTE SIZE_HEADER = sizeof(Header);

using namespace std;

HANDLE hRead = NULL;
HANDLE hWrite = NULL;
HANDLE hWriteConfirm = NULL;
HANDLE hReadConfirm = NULL;


extern "C"
{
	int _afxForceUSRDLL;

	__declspec(dllexport) 
		bool __stdcall programConfirm()
	{
		HANDLE hh = GetStdHandle(STD_ERROR_HANDLE);
		DWORD dwWrite;
		WriteFile(hh, "1", strlen("1"), &dwWrite, nullptr);
		return true;
	}

	__declspec(dllexport)
		bool __stdcall programWaitResponse()
	{
		const int MAXLEN = 1024;
		while (true) {
			DWORD dwRead;
			char buff[MAXLEN + 1];
			if (ReadFile(hReadConfirm, buff, MAXLEN, &dwRead, nullptr)) {
				break;
			}
		}
		return true;
	}

	_declspec(dllexport)
		void _stdcall Send(const char* pStr, const int eventNumber, const int threadNumber = -1)
	{
		DWORD dwWrite;
		Header header;
		header.size = string(pStr).length() + 1;
		header.eventNumber = eventNumber;
		header.threadNumber = threadNumber;
		WriteFile(hWrite, &header, SIZE_HEADER, &dwWrite, nullptr);
		WriteFile(hWrite, pStr, strlen(pStr), &dwWrite, nullptr);
	}

	_declspec(dllexport)
		void  _stdcall Init()
	{
		SECURITY_ATTRIBUTES sa = { sizeof(sa), NULL, TRUE };
		CreatePipe(&hRead, &hWrite, &sa, 0);
		CreatePipe(&hReadConfirm, &hWriteConfirm, &sa, 0);
		SetHandleInformation(hWrite, HANDLE_FLAG_INHERIT, 0);

		STARTUPINFO si = { 0 };
		si.cb = sizeof(si);
		si.dwFlags = STARTF_USESTDHANDLES;
		si.hStdInput = hRead;
		si.hStdError = hWriteConfirm;

		PROCESS_INFORMATION pi;

		CreateProcess(NULL, (LPSTR)"ConsoleApplication1.exe", &sa, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);
	}

	_declspec(dllexport) Header _stdcall getHeader()
	{
		Header header;
		HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
		const int MAXLEN = SIZE_HEADER;
		char buff[MAXLEN];
		while (true) {
			DWORD dwRead;
			if (ReadFile(hIn, buff, MAXLEN, &dwRead, nullptr)) {
				break;
			}
		}
		memcpy(&header, buff, SIZE_HEADER);
		return header;
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
