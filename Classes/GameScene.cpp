/**
 * @author  zju3180101729
 */

#include <algorithm>

#include "MyProject.h"

USING_NS_CC;

bool GameScene::init() {

    if (!Scene::init()) {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto visibleOrigin = Director::getInstance()->getVisibleOrigin();

    int currentWorld = MyController::getInstance()->getCurrentWorld();
    int currentLevel = MyController::getInstance()->getCurrentLevel();

    this->canvasSize = std::min(visibleSize.width, visibleSize.height) * 0.7;
    this->canvas = Rect(visibleOrigin.x + visibleSize.width / 2 - canvasSize / 2,
                        visibleOrigin.y + visibleSize.height / 2 - canvasSize / 2,
                        canvasSize, canvasSize);

    this->drawNode = DrawNode::create();

    this->addChild(this->drawNode, 1);

    MyController::getInstance()->initGame();

    this->game = MyController::getInstance()->getGame();
    this->blockSize = this->canvasSize /
                      (std::max(this->game->width, this->game->height) * (1 + SCALE_ROAD_BLOCK) +
                       1);
    this->roadSize = this->blockSize * SCALE_ROAD_BLOCK;
    this->origin = canvas.origin + canvas.size / 2 -
                   Vec2(blockSize * (game->width - 1) + roadSize * game->width,
                        blockSize * (game->height - 1) + roadSize * game->width) / 2;

    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = [&](Touch *touch, Event *event) {
        if (!this->canvas.containsPoint(touch->getLocation())) {
            return false;
        }
        Pos pos = this->pointToPos(touch->getLocation());
        if (pos != game->start) {
            return false;
        }
        this->isTouching = true;
        this->touchPoint = touch->getLocation();
        MyController::getInstance()->onTouchBegan(pos);
        this->redrawGame();
        return true;
    };
    listener->onTouchMoved = [&](Touch *touch, Event *event) {
        if (!this->isTouching)
            return;
        MyController::getInstance()->onTouchMoved(
                this->pointToPos(this->touchPoint = touch->getLocation()));
        this->redrawGame();
    };
    listener->onTouchEnded = [&](Touch *touch, Event *event) {
        if (!this->isTouching)
            return;
        this->isTouching = false;
        this->touchPoint = Vec2::ZERO;
        MyController::getInstance()->onTouchEnded(Pos(-1, -1));
        this->redrawGame();
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    /////////////////////////////////////////
    auto nextLabel = Label::createWithTTF("Next", DEFAULT_FONT, 16);
    this->nextItem = MenuItemLabel::create(
            nextLabel,
            [=](Ref *sender) {
                MyController::getInstance()->setCurrentLevel(currentLevel + 1);
                Director::getInstance()->replaceScene(GameScene::create());
            });
    auto nextButton = Menu::createWithItem(nextItem);
    nextButton->setPosition(visibleOrigin.x + visibleSize.width - nextLabel->getContentSize().width,
                            visibleOrigin.y + nextLabel->getContentSize().height * 4);
    this->addChild(nextButton);

    //this->addChild(createDefaultBackButton(WorldScene::create));
    CREATE_DEFAULT_BACK_BUTTON(WorldScene);

    this->redrawGame();

    return true;
}

Size GameScene::getRectSize(Pos pos) {
    return Size(pos.x & 1 ? blockSize : roadSize, pos.y & 1 ? blockSize : roadSize);
}

Vec2 GameScene::getLocalOrigin(Pos pos) {
    return origin + Vec2(pos.x / 2 * blockSize + (pos.x + 1) / 2 * roadSize,
                         pos.y / 2 * blockSize + (pos.y + 1) / 2 * roadSize);
}

Vec2 GameScene::getCenter(Pos pos) {
    if (pos == Pos(0, -1)) {
        pos = game->end;
        Size rectSize = getRectSize(pos);
        if (game->endDir == END_DIR_UP) {
            return getLocalOrigin(pos) + Vec2(rectSize.width / 2, rectSize.height * 1.5);
        }//TODO
        return Vec2::ZERO;
    } else {
        return getLocalOrigin(pos) + getRectSize(pos) / 2;
    }
}

Pos GameScene::pointToPos(Vec2 point) {
    for (int i = 0; i < 2 * game->width - 1; ++i) {
        for (int j = 0; j < 2 * game->height - 1; ++j) {
            /*Pos pos(i, j);
            Size rectSize = getRectSize(pos);
            Vec2 localOrigin = getLocalOrigin(pos);
            if (Rect(localOrigin, rectSize).containsPoint(point)) */
            if (point.distance(getCenter(Pos(i, j))) < roadSize * 0.7) {
                return Pos(i, j);
            }
        }
    }
    if (point.distance(getCenter(Pos(0, -1))) < roadSize * 0.7) {
        return Pos(0, -1);
    }
    return Pos(-1, -1);
}

void GameScene::redrawGame() {
    //update Next button
    nextItem->setEnabled(
            MyController::getInstance()->getLevelEnable(
                    MyController::getInstance()->getCurrentWorld(),
                    MyController::getInstance()->getCurrentLevel() + 1));
    //Clear all draws
    drawNode->clear();
    //Step1: draw background
    drawNode->drawSolidRect(canvas.origin, canvas.origin + canvas.size, COLOR_BG);
    //Step2: draw GameBoard
    for (int i = 0; i < 2 * game->width - 1; ++i) {
        for (int j = 0; j < 2 * game->height - 1; ++j) {
            Pos pos(i, j);
            Size rectSize = getRectSize(pos);
            Vec2 localOrigin = getLocalOrigin(pos);
            int mask = game->mask[pos.x][pos.y];
            if (!mask)
                drawNode->drawSolidRect(localOrigin, localOrigin + rectSize, COLOR_BLOCK);
            if (mask & MASK_ROAD) {
                drawNode->drawSolidRect(localOrigin, localOrigin + rectSize, COLOR_ROAD);
            }
            if (mask & MASK_KEY) {
                drawNode->drawSolidCircle(localOrigin + rectSize / 2, SCALE_KEY_ROAD * roadSize / 2,
                                          360.0f, 36, COLOR_KEY);
            }
            if (mask & MASK_BREAK) {
                drawNode->drawSolidRect(localOrigin + rectSize / 2 - Vec2(roadSize, roadSize) / 2,
                                        localOrigin + rectSize / 2 + Vec2(roadSize, roadSize) / 2,
                                        COLOR_BLOCK);
            }
            if (mask & MASK_END) {
                if (game->endDir == END_DIR_UP) {
                    drawNode->drawSolidRect(localOrigin + Vec2(0.0f, rectSize.height),
                                            localOrigin +
                                            Vec2(rectSize.width, rectSize.height * 1.5),
                                            COLOR_ROAD);
                    drawNode->drawSolidCircle(
                            localOrigin + Vec2(rectSize.width / 2, rectSize.height * 1.5),
                            rectSize.width / 2, 360.0f, 36, COLOR_ROAD);
                }//TODO
            }
        }
    }
    {
        Size rectSize = getRectSize(this->game->start);
        Vec2 localOrigin = getLocalOrigin(this->game->start);
        drawNode->drawSolidCircle(localOrigin + rectSize / 2,
                                  SCALE_START_ROAD * roadSize / 2, 360.0f, 36,
                                  COLOR_ROAD);
    }
    //Step3: draw path
    const auto &path = MyController::getInstance()->getPath();
    for (auto pos : path) {
        if (pos == Pos(0, -1)) {
            Size rectSize = getRectSize(game->end);
            Vec2 localOrigin = getLocalOrigin(game->end);
            if (game->endDir == END_DIR_UP) {
                drawNode->drawSolidRect(localOrigin + Vec2(0.0f, rectSize.height),
                                        localOrigin + Vec2(rectSize.width, rectSize.height * 1.5),
                                        COLOR_PATH);
                drawNode->drawSolidCircle(
                        localOrigin + Vec2(rectSize.width / 2, rectSize.height * 1.5),
                        rectSize.width / 2, 360.0f, 36, COLOR_PATH);
            }//TODO
        } else {
            Size rectSize = getRectSize(pos);
            Vec2 localOrigin = getLocalOrigin(pos);
            int mask = game->mask[pos.x][pos.y];
            if (mask & MASK_ROAD) {
                drawNode->drawSolidRect(localOrigin, localOrigin + rectSize, COLOR_PATH);
            }
            if (mask & MASK_START) {
                drawNode->drawSolidCircle(localOrigin + rectSize / 2, SCALE_START_ROAD * roadSize / 2, 360.0f, 36,
                                          COLOR_PATH);
            }
        }
    }
    //Step4: draw rect from path to finger
    if (isTouching) {
        Pos pos = *--MyController::getInstance()->getPath().end();
        Vec2 center = getCenter(pos);
        Vec2 vertical = this->touchPoint - center;
        Vec2 horizonal = Vec2(vertical.y, -vertical.x).getNormalized() * roadSize;
        Vec2 poly[4];
        poly[0] = center + horizonal / 2;
        poly[1] = poly[0] + vertical;
        poly[2] = poly[1] - horizonal;
        poly[3] = poly[2] - vertical;
        drawNode->drawSolidPoly(poly, 4, COLOR_PATH);
        drawNode->drawSolidCircle(this->touchPoint, SCALE_START_ROAD * roadSize / 2, 360.0f, 36, COLOR_PATH);
    }
}
