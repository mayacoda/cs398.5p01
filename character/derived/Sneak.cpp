
#include "Sneak.h"
#include "../../game-world/GameWorld.h"
#include "../../state/sneak-states/WanderSneak.h"
#include "../../state/sneak-states/EvadeSneak.h"

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
                                                         50, /*maxSpeed*/
                                                         -1,  /*melee attack distance*/
                                                         250, /*ranged attack distance*/
                                                         1    /*timeout*/) {
    m_antagonistDetectionDistance = 1000;

	m_pixels     = ReadBitmap("assets/sneak.bmp", &m_info);
    m_maskPixels = ReadBitmap("assets/sneak-mask.bmp", &m_maskInfo);

}

const double Sneak::calculateMaxSpeed() const {
    MapNode* current = m_world->getNodeByPosition(m_pos);
    double speed = m_maxSpeed;

    switch (current->getTerrain()) {
        case MapNode::terrainType::mountain:
            speed = m_maxSpeed * 1.48;
            break;
        case MapNode::terrainType::forest:
            speed = m_maxSpeed * 1.76;
            break;
        case MapNode::none:break;
        case MapNode::water:break;
    }

    // enable sneak to run away more quickly
    if (m_steeringBehavior->isOn(SteeringBehaviors::fEvade)) {
        speed *= 1.2;
    }

    return speed;
}

void Sneak::turnOnDefaultBehavior() {
    Character::turnOnDefaultBehavior();
    if (!m_isPlayerControlled) changeState(new WanderSneak());
}

costFn Sneak::getCostFunction() {
    return sneakCost;
}

void Sneak::takeDamage(double damage) {
    Character::takeDamage(damage);

    // randomly move when taking damage
    if (iRandomRange(0, 2) == 1 && !m_isPlayerControlled) {
        changeState(new WanderSneak());
    }
}

const char* Sneak::getMaskPath() {
    return "assets/sneak-mask.bmp";
}

const char* Sneak::getSpritePath() {
    return "assets/sneak.bmp";
}

void Sneak::render() const {
    Character::render();

    drawSprite(m_pos.x - globals::SPRITE_SIZE / 2,
            m_pos.y - globals::SPRITE_SIZE / 2);
}


void Sneak::drawSprite(int x, int y) const {
	drawSpriteFromPixels(m_pixels, m_maskPixels, m_info, m_maskInfo, x, y);
}
