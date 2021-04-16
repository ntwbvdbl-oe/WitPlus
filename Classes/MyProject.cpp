/**
 * @author  zju3180101729
 */

#include "MyProject.h"

/*
Menu *createDefaultBackButton(Scene* (*create)()) {

    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    auto backLabel = Label::createWithTTF("Back", DEFAULT_FONT, 16);
    auto backButton = Menu::createWithItem(
            MenuItemLabel::create(backLabel,
                                  [&](Ref *sender) {
                                      Director::getInstance()->replaceScene(create());
                                  }));
    backButton->setPosition(origin.x + backLabel->getContentSize().width,
                            origin.y + backLabel->getContentSize().height * 4);
    return backButton;
}*/
