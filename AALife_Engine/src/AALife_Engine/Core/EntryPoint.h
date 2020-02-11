#pragma once

#ifdef ALE_PLATFORM_WINDOWS

extern ale::Application* ale::CreateApplication();

int main(int argc, char** argv)
{
	ale::Log::Init();
	ALE_CORE_WARN("Initialized Log!");
	
    ALE_PROFILE_BEGIN_SESSION("Startup", "aleProfile-Startup.json");
	auto app = ale::CreateApplication();
    ALE_PROFILE_END_SESSION();

    ALE_PROFILE_BEGIN_SESSION("Runtime", "aleProfile-Runtime.json");
	app->Run();
    ALE_PROFILE_END_SESSION();

    ALE_PROFILE_BEGIN_SESSION("Shutdown", "aleProfile-Shutdown.json");
	delete app;
    ALE_PROFILE_END_SESSION();
}

#endif