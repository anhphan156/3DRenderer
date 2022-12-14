#pragma once
#include <functional>

namespace OpenGLTechniques {

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
		void (*OnResetLight)();
		static int gameMode = 1;
		static int specularStrength;
		static float specularR;
		static float specularG;
		static float specularB;

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
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::Label^ label8;
	private: System::Windows::Forms::Label^ label9;
	private: System::Windows::Forms::TrackBar^ SpecularStrengthTrackBar;
	private: System::Windows::Forms::TrackBar^ trackBar1;
	private: System::Windows::Forms::TrackBar^ trackBar2;
	private: System::Windows::Forms::TrackBar^ trackBar3;
	private: System::Windows::Forms::RadioButton^ radioMoveLight;
	private: System::Windows::Forms::RadioButton^ radioTransform;
	private: System::Windows::Forms::RadioButton^ radioWaterScene;
	private: System::Windows::Forms::RadioButton^ radioSpaceScene;
	private: System::Windows::Forms::Button^ ResetLightBtn;
	private: System::Windows::Forms::Button^ ResetTransformBtn;
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
			this->radioMoveLight = (gcnew System::Windows::Forms::RadioButton());
			this->radioTransform = (gcnew System::Windows::Forms::RadioButton());
			this->radioWaterScene = (gcnew System::Windows::Forms::RadioButton());
			this->radioSpaceScene = (gcnew System::Windows::Forms::RadioButton());
			this->ResetLightBtn = (gcnew System::Windows::Forms::Button());
			this->ResetTransformBtn = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->SpecularStrengthTrackBar = (gcnew System::Windows::Forms::TrackBar());
			this->trackBar1 = (gcnew System::Windows::Forms::TrackBar());
			this->trackBar2 = (gcnew System::Windows::Forms::TrackBar());
			this->trackBar3 = (gcnew System::Windows::Forms::TrackBar());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->SpecularStrengthTrackBar))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar3))->BeginInit();
			this->SuspendLayout();
			// 
			// radioMoveLight
			// 
			this->radioMoveLight->AutoSize = true;
			this->radioMoveLight->Location = System::Drawing::Point(32, 25);
			this->radioMoveLight->Name = L"radioMoveLight";
			this->radioMoveLight->Size = System::Drawing::Size(78, 17);
			this->radioMoveLight->TabIndex = 0;
			this->radioMoveLight->TabStop = true;
			this->radioMoveLight->Text = L"Move Light";
			this->radioMoveLight->UseVisualStyleBackColor = true;
			this->radioMoveLight->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::radioMoveLight_CheckedChanged);
			// 
			// radioTransform
			// 
			this->radioTransform->AutoSize = true;
			this->radioTransform->Location = System::Drawing::Point(32, 266);
			this->radioTransform->Name = L"radioTransform";
			this->radioTransform->Size = System::Drawing::Size(72, 17);
			this->radioTransform->TabIndex = 1;
			this->radioTransform->TabStop = true;
			this->radioTransform->Text = L"Transform";
			this->radioTransform->UseVisualStyleBackColor = true;
			// 
			// radioWaterScene
			// 
			this->radioWaterScene->AutoSize = true;
			this->radioWaterScene->Location = System::Drawing::Point(32, 433);
			this->radioWaterScene->Name = L"radioWaterScene";
			this->radioWaterScene->Size = System::Drawing::Size(88, 17);
			this->radioWaterScene->TabIndex = 2;
			this->radioWaterScene->TabStop = true;
			this->radioWaterScene->Text = L"Water Scene";
			this->radioWaterScene->UseVisualStyleBackColor = true;
			// 
			// radioSpaceScene
			// 
			this->radioSpaceScene->AutoSize = true;
			this->radioSpaceScene->Location = System::Drawing::Point(32, 546);
			this->radioSpaceScene->Name = L"radioSpaceScene";
			this->radioSpaceScene->Size = System::Drawing::Size(90, 17);
			this->radioSpaceScene->TabIndex = 3;
			this->radioSpaceScene->TabStop = true;
			this->radioSpaceScene->Text = L"Space Scene";
			this->radioSpaceScene->UseVisualStyleBackColor = true;
			// 
			// ResetLightBtn
			// 
			this->ResetLightBtn->Location = System::Drawing::Point(47, 48);
			this->ResetLightBtn->Name = L"ResetLightBtn";
			this->ResetLightBtn->Size = System::Drawing::Size(122, 23);
			this->ResetLightBtn->TabIndex = 4;
			this->ResetLightBtn->Text = L"Reset Light Position";
			this->ResetLightBtn->UseVisualStyleBackColor = true;
			this->ResetLightBtn->Click += gcnew System::EventHandler(this, &ToolWindow::ResetLightBtn_Click);
			// 
			// ResetTransformBtn
			// 
			this->ResetTransformBtn->Location = System::Drawing::Point(47, 289);
			this->ResetTransformBtn->Name = L"ResetTransformBtn";
			this->ResetTransformBtn->Size = System::Drawing::Size(122, 23);
			this->ResetTransformBtn->TabIndex = 5;
			this->ResetTransformBtn->Text = L"Reset Transform";
			this->ResetTransformBtn->UseVisualStyleBackColor = true;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(44, 91);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(92, 13);
			this->label1->TabIndex = 6;
			this->label1->Text = L"Specular Strength";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(44, 140);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(76, 13);
			this->label2->TabIndex = 7;
			this->label2->Text = L"Specular Color";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(126, 140);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(15, 13);
			this->label3->TabIndex = 8;
			this->label3->Text = L"R";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(126, 182);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(15, 13);
			this->label4->TabIndex = 9;
			this->label4->Text = L"G";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(127, 230);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(14, 13);
			this->label5->TabIndex = 10;
			this->label5->Text = L"B";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(423, 91);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(35, 13);
			this->label6->TabIndex = 11;
			this->label6->Text = L"label6";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(423, 140);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(35, 13);
			this->label7->TabIndex = 12;
			this->label7->Text = L"label7";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(423, 182);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(35, 13);
			this->label8->TabIndex = 13;
			this->label8->Text = L"label8";
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(423, 230);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(35, 13);
			this->label9->TabIndex = 14;
			this->label9->Text = L"label9";
			// 
			// SpecularStrengthTrackBar
			// 
			this->SpecularStrengthTrackBar->Location = System::Drawing::Point(142, 77);
			this->SpecularStrengthTrackBar->Maximum = 128;
			this->SpecularStrengthTrackBar->Minimum = 1;
			this->SpecularStrengthTrackBar->Name = L"SpecularStrengthTrackBar";
			this->SpecularStrengthTrackBar->Size = System::Drawing::Size(265, 45);
			this->SpecularStrengthTrackBar->TabIndex = 15;
			this->SpecularStrengthTrackBar->Value = 4;
			this->SpecularStrengthTrackBar->Scroll += gcnew System::EventHandler(this, &ToolWindow::SpecularStrengthTrackBar_Scroll);
			// 
			// trackBar1
			// 
			this->trackBar1->Location = System::Drawing::Point(147, 140);
			this->trackBar1->Maximum = 300;
			this->trackBar1->Name = L"trackBar1";
			this->trackBar1->Size = System::Drawing::Size(260, 45);
			this->trackBar1->TabIndex = 16;
			this->trackBar1->Value = 100;
			this->trackBar1->Scroll += gcnew System::EventHandler(this, &ToolWindow::trackBar1_Scroll);
			// 
			// trackBar2
			// 
			this->trackBar2->Location = System::Drawing::Point(147, 182);
			this->trackBar2->Maximum = 300;
			this->trackBar2->Name = L"trackBar2";
			this->trackBar2->Size = System::Drawing::Size(260, 45);
			this->trackBar2->TabIndex = 17;
			this->trackBar2->Value = 100;
			this->trackBar2->Scroll += gcnew System::EventHandler(this, &ToolWindow::trackBar2_Scroll);
			// 
			// trackBar3
			// 
			this->trackBar3->Location = System::Drawing::Point(147, 230);
			this->trackBar3->Maximum = 300;
			this->trackBar3->Name = L"trackBar3";
			this->trackBar3->Size = System::Drawing::Size(260, 45);
			this->trackBar3->TabIndex = 18;
			this->trackBar3->Value = 100;
			this->trackBar3->Scroll += gcnew System::EventHandler(this, &ToolWindow::trackBar3_Scroll);
			// 
			// ToolWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(470, 575);
			this->Controls->Add(this->trackBar3);
			this->Controls->Add(this->trackBar2);
			this->Controls->Add(this->trackBar1);
			this->Controls->Add(this->SpecularStrengthTrackBar);
			this->Controls->Add(this->label9);
			this->Controls->Add(this->label8);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->ResetTransformBtn);
			this->Controls->Add(this->ResetLightBtn);
			this->Controls->Add(this->radioSpaceScene);
			this->Controls->Add(this->radioWaterScene);
			this->Controls->Add(this->radioTransform);
			this->Controls->Add(this->radioMoveLight);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
			this->Name = L"ToolWindow";
			this->Text = L"Tool Window";
			this->TopMost = true;
			this->Load += gcnew System::EventHandler(this, &ToolWindow::ToolWindow_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->SpecularStrengthTrackBar))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar3))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void ToolWindow_Load(System::Object^ sender, System::EventArgs^ e) {
		specularStrength = SpecularStrengthTrackBar->Value;
		label6->Text = specularStrength.ToString();

		specularR = (float)trackBar1->Value / 100.f;
		label7->Text = specularR.ToString();
		specularG = (float)trackBar2->Value / 100.f;
		label8->Text = specularG.ToString();
		specularB = (float)trackBar2->Value / 100.f;
		label9->Text = specularB.ToString();
	}
	private: System::Void radioMoveLight_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		gameMode = 1;
	}
	private: System::Void ResetLightBtn_Click(System::Object^ sender, System::EventArgs^ e) {
		OnResetLight();
	}
	private: System::Void SpecularStrengthTrackBar_Scroll(System::Object^ sender, System::EventArgs^ e) {
		specularStrength = SpecularStrengthTrackBar->Value;
		label6->Text = specularStrength.ToString();
	}
	private: System::Void trackBar1_Scroll(System::Object^ sender, System::EventArgs^ e) {
		specularR = (float)trackBar1->Value / 100.f;
		label7->Text = specularR.ToString();
	}
	private: System::Void trackBar2_Scroll(System::Object^ sender, System::EventArgs^ e) {
		specularG = (float)trackBar2->Value / 100.f;
		label8->Text = specularG.ToString();
	}
	private: System::Void trackBar3_Scroll(System::Object^ sender, System::EventArgs^ e) {
		specularB = (float)trackBar3->Value / 100.f;
		label9->Text = specularB.ToString();
	}
};
}
