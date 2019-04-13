// CppCLR_WinformsProjekt.cpp: Hauptprojektdatei.

#include "stdafx.h"
#include "Form1.h"
#include "Header.h"

using namespace System;
using namespace System::Windows::Forms;

DataExchange dataobject;

ref class ManagedGlobals {
public:
	static CppCLR_WinformsProjekt::Form1^ mform;
};

DataExchange* GetExchangeInstance() {
	return &dataobject;
}


DataExchange::DataExchange() {
}

void UpdateForm() {
	ManagedGlobals::mform->Update();
	ManagedGlobals::mform->Refresh();
	
}

void DataExchange::update() {
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
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
//	dataobject = new DataExchange();
	CppCLR_WinformsProjekt::Form1 form(&dataobject);
	ManagedGlobals::mform = %form;
	Application::Run(%form); // "CppCLR_WinformsProjekt" noch anpassen
	return 0;
}