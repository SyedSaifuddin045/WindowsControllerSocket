#include <windows.h>
#include <xinput.h>
#include <iostream>
#include <iomanip>

#pragma comment(lib, "xinput.lib")

// Helper function to print analog stick values
void printStickValues(const char* stickName, SHORT x, SHORT y) {
    std::cout << stickName << ": X = " << std::setw(6) << x
        << " Y = " << std::setw(6) << y << std::endl;
}

// Helper function to check if a specific button is pressed
bool isButtonPressed(WORD buttons, WORD button) {
    return (buttons & button) != 0;
}

int main() {
    XINPUT_STATE state;

    std::cout << "Starting controller input reader..." << std::endl;
    std::cout << "Press Ctrl+C to exit" << std::endl << std::endl;

    while (true) {
        // Clear the state
        ZeroMemory(&state, sizeof(XINPUT_STATE));

        // Get the state of controller 0
        DWORD result = XInputGetState(0, &state);

        if (result == ERROR_SUCCESS) {
            system("cls"); // Clear console (Windows-specific)
            std::cout << "Controller connected:\n" << std::endl;

            // Print analog stick positions
            printStickValues("Left Stick ", state.Gamepad.sThumbLX, state.Gamepad.sThumbLY);
            printStickValues("Right Stick", state.Gamepad.sThumbRX, state.Gamepad.sThumbRY);

            // Print trigger values
            std::cout << "Left Trigger: " << std::setw(3)
                << static_cast<int>(state.Gamepad.bLeftTrigger) << std::endl;
            std::cout << "Right Trigger: " << std::setw(3)
                << static_cast<int>(state.Gamepad.bRightTrigger) << std::endl;

            // Print button states
            std::cout << "\nButtons pressed:" << std::endl;
            if (isButtonPressed(state.Gamepad.wButtons, XINPUT_GAMEPAD_A))
                std::cout << "A ";
            if (isButtonPressed(state.Gamepad.wButtons, XINPUT_GAMEPAD_B))
                std::cout << "B ";
            if (isButtonPressed(state.Gamepad.wButtons, XINPUT_GAMEPAD_X))
                std::cout << "X ";
            if (isButtonPressed(state.Gamepad.wButtons, XINPUT_GAMEPAD_Y))
                std::cout << "Y ";
            if (isButtonPressed(state.Gamepad.wButtons, XINPUT_GAMEPAD_LEFT_SHOULDER))
                std::cout << "LB ";
            if (isButtonPressed(state.Gamepad.wButtons, XINPUT_GAMEPAD_RIGHT_SHOULDER))
                std::cout << "RB ";
            if (isButtonPressed(state.Gamepad.wButtons, XINPUT_GAMEPAD_START))
                std::cout << "START ";
            if (isButtonPressed(state.Gamepad.wButtons, XINPUT_GAMEPAD_BACK))
                std::cout << "BACK ";
            if (isButtonPressed(state.Gamepad.wButtons, XINPUT_GAMEPAD_DPAD_UP))
                std::cout << "D-UP ";
            if (isButtonPressed(state.Gamepad.wButtons, XINPUT_GAMEPAD_DPAD_DOWN))
                std::cout << "D-DOWN ";
            if (isButtonPressed(state.Gamepad.wButtons, XINPUT_GAMEPAD_DPAD_LEFT))
                std::cout << "D-LEFT ";
            if (isButtonPressed(state.Gamepad.wButtons, XINPUT_GAMEPAD_DPAD_RIGHT))
                std::cout << "D-RIGHT ";
            std::cout << std::endl;
        }
        else {
            system("cls");
            std::cout << "No controller detected. Please connect an Xbox controller." << std::endl;
        }

        Sleep(16);
    }

    return 0;
}