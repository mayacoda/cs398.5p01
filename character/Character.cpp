
#include "Character.h"
#include "../state/State.h"
#include "../game-world/GameWorld.h"
#include "../geometry/Matrix.h"
#include "../geometry/geometry.h"
#include "attack/RangedAttack.h"
#include "attack/MeleeAttack.h"
#include <ctime>

#ifdef _WIN32
#include <GL\glut.h>
#elif __APPLE__
#endif


void Character::update(double timeElapsed) {
    m_timeElapsed = timeElapsed;

    if (currentState) {
        currentState->execute(this);
    }

    Vector2D<double> steeringForce = m_steeringBehavior->calculate();

    m_steeringForce = steeringForce;

    Vector2D<double> acceleration = steeringForce / m_mass;

    m_velocity += acceleration * timeElapsed;

    m_velocity.truncate(calculateMaxSpeed());

    m_pos += m_velocity * timeElapsed;

    m_pos.wrapAround(m_world->getWidth(), m_world->getHeight());

    if (m_velocity.squareMagnitude() > 0.00000001 && !m_isPlayerControlled) {
        m_heading = m_velocity.getNormalized();

        m_side = m_heading.getOrtho();
    }
}

void Character::renderAids() const {

    // heading vector RED
    glColor3d(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2d(m_pos.x, m_pos.y);
    Vector2D<double> heading = m_heading * 100;
    heading += m_pos;
    glVertex2d(heading.x, heading.y);
    glEnd();

    // side vector GREEN
    glColor3d(0.0, 1.0, 0.0);
    glBegin(GL_LINES);
    glVertex2d(m_pos.x, m_pos.y);
    Vector2D<double> side = m_side * 100;
    side += m_pos;
    glVertex2d(side.x, side.y);
    glEnd();

    // steering force BLUE
    glColor3d(0.0, 0.0, 1.0);
    glBegin(GL_LINES);
    glVertex2d(m_pos.x, m_pos.y);
    glVertex2d(m_steeringForce.x + m_pos.x, m_steeringForce.y + m_pos.y);
    glEnd();


    // detection zone PURPLE
    glColor3d(.8, 0, .7);
    drawCircle(m_antagonistDetectionDistance, m_pos);

    // melee attack zone ORANGE
    if (m_distanceToAttackMelee > 0) {
        glColor3d(1, .4, .3);
        drawCircle(m_distanceToAttackMelee, m_pos);
    }

    // ranged attack zone YELLOW
    if (m_distanceToAttackRanged > 0) {
        glColor3d(1, .8, 0);
        drawCircle(m_distanceToAttackRanged, m_pos);
    }

    if (m_steeringBehavior->isOn(SteeringBehaviors::fWander)) {
        // wandering target
        glColor3d(0.0, 0.0, 1.0);
        glPointSize(5.0f);
        glBegin(GL_POINTS);
        glVertex2d(wanderTarget.x, wanderTarget.y);
        glEnd();

        // wandering circle
        glColor3d(1.0, 0.0, 1.0);
        Vector2D<double> dir = m_heading * m_steeringBehavior->m_wanderDistance;;
        drawCircle(m_steeringBehavior->m_wanderRadius, dir + m_pos);
    }

    if (m_steeringBehavior->isOn(SteeringBehaviors::fFollow_path)) {
        m_steeringBehavior->m_path->render(m_color.r, m_color.g, m_color.b);
    }
}

void Character::render() const {
    if (globals::debug) renderAids();

    if (m_isPlayerControlled && m_steeringBehavior->isOn(SteeringBehaviors::fSeek)) {
        glColor3f(0.1, 0.1, 0.1);
        glLineWidth(2);
        glBegin(GL_LINES);
        glVertex2d(m_destination.x - 10, m_destination.y);
        glVertex2d(m_destination.x + 10, m_destination.y);
        glEnd();

        glBegin(GL_LINES);
        glVertex2d(m_destination.x, m_destination.y - 10);
        glVertex2d(m_destination.x, m_destination.y + 10);
        glEnd();

        glLineWidth(1);
    }
}

Character::Character(GameWorld* m_world,
                     const Vector2D<double> &pos,
                     const Vector2D<double> &scale,
                     const Vector2D<double> &m_velocity,
                     const Vector2D<double> &m_heading,
                     const Vector2D<double> &m_side,
                     double m_mass,
                     double m_maxSpeed,
                     double meleeAttackDistance,
                     double rangedAttackDistance,
                     double attackTimeout) : MovingEntity(pos,
                                                          globals::SPRITE_SIZE/2,
                                                          scale,
                                                          m_velocity,
                                                          m_heading,
                                                          m_side,
                                                          m_mass,
                                                          m_maxSpeed,
                                                          1,
                                                          1),
                                             currentState(),
                                             m_world(m_world),
                                             m_distanceToAttackMelee(meleeAttackDistance),
                                             m_distanceToAttackRanged(rangedAttackDistance),
                                             m_attackTimeout(attackTimeout),
                                             m_timeElapsed(0),
                                             m_leader(nullptr),
                                             m_color(0.3, 0.3, 0.6),
                                             m_dead(false),
                                             interposeTargetA(),
                                             interposeTargetB() {

    m_steeringForce = Vector2D<double>(0.0, 0.0);
    wanderTarget    = Vector2D<double>(0.0, 0.0);
    m_offset        = Vector2D<double>(0.0, 0.0);

    m_timeLastAttacked = time(nullptr);

    m_detectionBoxLength = 200;

    m_timeLastAttacked = 0;

    m_health = 100;

    m_antagonistDetectionDistance = 400;

    m_steeringBehavior = new SteeringBehaviors(this);

    m_isPlayerControlled = false;

    m_attackSpeed = 100;

    currentState = new State();
}

Character* Character::seekEnemies() const {
    Character* closest = nullptr;
    double smallestDist = std::numeric_limits<double>::infinity();

    for (auto it = m_antagonists.begin(); it != m_antagonists.end(); ++it) {
        double distanceTo = (*it)->getPos().distanceTo(m_pos);
        if (distanceTo <= smallestDist && distanceTo <= m_antagonistDetectionDistance) {
            smallestDist = distanceTo;
            closest      = *it;
        }
    }

    return closest;
}

bool Character::canDetect(Character* enemy) {
    return enemy->getPos().distanceTo(m_pos) < m_antagonistDetectionDistance;
}

void Character::changeState(State* newState) {
    if (currentState) currentState->exit(this);

    currentState = newState;

    currentState->enter(this);
}

void Character::attackRanged(Vector2D<double> target) {
    double currentTime = time(nullptr);

    if (currentTime - m_timeLastAttacked >= m_attackTimeout) {
        turnToFace(target);
        m_velocity = Vector2D<double>(0, 0);

        m_world->addProjectile(new RangedAttack(this, m_distanceToAttackRanged, m_attackSpeed));
        m_timeLastAttacked = currentTime;
    }
}

void Character::attackMelee(Vector2D<double> target) {
    double currentTime = time(nullptr);

    if (currentTime - m_timeLastAttacked >= m_attackTimeout) {
        turnToFace(target);
        m_velocity = Vector2D<double>(0, 0);

        m_world->addProjectile(new MeleeAttack(this, m_distanceToAttackMelee, m_attackSpeed * .5));
        m_timeLastAttacked = currentTime;
    }
}

void Character::turnToFace(Vector2D<double> target) {
    m_heading  = (target - m_pos).getNormalized();
    m_side = m_heading.getOrtho();
}

Character::~Character() {
    delete m_steeringBehavior;
    delete currentState;
}
