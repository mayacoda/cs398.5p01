#include "StalkSneak.h"
#include "../../game-world/GameWorld.h"
#include "../../map/AStar.h"
#include "AttackSneak.h"


void StalkSneak::execute(Character* stateMachine) {
    if (stateMachine->closeEnoughToAttackRanged(m_enemy)) {
        // if enemy can be attacked, do so
        stateMachine->changeState(new AttackSneak(m_enemy));

        // can no longer detect the enemy
    } else if (!stateMachine->canDetect(m_enemy)) {

        stateMachine->changeState(new WanderSneak());

        // only recalculate path if enemy has moved enough
    } else if (m_enemyPos.squareDistanceTo(m_enemy->getPos()) >= m_recalculateThreshold * m_recalculateThreshold ||
               !m_pathInitialized) {
        m_enemyPos        = m_enemy->getPos();
        m_pathInitialized = true;

        MapNode* start = stateMachine->getWorld()->getNodeByPosition(stateMachine->getPos());
        MapNode* goal  = stateMachine->getWorld()->getNodeByPosition(m_enemy->getPos());

        stateMachine->setPath(AStar::shortestPath(stateMachine->getWorld()->getGraph(),
                                                  start,
                                                  goal,
                                                  stateMachine->getCostFunction()));
    }

    State::execute(stateMachine);
}

