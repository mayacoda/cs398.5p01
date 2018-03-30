
#ifndef DZ04_ATTACKSNEAK_H
#define DZ04_ATTACKSNEAK_H


#include <iostream>
#include "../State.h"

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
        // check if character is facing the enemy

        // if they aren't, turn them

        // else attack
        stateMachine->attackRanged(m_enemy->getPos());


        State::execute(stateMachine);
    }
};


#endif //DZ04_ATTACKSNEAK_H
