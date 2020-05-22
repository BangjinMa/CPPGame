#include <iostream>
#include "IApplication.h"
#include "MemoryManager.h"
#include "InputManager.h"
using namespace GameEngine;

namespace GameEngine{
	extern IApplication*    g_pApp;
    extern MemoryManager*   g_pMemoryManager;
	extern InputManager*   g_pInputManager;
}
int main(int argc, char* argv[])
{
	for (int i = 0; i < argc; i++)
		printf(argv[i]);

	int ret;

	if ((ret = g_pApp->Initialize()) != 0) {
		printf("App Initialize failed, will exit now.");
		return ret;
	}

	if ((ret = g_pMemoryManager->Initialize()) != 0) {
		printf("App Initialize failed, will exit now.");
		return ret;
	}

	if ((ret = g_pInputManager->Initialize()) != 0) {
		printf("App Initialize failed, will exit now.");
		return ret;
	}

	while (!g_pApp->IsQuit()) {
		g_pApp->Tick();
		g_pMemoryManager->Tick();
		g_pInputManager->Tick();
	}

	g_pApp->Finalize();
	g_pMemoryManager->Finalize();
	g_pInputManager->Finalize();
	return 0;
}