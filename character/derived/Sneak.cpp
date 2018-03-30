
#include "Sneak.h"
#include "../../game-world/GameWorld.h"
#include "../../state/sneak-states/WanderSneak.h"

Sneak::Sneak(GameWorld* m_world,
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
                                                         30,
                                                         100 /*range*/,
                                                         1 /*timeout*/) {
    m_antagonistDetectionDistance = 200;
    m_distanceToAttack            = 100;
}

const double Sneak::calculateMaxSpeed() const {
    MapNode* current = m_world->getNodeByPosition(m_pos);

    switch (current->getTerrain()) {
        case MapNode::terrainType::mountain:
            return m_maxSpeed * 1.5;
        case MapNode::terrainType::forest:
            return m_maxSpeed * 1.75;
        default:
            return m_maxSpeed;
    }
}

void Sneak::turnOnDefaultBehavior() {
    Character::turnOnDefaultBehavior();
    changeState(new WanderSneak());
}

Character::fptr Sneak::getCostFunction() {
    return sneakCost;
}

const char* Sneak::getMaskPath() {
    return "assets/sneak-mask.bmp";
}

const char* Sneak::getSpritePath() {
    return "assets/sneak.bmp";
}

void Sneak::render() const {
    drawSpriteWithMask(Sneak::getSpritePath(), Sneak::getMaskPath(), m_pos.x - 18, m_pos.y - 18);
}

void Sneak::update(double timeElapsed) {
    Character::update(timeElapsed);
}
