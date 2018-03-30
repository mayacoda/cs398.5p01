
#ifndef DZ04_STALKSNEAK_H
#define DZ04_STALKSNEAK_H


#include <iostream>
#include "../State.h"

class StalkSneak : public State {
private:
    Character* m_enemy;

public:

    StalkSneak(Character* m_enemy) : m_enemy(m_enemy) {}

    void enter(Character* stateMachine) override {
        std::cout << "entering stalk" << std::endl;
        State::enter(stateMachine);
    }

    void exit(Character* stateMachine) override {
        std::cout << "exiting stalk" << std::endl;
        State::exit(stateMachine);
    }

    void execute(Character* stateMachine) override {
        State::execute(stateMachine);
    }
};


#endif //DZ04_STALKSNEAK_H
