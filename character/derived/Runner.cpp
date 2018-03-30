
#include "Runner.h"
#include "../../game-world/GameWorld.h"

Runner::Runner(GameWorld* m_world,
               const Vector2D<double> &pos,
               const Vector2D<double> &scale,
               const Vector2D<double> &m_velocity,
               const Vector2D<double> &m_heading,
               const Vector2D<double> &m_side) : Character(m_world,
                                                           pos,
                                                           scale,
                                                           m_velocity,
                                                           m_heading,
                                                           m_side,
                                                           1,
                                                           40 /* maxSpeed */,
                                                           100 /* range */,
                                                           1 /* timeout */) {}

const double Runner::calculateMaxSpeed() const {
    MapNode* current = m_world->getNodeByPosition(m_pos);

    switch (current->getTerrain()) {
        case MapNode::terrainType::none:
            return m_maxSpeed * 2;
        default:
            return m_maxSpeed;
    }
}

Character::fptr Runner::getCostFunction() {
    return runnerCost;
}

const char* Runner::getMaskPath() {
    return "assets/runner-mask.bmp";
}

const char* Runner::getSpritePath() {
    return "assets/runner.bmp";
}

void Runner::render() const {
    renderAids();

    drawSpriteWithMask(Runner::getSpritePath(), Runner::getMaskPath(), m_pos.x - 18, m_pos.y - 18);
}
