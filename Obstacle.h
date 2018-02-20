
#ifndef DZ04_OBSTACLE_H
#define DZ04_OBSTACLE_H


#include "BaseGameEntity.h"

class Obstacle : public BaseGameEntity {
public:
    Obstacle(double x, double y, double r) : BaseGameEntity(0, Vector2D<double>(x, y), r) {}

    Obstacle(Vector2D<double> pos, double radius) : BaseGameEntity(0, pos, radius) {}

    void update(double time_elapsed) {}

    void render();
};


#endif //DZ04_OBSTACLE_H
