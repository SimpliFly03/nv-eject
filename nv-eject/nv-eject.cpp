// nv-eject.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#pragma comment (lib, "Setupapi.lib")
#pragma comment (lib, "Cfgmgr32.lib")

#include <iostream>
#include <Windows.h>
#include <Cfgmgr32.h>

int wmain(int argc, wchar_t* argv[]){
    std::cout << "Nv-eject 1.0" << std::endl << std::endl;

    if (argc != 2) {
        std::cout << "[ERROR] Usage: nv-eject.exe <Device instance path>" << std::endl;
        return 0;
    }

    CONFIGRET CMResult = CR_SUCCESS;
    DEVNODE DeviceNode = (DWORD)0;

    DEVINSTID_W DeviceInstanceID = argv[1];

    std::cout << "Locating ";
    std::wcout << DeviceInstanceID;
    std::cout << " ..." << std::endl;

    CMResult = CM_Locate_DevNodeW((PDEVINST)&DeviceNode, DeviceInstanceID, CM_LOCATE_DEVNODE_NORMAL);
    if (CMResult == CR_SUCCESS) {
        std::cout << "[SUCCESS] Device has been successfully located!" << std::endl;
    }
    else {
        std::cout << "[ERROR] Cannot locate device! Please make sure you typed correctly." << std::endl;
        return 1;
    }

    std::cout << "Ejecting ";
    std::wcout << DeviceInstanceID;
    std::cout << " ..." << std::endl;

    CMResult = CM_Request_Device_EjectW(DeviceNode, NULL, NULL, MAX_PATH, 0x0);
    if (CMResult == CR_SUCCESS) {
        std::cout << "[SUCCESS] Device has been successfully ejected!" << std::endl;
    }
    else {
        std::cout << "[ERROR] Cannot eject device!" << std::endl;
        return 1;
    }

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
