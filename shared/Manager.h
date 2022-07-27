#pragma once
#include "UDPsocket.h"
#include <vector>
#include <thread>
class Manager
{

	// the components to send them control messages
	vector<Controller> controllers;
	//list for save the messages that send from the manager
	vector<sendedMessage> lst = {};
	int time = 0;

public:
	/// <summary>
	/// send a message every second 
	/// </summary>
	/// <param name="socket"></param>
	void SendMsgs(UDPsocket socket) {
		while (true) {
			this_thread::sleep_for(chrono::seconds(1));
			for (int i = 0; i < controllers.size(); i++) {
				ControlMessage cm;
				cm.Ack = 0;
				cm.header.msgCounter = time;
				cm.header.msgSync = MSG_SYNC;
				cm.header.Opcode = controllers[i].opCode;
				//true if the sending has error
				if (!socket.Send(cm, controllers[i].port))
				{
					cout << "problem to send message\n";
				}
				else {
					sendedMessage s{ controllers[i].port,cm };
					lst.push_back(s);
				}
			}
			time++;
		}
	}

	/// <summary>
	/// wait for returned messages and check if valid
	///for data messages send to the next station
	/// </summary>
	/// <param name="socket"></param>
	void GetMsgs(UDPsocket socket) {
		while (true) {
			if (!lst.empty()) {
				sendedMessage sm = socket.Get();
				//contrl messages reciving
				if (sm.message.header.Opcode != DATA_MSG_OPCODE) {
					for (size_t i = 0; i < lst.size(); i++) {
						if (lst[i].port == sm.port && lst[i].message.header.msgCounter == sm.message.header.msgCounter)
						{
							lst.erase(lst.begin() + i);
							cout << "get message " << sm.message.header.Opcode << endl;
						}
					}
				}
				//data messages sending
				else {
					if (sm.port == MANAGER_TRANSMITTER_SEND_PORT)
					{
						socket.Send(sm.message, MODEM_TRANSMITTER_PORT);
					}
					else {
						socket.Send(sm.message, MESSAGE_GENERATOR_PORT);
					}
				}
			}
		}
	}


/// <summary>
/// check if there are messages from more then 5 seconds
/// </summary>
void CheckTheList() {
	while (true) {
		this_thread::sleep_for(chrono::seconds(4));
		for (size_t i = 0; i < lst.size(); i++) {
			if (lst[i].message.header.msgCounter + 5 < time)
			{
				cout << "dont get a answer from port " << lst[i].port << endl;
				lst.erase(lst.begin() + i);
			}
		}
	}
}

Manager(vector<Controller> controllers,unsigned short get_port, unsigned short send_port) {

	thread t(&Manager::Act, this, controllers,get_port,send_port);
	t.detach();
}

void Act(vector<Controller> controllers, unsigned short get_port, unsigned short send_port) {
	UDPsocket send_socket;
	UDPsocket get_socket;
	get_socket.Bind(get_port);
	this->lst = {};
	this->controllers = controllers;
	thread send(&Manager::SendMsgs, this, send_socket);
	thread get(&Manager::GetMsgs, this, get_socket);
	thread check(&Manager::CheckTheList, this);
	send.detach();
	get.detach();
	check.detach();
	while (true);
}
};

