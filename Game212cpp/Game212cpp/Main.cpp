#include "Application.h"

int main(int argc, char* args[])
{
	Application::InitSingleton();

	if (Application::GetInstance().init())
	{
		Application::GetInstance().run();
		Application::GetInstance().close();
	}

	Application::DeinitSingleton();

	return 0;
};