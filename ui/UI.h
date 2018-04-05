
#ifndef DZ04_UI_H
#define DZ04_UI_H


#include "../game-world/GameWorld.h"

class UI {
private:
    GameWorld* m_world;

public:
    explicit UI(GameWorld* m_world);

    void renderHUD() const;

    void renderGameOver(int width, int height) const;

    void renderWinScreen(int width, int height) const;

	void renderLoading(int width, int height) const;

};


#endif //DZ04_UI_H
