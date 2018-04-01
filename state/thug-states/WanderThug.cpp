
#include "WanderThug.h"
#include "PursueThug.h"
#include "AttackThug.h"

void WanderThug::execute(Character* stateMachine) {

    Character* enemy = stateMachine->seekEnemies();

    // detected an enemy in the field of view
    if (enemy != nullptr) {
        // thug will only worry about health if he's attacking
        if (stateMachine->closeEnoughToAttack(enemy)) {
            stateMachine->changeState(new AttackThug(enemy));

        } else {
            stateMachine->changeState(new PursueThug(enemy));
        }
    }

    State::execute(stateMachine);
}
