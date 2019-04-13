#include "stdafx.h"
#include "GUI.h"
#include "Header.h"

using namespace System;
using namespace System::Windows::Forms;

DataExchange* GetExchangeInstance() {
	return dataobject;
}

DataExchange* dataobject;


DataExchange::DataExchange() {
}

void DataExchange::update() {
	UpdateForm();
}

void UpdateForm() {
	ManagedGlobals::mform->Refresh();
}

ref class ManagedGlobals {
public:
	static CppCLR_WinformsProjekt1::GUI^ mform;
};


[STAThreadAttribute]
void main(array<String^>^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	dataobject = new DataExchange();
	CppCLR_WinformsProjekt1::GUI form(dataobject);
	ManagedGlobals::mform = %form;

	Application::Run(%form);



}
