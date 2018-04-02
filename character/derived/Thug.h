
#ifndef DZ04_THUG_H
#define DZ04_THUG_H


#include "../Character.h"

class Thug : public Character {
public:
    Thug(GameWorld* m_world,
         const Vector2D<double> &pos,
         const Vector2D<double> &scale,
         const Vector2D<double> &m_velocity,
         const Vector2D<double> &m_heading,
         const Vector2D<double> &m_side);

    const double calculateMaxSpeed() const override;

    void turnOnDefaultBehavior() override;

    costFn getCostFunction() override;

    static const char* getSpritePath();

    static const char* getMaskPath();

    void drawSprite(int x, int y) const override;

    void render() const override;
};


#endif //DZ04_THUG_H
