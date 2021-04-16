/**
 * @author  zju3180101729
 */

#include <stdio.h>

#include "MyProject.h"

USING_NS_CC;

bool MapScene::init() {
    if (!Scene::init()) {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
    auto userDefault = UserDefault::getInstance();

    Vector < MenuItem * > menuItems;

    for (int i = 0; i < WORLDS_NUM; ++i) {
        char label[10];
        sprintf(label, "World %d", i + 1);
        auto world = MenuItemLabel::create(
                Label::createWithTTF(label, DEFAULT_FONT, 20),
                [=](Ref *sender) {
                    MyController::getInstance()->setCurrentWorld(i);
                    Director::getInstance()->replaceScene(WorldScene::create());
                });
        world->setEnabled(MyController::getInstance()->getWorldEnable(i));
        menuItems.pushBack(world);
    }

    auto menu = Menu::createWithArray(menuItems);
    menu->alignItemsVertically();
    menu->setPosition(origin + visibleSize / 2);

    this->addChild(menu);

    //this->addChild(createDefaultBackButton(StartScene::create));
    CREATE_DEFAULT_BACK_BUTTON(StartScene);

    return true;
}
