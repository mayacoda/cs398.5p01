
#ifndef DZ04_STALKSNEAK_H
#define DZ04_STALKSNEAK_H


#include <iostream>
#include "../State.h"

class StalkSneak : public State {
private:
    Character* m_enemy;
    Vector2D<double> m_enemyPos;

    bool m_pathInitialized;
    double m_recalculateThreshold;

public:

    StalkSneak(Character* m_enemy) : m_enemy(m_enemy) {
        m_recalculateThreshold = 150;
        m_pathInitialized = false;
    }

    void enter(Character* stateMachine) override {
        if (globals::debug) std::cout << *stateMachine << "enter stalk sneak" << std::endl;
        stateMachine->turnOnBehavior(SteeringBehaviors::fFollow_path);
        stateMachine->setPath(new Path(stateMachine->getPos()));
        m_enemyPos = m_enemy->getPos();
        State::enter(stateMachine);
    }

    void exit(Character* stateMachine) override {
        if (globals::debug) std::cout << *stateMachine << "exit stalk sneak" << std::endl;
        stateMachine->turnOffBehavior(SteeringBehaviors::fFollow_path);
        State::exit(stateMachine);
    }

    void execute(Character* stateMachine) override;
};

#endif //DZ04_STALKSNEAK_H
