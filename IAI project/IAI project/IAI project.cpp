// IAI project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <thread>
#include "pch.h"
#include <iostream>
#include "../../shared/Manager.h"
#include "../../shared/Modem.h"
#include <vector>
#include "../../shared/Antena.h"
#include "Amplifier.h"



int main()
{
    Modem mod(MODEM_TRANSMITTER_PORT);
    Antena a(ANTENA_TRANSMITTER_PORT);
    Amplifier amp(AMPLIFIER_TRANSMITTER_PORT);
    //the cmponents
    Controller c;
    c.opCode = MANAGER_TO_MODEM_CONTROL_MSG_OPCODE;
    c.port = MODEM_TRANSMITTER_PORT;
    Controller c2;
    c2.opCode = MANAGER_TO_AMPLIFIER_CONTROL_MSG_OPCODE;
    c2.port = AMPLIFIER_TRANSMITTER_PORT;
    Controller c3;
    c3.opCode = MANAGER_TO_ANTENNA_CONTROL_MSG_OPCODE;
    c3.port = ANTENA_TRANSMITTER_PORT;
    vector<Controller> vec = { c,c2,c3 };
    Manager m(vec,MANAGER_TRANSMITTER_GET_PORT, MANAGER_TRANSMITTER_SEND_PORT);
    while (true);
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
