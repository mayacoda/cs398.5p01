
#ifndef DZ04_RUNNER_H
#define DZ04_RUNNER_H


#include "../Character.h"

class Runner : public Character {
public:
    Runner(GameWorld* m_world,
           const Vector2D<double> &pos,
           const Vector2D<double> &scale,
           const Vector2D<double> &m_velocity,
           const Vector2D<double> &m_heading,
           const Vector2D<double> &m_side);

    const double calculateMaxSpeed() const override;

    fptr getCostFunction() override;

    static const char* getMaskPath();

    static const char* getSpritePath();

    void render() const override;
};


#endif //DZ04_RUNNER_H
