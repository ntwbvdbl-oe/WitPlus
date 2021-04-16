/**
 * @author  zju3180101729
 */

#ifndef MYPROJECT_GAMESCENE_H
#define MYPROJECT_GAMESCENE_H

#include "cocos2d.h"
#include "GameBoard.h"
#include "Pos.h"

#define COLOR_BG            cocos2d::Color4F(8.0f / 255, 66.0f / 255, 52.0f / 255, 1.0f)
#define COLOR_ROAD          cocos2d::Color4F(26.0f / 255, 88.0f / 255, 66.0f / 255, 1.0f)
#define COLOR_BLOCK         cocos2d::Color4F(0.0f, 172.0f / 255, 131.0f / 255, 1.0f)
#define COLOR_KEY           cocos2d::Color4F(177.0f / 255, 177.0f / 255, 177.0f / 255, 1.0f)
#define COLOR_PATH          cocos2d::Color4F(0.0f, 221.0f / 255, 96.0f / 255, 1.0f)
#define SCALE_ROAD_BLOCK    0.333f
#define SCALE_START_ROAD    2.0f
#define SCALE_KEY_ROAD      0.9f

class GameScene : public cocos2d::Scene {
public:
    virtual bool init() override;

    virtual ~GameScene() {}

    CREATE_FUNC(GameScene);

private:
    cocos2d::MenuItem *nextItem;

    bool isTouching = false;

    float canvasSize;

    float blockSize;

    float roadSize;

    cocos2d::Vec2 origin;

    cocos2d::Vec2 touchPoint;

    cocos2d::Rect canvas;

    cocos2d::DrawNode *drawNode;

    GameBoard *game;

    void redrawGame();

    cocos2d::Size getRectSize(Pos pos);

    cocos2d::Vec2 getLocalOrigin(Pos pos);

    cocos2d::Vec2 getCenter(Pos pos);

    Pos pointToPos(cocos2d::Vec2 point);

};


#endif //MYPROJECT_GAMESCENE_H
