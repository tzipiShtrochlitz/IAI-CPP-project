#pragma once
#include <thread>
#include "../../shared/UDPsocket.h"
class MessageGenerator
{
	int return_messages_counter = 0;
	int count = 0;
public:
	/// <summary>
	/// send data messages to the manager of the transmitter
	/// </summary>
	void send(UDPsocket socket) {
		while (true) {
			this_thread::sleep_for(chrono::seconds(1));
			ControlMessage cm;
			cm.header.msgCounter = count;
			cm.header.msgSync = MSG_SYNC;
			cm.header.Opcode = DATA_MSG_OPCODE;
			if (!socket.Send(cm, MANAGER_TRANSMITTER_GET_PORT)) {
				cout << "cant send message" << endl;
			}
			else {
				count++;
			}
		}
	}

	/// <summary>
	/// get the return data messages from the modem of the reciver
	/// </summary>
	void get(UDPsocket socket) {
		while (count>0) {
			sendedMessage sm = socket.Get();
			if (sm.message.header.msgSync == MSG_SYNC && sm.message.header.Opcode == DATA_MSG_OPCODE)
				return_messages_counter++;
		}
	}

	/// <summary>
	/// print the submition
	/// </summary>
	void submit() {
		if (count>0 && count == return_messages_counter)
			cout << "all the messages are returned" << endl;
		cout << count << " messages are sended, " << return_messages_counter << "messages are return\n";
	}

	MessageGenerator() {
		UDPsocket socket();
		thread send(&MessageGenerator::send, this,socket);
		thread get(&MessageGenerator::get, this,socket);
		send.detach();
		get.detach();
	}

	~MessageGenerator() {
	}
};

