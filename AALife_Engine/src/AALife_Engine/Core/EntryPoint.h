#pragma once

#ifdef ALE_PLATFORM_WINDOWS

extern ale::Application* ale::CreateApplication();

int main(int argc, char** argv)
{
	ale::Log::Init();
	ALE_CORE_WARN("Initialized Log!");
	
	//ALE_INFO("Hi! My log system is working? {0}", "123");
	//ALE_ERROR("This is a fatal message");
	//ALE_TRACE("This is a TRACE message");
	auto app = ale::CreateApplication();
	app->Run();
	delete app;
}

#endif