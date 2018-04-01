
#ifndef DZ04_ATTACKTHUG_H
#define DZ04_ATTACKTHUG_H


#include "../State.h"

class AttackThug : public State {
private:
    Character *m_enemy;
public:
    AttackThug(Character* m_enemy);

    void execute(Character* stateMachine) override;

};


#endif //DZ04_ATTACKTHUG_H
