#include "pch.h"
#include "TickerHook.h"

Decider* myDecider;

void TickerOut(uintptr_t tickerText)
{
    if (strcmp((char*)tickerText, "         ") != 0)
    {
        myDecider->updateTicker((char*)tickerText);
    }
}

#if _WIN64
// 64bit funcs
// check for two of these
std::vector<BYTE> TickerFunc1_vec = { 0x48, 0x89, 0x5C, 0x24, 0x08, 0x57, 0x48, 0x83, 0xEC, 0x20, 0x48,
0x8B, 0xD9, 0x8B, 0xFA, 0xB9, 0x01, 0x00, 0x00, 0x00 };
__int64(__fastcall* TickerFunc1)(__int64 ticker, int a2) = nullptr;
__int64 __fastcall TickerFunc1_rep(__int64 ticker, int a2)
{
    TickerOut(ticker);

    return TickerFunc1(ticker, a2);
}

std::vector<BYTE> TickerFunc2_vec = { 0x48, 0x89, 0x5C, 0x24, 0x08, 0x48, 0x89, 0x6C, 0x24, 0x10, 0x48,
0x89, 0x74, 0x24, 0x18, 0x57, 0x41, 0x56, 0x41, 0x57, 0x48, 0x83, 0xEC, 0x20, 0x4C, 0x8B, 0xF1, 0x33,
0xF6, 0x8B, 0xCE, 0x85, 0xD2, 0x41, 0x0F, 0xB6, 0xE8, 0x0F, 0x95, 0xC1, 0x83, 0xC1, 0x04 };
__int64(__fastcall* TickerFunc2)(__int64 ticker, int emptyStringFlag, unsigned __int8 a3) = nullptr;
__int64 __fastcall TickerFunc2_rep(__int64 ticker, int emptyStringFlag, unsigned __int8 a3)
{
    if (!emptyStringFlag)
    {
        TickerOut(ticker);
    }

    return TickerFunc2(ticker, emptyStringFlag, a3);
}

// 89 54 24 10 48 89 4C 24 08 48 83 EC 28 B9 01 00 00 00
std::vector<BYTE> TickerFunc3_vec = { 0x89, 0x54, 0x24, 0x10, 0x48, 0x89, 0x4C, 0x24, 0x08, 0x48, 0x83, 0xEC, 0x28, 0xB9, 0x01, 0x00, 0x00, 0x00 };
__int64(__fastcall* TickerFunc3)(__int64 ticker, void* a2) = nullptr;
__int64 __fastcall TickerFunc3_rep(__int64 ticker, void* a2)
{
    TickerOut(ticker);

    return TickerFunc3(ticker, a2);
}

// 44 88 44 24 18 89 54 24  10 48 89 4C 24 08 48 83
// EC 38 83 7C 24 48 00
std::vector<BYTE> TickerFunc4_vec = { 0x44, 0x88, 0x44, 0x24, 0x18, 0x89, 0x54, 0x24, 0x10, 0x48, 0x89, 0x4C, 0x24, 0x08, 0x48, 0x83, 0xEC, 0x38, 0x83, 0x7C, 0x24, 0x48, 0x00 };
__int64(__fastcall* TickerFunc4)(__int64 ticker, void* a2, void* a3) = nullptr;
__int64 __fastcall TickerFunc4_rep(__int64 ticker, void* a2, void* a3)
{
    TickerOut(ticker);

    return TickerFunc4(ticker, a2, a3);
}

#else
// 32bit funcs
std::vector<BYTE> TickerFunc1_vec = { 0xCC, 0x56, 0xB8, 0x01, 0x00, 0x00, 0x00 };
int(__cdecl* TickerFunc1)(int ticker, int a2) = nullptr;
int __cdecl TickerFunc1_rep(int ticker, int a2)
{
    TickerOut(ticker);

    return TickerFunc1(ticker, a2);
}

std::vector<BYTE> TickerFunc2_vec = { 0xCC, 0x8B, 0x44, 0x24, 0x08, 0x53, 0x50, 0x8B, 0x44, 0x24, 0x0C, 0xB3, 0x01 };
int(__cdecl* TickerFunc2)(void* ticker) = nullptr;
int __cdecl TickerFunc2_rep(void* ticker)
{
    TickerOut((uintptr_t)ticker);

    return TickerFunc2(ticker);
}

std::vector<BYTE> TickerFunc3_vec = { 0xCC, 0x56, 0x57, 0xB8, 0x01, 0x00, 0x00, 0x00 };
int(__cdecl* TickerFunc3)(int ticker, int a2) = nullptr;
int __cdecl TickerFunc3_rep(int ticker, int a2)
{
    TickerOut(ticker);

    return TickerFunc3(ticker, a2);
}

std::vector<BYTE> TickerFunc4_vec = { 0xCC, 0x53, 0x56, 0x57, 0xB8, 0x01, 0x00, 0x00, 0x00 };
int(__cdecl* TickerFunc4)(int ticker, int a2) = nullptr;
int __cdecl TickerFunc4_rep(int ticker, int a2)
{
    TickerOut(ticker);

    return TickerFunc4(ticker, a2);
}

std::vector<BYTE> TickerFunc5_vec = { 0xCC, 0x83, 0x7C, 0x24, 0x08, 0x00, 0xB8, 0x05, 0x00, 0x00, 0x00 };
int(__cdecl* TickerFunc5)(BYTE* ticker) = nullptr;
int __cdecl TickerFunc5_rep(BYTE* ticker)
{
    TickerOut((uintptr_t)ticker);

    return TickerFunc5(ticker);
}

// exe funcs below

std::vector<BYTE> TickerFunc6_vec = { 0xCC, 0x56, 0x57, 0x33, 0xC0, 0xB9, 0x83, 0x00, 0x00, 0x00 };
int(__cdecl* TickerFunc6)(const char* ticker, int a2) = nullptr;
int __cdecl TickerFunc6_rep(const char* ticker, int a2)
{
    TickerOut((uintptr_t)ticker);

    return TickerFunc6(ticker, a2);
}

std::vector<BYTE> TickerFunc7_vec = { 0xCC, 0x8B, 0x54, 0x24, 0x08, 0x33, 0xC0, 0x85, 0xD2, 0x0F, 0x95,
0xC0, 0x56, 0x8B, 0x74, 0x24, 0x08, 0x57 };
int(__cdecl* TickerFunc7)(char* ticker, int a2) = nullptr;
int __cdecl TickerFunc7_rep(char* ticker, int a2)
{
    TickerOut((uintptr_t)ticker);

    return TickerFunc7(ticker, a2);
}

std::vector<BYTE> TickerFunc8_vec = { 0x8B, 0xD1, 0xC1, 0xE9, 0x02, 0xB8, 0x20, 0x20, 0x20, 0x20, 0xF3,
0xAB, 0x8B, 0xCA, 0x83, 0xE1, 0x03, 0xF3, 0xAA, 0x5F }; // align -106
int(__cdecl* TickerFunc8)(char* ticker) = nullptr;
int __cdecl TickerFunc8_rep(char* ticker)
{
    TickerOut((uintptr_t)ticker);

    return TickerFunc8(ticker);
}

std::vector<BYTE> TickerFunc9_vec = { 0x56, 0x57, 0x33, 0xC0, 0xB9, 0x41, 0x00, 0x00, 0x00 };
int(__cdecl* TickerFunc9)(const char* ticker, int a2) = nullptr;
int __cdecl TickerFunc9_rep(const char* ticker, int a2)
{
    TickerOut((uintptr_t)ticker);

    return TickerFunc9(ticker, a2);
}

std::vector<BYTE> TickerFunc10_vec = { 0x83, 0xC9, 0xFF, 0x33, 0xC0, 0x83, 0xC4, 0x1C, 0xF2,
0xAE, 0xF7, 0xD1, 0x2B, 0xF9, 0x8B, 0xC1, 0x8B, 0xF7 }; // align -68
int(__cdecl* TickerFunc10)(const char* ticker, int a2) = nullptr;
int __cdecl TickerFunc10_rep(const char* ticker, int a2)
{
    TickerOut((uintptr_t)ticker);

    return TickerFunc10(ticker, a2);
}

std::vector<BYTE> TickerFunc11_vec = { 0x55, 0x56, 0x57, 0x6A, 0x04 };
int(__cdecl* TickerFunc11)(char* ticker) = nullptr;
int __cdecl TickerFunc11_rep(char* ticker)
{
    TickerOut((uintptr_t)ticker);

    return TickerFunc11(ticker);
}

std::vector<BYTE> TickerFunc12_vec = { 0x2B, 0xCD, 0xB8, 0x20, 0x20, 0x20, 0x20, 0x8B, 0xD1,
0xC1, 0xE9, 0x02, 0xF3, 0xAB, 0x8B, 0xCA, 0x83, 0xE1, 0x03, 0xF3, 0xAA }; // align -69
int(__cdecl* TickerFunc12)(char* ticker, int a2) = nullptr;
int __cdecl TickerFunc12_rep(char* ticker, int a2)
{
    TickerOut((uintptr_t)ticker);

    return TickerFunc12(ticker, a2);
}
#endif

void CreateDllHook(MODULEINFO moduleInfo)
{
    int hooksMade = 0;

    std::cout << "Module base address: " << moduleInfo.lpBaseOfDll << std::endl
        << "Module size: " << moduleInfo.SizeOfImage << " bytes" << std::endl;

    BYTE* addrLow = static_cast<BYTE*>(moduleInfo.lpBaseOfDll);
    BYTE* addrHigh = addrLow + moduleInfo.SizeOfImage;

    LOG_DEBUG << "Searching for hook points";

#if _WIN64
    // 64bit hooks
    BYTE* result = std::search(addrLow, addrHigh, TickerFunc1_vec.begin(), TickerFunc1_vec.end());
    if (result != addrHigh)
    {
        hooksMade++;
        LOG_DEBUG << "Found TickerFunc1 at: " << std::hex << (uintptr_t)result << std::endl;
        MH_CreateHook(
            reinterpret_cast<void*>((uintptr_t)result),
            reinterpret_cast<void*>(TickerFunc1_rep),
            reinterpret_cast<void**>(&TickerFunc1)
        );
        result = std::search(result + TickerFunc1_vec.size(), addrHigh, TickerFunc1_vec.begin(), TickerFunc1_vec.end());
        if (result != addrHigh)
        {
            hooksMade++;
            LOG_DEBUG << "Found TickerFunc1 at: " << std::hex << (uintptr_t)result << std::endl;
            MH_CreateHook(
                reinterpret_cast<void*>((uintptr_t)result),
                reinterpret_cast<void*>(TickerFunc1_rep),
                reinterpret_cast<void**>(&TickerFunc1)
            );
        }
    }
    result = std::search(addrLow, addrHigh, TickerFunc2_vec.begin(), TickerFunc2_vec.end());
    if (result != addrHigh)
    {
        hooksMade++;
        LOG_DEBUG << "Found TickerFunc2 at: " << std::hex << (uintptr_t)result << std::endl;
        MH_CreateHook(
            reinterpret_cast<void*>((uintptr_t)result),
            reinterpret_cast<void*>(TickerFunc2_rep),
            reinterpret_cast<void**>(&TickerFunc2)
        );
    }

    result = std::search(addrLow, addrHigh, TickerFunc3_vec.begin(), TickerFunc3_vec.end());
    if (result != addrHigh)
    {
        hooksMade++;
        LOG_DEBUG << "Found TickerFunc3 at: " << std::hex << (uintptr_t)result << std::endl;
        MH_CreateHook(
            reinterpret_cast<void*>((uintptr_t)result),
            reinterpret_cast<void*>(TickerFunc3_rep),
            reinterpret_cast<void**>(&TickerFunc3)
        );

        result = std::search(result + TickerFunc3_vec.size(), addrHigh, TickerFunc3_vec.begin(), TickerFunc3_vec.end());
        if (result != addrHigh)
        {
            hooksMade++;
            LOG_DEBUG << "Found TickerFunc3 at: " << std::hex << (uintptr_t)result << std::endl;
            MH_CreateHook(
                reinterpret_cast<void*>((uintptr_t)result),
                reinterpret_cast<void*>(TickerFunc3_rep),
                reinterpret_cast<void**>(&TickerFunc3)
            );
        }
    }

    result = std::search(addrLow, addrHigh, TickerFunc4_vec.begin(), TickerFunc4_vec.end());
    if (result != addrHigh)
    {
        hooksMade++;
        LOG_INFO << "Found TickerFunc4 at: " << std::hex << (uintptr_t)result << std::endl;
        MH_CreateHook(
            reinterpret_cast<void*>((uintptr_t)result),
            reinterpret_cast<void*>(TickerFunc4_rep),
            reinterpret_cast<void**>(&TickerFunc4)
        );
    }

#else
    // 32bit hooks
    BYTE* result = std::search(addrLow, addrHigh, TickerFunc1_vec.begin(), TickerFunc1_vec.end());
    if (result != addrHigh)
    {
        result += 0x1; // +1 because of the CC
        hooksMade++;
        std::cout << "Found TickerFunc1 at: " << std::hex << (uintptr_t)result << std::endl;
        MH_CreateHook(
            reinterpret_cast<void*>((uintptr_t)result),
            reinterpret_cast<void*>(TickerFunc1_rep),
            reinterpret_cast<void**>(&TickerFunc1)
        );
        result = std::search(result + TickerFunc1_vec.size(), addrHigh, TickerFunc1_vec.begin(), TickerFunc1_vec.end());
        if (result != addrHigh)
        {
            result += 0x1; // +1 because of the CC
            hooksMade++;
            std::cout << "Found TickerFunc1 at: " << std::hex << (uintptr_t)result << std::endl;
            MH_CreateHook(
                reinterpret_cast<void*>((uintptr_t)result),
                reinterpret_cast<void*>(TickerFunc1_rep),
                reinterpret_cast<void**>(&TickerFunc1)
            );
        }
    }

    result = std::search(addrLow, addrHigh, TickerFunc2_vec.begin(), TickerFunc2_vec.end());
    if (result != addrHigh)
    {
        result += 0x1; // +1 because of the CC
        hooksMade++;
        std::cout << "Found TickerFunc2 at: " << std::hex << (uintptr_t)result << std::endl;
        MH_CreateHook(
            reinterpret_cast<void*>((uintptr_t)result),
            reinterpret_cast<void*>(TickerFunc2_rep),
            reinterpret_cast<void**>(&TickerFunc2)
        );
    }

    result = std::search(addrLow, addrHigh, TickerFunc3_vec.begin(), TickerFunc3_vec.end());
    if (result != addrHigh)
    {
        result += 0x1; // +1 because of the CC
        hooksMade++;
        std::cout << "Found TickerFunc3 at: " << std::hex << (uintptr_t)result << std::endl;
        MH_CreateHook(
            reinterpret_cast<void*>((uintptr_t)result),
            reinterpret_cast<void*>(TickerFunc3_rep),
            reinterpret_cast<void**>(&TickerFunc3)
        );
        result = std::search(result + TickerFunc3_vec.size(), addrHigh, TickerFunc3_vec.begin(), TickerFunc3_vec.end());
        if (result != addrHigh)
        {
            result += 0x1; // +1 because of the CC
            hooksMade++;
            std::cout << "Found TickerFunc3 at: " << std::hex << (uintptr_t)result << std::endl;
            MH_CreateHook(
                reinterpret_cast<void*>((uintptr_t)result),
                reinterpret_cast<void*>(TickerFunc3_rep),
                reinterpret_cast<void**>(&TickerFunc3)
            );
        }
    }

    result = std::search(addrLow, addrHigh, TickerFunc4_vec.begin(), TickerFunc4_vec.end());
    if (result != addrHigh)
    {
        result += 0x1; // +1 because of the CC
        hooksMade++;
        std::cout << "Found TickerFunc4 at: " << std::hex << (uintptr_t)result << std::endl;
        MH_CreateHook(
            reinterpret_cast<void*>((uintptr_t)result),
            reinterpret_cast<void*>(TickerFunc4_rep),
            reinterpret_cast<void**>(&TickerFunc4)
        );
    }

    result = std::search(addrLow, addrHigh, TickerFunc5_vec.begin(), TickerFunc5_vec.end());
    if (result != addrHigh)
    {
        result += 0x1; // +1 because of the CC
        hooksMade++;
        std::cout << "Found TickerFunc5 at: " << std::hex << (uintptr_t)result << std::endl;
        MH_CreateHook(
            reinterpret_cast<void*>((uintptr_t)result),
            reinterpret_cast<void*>(TickerFunc5_rep),
            reinterpret_cast<void**>(&TickerFunc5)
        );
    }
#endif
    LOG_INFO << "Hooked " << hooksMade << " functions" << std::endl;

    MH_EnableHook(MH_ALL_HOOKS);
}

#if _WIN64
#else
void CreateExeHook(MODULEINFO moduleInfo)
{
    int hooksMade = 0;
    bool found7 = false;

    LOG_DEBUG << "Module base address: " << moduleInfo.lpBaseOfDll << std::endl
        << "Module size: " << moduleInfo.SizeOfImage << " bytes" << std::endl;

    BYTE* addrLow = static_cast<BYTE*>(moduleInfo.lpBaseOfDll);
    BYTE* addrHigh = addrLow + moduleInfo.SizeOfImage;

    LOG_DEBUG << "Searching for hook points" << std::endl;

    BYTE* result = std::search(addrLow, addrHigh, TickerFunc3_vec.begin(), TickerFunc3_vec.end());
    if (result != addrHigh)
    {
        result += 0x1; // +1 because of the CC
        hooksMade++;
        LOG_DEBUG << "Found TickerFunc3 at: " << std::hex << (uintptr_t)result << std::endl;
        MH_CreateHook(
            reinterpret_cast<void*>((uintptr_t)result),
            reinterpret_cast<void*>(TickerFunc3_rep),
            reinterpret_cast<void**>(&TickerFunc3)
        );
        result = std::search(result + TickerFunc3_vec.size(), addrHigh, TickerFunc3_vec.begin(), TickerFunc3_vec.end());
        if (result != addrHigh)
        {
            result += 0x1; // +1 because of the CC
            hooksMade++;
            LOG_DEBUG << "Found TickerFunc3 at: " << std::hex << (uintptr_t)result << std::endl;
            MH_CreateHook(
                reinterpret_cast<void*>((uintptr_t)result),
                reinterpret_cast<void*>(TickerFunc3_rep),
                reinterpret_cast<void**>(&TickerFunc3)
            );
        }
    }

    result = std::search(addrLow, addrHigh, TickerFunc5_vec.begin(), TickerFunc5_vec.end());
    if (result != addrHigh)
    {
        result += 0x1; // +1 because of the CC
        hooksMade++;
        LOG_DEBUG << "Found TickerFunc5 at: " << std::hex << (uintptr_t)result << std::endl;
        MH_CreateHook(
            reinterpret_cast<void*>((uintptr_t)result),
            reinterpret_cast<void*>(TickerFunc5_rep),
            reinterpret_cast<void**>(&TickerFunc5)
        );
    }

    result = std::search(addrLow, addrHigh, TickerFunc6_vec.begin(), TickerFunc6_vec.end());
    if (result != addrHigh)
    {
        result += 0x1; // +1 because of the CC
        hooksMade++;
        LOG_DEBUG << "Found TickerFunc6 at: " << std::hex << (uintptr_t)result << std::endl;
        MH_CreateHook(
            reinterpret_cast<void*>((uintptr_t)result),
            reinterpret_cast<void*>(TickerFunc6_rep),
            reinterpret_cast<void**>(&TickerFunc6)
        );
        result = std::search(result + TickerFunc6_vec.size(), addrHigh, TickerFunc6_vec.begin(), TickerFunc6_vec.end());
        if (result != addrHigh)
        {
            result += 0x1; // +1 because of the CC
            hooksMade++;
            LOG_DEBUG << "Found TickerFunc6 at: " << std::hex << (uintptr_t)result << std::endl;
            MH_CreateHook(
                reinterpret_cast<void*>((uintptr_t)result),
                reinterpret_cast<void*>(TickerFunc6_rep),
                reinterpret_cast<void**>(&TickerFunc6)
            );
        }
    }

    result = std::search(addrLow, addrHigh, TickerFunc7_vec.begin(), TickerFunc7_vec.end());
    if (result != addrHigh)
    {
        found7 = true;
        result += 0x1; // +1 because of the CC
        hooksMade++;
        LOG_DEBUG << "Found TickerFunc7 at: " << std::hex << (uintptr_t)result << std::endl;
        MH_CreateHook(
            reinterpret_cast<void*>((uintptr_t)result),
            reinterpret_cast<void*>(TickerFunc7_rep),
            reinterpret_cast<void**>(&TickerFunc7)
        );
    }

    if (!found7)
    {
        result = std::search(addrLow, addrHigh, TickerFunc8_vec.begin(), TickerFunc8_vec.end());
        if (result != addrHigh)
        {
            result -= 106; // align -106
            hooksMade++;
            LOG_DEBUG << "Found TickerFunc8 at: " << std::hex << (uintptr_t)result << std::endl;
            MH_CreateHook(
                reinterpret_cast<void*>((uintptr_t)result),
                reinterpret_cast<void*>(TickerFunc8_rep),
                reinterpret_cast<void**>(&TickerFunc8)
            );
        }
    }
    result = std::search(addrLow, addrHigh, TickerFunc9_vec.begin(), TickerFunc9_vec.end());
    if (result != addrHigh)
    {
        hooksMade++;
        LOG_DEBUG << "Found TickerFunc9 at: " << std::hex << (uintptr_t)result << std::endl;
        MH_CreateHook(
            reinterpret_cast<void*>((uintptr_t)result),
            reinterpret_cast<void*>(TickerFunc9_rep),
            reinterpret_cast<void**>(&TickerFunc9)
        );
        result = std::search(result + TickerFunc9_vec.size(), addrHigh, TickerFunc9_vec.begin(), TickerFunc9_vec.end());
        if (result != addrHigh)
        {
            hooksMade++;
            LOG_DEBUG << "Found TickerFunc9 at: " << std::hex << (uintptr_t)result << std::endl;
            MH_CreateHook(
                reinterpret_cast<void*>((uintptr_t)result),
                reinterpret_cast<void*>(TickerFunc9_rep),
                reinterpret_cast<void**>(&TickerFunc9)
            );
        }
    }

    result = std::search(addrLow, addrHigh, TickerFunc10_vec.begin(), TickerFunc10_vec.end());
    if (result != addrHigh)
    {
        result -= 68;
        hooksMade++;
        LOG_DEBUG << "Found TickerFunc10 at: " << std::hex << (uintptr_t)result << std::endl;
        MH_CreateHook(
            reinterpret_cast<void*>((uintptr_t)result),
            reinterpret_cast<void*>(TickerFunc10_rep),
            reinterpret_cast<void**>(&TickerFunc10)
        );
        result = std::search(result + 69 + TickerFunc10_vec.size(), addrHigh, TickerFunc10_vec.begin(), TickerFunc10_vec.end());
        if (result != addrHigh)
        {
            result -= 68;
            hooksMade++;
            LOG_DEBUG << "Found TickerFunc10 at: " << std::hex << (uintptr_t)result << std::endl;
            MH_CreateHook(
                reinterpret_cast<void*>((uintptr_t)result),
                reinterpret_cast<void*>(TickerFunc10_rep),
                reinterpret_cast<void**>(&TickerFunc10)
            );
        }
    }

    result = std::search(addrLow, addrHigh, TickerFunc11_vec.begin(), TickerFunc11_vec.end());
    if (result != addrHigh)
    {
        hooksMade++;
        LOG_DEBUG << "Found TickerFunc11 at: " << std::hex << (uintptr_t)result << std::endl;
        MH_CreateHook(
            reinterpret_cast<void*>((uintptr_t)result),
            reinterpret_cast<void*>(TickerFunc11_rep),
            reinterpret_cast<void**>(&TickerFunc11)
        );
    }

    result = std::search(addrLow, addrHigh, TickerFunc12_vec.begin(), TickerFunc12_vec.end());
    if (result != addrHigh)
    {
        result -= 69;
        hooksMade++;
        LOG_DEBUG << "Found TickerFunc12 at: " << std::hex << (uintptr_t)result << std::endl;
        MH_CreateHook(
            reinterpret_cast<void*>((uintptr_t)result),
            reinterpret_cast<void*>(TickerFunc12_rep),
            reinterpret_cast<void**>(&TickerFunc12)
        );
    }

    LOG_INFO << "Hooked " << hooksMade << " functions" << std::endl;

    MH_EnableHook(MH_ALL_HOOKS);
}
#endif

bool DetectModuleAndCreateHook(Decider *decider)
{
    myDecider = decider;

    unsigned int hooksMade = 0;
    MODULEINFO moduleInfo;

    HMODULE bm2dxModule = GetModuleHandleA("bm2dx.dll");
    if (bm2dxModule != nullptr) {
        GetModuleInformation(GetCurrentProcess(), bm2dxModule, &moduleInfo, sizeof(moduleInfo));
        CreateDllHook(moduleInfo);
        return true;
    }

    bm2dxModule = GetModuleHandleA("bm2dx_omni.dll");
    if (bm2dxModule != nullptr) {
        GetModuleInformation(GetCurrentProcess(), bm2dxModule, &moduleInfo, sizeof(moduleInfo));
        CreateDllHook(moduleInfo);
        return true;
    }

    bm2dxModule = GetModuleHandleA("bm2dx.exe");
    if (bm2dxModule != nullptr) {
        GetModuleInformation(GetCurrentProcess(), bm2dxModule, &moduleInfo, sizeof(moduleInfo));
#if _WIN64
#else
        CreateExeHook(moduleInfo);
#endif
        return true;
    }

    LOG_FATAL << "No hookable module found!" << endl;

    return false;
}