// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "TickerHook.h"

Logger logger;
boost::property_tree::ptree ptree;

DWORD WINAPI Initialize(LPVOID hModule)
{
    Decider *decider = new Decider();

    // Get path to ini file
    LPWSTR path = new WCHAR[MAX_PATH];
    GetModuleFileName((HMODULE)hModule, path, MAX_PATH);
    string pathStr = string(CW2A(path));

    // Use whatever the dll file name is to locate the INI file
    // This allows multiple dll to be hooked with different configuration
    pathStr.replace(pathStr.length() - 4, 4, ".ini");
    LOG_DEBUG << "INI path: " << pathStr << endl;

    try {
        boost::property_tree::ini_parser::read_ini(pathStr, ptree);
        decider->initSceneMap(ptree);
        wsInit(ptree);
    }
    catch (std::exception const& e) {
        LOG_ERROR << "Cannot load INI file: " << e.what() << endl;
    }

    bool hasCreatedHook = DetectModuleAndCreateHook(decider);

    if (!hasCreatedHook) {
        return EXIT_FAILURE;
    }

    // Initialize WebSocket
    wsConnect();

    return EXIT_SUCCESS;
}

BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    {
        AllocConsole();
        freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);

        MH_Initialize();

        Logger::init();

        CreateThread(NULL, NULL, Initialize, hModule, NULL, NULL);
    }
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

