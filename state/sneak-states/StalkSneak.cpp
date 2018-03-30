#include "StalkSneak.h"
#include "../../game-world/GameWorld.h"
#include "../../map/AStar.h"
#include "AttackSneak.h"


void StalkSneak::execute(Character* stateMachine) {
    if (stateMachine->closeEnoughToAttack(m_enemy)) {
        // if enemy can be attacked, do so
        stateMachine->changeState(new AttackSneak(m_enemy));
    }

    // only recalculate path if enemy has moved enough
    if (m_enemyPos.distanceTo(m_enemy->getPos()) >= m_recalculateThreshold) {

        MapNode* start = stateMachine->getWorld()->getNodeByPosition(stateMachine->getPos());
        MapNode* goal  = stateMachine->getWorld()->getNodeByPosition(m_enemy->getPos());

        stateMachine->setPath(AStar::shortestPath(stateMachine->getWorld()->getGraph(),
                                                  start,
                                                  goal,
                                                  stateMachine->getCostFunction()));
    }


    State::execute(stateMachine);
}
