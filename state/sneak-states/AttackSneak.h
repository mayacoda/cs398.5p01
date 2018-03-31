
#ifndef DZ04_ATTACKSNEAK_H
#define DZ04_ATTACKSNEAK_H


#include <iostream>
#include "../State.h"
#include "WanderSneak.h"
#include "EvadeSneak.h"

class AttackSneak : public State {
private:
    Character* m_enemy;
public:
    AttackSneak(Character* m_enemy) : m_enemy(m_enemy) {}

    void enter(Character* stateMachine) override {
        std::cout << "entering attack mode!" << std::endl;
        State::enter(stateMachine);
    }

    void exit(Character* stateMachine) override {
        std::cout << "exiting attack mode!" << std::endl;
        State::exit(stateMachine);
    }

    void execute(Character* stateMachine) override {

        // opponent has been defeated
        if (m_enemy->isDead()) {
            stateMachine->changeState(new WanderSneak());

            // players health has gotten too low
        } else if (stateMachine->getHealthRatio() <= .25) {
            stateMachine->changeState(new EvadeSneak(m_enemy));

            // otherwise keep attacking
        } else {
            // enemy is close enough to attack
            if (stateMachine->closeEnoughToAttack(m_enemy)) {
                stateMachine->attackRanged(m_enemy->getPos());
            } else {
                // if enemy is too far away, stalk it
                stateMachine->changeState(new StalkSneak(m_enemy));
            }
        }


        State::execute(stateMachine);
    }
};


#endif //DZ04_ATTACKSNEAK_H
