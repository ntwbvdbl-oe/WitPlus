/**
 * @author  zju3180101729
 */

#include <stdio.h>

#include "MyProject.h"

USING_NS_CC;

bool WorldScene::init() {

    if (!Scene::init()) {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    Vector < MenuItem * > levelLabels;

    auto _size = Label::createWithTTF("00", DEFAULT_FONT, 16)->getContentSize();

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (i * 4 + j == LEVELS_PER_WORLD) {
                break;
            }
            char labelText[10];
            sprintf(labelText, "%02d", i * 4 + j + 1);
            auto item = MenuItemLabel::create(
                    Label::createWithTTF(labelText, DEFAULT_FONT, 16),
                    [=](Ref *sender) {
                        MyController::getInstance()->setCurrentLevel(i * 4 + j);
                        Director::getInstance()->replaceScene(GameScene::create());
                    });
            item->setEnabled(MyController::getInstance()->getLevelEnable(
                    MyController::getInstance()->getCurrentWorld(), i * 4 + j));
            auto level = Menu::createWithItem(item);
            level->setPosition(origin + visibleSize / 2 +
                               Vec2(_size.width * (2 * j - 3), _size.height * (3 - 2 * i)));
            this->addChild(level);
        }
    }

    //this->addChild(createDefaultBackButton(MapScene::create));
    CREATE_DEFAULT_BACK_BUTTON(MapScene);

    return true;
}
