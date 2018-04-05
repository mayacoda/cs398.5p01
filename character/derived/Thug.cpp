
#include "Thug.h"
#include "../../state/thug-states/WanderThug.h"

Thug::Thug(GameWorld* m_world,
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
                                                       60 /* maxSpeed */,
                                                       50, /*melee attack distance*/
                                                       -1, /*ranged attack distance*/
                                                       2 /*timeout*/) {}

const double Thug::calculateMaxSpeed() const {
    // enable thug to "sprint" when he is pursuing an enemy
    if (m_steeringBehavior->isOn(SteeringBehaviors::fPursue)) {
        return m_maxSpeed * 1.23;
    }

	
    m_pixels     = ReadBitmap("assets/thug.bmp", &m_info);
    m_maskPixels = ReadBitmap("assets/thug-mask.bmp", &m_maskInfo);

    return m_maxSpeed;
}

void Thug::turnOnDefaultBehavior() {
    Character::turnOnDefaultBehavior();
	if (!m_isPlayerControlled) changeState(new WanderThug());	
}

costFn Thug::getCostFunction() {
    return thugCost;
}

void Thug::takeDamage(double damage) {
    m_health -= damage * .8;
    if (globals::debug) std::cout << "[" << getId() << "] health is: " << m_health << std::endl;

    if (m_health <= 0) {
        m_dead = true;
    }
}

const char* Thug::getSpritePath() {
    return "assets/thug.bmp";
}

const char* Thug::getMaskPath() {
    return "assets/thug-mask.bmp";
}

void Thug::render() const {
    Character::render();
    drawSprite(m_pos.x - globals::SPRITE_SIZE / 2, m_pos.y - globals::SPRITE_SIZE / 2);
}

void Thug::drawSprite(int x, int y) const {
	drawSpriteFromPixels(m_pixels, m_maskPixels, m_info, m_maskInfo, x, y);
}
