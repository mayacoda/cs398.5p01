
#include "WanderState.h"


void WanderState::enter(Character* stateMachine) {
    stateMachine->turnOnBehavior(SteeringBehaviors::fWander);
    State::enter(stateMachine);
}

void WanderState::exit(Character* stateMachine) {
    stateMachine->turnOffBehavior(SteeringBehaviors::fWander);
    State::exit(stateMachine);
}

