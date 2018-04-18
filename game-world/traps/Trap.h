
#ifndef DZ04_TRAP_H
#define DZ04_TRAP_H


#include "../BaseGameEntity.h"
#include "../../graphics/opengl_helpers.h"

class GameWorld;

class Character;

class Trap : public BaseGameEntity {

protected:
    Color m_color;
public:
    Trap(GameWorld* world, const Vector2D<double> &pos);

    enum trapType {
        visibility,
        movement
    };

private:
    double m_activationSqDistance;
    double m_expirationTime;
    double m_duration;

    bool m_isAttached;
    bool m_isDead;

    Character* m_victim;
    GameWorld* m_world;

protected:
    trapType m_type;

public:
    void update(double timeElapsed) override;

    void render() const override;

    bool isDead() const { return m_isDead; }
};


#endif //DZ04_TRAP_H
