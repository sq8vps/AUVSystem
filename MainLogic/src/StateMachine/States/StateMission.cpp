#include "StateMission.h"
#include <iostream>
#include <utility>

StateReturnType StateMission::process()
{
	return { StateProcessed::pushChild, *this->childStates.begin() };
}
void StateMission::checkExitCondition() {}
