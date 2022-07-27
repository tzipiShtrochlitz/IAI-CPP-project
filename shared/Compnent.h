#pragma once
#include "UDPsocket.h"
#include <thread>

//one cmponent in the whole item- abstract class
class Component
{
protected:
	int lastMessage=-1;

public:
	/// <summary>
	/// check if the message is valid
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	virtual bool Valid(ControlMessage) = 0 ;
	/// <summary>
	/// get a opcode to return the message
	/// </summary>
	/// <returns></returns>
	virtual unsigned short GetOp() = 0;
	
	Component(unsigned short port) {
		
		thread t(&Component::Act, this, port);
		t.detach();
	}
	
	/// <summary>
	/// the action of the component
	/// </summary>
	/// <param name="port"></param>
	/// <param name="socket"></param>
	void Act(unsigned short port) {
		UDPsocket socket;
		socket.Bind(port);
		while (true) {
			//wait for a message for another component
			sendedMessage mes = socket.Get();
			//if it is control message check if it is valid and return to the manager
			if (mes.message.header.Opcode != DATA_MSG_OPCODE) {
				if (Valid(mes.message)) mes.message.Ack = 1;else mes.message.Ack = 0;
				mes.message.header.Opcode = this->GetOp();
				if (mes.port == ANTENA_TRANSMITTER_PORT || mes.port == MODEM_TRANSMITTER_PORT || mes.port == AMPLIFIER_TRANSMITTER_PORT)
					mes.port = MANAGER_TRANSMITTER_GET_PORT;
				else
					mes.port = MANAGER_RECIVER_GET_PORT;
			}
			//if it is data message send to the next component for data
			else {
				if (mes.port == MODEM_TRANSMITTER_PORT)
					mes.port = MODEM_RECIVER_PORT;
				else
					mes.port = MANAGER_RECIVER_GET_PORT;
			}
			socket.Send(mes.message, mes.port);
		}
	}

	~Component() {
	}
};

