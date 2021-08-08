﻿/**
 *Copyright (c) 2020 LZ.All Right Reserved
 *Author : LZ
 *Date: 2020.3.9
 *Email: 2117610943@qq.com
 */

#include "LZASPSRequriementLayer.h"
#include "LZASPSSpriteLayer.h"

#include "Based/LZUserWinRequirement.h"
#include "Based/LZGameType.h"
#include "Based/LZPlayMusic.h"

SPSRequriementLayer::SPSRequriementLayer():
	_requirement(nullptr)
{
}

SPSRequriementLayer::~SPSRequriementLayer()
{
	if (_requirement)delete _requirement;
}

bool SPSRequriementLayer::init()
{
    if (!LayerColor::initWithColor(Color4B(0, 0, 0, 180)))return false;

	createDialog();
    return true;
}

void SPSRequriementLayer::createDialog()
{
	_requirement = new UserWinRequirement(this);
	_requirement->createDialogBox(GameTypes::None);
	_requirement->setShowDialogAction();

	auto button = Button::create("Continue1.png", "Continue.png", "",cocos2d::ui::Widget::TextureResType::PLIST);
	button->setTitleText(Global::getInstance()->userInformation->getGameText().find("确定")->second->text);
	button->setTitleFontName(GAME_FONT_NAME_1);
	button->setTitleFontSize(Global::getInstance()->userInformation->getGameText().find("确定")->second->fontsize);
	button->setTitleColor(Color3B::YELLOW);
	button->setPosition(Vec2(_requirement->getDialog()->getContentSize().width / 2.0f, 10));
	button->setOpacity(0);
	button->setScale(0.5f);
	button->runAction(FadeIn::create(0.5f));
	button->addTouchEventListener([=](Ref* sender, cocos2d::ui::Widget::TouchEventType type)
		{
			switch (type)
			{
			case cocos2d::ui::Widget::TouchEventType::BEGAN:
				PlayMusic::playMusic("tap");
				break;
			case cocos2d::ui::Widget::TouchEventType::ENDED:
				_requirement->setDelectDialogAction();
				this->runAction(Sequence::create(Spawn::create(DelayTime::create(0.2f), FadeOut::create(0.2f), nullptr),
					CallFunc::create([&]()
						{
							SPSSpriteLayer::resumeButtonHoverEffect();
							this->removeFromParent();
						}), nullptr));
				break;
			}
		});
	_requirement->getDialog()->addChild(button);
}
