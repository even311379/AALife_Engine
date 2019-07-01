#pragma once

#ifdef ALE_PLATFORM_WINDOWS

extern ale::Application* ale::CreateApplication();

int main(int argc, char** argv)
{
	auto app = ale::CreateApplication();
	app->Run();
	delete app;
}

#endif