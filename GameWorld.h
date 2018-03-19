
#ifndef DZ04_GAMEWORLD_H
#define DZ04_GAMEWORLD_H


#include "Vehicle.h"
#include "Obstacle.h"
#include "Map.h"
#include <vector>

class Wall2D;

class GameWorld {

private:
    std::vector<Vehicle*>  m_vehicles;
    std::vector<Obstacle*> m_obstacles;
    //std::vector<Wall2D> m_walls;

    int m_width;
    int m_height;

    Vehicle* m_player;

    Map* map;

public:
    GameWorld(int m_width, int m_height);

    ~GameWorld() {
        delete m_player;
        delete map;
    }

    enum behaviors {
        none          = 0,
        wander        = 1,
        pathFollow    = 2,
        hide          = 3,
        offsetPursuit = 4,
        interpose     = 5
    };

    void update(double timeElapsed);

    void render();

    void setDimensions(int width, int height);

    int getWidth() const { return m_width; }

    int getHeight() const { return m_height; }

    std::vector<Obstacle*> getObstacles() const { return m_obstacles; }

    GameWorld::behaviors getActiveBehavior() const { return m_activeBehavior; }

    void clickHandler(int button, int state, int x, int y);

    void keyboardHandler(unsigned char i, int i1, int i2);

private:
    GameWorld::behaviors m_activeBehavior;
};


#endif //DZ04_GAMEWORLD_H
