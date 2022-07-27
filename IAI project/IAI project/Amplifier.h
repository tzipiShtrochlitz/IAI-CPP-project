#pragma once
#include "../../shared/Compnent.h"
class Amplifier:public Component
{
public:
	Amplifier(unsigned short port) :Component(port) {}

	unsigned short GetOp() override{
		return AMPLIFIER_TO_MANAGER_CONTROL_MSG_OPCODE;
	}

	bool Valid(ControlMessage cm)override {
		if (cm.header.msgSync != MSG_SYNC)
			return false;
		if (cm.header.Opcode != MANAGER_TO_AMPLIFIER_CONTROL_MSG_OPCODE)
			return false;
		if (cm.header.msgCounter != lastMessage + 1)
			return false;
		return true;
	}
};

