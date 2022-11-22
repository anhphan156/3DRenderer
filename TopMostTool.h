#pragma once

namespace OpenGLLearning2 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for TopMostTool
	/// </summary>
	public ref class TopMostTool : public System::Windows::Forms::Form
	{
	public:
		TopMostTool(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	   static int resetLightPosition = 0;
	   static int resetTeapotPosition = 0;
		static int gameMode = 0;
		static float S = 4.f;
		static float R = 100.f;
		static float G = 100.f;
		static float B = 100.f;

	private: System::Windows::Forms::Label^ label1;
	public:
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::TrackBar^ trackBar1;
	private: System::Windows::Forms::TrackBar^ trackBar2;
	private: System::Windows::Forms::TrackBar^ trackBar3;
	private: System::Windows::Forms::TrackBar^ trackBar4;
	private: System::Windows::Forms::Label^ SLabel;
	private: System::Windows::Forms::Label^ RLabel;
	private: System::Windows::Forms::Label^ GLabel;
	private: System::Windows::Forms::Button^ resetLight;
	private: System::Windows::Forms::Label^ BLabel;



	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~TopMostTool()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::RadioButton^ radioButton1;
	protected:
	private: System::Windows::Forms::RadioButton^ radioButton2;
	private: System::Windows::Forms::RadioButton^ radioButton3;
	private: System::Windows::Forms::Button^ resetTeapot;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->radioButton1 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton2 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton3 = (gcnew System::Windows::Forms::RadioButton());
			this->resetTeapot = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->trackBar1 = (gcnew System::Windows::Forms::TrackBar());
			this->trackBar2 = (gcnew System::Windows::Forms::TrackBar());
			this->trackBar3 = (gcnew System::Windows::Forms::TrackBar());
			this->trackBar4 = (gcnew System::Windows::Forms::TrackBar());
			this->SLabel = (gcnew System::Windows::Forms::Label());
			this->RLabel = (gcnew System::Windows::Forms::Label());
			this->GLabel = (gcnew System::Windows::Forms::Label());
			this->BLabel = (gcnew System::Windows::Forms::Label());
			this->resetLight = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar3))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar4))->BeginInit();
			this->SuspendLayout();
			// 
			// radioButton1
			// 
			this->radioButton1->AutoSize = true;
			this->radioButton1->Checked = true;
			this->radioButton1->Location = System::Drawing::Point(12, 12);
			this->radioButton1->Name = L"radioButton1";
			this->radioButton1->Size = System::Drawing::Size(78, 17);
			this->radioButton1->TabIndex = 0;
			this->radioButton1->TabStop = true;
			this->radioButton1->Text = L"Move Light";
			this->radioButton1->UseVisualStyleBackColor = true;
			this->radioButton1->CheckedChanged += gcnew System::EventHandler(this, &TopMostTool::radioButton1_CheckedChanged);
			// 
			// radioButton2
			// 
			this->radioButton2->AutoSize = true;
			this->radioButton2->Location = System::Drawing::Point(11, 269);
			this->radioButton2->Name = L"radioButton2";
			this->radioButton2->Size = System::Drawing::Size(103, 17);
			this->radioButton2->TabIndex = 1;
			this->radioButton2->Text = L"Color by Position";
			this->radioButton2->UseVisualStyleBackColor = true;
			this->radioButton2->CheckedChanged += gcnew System::EventHandler(this, &TopMostTool::radioButton2_CheckedChanged);
			// 
			// radioButton3
			// 
			this->radioButton3->AutoSize = true;
			this->radioButton3->Location = System::Drawing::Point(11, 333);
			this->radioButton3->Name = L"radioButton3";
			this->radioButton3->Size = System::Drawing::Size(134, 17);
			this->radioButton3->TabIndex = 2;
			this->radioButton3->Text = L"Move Cubes to Sphere";
			this->radioButton3->UseVisualStyleBackColor = true;
			this->radioButton3->CheckedChanged += gcnew System::EventHandler(this, &TopMostTool::radioButton3_CheckedChanged);
			// 
			// resetTeapot
			// 
			this->resetTeapot->Location = System::Drawing::Point(36, 292);
			this->resetTeapot->Name = L"resetTeapot";
			this->resetTeapot->Size = System::Drawing::Size(130, 23);
			this->resetTeapot->TabIndex = 3;
			this->resetTeapot->Text = L"Reset Teapot Position";
			this->resetTeapot->UseVisualStyleBackColor = true;
			this->resetTeapot->Click += gcnew System::EventHandler(this, &TopMostTool::resetTeapot_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(33, 85);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(92, 13);
			this->label1->TabIndex = 4;
			this->label1->Text = L"Specular Strength";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(33, 140);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(76, 13);
			this->label2->TabIndex = 5;
			this->label2->Text = L"Specular Color";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(116, 140);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(15, 13);
			this->label3->TabIndex = 6;
			this->label3->Text = L"R";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(116, 189);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(15, 13);
			this->label4->TabIndex = 7;
			this->label4->Text = L"G";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(116, 232);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(14, 13);
			this->label5->TabIndex = 8;
			this->label5->Text = L"B";
			// 
			// trackBar1
			// 
			this->trackBar1->Location = System::Drawing::Point(164, 74);
			this->trackBar1->Maximum = 128;
			this->trackBar1->Minimum = 1;
			this->trackBar1->Name = L"trackBar1";
			this->trackBar1->Size = System::Drawing::Size(318, 45);
			this->trackBar1->TabIndex = 9;
			this->trackBar1->Value = 4;
			this->trackBar1->Scroll += gcnew System::EventHandler(this, &TopMostTool::trackBar1_Scroll);
			// 
			// trackBar2
			// 
			this->trackBar2->Location = System::Drawing::Point(164, 125);
			this->trackBar2->Maximum = 300;
			this->trackBar2->Name = L"trackBar2";
			this->trackBar2->Size = System::Drawing::Size(318, 45);
			this->trackBar2->TabIndex = 10;
			this->trackBar2->Value = 100;
			this->trackBar2->Scroll += gcnew System::EventHandler(this, &TopMostTool::trackBar2_Scroll);
			// 
			// trackBar3
			// 
			this->trackBar3->Location = System::Drawing::Point(164, 176);
			this->trackBar3->Maximum = 300;
			this->trackBar3->Name = L"trackBar3";
			this->trackBar3->Size = System::Drawing::Size(318, 45);
			this->trackBar3->TabIndex = 11;
			this->trackBar3->Value = 100;
			this->trackBar3->Scroll += gcnew System::EventHandler(this, &TopMostTool::trackBar3_Scroll);
			// 
			// trackBar4
			// 
			this->trackBar4->Location = System::Drawing::Point(164, 227);
			this->trackBar4->Maximum = 300;
			this->trackBar4->Name = L"trackBar4";
			this->trackBar4->Size = System::Drawing::Size(318, 45);
			this->trackBar4->TabIndex = 12;
			this->trackBar4->Value = 100;
			this->trackBar4->Scroll += gcnew System::EventHandler(this, &TopMostTool::trackBar4_Scroll);
			// 
			// SLabel
			// 
			this->SLabel->AutoSize = true;
			this->SLabel->Location = System::Drawing::Point(509, 85);
			this->SLabel->Name = L"SLabel";
			this->SLabel->Size = System::Drawing::Size(35, 13);
			this->SLabel->TabIndex = 13;
			this->SLabel->Text = L"label6";
			// 
			// RLabel
			// 
			this->RLabel->AutoSize = true;
			this->RLabel->Location = System::Drawing::Point(509, 140);
			this->RLabel->Name = L"RLabel";
			this->RLabel->Size = System::Drawing::Size(35, 13);
			this->RLabel->TabIndex = 14;
			this->RLabel->Text = L"label7";
			// 
			// GLabel
			// 
			this->GLabel->AutoSize = true;
			this->GLabel->Location = System::Drawing::Point(509, 189);
			this->GLabel->Name = L"GLabel";
			this->GLabel->Size = System::Drawing::Size(35, 13);
			this->GLabel->TabIndex = 15;
			this->GLabel->Text = L"label8";
			// 
			// BLabel
			// 
			this->BLabel->AutoSize = true;
			this->BLabel->Location = System::Drawing::Point(509, 232);
			this->BLabel->Name = L"BLabel";
			this->BLabel->Size = System::Drawing::Size(35, 13);
			this->BLabel->TabIndex = 16;
			this->BLabel->Text = L"label9";
			// 
			// resetLight
			// 
			this->resetLight->Location = System::Drawing::Point(36, 35);
			this->resetLight->Name = L"resetLight";
			this->resetLight->Size = System::Drawing::Size(130, 23);
			this->resetLight->TabIndex = 17;
			this->resetLight->Text = L"Reset Light Position";
			this->resetLight->UseVisualStyleBackColor = true;
			this->resetLight->Click += gcnew System::EventHandler(this, &TopMostTool::resetLight_Click);
			// 
			// TopMostTool
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(557, 367);
			this->Controls->Add(this->resetLight);
			this->Controls->Add(this->BLabel);
			this->Controls->Add(this->GLabel);
			this->Controls->Add(this->RLabel);
			this->Controls->Add(this->SLabel);
			this->Controls->Add(this->trackBar4);
			this->Controls->Add(this->trackBar3);
			this->Controls->Add(this->trackBar2);
			this->Controls->Add(this->trackBar1);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->resetTeapot);
			this->Controls->Add(this->radioButton3);
			this->Controls->Add(this->radioButton2);
			this->Controls->Add(this->radioButton1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
			this->Name = L"TopMostTool";
			this->Text = L"TopMostTool";
			this->TopMost = true;
			this->Load += gcnew System::EventHandler(this, &TopMostTool::TopMostTool_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar3))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar4))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void radioButton1_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		gameMode = 0;
	}
	private: System::Void radioButton2_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		gameMode = 1;
	}
	private: System::Void radioButton3_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		gameMode = 2;
	}
	private: System::Void resetTeapot_Click(System::Object^ sender, System::EventArgs^ e) {
		resetTeapotPosition = 1;
	}
	private: System::Void TopMostTool_Load(System::Object^ sender, System::EventArgs^ e) {
		S = trackBar1->Value;
		SLabel->Text = S.ToString();
		R = trackBar2->Value / 100.f;
		RLabel->Text = R.ToString();
		G = trackBar3->Value / 100.f;
		GLabel->Text = G.ToString();
		B = trackBar4->Value / 100.f;
		BLabel->Text = B.ToString();
	}
	private: System::Void trackBar1_Scroll(System::Object^ sender, System::EventArgs^ e) {
		S = trackBar1->Value;
		SLabel->Text = S.ToString();
	}
	private: System::Void trackBar2_Scroll(System::Object^ sender, System::EventArgs^ e) {
		R = trackBar2->Value / 100.f;
		RLabel->Text = R.ToString();
	}
	private: System::Void trackBar3_Scroll(System::Object^ sender, System::EventArgs^ e) {
		G = trackBar3->Value / 100.f;
		GLabel->Text = G.ToString();
	}
	private: System::Void trackBar4_Scroll(System::Object^ sender, System::EventArgs^ e) {
		B = trackBar4->Value / 100.f;
		BLabel->Text = B.ToString();
	}
	private: System::Void resetLight_Click(System::Object^ sender, System::EventArgs^ e) {
		resetLightPosition = 1;
	}
};
}
