// Message generator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <thread>
#include "MessageGenerator.h"
using namespace std;

string flag;

//always check if the user enter "stop" to stop and submit
void stop() {
    while(true) {
        string s;
        cin >> s;
        if (s.compare("stop") == 0)
            flag = "no";
    }
}

int main()
{
    cout << "want to start?";
    cin >> flag;
    if(flag.compare("yes") == 0) {
        //start the action of the message generator
        MessageGenerator m;
        thread s(stop);
        s.detach();
        while (true) {
            if (flag.compare("no")==0)
            {
                m.submit();
                exit(0);
            }
        }
    }
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
