
#ifndef DZ04_PURSUETHUG_H
#define DZ04_PURSUETHUG_H


#include "../State.h"

class PursueThug : public State {
private:
    Character * m_enemy;
public:
    PursueThug(Character* m_enemy);

    void enter(Character* stateMachine) override;

    void exit(Character* stateMachine) override;

    void execute(Character* stateMachine) override;
};


#endif //DZ04_PURSUETHUG_H
