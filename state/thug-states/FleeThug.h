
#ifndef DZ04_FLEETHUG_H
#define DZ04_FLEETHUG_H


#include "../State.h"

class FleeThug : public State {
private:
    Character* m_enemy;
public:
    FleeThug(Character* m_enemy);

    void enter(Character* stateMachine) override;

    void exit(Character* stateMachine) override;

    void execute(Character* stateMachine) override;
};


#endif //DZ04_FLEETHUG_H
