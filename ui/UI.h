
#ifndef DZ04_UI_H
#define DZ04_UI_H


#include "../game-world/GameWorld.h"
#include "Bounds.h"

class UI {
private:
    GameWorld* m_world;
    mutable Bounds<int> characters[3];
    mutable Bounds<int> menuOptions[2];

    void calculateCharacterPositions(int width, int height) const;

    void calculateMenuPositions(int width, int height) const;

public:
    explicit UI(GameWorld* m_world);

    void renderHUD() const;

    void renderGameOver(int width, int height) const;

    void renderWinScreen(int width, int height) const;

    void renderCharacterSelection(int width, int height) const;

    void renderMenu(int width, int height) const;

    GameWorld::gameState chooseCharacter(int x, int y) const;

    GameWorld::gameState chooseMenuOption(int x, int y) const;
};


#endif //DZ04_UI_H
