#pragma once
#include <atomic>
class Payloads
{
public: 
	static std::atomic<bool> ScreenShakeStop;
	static void MouseShake();
	static void ScreenShake();
	static void ReverseText();
	static void RandomErrors();
	static void DisplayBugs();
	static void DisplayArtifacts();
	static void OpenRandomApps();
};

