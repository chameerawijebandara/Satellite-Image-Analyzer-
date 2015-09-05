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
	public:
		Main(void)
		{
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
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->panel2 = (gcnew System::Windows::Forms::Panel());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->panel3 = (gcnew System::Windows::Forms::Panel());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->panel1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->BeginInit();
			this->panel2->SuspendLayout();
			this->panel3->SuspendLayout();
			this->SuspendLayout();
			// 
			// btn_openImage
			// 
			this->btn_openImage->Location = System::Drawing::Point(630, 61);
			this->btn_openImage->Name = L"btn_openImage";
			this->btn_openImage->Size = System::Drawing::Size(242, 44);
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
			this->panel1->Controls->Add(this->pictureBox1);
			this->panel1->Controls->Add(this->panel2);
			this->panel1->Controls->Add(this->button1);
			this->panel1->Controls->Add(this->textBox1);
			this->panel1->Controls->Add(this->btn_openImage);
			this->panel1->Controls->Add(this->panel3);
			this->panel1->Location = System::Drawing::Point(12, 12);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(918, 701);
			this->panel1->TabIndex = 1;
			// 
			// pictureBox1
			// 
			this->pictureBox1->Location = System::Drawing::Point(62, 148);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(496, 178);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox1->TabIndex = 4;
			this->pictureBox1->TabStop = false;
			// 
			// panel2
			// 
			this->panel2->AccessibleName = L"";
			this->panel2->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->panel2->Controls->Add(this->textBox3);
			this->panel2->Controls->Add(this->textBox2);
			this->panel2->Controls->Add(this->label2);
			this->panel2->Controls->Add(this->label1);
			this->panel2->Location = System::Drawing::Point(29, 380);
			this->panel2->Name = L"panel2";
			this->panel2->Size = System::Drawing::Size(870, 294);
			this->panel2->TabIndex = 3;
			this->panel2->Tag = L"";
			this->panel2->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Main::panel2_Paint);
			// 
			// textBox3
			// 
			this->textBox3->Location = System::Drawing::Point(437, 147);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(251, 38);
			this->textBox3->TabIndex = 3;
			this->textBox3->TextChanged += gcnew System::EventHandler(this, &Main::textBox3_TextChanged);
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(437, 81);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(251, 38);
			this->textBox2->TabIndex = 2;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(26, 150);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(321, 32);
			this->label2->TabIndex = 1;
			this->label2->Text = L"Number of Type B Trees";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(26, 87);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(321, 32);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Number of Type A Trees";
			this->label1->Click += gcnew System::EventHandler(this, &Main::label1_Click);
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(630, 148);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(242, 44);
			this->button1->TabIndex = 2;
			this->button1->Text = L"Prosses Image ";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Main::button1_Click);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(62, 65);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(496, 38);
			this->textBox1->TabIndex = 1;
			// 
			// panel3
			// 
			this->panel3->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->panel3->Controls->Add(this->button2);
			this->panel3->Location = System::Drawing::Point(29, 33);
			this->panel3->Name = L"panel3";
			this->panel3->Size = System::Drawing::Size(870, 321);
			this->panel3->TabIndex = 5;
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(592, 219);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(251, 44);
			this->button2->TabIndex = 4;
			this->button2->Text = L"View Output";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Main::button2_Click);
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			// 
			// Main
			// 
			this->ClientSize = System::Drawing::Size(942, 725);
			this->Controls->Add(this->panel1);
			this->Name = L"Main";
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->EndInit();
			this->panel2->ResumeLayout(false);
			this->panel2->PerformLayout();
			this->panel3->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion

	private: System::Void panel2_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
			 }
	private: System::Void label1_Click(System::Object^  sender, System::EventArgs^  e) {
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
			 msclr::interop::marshal_context context;
			 imgp = new ImageProcessor(context.marshal_as<std::string>(fileName));
			 imgp->Process();

			 textBox2->Text = ""+ImageProcessor::type_A_no;
			 textBox3->Text = ""+ImageProcessor::type_B_no;
		 }
private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
			 imgp->showOutput();
		 }
};
}
