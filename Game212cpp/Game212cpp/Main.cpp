#include "Application.h"

int main(int argc, char* args[])
{
	Application::Initialize();

	if (Application::GetInstance().init())
	{
		Application::GetInstance().run();
		Application::GetInstance().close();
	}

	Application::Deinitialize();

	return 0;
};