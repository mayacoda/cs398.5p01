
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
                                                       40 /* maxSpeed */,
                                                       50, /*melee attack distance*/
                                                       -1, /*ranged attack distance*/
                                                       2 /*timeout*/) {}

const double Thug::calculateMaxSpeed() const {
    // enable thug to "sprint" when he is pursuing an enemy
    if (m_steeringBehavior->isOn(SteeringBehaviors::fPursue)) {
        return m_maxSpeed * 1.53;
    }
    return m_maxSpeed;
}

void Thug::turnOnDefaultBehavior() {
    Character::turnOnDefaultBehavior();
    changeState(new WanderThug());
}

costFn Thug::getCostFunction() {
    return thugCost;
}

const char* Thug::getSpritePath() {
    return "assets/thug.bmp";
}

const char* Thug::getMaskPath() {
    return "assets/thug-mask.bmp";
}

void Thug::render() const {
    renderAids();

    drawSpriteWithMask(Thug::getSpritePath(),
                       Thug::getMaskPath(),
                       m_pos.x - globals::SPRITE_SIZE / 2,
                       m_pos.y - globals::SPRITE_SIZE / 2);
}
