
#ifndef DZ04_GRAPHICS_H
#define DZ04_GRAPHICS_H


#include "GameWorld.h"

class Graphics {
private:
    int m_width;
    int m_height;
    GameWorld * m_gameWorld;

    void initialize();

    static void reshape(int w, int h);

    static void render();
public:
    Graphics(GameWorld *gameWorld, int width, int height);

    int init(int argc, char *argv[]);
};


#endif //DZ04_GRAPHICS_H
