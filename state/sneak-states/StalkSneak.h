
#ifndef DZ04_STALKSNEAK_H
#define DZ04_STALKSNEAK_H


#include <iostream>
#include "../State.h"

class StalkSneak : public State {
private:
    Character* m_enemy;
    Vector2D<double> m_enemyPos;
    double m_recalculateThreshold = 30;

public:

    StalkSneak(Character* m_enemy) : m_enemy(m_enemy) {}

    void enter(Character* stateMachine) override {
        std::cout << "entering stalk" << std::endl;
        stateMachine->turnOnBehavior(SteeringBehaviors::fFollow_path);
        stateMachine->setPath(new Path(stateMachine->getPos()));
        m_enemyPos = m_enemy->getPos();
        State::enter(stateMachine);
    }

    void exit(Character* stateMachine) override {
        std::cout << "exiting stalk" << std::endl;
        stateMachine->turnOffBehavior(SteeringBehaviors::fFollow_path);
        State::exit(stateMachine);
    }

    void execute(Character* stateMachine) override;
};

#endif //DZ04_STALKSNEAK_H
