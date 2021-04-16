/**
 * @author  zju3180101729
 */

#include "MyProject.h"

USING_NS_CC;

bool StartScene::init() {

    if (!Scene::init()) {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    auto playButton = MenuItemLabel::create(
            Label::createWithTTF("Play", DEFAULT_FONT, 24),
            [&](Ref *sender) {
                Director::getInstance()->replaceScene(MapScene::create());
            });

    auto quitButton = MenuItemLabel::create(
            Label::createWithTTF("Quit", DEFAULT_FONT, 16),
            [&](Ref *sender) {
                Director::getInstance()->end();
            });

    auto menu = Menu::create();
    menu->addChild(playButton);
    menu->addChild(quitButton);
    menu->alignItemsVertically();
    menu->setPosition(origin + visibleSize / 2);

    this->addChild(menu);

    auto title = Label::createWithTTF("WitPlus", DEFAULT_FONT, 36);
    title->setPosition(origin.x + visibleSize.width / 2,
                       origin.y + visibleSize.height - title->getContentSize().height);

    this->addChild(title);

    return true;
}
