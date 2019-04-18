// CppCLR_WinformsProjekt.cpp: Hauptprojektdatei.

#include "stdafx.h"
#include "Form1.h"
#include "DataStorage.h"

using namespace System;
using namespace System::Windows::Forms;

ref class ManagedGlobals {
public:
	static CppCLR_WinformsProjekt::Form1^ mform;
};

void UpdateForm() {
	ManagedGlobals::mform->Update();
	ManagedGlobals::mform->Refresh();	
}

void FormUpdateCallback(int t) {
	UpdateForm();
}





//int main(array<System::String ^> ^args)
//{
//    Console::WriteLine(L"Hello World");
//    return 0;
//}

[STAThread]
int GUI_main() 
{
	DataExchange::Instance()->SetMode(DataExchange::GUI);
	DataExchange::Instance()->Connect();
	DataExchange::Instance()->RegisterCallback(FormUpdateCallback);
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	CppCLR_WinformsProjekt::Form1 form;
	ManagedGlobals::mform = %form;
	Application::Run(%form); // "CppCLR_WinformsProjekt" noch anpassen
	DataExchange::Instance()->Disconnect();
	return 0;
}