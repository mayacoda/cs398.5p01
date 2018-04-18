
#include "Runner.h"
#include "../../game-world/GameWorld.h"
#include "../../state/runner-states/WanderRunner.h"

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
                                                           50,   /* maxSpeed */
                                                           30,  /*melee attack distance*/
                                                           150, /*ranged attack distance*/
                                                           1    /* timeout */)
{
	
	m_pixels     = ReadBitmap("assets/runner.bmp", &m_info);
    m_maskPixels = ReadBitmap("assets/runner-mask.bmp", &m_maskInfo);
}

const double Runner::calculateMaxSpeed() const {
    MapNode* current = m_world->getNodeByPosition(m_pos);

    switch (current->getTerrain()) {
        case MapNode::terrainType::none:
            return m_effectiveSpeed * 1.98;
        default:
            return m_effectiveSpeed;
    }
}

void Runner::turnOnDefaultBehavior() {
    Character::turnOnDefaultBehavior();
    if (!m_isPlayerControlled) changeState(new WanderRunner());
}

costFn Runner::getCostFunction() {
    return runnerCost;
}

void Runner::takeDamage(double damage) {
    Character::takeDamage(damage);
	
    // randomly move when taking damage
    if (iRandomRange(0, 4) == 1 && !m_isPlayerControlled) {
        changeState(new WanderRunner());
    }
}

const char* Runner::getMaskPath() {
    return "assets/runner-mask.bmp";
}

const char* Runner::getSpritePath() {
    return "assets/runner.bmp";
}

void Runner::render() const {
    Character::render();

    drawSprite(m_pos.x - globals::SPRITE_SIZE / 2,
               m_pos.y - globals::SPRITE_SIZE / 2);
}

void Runner::drawSprite(int x, int y) const {
	drawSpriteFromPixels(m_pixels, m_maskPixels, m_info, m_maskInfo, x, y);
}

void Runner::notify(Event e) {
    Character::notify(e);

    if (e.type == Event::enemyKill && m_world->getCharacters().size() == 2) {
        changeState(new WanderRunner());
    }
}