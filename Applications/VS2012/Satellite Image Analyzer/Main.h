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
			imgp = new ImageProcessor();
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

	private: System::Windows::Forms::RadioButton^  radioButton1;
	private: System::Windows::Forms::Label^  label3;


	private: System::Windows::Forms::TextBox^  textBox4;
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::Label^  label4;

	private: System::Windows::Forms::Button^  button4;
	private: System::Windows::Forms::FolderBrowserDialog^  folderBrowserDialog1;
	private: System::Windows::Forms::NumericUpDown^  numericUpDown2;
	private: System::Windows::Forms::NumericUpDown^  numericUpDown1;




			 ImageProcessor *imgp;
			 std::string *folderPath;


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
			this->numericUpDown2 = (gcnew System::Windows::Forms::NumericUpDown());
			this->numericUpDown1 = (gcnew System::Windows::Forms::NumericUpDown());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->radioButton3 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton1 = (gcnew System::Windows::Forms::RadioButton());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->folderBrowserDialog1 = (gcnew System::Windows::Forms::FolderBrowserDialog());
			this->panel1->SuspendLayout();
			this->panel2->SuspendLayout();
			this->panel3->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown1))->BeginInit();
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
			this->panel1->Size = System::Drawing::Size(519, 579);
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
			this->panel2->Location = System::Drawing::Point(3, 453);
			this->panel2->Name = L"panel2";
			this->panel2->Size = System::Drawing::Size(503, 112);
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
			this->textBox3->Location = System::Drawing::Point(261, 69);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(69, 26);
			this->textBox3->TabIndex = 3;
			this->textBox3->TextChanged += gcnew System::EventHandler(this, &Main::textBox3_TextChanged);
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(261, 32);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(69, 26);
			this->textBox2->TabIndex = 2;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(26, 69);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(176, 20);
			this->label2->TabIndex = 1;
			this->label2->Text = L"Number of Dicots Trees";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(26, 32);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(201, 20);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Number of Monocots Trees";
			// 
			// panel3
			// 
			this->panel3->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->panel3->Controls->Add(this->numericUpDown2);
			this->panel3->Controls->Add(this->numericUpDown1);
			this->panel3->Controls->Add(this->button4);
			this->panel3->Controls->Add(this->button3);
			this->panel3->Controls->Add(this->label4);
			this->panel3->Controls->Add(this->label3);
			this->panel3->Controls->Add(this->textBox4);
			this->panel3->Controls->Add(this->radioButton3);
			this->panel3->Controls->Add(this->radioButton1);
			this->panel3->Controls->Add(this->pictureBox1);
			this->panel3->Controls->Add(this->textBox1);
			this->panel3->Controls->Add(this->button1);
			this->panel3->Controls->Add(this->btn_openImage);
			this->panel3->Location = System::Drawing::Point(3, 3);
			this->panel3->Name = L"panel3";
			this->panel3->Size = System::Drawing::Size(503, 432);
			this->panel3->TabIndex = 5;
			this->panel3->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Main::panel3_Paint);
			// 
			// numericUpDown2
			// 
			this->numericUpDown2->Location = System::Drawing::Point(12, 395);
			this->numericUpDown2->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {1000000000, 0, 0, 0});
			this->numericUpDown2->Name = L"numericUpDown2";
			this->numericUpDown2->Size = System::Drawing::Size(96, 26);
			this->numericUpDown2->TabIndex = 16;
			// 
			// numericUpDown1
			// 
			this->numericUpDown1->Location = System::Drawing::Point(12, 358);
			this->numericUpDown1->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {100000000, 0, 0, 0});
			this->numericUpDown1->Name = L"numericUpDown1";
			this->numericUpDown1->Size = System::Drawing::Size(96, 26);
			this->numericUpDown1->TabIndex = 15;
			// 
			// button4
			// 
			this->button4->Location = System::Drawing::Point(376, 386);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(114, 31);
			this->button4->TabIndex = 14;
			this->button4->Text = L"Train";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &Main::button4_Click);
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(376, 320);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(114, 31);
			this->button3->TabIndex = 13;
			this->button3->Text = L"Image Folder";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &Main::button3_Click);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(117, 397);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(98, 20);
			this->label4->TabIndex = 12;
			this->label4->Text = L"Tree Images";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(114, 362);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(101, 20);
			this->label3->TabIndex = 11;
			this->label3->Text = L"Total Images";
			// 
			// textBox4
			// 
			this->textBox4->Location = System::Drawing::Point(12, 326);
			this->textBox4->Name = L"textBox4";
			this->textBox4->Size = System::Drawing::Size(318, 26);
			this->textBox4->TabIndex = 8;
			// 
			// radioButton3
			// 
			this->radioButton3->AutoSize = true;
			this->radioButton3->Location = System::Drawing::Point(174, 293);
			this->radioButton3->Name = L"radioButton3";
			this->radioButton3->Size = System::Drawing::Size(124, 24);
			this->radioButton3->TabIndex = 7;
			this->radioButton3->TabStop = true;
			this->radioButton3->Text = L"Use New NN";
			this->radioButton3->UseVisualStyleBackColor = true;
			// 
			// radioButton1
			// 
			this->radioButton1->AutoSize = true;
			this->radioButton1->Checked = true;
			this->radioButton1->Location = System::Drawing::Point(29, 293);
			this->radioButton1->Name = L"radioButton1";
			this->radioButton1->Size = System::Drawing::Size(145, 24);
			this->radioButton1->TabIndex = 5;
			this->radioButton1->TabStop = true;
			this->radioButton1->Text = L"Use Default NN";
			this->radioButton1->UseVisualStyleBackColor = true;
			// 
			// pictureBox1
			// 
			this->pictureBox1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
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
			this->textBox1->Size = System::Drawing::Size(318, 26);
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
			this->ClientSize = System::Drawing::Size(543, 603);
			this->Controls->Add(this->panel1);
			this->MaximizeBox = false;
			this->Name = L"Main";
			this->Text = L"Tree Crown Analysis System";
			this->panel1->ResumeLayout(false);
			this->panel2->ResumeLayout(false);
			this->panel2->PerformLayout();
			this->panel3->ResumeLayout(false);
			this->panel3->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown1))->EndInit();
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
				 if( imgp )
					 delete imgp;
				 imgp = new ImageProcessor(context.marshal_as<std::string>(fileName));
				 if(radioButton1->Checked){
					imgp->Process(0);
					isproccesed = true;
				 }
				 else if(radioButton3->Checked){
					imgp->Process(1);
					isproccesed = true;
				 }
				 
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
			 button4->Enabled = true;
			 textBox4->Enabled = true;
			 numericUpDown1->Enabled = true;
			 numericUpDown2->Enabled = true;
			 label3->Enabled = true;
			 label4->Enabled = true;

		 }


private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {


			 if (folderBrowserDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
			{
				String^ _inputFileName = folderBrowserDialog1->SelectedPath;
				textBox4->Text = _inputFileName;
				msclr::interop::marshal_context context;
				if( folderPath )
					delete folderPath;
				folderPath = new std::string( context.marshal_as<std::string>(_inputFileName) );
			}
		 }

private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(textBox4->Text==""){
				 MessageBox::Show("Select the Folder Containig Sample Images to Train Neural Network","",MessageBoxButtons::OK,
									MessageBoxIcon::Error);
			 }
			 else if((int)numericUpDown1->Value==0){
				 MessageBox::Show("Mention the Number of Images in the Image Folder","",MessageBoxButtons::OK,
									MessageBoxIcon::Error);
			 }
			 else if((int)numericUpDown2->Value==0){
				 MessageBox::Show("Mention the Number of TREE Images in the Image Folder","",MessageBoxButtons::OK,
									MessageBoxIcon::Error);
			 }
			 else{
				 imgp->train(*folderPath, (int)numericUpDown1->Value, (int)numericUpDown2->Value );
			 }
		 }
};
}
