
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
                                                       20 /* maxSpeed */,
                                                       50 /*range*/,
                                                       2 /*timeout*/) {}

const double Thug::calculateMaxSpeed() const {
    return m_maxSpeed;
}

void Thug::turnOnDefaultBehavior() {
    Character::turnOnDefaultBehavior();
    changeState(new WanderThug());
}

Character::fptr Thug::getCostFunction() {
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

    drawSpriteWithMask(Thug::getSpritePath(), Thug::getMaskPath(), m_pos.x - 18, m_pos.y - 18);
}
