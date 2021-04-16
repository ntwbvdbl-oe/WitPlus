/**
 * @author  zju3180101729
 */

#ifndef MYPROJECT_MYPROJECT_H
#define MYPROJECT_MYPROJECT_H

#include "AppDelegate.h"
#include "AppMacros.h"
#include "GameBoard.h"
#include "GameScene.h"
#include "MapScene.h"
#include "MyController.h"
#include "Pos.h"
#include "StartScene.h"
#include "WorldScene.h"

#define DEFAULT_FONT "fonts/consola.ttf"

//cocos2d::Menu *createDefaultBackButton((cocos2d::Scene*) (*create)());
#define CREATE_DEFAULT_BACK_BUTTON(SCENE) {                                                     \
    auto visibleSize = Director::getInstance()->getVisibleSize();                               \
    auto origin = Director::getInstance()->getVisibleOrigin();                                  \
    auto backLabel = Label::createWithTTF("Back", DEFAULT_FONT, 16);                            \
    auto backButton = Menu::createWithItem(                                                     \
            MenuItemLabel::create(backLabel,                                                    \
                                  [&](Ref *sender) {                                            \
                                      Director::getInstance()->replaceScene(SCENE::create());   \
                                  }));                                                          \
    backButton->setPosition(origin.x + backLabel->getContentSize().width,                       \
                            origin.y + backLabel->getContentSize().height * 4);                 \
    this->addChild(backButton);                                                                 \
}

#endif //MYPROJECT_MYPROJECT_H
