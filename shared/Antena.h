#pragma once
#include "Compnent.h"
class Antena :public Component
{
public:
	Antena(unsigned short port):Component(port) {}

	unsigned short GetOp()override {
		return ANTENNA_TO_MANAGER_CONTROL_MSG_OPCODE;
	}

	bool Valid(ControlMessage cm)override {
		if (cm.header.msgSync != MSG_SYNC)
			return false;
		if (cm.header.Opcode != MANAGER_TO_ANTENNA_CONTROL_MSG_OPCODE)
			return false;
		if (cm.header.msgCounter != lastMessage + 1)
			return false;
		return true;
	}
};

