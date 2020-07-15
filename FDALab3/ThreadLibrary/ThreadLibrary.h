// ThreadLibrary.h: основной файл заголовка для библиотеки DLL ThreadLibrary
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CThreadLibraryApp
// Реализацию этого класса см. в файле ThreadLibrary.cpp
//

class CThreadLibraryApp : public CWinApp
{
public:
	CThreadLibraryApp();

// Переопределение
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
