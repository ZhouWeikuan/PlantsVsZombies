/**
 *Copyright (c) 2021 LZ.All Right Reserved
 *Author : LZ
 *Date: 2021.4.07
 *Email: 2117610943@qq.com
 */

#include "LZTSPSBackgroundLayer.h"
#include "Scenes/GameScenes/Adventure/GameScene/LZAGSAnimationLayer.h"
#include "Scenes/GameScenes/Adventure/SelectPlantsScene/LZASPSBackgroundLayer.h"
#include "Zombies/LZZombies.h"

TSPSBackgroundLayer::TSPSBackgroundLayer()
{
}

TSPSBackgroundLayer::~TSPSBackgroundLayer()
{
}

bool TSPSBackgroundLayer::init()
{
	if (!Layer::init()) return false;

	/* �������� */
	createBackGroundEffect();
	showPreviewZombies();

	SPSBackgroundLayer::setBackgroundImagePosition();

	return true;
}

void TSPSBackgroundLayer::createBackGroundEffect()
{
	_global->userInformation->setBackground(Sprite::createWithSpriteFrameName("background9.png"));
}

void TSPSBackgroundLayer::showPreviewZombies()
{
	const uniform_int_distribution<unsigned>n(0, 2);
	uniform_int_distribution<unsigned>n1(0, 550);
	uniform_int_distribution<unsigned>n2(0, 650);
	
	for (unsigned int i = 0; i < 16; ++i)
	{
		int k;
		_previewZombies.size() < 20 ? k = n(_random) + 1 : k = 1;
		for (int j = 0; j < k; ++j)
		{
			auto zombies = GSAnimationLayer::createDifferentZombies(static_cast<ZombiesType>(i+1), this);
			zombies->setZombiePosition(getPreviewZombiesPosition(n1, n2));
			zombies->setZombieTag(_previewZombiesTag++);
			zombies->createPreviewZombie();
			zombies->setZombieOpacity(255);

			PreviewZombies previewzombies{};
			previewzombies.animation = zombies->getZombieAnimation();
			previewzombies.position_y = previewzombies.animation->getPositionY();
			previewzombies.position_x = previewzombies.animation->getPositionX();
			_previewZombies.push_back(previewzombies);
		}
	}

	sortZombiesPosition();
}
