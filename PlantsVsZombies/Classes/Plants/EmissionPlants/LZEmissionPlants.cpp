﻿/**
 *Copyright (c) 2020 LZ.All Right Reserved
 *Author : LZ
 *Date: 2020.2.6
 *Email: 2117610943@qq.com
 */

#include "LZEmissionPlants.h"
#include "Based/LZPlayMusic.h"

EmissionPlants::EmissionPlants():
    _isChanged(false)
,   _isHaveZombies(false)
,   _isReadFileData(false)
,   _bulletAnimation(nullptr)
{
}

EmissionPlants::~EmissionPlants()
{
}

void EmissionPlants::createListener(std::string animationName, std::string actionName, std::string musicName)
{
    _plantAnimation->setEventListener([=](spTrackEntry* entry, spEvent* event)
        {
            if (!actionName.compare(event->data->name))
            {
                if (!_isReadFileData)
                {
                    _isReadFileData = true;
                    if (musicName.empty())
                    {
                        PlayMusic::playMusic(rand() % 2 ? "throw" : "throw2");
                    }
                    else
                    {
                        PlayMusic::playMusic(musicName);
                    }
                    createBullet();
                }
            }
        });

    _plantAnimation->setCompleteListener([=](spTrackEntry* entry)
        {
            if (!animationName.compare(entry->animation->name))
            {
                _isReadFileData = false;
            }
        });
}

void EmissionPlants::cavePlantInformation(rapidjson::Value& object, rapidjson::Document::AllocatorType& allocator)
{
    object.AddMember("isChanged", _isChanged, allocator);
    object.AddMember("IsReadFileData", _isReadFileData, allocator);
}

void EmissionPlants::readPlantInforamtion(rapidjson::Document* levelDataDocument, char* key, int i)
{
    _isReadFileData = (*levelDataDocument)[key]["Plants"][to_string(i).c_str()]["IsReadFileData"].GetBool();
    _isChanged = (*levelDataDocument)[key]["Plants"][to_string(i).c_str()]["isChanged"].GetBool();
}