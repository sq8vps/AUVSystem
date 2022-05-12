#pragma once

#include "CommonEnums.h"
#include "StateBase.h"
#include "StateEnums.h"

#include "jsonCommonFunctions.h"

class StateTask1 : public StateBase
{
private:
protected:
public:
	explicit StateTask1( LogicCommonData* const data, AdditionalDataParameter param, StateBase* const parentState )
	    : StateBase( parentState, data, StateLevel::intermediate, StateType::task1, param )
	{
		this->childStates.insert( this->childStates.begin(),
		                          { StateType::diveToDepth, StateType::findGate, StateType::goLittleTowardsGate } );
	}
	void checkExitCondition() override;
};