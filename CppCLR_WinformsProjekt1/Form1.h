#pragma once
#include "DataStorage.h"

namespace CppCLR_WinformsProjekt {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	

	/// <summary>
	/// Zusammenfassung für Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1()
		{
			InitializeComponent();
			//
			//TODO: Konstruktorcode hier hinzufügen.
			//
		}

		void Update() {
			DataExchange* data = DataExchange::Instance();
			errX->Text = gcnew String(Convert::ToString(data->acq_data[DataExchange::DELTA_X]));
			errY->Text = gcnew String(Convert::ToString(data->acq_data[DataExchange::DELTA_Y]));
			cam->Text = gcnew String(Convert::ToString(data->acq_data[DataExchange::EST_CAM_STATUS]));
			motorA->Text = gcnew String(Convert::ToString(data->acq_data[DataExchange::MOTOR_ALPHA]));
			motorB->Text = gcnew String(Convert::ToString(data->acq_data[DataExchange::MOTOR_BETA]));
			pwr->Text = gcnew String(Convert::ToString(data->acq_data[DataExchange::POWER_STATUS]));
			SNR->Text = gcnew String(Convert::ToString(data->acq_data[DataExchange::SNR]));
			tgtX->Text = gcnew String(Convert::ToString(data->acq_data[DataExchange::TARGET_X]));
			tgtY->Text = gcnew String(Convert::ToString(data->acq_data[DataExchange::TARGET_Y]));
			vel->Text = gcnew String(Convert::ToString(data->acq_data[DataExchange::VELOCITY]));
		}

	protected:
		/// <summary>
		/// Verwendete Ressourcen bereinigen.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  fileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  eXITToolStripMenuItem;
	private: System::Windows::Forms::GroupBox^  Diagnostics;
	private: System::Windows::Forms::Label^  label11;
	private: System::Windows::Forms::Label^  label10;
	private: System::Windows::Forms::Label^  label9;
	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::TextBox^  errY;

	private: System::Windows::Forms::TextBox^  tgtY;

	private: System::Windows::Forms::TextBox^  motorB;
	private: System::Windows::Forms::TextBox^  cam;


	private: System::Windows::Forms::TextBox^  errX;

	private: System::Windows::Forms::TextBox^  SNR;

	private: System::Windows::Forms::TextBox^  tgtX;

	private: System::Windows::Forms::TextBox^  motorA;

	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label12;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::TextBox^  textBox9;
	private: System::Windows::Forms::Label^  label15;
	private: System::Windows::Forms::Label^  label14;
	private: System::Windows::Forms::Label^  label13;
	private: System::Windows::Forms::TextBox^  textBox10;
	private: System::Windows::Forms::ComboBox^  comboBox1;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Label^  label16;
	private: System::Windows::Forms::TextBox^  vel;
	private: System::Windows::Forms::Label^  label18;
	private: System::Windows::Forms::TextBox^  pwr;
	private: System::Windows::Forms::Label^  label17;
	private: System::Windows::Forms::Button^ button3;

	protected:

	private:
		/// <summary>
		/// Erforderliche Designervariable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Erforderliche Methode für die Designerunterstützung.
		/// Der Inhalt der Methode darf nicht mit dem Code-Editor geändert werden.
		/// </summary>
		void InitializeComponent(void)
		{
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->eXITToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->Diagnostics = (gcnew System::Windows::Forms::GroupBox());
			this->vel = (gcnew System::Windows::Forms::TextBox());
			this->label18 = (gcnew System::Windows::Forms::Label());
			this->pwr = (gcnew System::Windows::Forms::TextBox());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->label17 = (gcnew System::Windows::Forms::Label());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->errY = (gcnew System::Windows::Forms::TextBox());
			this->tgtY = (gcnew System::Windows::Forms::TextBox());
			this->motorB = (gcnew System::Windows::Forms::TextBox());
			this->cam = (gcnew System::Windows::Forms::TextBox());
			this->errX = (gcnew System::Windows::Forms::TextBox());
			this->SNR = (gcnew System::Windows::Forms::TextBox());
			this->tgtX = (gcnew System::Windows::Forms::TextBox());
			this->motorA = (gcnew System::Windows::Forms::TextBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->textBox10 = (gcnew System::Windows::Forms::TextBox());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->textBox9 = (gcnew System::Windows::Forms::TextBox());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->label16 = (gcnew System::Windows::Forms::Label());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->menuStrip1->SuspendLayout();
			this->Diagnostics->SuspendLayout();
			this->groupBox1->SuspendLayout();
			this->SuspendLayout();
			// 
			// menuStrip1
			// 
			this->menuStrip1->ImageScalingSize = System::Drawing::Size(24, 24);
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->fileToolStripMenuItem });
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Padding = System::Windows::Forms::Padding(9, 3, 0, 3);
			this->menuStrip1->Size = System::Drawing::Size(777, 35);
			this->menuStrip1->TabIndex = 0;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// fileToolStripMenuItem
			// 
			this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->eXITToolStripMenuItem });
			this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			this->fileToolStripMenuItem->Size = System::Drawing::Size(50, 29);
			this->fileToolStripMenuItem->Text = L"&File";
			// 
			// eXITToolStripMenuItem
			// 
			this->eXITToolStripMenuItem->Name = L"eXITToolStripMenuItem";
			this->eXITToolStripMenuItem->Size = System::Drawing::Size(130, 30);
			this->eXITToolStripMenuItem->Text = L"E&XIT";
			this->eXITToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::eXITToolStripMenuItem_Click);
			// 
			// Diagnostics
			// 
			this->Diagnostics->Controls->Add(this->vel);
			this->Diagnostics->Controls->Add(this->label18);
			this->Diagnostics->Controls->Add(this->pwr);
			this->Diagnostics->Controls->Add(this->label12);
			this->Diagnostics->Controls->Add(this->label17);
			this->Diagnostics->Controls->Add(this->label11);
			this->Diagnostics->Controls->Add(this->label10);
			this->Diagnostics->Controls->Add(this->label9);
			this->Diagnostics->Controls->Add(this->label8);
			this->Diagnostics->Controls->Add(this->label7);
			this->Diagnostics->Controls->Add(this->label6);
			this->Diagnostics->Controls->Add(this->errY);
			this->Diagnostics->Controls->Add(this->tgtY);
			this->Diagnostics->Controls->Add(this->motorB);
			this->Diagnostics->Controls->Add(this->cam);
			this->Diagnostics->Controls->Add(this->errX);
			this->Diagnostics->Controls->Add(this->SNR);
			this->Diagnostics->Controls->Add(this->tgtX);
			this->Diagnostics->Controls->Add(this->motorA);
			this->Diagnostics->Controls->Add(this->label5);
			this->Diagnostics->Controls->Add(this->label4);
			this->Diagnostics->Controls->Add(this->label3);
			this->Diagnostics->Controls->Add(this->label2);
			this->Diagnostics->Controls->Add(this->label1);
			this->Diagnostics->Location = System::Drawing::Point(18, 57);
			this->Diagnostics->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->Diagnostics->Name = L"Diagnostics";
			this->Diagnostics->Padding = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->Diagnostics->Size = System::Drawing::Size(561, 358);
			this->Diagnostics->TabIndex = 1;
			this->Diagnostics->TabStop = false;
			this->Diagnostics->Text = L"Diagnostics";
			// 
			// vel
			// 
			this->vel->Location = System::Drawing::Point(170, 320);
			this->vel->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->vel->Name = L"vel";
			this->vel->ReadOnly = true;
			this->vel->Size = System::Drawing::Size(148, 26);
			this->vel->TabIndex = 21;
			// 
			// label18
			// 
			this->label18->AutoSize = true;
			this->label18->Location = System::Drawing::Point(9, 320);
			this->label18->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label18->Name = L"label18";
			this->label18->Size = System::Drawing::Size(64, 20);
			this->label18->TabIndex = 20;
			this->label18->Text = L"Velocity";
			// 
			// pwr
			// 
			this->pwr->Location = System::Drawing::Point(170, 277);
			this->pwr->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->pwr->Name = L"pwr";
			this->pwr->ReadOnly = true;
			this->pwr->Size = System::Drawing::Size(148, 26);
			this->pwr->TabIndex = 11;
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Location = System::Drawing::Point(328, 192);
			this->label12->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(31, 20);
			this->label12->TabIndex = 19;
			this->label12->Text = L"ΔY";
			// 
			// label17
			// 
			this->label17->AutoSize = true;
			this->label17->Location = System::Drawing::Point(9, 277);
			this->label17->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label17->Name = L"label17";
			this->label17->Size = System::Drawing::Size(104, 20);
			this->label17->TabIndex = 10;
			this->label17->Text = L"Power Status";
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Location = System::Drawing::Point(129, 192);
			this->label11->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(31, 20);
			this->label11->TabIndex = 18;
			this->label11->Text = L"ΔX";
			this->label11->Click += gcnew System::EventHandler(this, &Form1::label11_Click);
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Location = System::Drawing::Point(4, 25);
			this->label10->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(60, 20);
			this->label10->TabIndex = 17;
			this->label10->Text = L"label10";
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(336, 106);
			this->label9->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(20, 20);
			this->label9->TabIndex = 16;
			this->label9->Text = L"Y";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(140, 106);
			this->label8->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(20, 20);
			this->label8->TabIndex = 15;
			this->label8->Text = L"X";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(336, 60);
			this->label7->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(18, 20);
			this->label7->TabIndex = 14;
			this->label7->Text = L"β";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(140, 60);
			this->label6->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(18, 20);
			this->label6->TabIndex = 13;
			this->label6->Text = L"α";
			// 
			// errY
			// 
			this->errY->Location = System::Drawing::Point(366, 188);
			this->errY->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->errY->Name = L"errY";
			this->errY->ReadOnly = true;
			this->errY->Size = System::Drawing::Size(148, 26);
			this->errY->TabIndex = 12;
			this->errY->TextChanged += gcnew System::EventHandler(this, &Form1::textBox8_TextChanged);
			// 
			// tgtY
			// 
			this->tgtY->Location = System::Drawing::Point(366, 102);
			this->tgtY->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->tgtY->Name = L"tgtY";
			this->tgtY->ReadOnly = true;
			this->tgtY->Size = System::Drawing::Size(148, 26);
			this->tgtY->TabIndex = 11;
			// 
			// motorB
			// 
			this->motorB->Location = System::Drawing::Point(366, 55);
			this->motorB->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->motorB->Name = L"motorB";
			this->motorB->ReadOnly = true;
			this->motorB->Size = System::Drawing::Size(148, 26);
			this->motorB->TabIndex = 10;
			// 
			// cam
			// 
			this->cam->Location = System::Drawing::Point(170, 237);
			this->cam->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->cam->Name = L"cam";
			this->cam->ReadOnly = true;
			this->cam->Size = System::Drawing::Size(148, 26);
			this->cam->TabIndex = 9;
			// 
			// errX
			// 
			this->errX->Location = System::Drawing::Point(170, 188);
			this->errX->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->errX->Name = L"errX";
			this->errX->ReadOnly = true;
			this->errX->Size = System::Drawing::Size(148, 26);
			this->errX->TabIndex = 8;
			// 
			// SNR
			// 
			this->SNR->Location = System::Drawing::Point(170, 142);
			this->SNR->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->SNR->Name = L"SNR";
			this->SNR->ReadOnly = true;
			this->SNR->Size = System::Drawing::Size(148, 26);
			this->SNR->TabIndex = 7;
			// 
			// tgtX
			// 
			this->tgtX->Location = System::Drawing::Point(170, 102);
			this->tgtX->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->tgtX->Name = L"tgtX";
			this->tgtX->ReadOnly = true;
			this->tgtX->Size = System::Drawing::Size(148, 26);
			this->tgtX->TabIndex = 6;
			// 
			// motorA
			// 
			this->motorA->Location = System::Drawing::Point(170, 55);
			this->motorA->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->motorA->Name = L"motorA";
			this->motorA->ReadOnly = true;
			this->motorA->Size = System::Drawing::Size(148, 26);
			this->motorA->TabIndex = 5;
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(9, 237);
			this->label5->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(116, 20);
			this->label5->TabIndex = 4;
			this->label5->Text = L"Camera Status";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(9, 188);
			this->label4->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(108, 20);
			this->label4->TabIndex = 3;
			this->label4->Text = L"Tracking Error";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(9, 142);
			this->label3->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(43, 20);
			this->label3->TabIndex = 2;
			this->label3->Text = L"SNR";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(9, 102);
			this->label2->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(115, 20);
			this->label2->TabIndex = 1;
			this->label2->Text = L"Target Position";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(9, 55);
			this->label1->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(58, 20);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Motors";
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->textBox10);
			this->groupBox1->Controls->Add(this->comboBox1);
			this->groupBox1->Controls->Add(this->textBox9);
			this->groupBox1->Controls->Add(this->label15);
			this->groupBox1->Controls->Add(this->label14);
			this->groupBox1->Controls->Add(this->label13);
			this->groupBox1->Location = System::Drawing::Point(18, 425);
			this->groupBox1->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Padding = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->groupBox1->Size = System::Drawing::Size(432, 203);
			this->groupBox1->TabIndex = 2;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Settings";
			this->groupBox1->Enter += gcnew System::EventHandler(this, &Form1::groupBox1_Enter);
			// 
			// textBox10
			// 
			this->textBox10->Location = System::Drawing::Point(230, 145);
			this->textBox10->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->textBox10->Name = L"textBox10";
			this->textBox10->Size = System::Drawing::Size(148, 26);
			this->textBox10->TabIndex = 5;
			this->textBox10->TextChanged += gcnew System::EventHandler(this, &Form1::textBox10_TextChanged);
			// 
			// comboBox1
			// 
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Items->AddRange(gcnew cli::array< System::Object^  >(2) { L"Right", L"Left" });
			this->comboBox1->Location = System::Drawing::Point(230, 94);
			this->comboBox1->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(148, 28);
			this->comboBox1->TabIndex = 4;
			this->comboBox1->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::comboBox1_SelectedIndexChanged);
			// 
			// textBox9
			// 
			this->textBox9->Location = System::Drawing::Point(230, 38);
			this->textBox9->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->textBox9->Name = L"textBox9";
			this->textBox9->Size = System::Drawing::Size(148, 26);
			this->textBox9->TabIndex = 3;
			this->textBox9->TextChanged += gcnew System::EventHandler(this, &Form1::textBox9_TextChanged);
			// 
			// label15
			// 
			this->label15->AutoSize = true;
			this->label15->Location = System::Drawing::Point(9, 155);
			this->label15->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(135, 20);
			this->label15->TabIndex = 2;
			this->label15->Text = L"Sun Position (1-3)";
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->Location = System::Drawing::Point(9, 106);
			this->label14->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(96, 20);
			this->label14->TabIndex = 1;
			this->label14->Text = L"Object Entry";
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->Location = System::Drawing::Point(10, 49);
			this->label13->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(186, 20);
			this->label13->TabIndex = 0;
			this->label13->Text = L"Enter Distance 50 -300m";
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(486, 500);
			this->button1->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(100, 35);
			this->button1->TabIndex = 3;
			this->button1->Text = L"Move Left";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(615, 500);
			this->button2->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(114, 35);
			this->button2->TabIndex = 4;
			this->button2->Text = L"Move Right";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Form1::button2_Click);
			// 
			// label16
			// 
			this->label16->AutoSize = true;
			this->label16->Location = System::Drawing::Point(640, 15);
			this->label16->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label16->Name = L"label16";
			this->label16->Size = System::Drawing::Size(125, 20);
			this->label16->TabIndex = 5;
			this->label16->Text = L"GOTT Tracking\?";
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(539, 558);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(132, 41);
			this->button3->TabIndex = 6;
			this->button3->Text = L"Push Settings";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &Form1::Button3_Click);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(777, 646);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->label16);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->Diagnostics);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->Name = L"Form1";
			this->Text = L"Form1";
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->Diagnostics->ResumeLayout(false);
			this->Diagnostics->PerformLayout();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void eXITToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		this->Close();
	}
	private: System::Void label11_Click(System::Object^  sender, System::EventArgs^  e) {
	}
private: System::Void textBox8_TextChanged(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void groupBox1_Enter(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void textBox9_TextChanged(System::Object^  sender, System::EventArgs^  e) {
	DataExchange::Instance()->gui_data[DataExchange::TARGET_DISTANCE] = Convert::ToInt32(textBox9->Text);
}
private: System::Void comboBox1_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
	System::String^ test(Convert::ToString("Right"));
	System::String^ value = comboBox1->Text;

	if (System::String::Compare(value, test)) {
		DataExchange::Instance()->gui_data[DataExchange::POINT_OF_ENTRY] = 0;
	}
	else {
		DataExchange::Instance()->gui_data[DataExchange::POINT_OF_ENTRY] = 1;
	}
}
private: System::Void textBox10_TextChanged(System::Object^  sender, System::EventArgs^  e) {
	DataExchange::Instance()->gui_data[DataExchange::SUN_POS] = Convert::ToInt32(textBox10->Text);
}
private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
	DataExchange::Instance()->MoveLaser(true);
}
private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
	DataExchange::Instance()->MoveLaser(false);
}
private: System::Void Button3_Click(System::Object^ sender, System::EventArgs^ e) {
	DataExchange::Instance()->Update();
}
};
}
