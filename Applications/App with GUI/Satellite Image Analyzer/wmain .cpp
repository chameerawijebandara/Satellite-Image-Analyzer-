#include "Main.h"

using namespace System;
using namespace System::Windows::Forms;

void wmain()
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	SatelliteImageAnalyzer::Main form;
	Application::Run(%form);
}