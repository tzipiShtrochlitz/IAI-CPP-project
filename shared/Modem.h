#pragma once
#include "Compnent.h"
class Modem:public Component
{
public:
	Modem(unsigned short port):Component(port){}

	unsigned short GetOp() override{
		return MODEM_TO_MANAGER_CONTROL_MSG_OPCODE;
	}

	bool Valid(ControlMessage cm) override{
		if (cm.header.msgSync != MSG_SYNC)
			return false;
		if (cm.header.Opcode == MANAGER_TO_MODEM_CONTROL_MSG_OPCODE)
		{
			if (cm.header.msgCounter !=lastMessage + 1)
				return false;
		}
		else if (cm.header.Opcode != DATA_MSG_OPCODE) {
			return false;
		}
		return true;
	}
};

