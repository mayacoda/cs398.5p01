
#ifndef DZ04_GAMEWORLD_H
#define DZ04_GAMEWORLD_H


#include "Vehicle.h"
#include "Graphics.h"
#include <vector>

class Wall2D;

class GameWorld {

private:
    std::vector<Vehicle *> m_vehicles;
    std::vector<BaseGameEntity *> m_obstacles;
    //std::vector<Wall2D> m_walls;

    int m_width;
    int m_height;

public:
    GameWorld(int m_width, int m_height);

    void update(double timeElapsed);

    void render();


    int getWidth() { return m_width; }

    int getHeight() { return m_height; }
};


#endif //DZ04_GAMEWORLD_H
