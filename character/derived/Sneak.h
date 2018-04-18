
#ifndef DZ04_SNEAK_H
#define DZ04_SNEAK_H


#include "../Character.h"

class Sneak: public Character {
public:
    Sneak(GameWorld* m_world,
          const Vector2D<double> &pos,
          const Vector2D<double> &scale,
          const Vector2D<double> &m_velocity,
          const Vector2D<double> &m_heading,
          const Vector2D<double> &m_side);

    const double calculateMaxSpeed() const override;

    costFn getCostFunction() override;

    static const char * getMaskPath();

    static const char * getSpritePath();

    void turnOnDefaultBehavior() override;

    void render() const override;

    void drawSprite(int x, int y) const override;

    void takeDamage(double damage) override;

    void notify(Event e) override;
};


#endif //DZ04_SNEAK_H
