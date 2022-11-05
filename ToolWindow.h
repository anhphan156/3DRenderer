#pragma once

namespace Exercise2 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for ToolWindow
	/// </summary>
	public ref class ToolWindow : public System::Windows::Forms::Form
	{
	public:
		static bool InvertColors;
		static float Y = 100.f;
		static float U = 100.f;
		static float V = 100.f;
		ToolWindow(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~ToolWindow()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::CheckBox^ checkBox1;
	private: System::Windows::Forms::TrackBar^ YTrackBar;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::TrackBar^ UTrackBar;
	private: System::Windows::Forms::TrackBar^ VTrackBar;
	private: System::Windows::Forms::Label^ YVal;
	private: System::Windows::Forms::Label^ UVal;
	private: System::Windows::Forms::Label^ VVal;
	protected:

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
			this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			this->YTrackBar = (gcnew System::Windows::Forms::TrackBar());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->UTrackBar = (gcnew System::Windows::Forms::TrackBar());
			this->VTrackBar = (gcnew System::Windows::Forms::TrackBar());
			this->YVal = (gcnew System::Windows::Forms::Label());
			this->UVal = (gcnew System::Windows::Forms::Label());
			this->VVal = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->YTrackBar))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->UTrackBar))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->VTrackBar))->BeginInit();
			this->SuspendLayout();
			// 
			// checkBox1
			// 
			this->checkBox1->AutoSize = true;
			this->checkBox1->Location = System::Drawing::Point(12, 222);
			this->checkBox1->Name = L"checkBox1";
			this->checkBox1->Size = System::Drawing::Size(84, 17);
			this->checkBox1->TabIndex = 0;
			this->checkBox1->Text = L"Invert colors";
			this->checkBox1->UseVisualStyleBackColor = true;
			this->checkBox1->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::checkBox1_CheckedChanged);
			// 
			// YTrackBar
			// 
			this->YTrackBar->Location = System::Drawing::Point(58, 26);
			this->YTrackBar->Maximum = 200;
			this->YTrackBar->Name = L"YTrackBar";
			this->YTrackBar->Size = System::Drawing::Size(167, 45);
			this->YTrackBar->TabIndex = 1;
			this->YTrackBar->Value = 100;
			this->YTrackBar->Scroll += gcnew System::EventHandler(this, &ToolWindow::YTrackBar_Scroll);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(12, 26);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(14, 13);
			this->label1->TabIndex = 2;
			this->label1->Text = L"Y";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(12, 91);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(15, 13);
			this->label2->TabIndex = 3;
			this->label2->Text = L"U";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(12, 151);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(14, 13);
			this->label3->TabIndex = 4;
			this->label3->Text = L"V";
			// 
			// UTrackBar
			// 
			this->UTrackBar->Location = System::Drawing::Point(58, 91);
			this->UTrackBar->Maximum = 200;
			this->UTrackBar->Name = L"UTrackBar";
			this->UTrackBar->Size = System::Drawing::Size(167, 45);
			this->UTrackBar->TabIndex = 5;
			this->UTrackBar->Value = 100;
			this->UTrackBar->Scroll += gcnew System::EventHandler(this, &ToolWindow::UTrackBar_Scroll);
			// 
			// VTrackBar
			// 
			this->VTrackBar->Location = System::Drawing::Point(58, 151);
			this->VTrackBar->Maximum = 200;
			this->VTrackBar->Name = L"VTrackBar";
			this->VTrackBar->Size = System::Drawing::Size(167, 45);
			this->VTrackBar->TabIndex = 6;
			this->VTrackBar->Value = 100;
			this->VTrackBar->Scroll += gcnew System::EventHandler(this, &ToolWindow::VTrackBar_Scroll);
			// 
			// YVal
			// 
			this->YVal->AutoSize = true;
			this->YVal->Location = System::Drawing::Point(237, 26);
			this->YVal->Name = L"YVal";
			this->YVal->Size = System::Drawing::Size(33, 13);
			this->YVal->TabIndex = 7;
			this->YVal->Text = L"100%";
			// 
			// UVal
			// 
			this->UVal->AutoSize = true;
			this->UVal->Location = System::Drawing::Point(237, 91);
			this->UVal->Name = L"UVal";
			this->UVal->Size = System::Drawing::Size(33, 13);
			this->UVal->TabIndex = 8;
			this->UVal->Text = L"100%";
			// 
			// VVal
			// 
			this->VVal->AutoSize = true;
			this->VVal->Location = System::Drawing::Point(237, 151);
			this->VVal->Name = L"VVal";
			this->VVal->Size = System::Drawing::Size(33, 13);
			this->VVal->TabIndex = 9;
			this->VVal->Text = L"100%";
			// 
			// ToolWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 261);
			this->Controls->Add(this->VVal);
			this->Controls->Add(this->UVal);
			this->Controls->Add(this->YVal);
			this->Controls->Add(this->VTrackBar);
			this->Controls->Add(this->UTrackBar);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->YTrackBar);
			this->Controls->Add(this->checkBox1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
			this->Name = L"ToolWindow";
			this->Text = L"ToolWindow";
			this->TopMost = true;
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->YTrackBar))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->UTrackBar))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->VTrackBar))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void checkBox1_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		InvertColors = checkBox1->Checked;
	}
	private: System::Void YTrackBar_Scroll(System::Object^ sender, System::EventArgs^ e) {
		Y = YTrackBar->Value;
		YVal->Text = Y.ToString() + "%";
	}
	private: System::Void UTrackBar_Scroll(System::Object^ sender, System::EventArgs^ e) {
		U = UTrackBar->Value;
		UVal->Text = U.ToString() + "%";
	}
	private: System::Void VTrackBar_Scroll(System::Object^ sender, System::EventArgs^ e) {
		V = VTrackBar->Value;
		VVal->Text = V.ToString() + "%";
	}
};
}
