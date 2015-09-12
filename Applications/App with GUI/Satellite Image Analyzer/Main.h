#pragma once

#include "ImageProcessor.h"
#include <msclr\marshal_cppstd.h>
#include <algorithm>
#include <String>
#include <Shlwapi.h>
#include <Windows.h>
#include <iostream>

namespace SatelliteImageAnalyzer {

	using namespace System;
	using namespace System::Collections::Generic;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Main
	/// </summary>
	public ref class Main : public System::Windows::Forms::Form
	{
	bool isproccesed;
	public:
		Main(void)
		{
			isproccesed = false;
			InitializeComponent();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Main()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  btn_openImage;
	protected: 
	private: System::Windows::Forms::Panel^  panel1;
	private: System::Windows::Forms::Panel^  panel2;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;
	private: System::Windows::Forms::PictureBox^  pictureBox1;

	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TextBox^  textBox3;
	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Panel^  panel3;

	private: System::ComponentModel::IContainer^  components;

	System::String^ fileName;
	private: System::Windows::Forms::RadioButton^  radioButton3;
	private: System::Windows::Forms::RadioButton^  radioButton2;
	private: System::Windows::Forms::RadioButton^  radioButton1;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::TextBox^  textBox6;
	private: System::Windows::Forms::TextBox^  textBox5;
	private: System::Windows::Forms::TextBox^  textBox4;
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::Label^  label4;




			 ImageProcessor *imgp;


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->btn_openImage = (gcnew System::Windows::Forms::Button());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->panel2 = (gcnew System::Windows::Forms::Panel());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->panel3 = (gcnew System::Windows::Forms::Panel());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->textBox6 = (gcnew System::Windows::Forms::TextBox());
			this->textBox5 = (gcnew System::Windows::Forms::TextBox());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->radioButton3 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton2 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton1 = (gcnew System::Windows::Forms::RadioButton());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->panel1->SuspendLayout();
			this->panel2->SuspendLayout();
			this->panel3->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// btn_openImage
			// 
			this->btn_openImage->Location = System::Drawing::Point(376, 30);
			this->btn_openImage->Name = L"btn_openImage";
			this->btn_openImage->Size = System::Drawing::Size(114, 31);
			this->btn_openImage->TabIndex = 0;
			this->btn_openImage->Text = L"Open Image";
			this->btn_openImage->UseVisualStyleBackColor = true;
			this->btn_openImage->Click += gcnew System::EventHandler(this, &Main::btn_openImage_Click);
			// 
			// panel1
			// 
			this->panel1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->panel1->Controls->Add(this->panel2);
			this->panel1->Controls->Add(this->panel3);
			this->panel1->Location = System::Drawing::Point(12, 12);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(518, 547);
			this->panel1->TabIndex = 1;
			// 
			// panel2
			// 
			this->panel2->AccessibleName = L"";
			this->panel2->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->panel2->Controls->Add(this->button2);
			this->panel2->Controls->Add(this->textBox3);
			this->panel2->Controls->Add(this->textBox2);
			this->panel2->Controls->Add(this->label2);
			this->panel2->Controls->Add(this->label1);
			this->panel2->Location = System::Drawing::Point(0, 403);
			this->panel2->Name = L"panel2";
			this->panel2->Size = System::Drawing::Size(503, 140);
			this->panel2->TabIndex = 3;
			this->panel2->Tag = L"";
			this->panel2->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Main::panel2_Paint);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(376, 60);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(114, 31);
			this->button2->TabIndex = 4;
			this->button2->Text = L"View Output";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Main::button2_Click);
			// 
			// textBox3
			// 
			this->textBox3->Location = System::Drawing::Point(182, 69);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(69, 20);
			this->textBox3->TabIndex = 3;
			this->textBox3->TextChanged += gcnew System::EventHandler(this, &Main::textBox3_TextChanged);
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(182, 32);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(69, 20);
			this->textBox2->TabIndex = 2;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(26, 69);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(123, 13);
			this->label2->TabIndex = 1;
			this->label2->Text = L"Number of Type B Trees";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(26, 32);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(123, 13);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Number of Type A Trees";
			// 
			// panel3
			// 
			this->panel3->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->panel3->Controls->Add(this->button3);
			this->panel3->Controls->Add(this->label4);
			this->panel3->Controls->Add(this->label3);
			this->panel3->Controls->Add(this->textBox6);
			this->panel3->Controls->Add(this->textBox5);
			this->panel3->Controls->Add(this->textBox4);
			this->panel3->Controls->Add(this->radioButton3);
			this->panel3->Controls->Add(this->radioButton2);
			this->panel3->Controls->Add(this->radioButton1);
			this->panel3->Controls->Add(this->pictureBox1);
			this->panel3->Controls->Add(this->textBox1);
			this->panel3->Controls->Add(this->button1);
			this->panel3->Controls->Add(this->btn_openImage);
			this->panel3->Location = System::Drawing::Point(3, 3);
			this->panel3->Name = L"panel3";
			this->panel3->Size = System::Drawing::Size(503, 394);
			this->panel3->TabIndex = 5;
			this->panel3->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Main::panel3_Paint);
			// 
			// button3
			// 
			this->button3->Enabled = false;
			this->button3->Location = System::Drawing::Point(371, 323);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(108, 23);
			this->button3->TabIndex = 13;
			this->button3->Text = L"Image Folder";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &Main::button3_Click);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Enabled = false;
			this->label4->Location = System::Drawing::Point(352, 355);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(66, 13);
			this->label4->TabIndex = 12;
			this->label4->Text = L"Tree Images";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Enabled = false;
			this->label3->Location = System::Drawing::Point(122, 355);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(68, 13);
			this->label3->TabIndex = 11;
			this->label3->Text = L"Total Images";
			// 
			// textBox6
			// 
			this->textBox6->Enabled = false;
			this->textBox6->Location = System::Drawing::Point(249, 352);
			this->textBox6->Name = L"textBox6";
			this->textBox6->Size = System::Drawing::Size(78, 20);
			this->textBox6->TabIndex = 10;
			// 
			// textBox5
			// 
			this->textBox5->Enabled = false;
			this->textBox5->Location = System::Drawing::Point(29, 352);
			this->textBox5->Name = L"textBox5";
			this->textBox5->Size = System::Drawing::Size(78, 20);
			this->textBox5->TabIndex = 9;
			// 
			// textBox4
			// 
			this->textBox4->Enabled = false;
			this->textBox4->Location = System::Drawing::Point(29, 326);
			this->textBox4->Name = L"textBox4";
			this->textBox4->Size = System::Drawing::Size(336, 20);
			this->textBox4->TabIndex = 8;
			// 
			// radioButton3
			// 
			this->radioButton3->AutoSize = true;
			this->radioButton3->Location = System::Drawing::Point(144, 293);
			this->radioButton3->Name = L"radioButton3";
			this->radioButton3->Size = System::Drawing::Size(107, 17);
			this->radioButton3->TabIndex = 7;
			this->radioButton3->TabStop = true;
			this->radioButton3->Text = L"Use Previous NN";
			this->radioButton3->UseVisualStyleBackColor = true;
			this->radioButton3->CheckedChanged += gcnew System::EventHandler(this, &Main::radioButton3_CheckedChanged);
			// 
			// radioButton2
			// 
			this->radioButton2->AutoSize = true;
			this->radioButton2->Location = System::Drawing::Point(272, 293);
			this->radioButton2->Name = L"radioButton2";
			this->radioButton2->Size = System::Drawing::Size(93, 17);
			this->radioButton2->TabIndex = 6;
			this->radioButton2->TabStop = true;
			this->radioButton2->Text = L"Train New NN";
			this->radioButton2->UseVisualStyleBackColor = true;
			this->radioButton2->CheckedChanged += gcnew System::EventHandler(this, &Main::radioButton2_CheckedChanged);
			// 
			// radioButton1
			// 
			this->radioButton1->AutoSize = true;
			this->radioButton1->Checked = true;
			this->radioButton1->Location = System::Drawing::Point(29, 293);
			this->radioButton1->Name = L"radioButton1";
			this->radioButton1->Size = System::Drawing::Size(100, 17);
			this->radioButton1->TabIndex = 5;
			this->radioButton1->TabStop = true;
			this->radioButton1->Text = L"Use Default NN";
			this->radioButton1->UseVisualStyleBackColor = true;
			this->radioButton1->CheckedChanged += gcnew System::EventHandler(this, &Main::radioButton1_CheckedChanged);
			// 
			// pictureBox1
			// 
			this->pictureBox1->Location = System::Drawing::Point(12, 67);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(318, 209);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox1->TabIndex = 4;
			this->pictureBox1->TabStop = false;
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(12, 36);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(318, 20);
			this->textBox1->TabIndex = 1;
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(376, 85);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(114, 31);
			this->button1->TabIndex = 2;
			this->button1->Text = L"Prosses Image ";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Main::button1_Click);
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			// 
			// Main
			// 
			this->ClientSize = System::Drawing::Size(542, 571);
			this->Controls->Add(this->panel1);
			this->MaximizeBox = false;
			this->Name = L"Main";
			this->panel1->ResumeLayout(false);
			this->panel2->ResumeLayout(false);
			this->panel2->PerformLayout();
			this->panel3->ResumeLayout(false);
			this->panel3->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion

	private: System::Void panel2_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
			 }

private: System::Void textBox3_TextChanged(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void btn_openImage_Click(System::Object^  sender, System::EventArgs^  e) {

				 openFileDialog1->Filter = "Image Files|*.*";
				 openFileDialog1->Title = "Select a Image File";
				 openFileDialog1->FileName = "";
				 if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
				 {
					 String^ _inputFileName = openFileDialog1->FileName;
					 textBox1->Text = _inputFileName;
					 fileName = _inputFileName;

					 System::Drawing::Image^ image = Image::FromFile(_inputFileName);
					 pictureBox1->Height =  ( image->Height*pictureBox1->Width)/image->Width;
					 pictureBox1->Image = image;
				 }
		 }
private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(textBox1->Text==""){
				 MessageBox::Show("Open an Image","",MessageBoxButtons::OK,
									MessageBoxIcon::Error);
			 }
			 else
			 {
				 msclr::interop::marshal_context context;
				 imgp = new ImageProcessor(context.marshal_as<std::string>(fileName));
				 imgp->Process();
				 isproccesed = true;
			 }

			 textBox2->Text = ""+ImageProcessor::type_A_no;
			 textBox3->Text = ""+ImageProcessor::type_B_no;
		 }
private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(isproccesed){
				imgp->showOutput();
			 }
			 else if(textBox1->Text==""){
				 MessageBox::Show("Open an Image","",MessageBoxButtons::OK,
									MessageBoxIcon::Error);
			 }
			 else{
				 MessageBox::Show("Process is not Done","",MessageBoxButtons::OK,
					 MessageBoxIcon::Exclamation);
			 }
		 }


private: System::Void panel3_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
		 }
private: System::Void radioButton2_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 button3->Enabled = true;
			 textBox4->Enabled = true;
			 textBox5->Enabled = true;
			 textBox6->Enabled = true;
			 label3->Enabled = true;
			 label4->Enabled = true;

		 }
private: System::Void radioButton3_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 button3->Enabled = false;
			 textBox4->Enabled = false;
			 textBox5->Enabled = false;
			 textBox6->Enabled = false;
			 label3->Enabled = false;
			 label4->Enabled = false;
		 }
private: System::Void radioButton1_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 button3->Enabled = false;
			 textBox4->Enabled = false;
			 textBox5->Enabled = false;
			 textBox6->Enabled = false;
			 label3->Enabled = false;
			 label4->Enabled = false;
		 }
private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
			
		 }
};
}
