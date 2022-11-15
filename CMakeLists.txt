#/****************************************************************************
# Copyright (c) 2013-2014 cocos2d-x.org
# Copyright (c) 2015-2017 Chukong Technologies Inc.
#
# http://www.cocos2d-x.org
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
# ****************************************************************************/

cmake_minimum_required(VERSION 3.6)

set(APP_NAME CMyGame)

project(${APP_NAME})

if(XCODE)
    if(NOT DEFINED CMAKE_XCODE_ATTRIBUTE_IPHONEOS_DEPLOYMENT_TARGET)
        SET (CMAKE_XCODE_ATTRIBUTE_IPHONEOS_DEPLOYMENT_TARGET 8.0)
    endif()
endif()

if(NOT DEFINED BUILD_ENGINE_DONE) # to test CMyGame into root project
    set(COCOS2DX_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cocos2d)
    set(CMAKE_MODULE_PATH ${COCOS2DX_ROOT_PATH}/cmake/Modules/)

    include(CocosBuildSet)
    set(CMAKE_CXX_STANDARD 17)
    add_subdirectory(${COCOS2DX_ROOT_PATH}/cocos ${ENGINE_BINARY_PATH}/cocos/core)
endif()

# record sources, headers, resources...
set(GAME_SOURCE)
set(GAME_HEADER)

set(GAME_RES_FOLDER
    "${CMAKE_CURRENT_SOURCE_DIR}/Resources"
    )
if(APPLE OR WINDOWS)
    cocos_mark_multi_resources(common_res_files RES_TO "Resources" FOLDERS ${GAME_RES_FOLDER})
endif()

# add cross-platforms source files and header files 
list(APPEND GAME_SOURCE
     Classes/AppDelegate.cpp
     Classes/HelloWorldScene.cpp
        Classes/GameScene/MainMenuScene.cpp
        Classes/GameScene/PauseScene.cpp
        Classes/GameScene/GameOverScene.cpp
        Classes/GameScene/GameScene.cpp
        Classes/GameScene/BattleScene.cpp
        Classes/GameScene/Login.cpp
        Classes/GameScene/ShopScene.cpp

        Classes/User/User.cpp

        Classes/Champion/Champion.cpp
        Classes/Champion/ChampionStatus_Buff.cpp
        Classes/Champion/ChampionStatus_Debuff.cpp
        Classes/Champion/Hero/Hero.cpp

        Classes/Item/Weapon/Weapon.cpp
        Classes/Item/Item.cpp

        Classes/DataManager/UserData_Manager.cpp
        Classes/DataManager/ChampionData_Manager.cpp
        Classes/DataManager/Database.cpp
        Classes/DataManager/ItemData_Manager.cpp

        Classes/GameObject/GameObject.cpp

        Classes/ObjectManager/BulletManager.cpp

        Classes/GameFight/GameEnvironment.cpp
        Classes/GameFight/BattleElement.cpp

        Classes/Player/Player.cpp
        Classes/Player/Human/Human.cpp
        Classes/Player/Bot/Bot.cpp

        Classes/Factory/GameObjectFactory.cpp
        Classes/Factory/BulletPhysicFactory.cpp
        Classes/Factory/Bot_Factory.cpp
        Classes/Factory/SkillFactory.cpp
        Classes/Factory/ChampionSkillFacatory.cpp
        Classes/Factory/SkillTriggerCondition.cpp
        Classes/Factory/SkillTypeFactory.cpp
        Classes/Factory/PlayerFactory.cpp

        Classes/Extention/Node_StringNTag.cpp
        Classes/Extention/InGameUI.cpp
        Classes/Extention/GameRandom.cpp

        Classes/Physic/BulletPhysic_Default.cpp

        Classes/Map/Map.cpp

        Classes/sqLite3/sqlite3.c

        Classes/Inventory/Inventory.cpp

        Classes/AI/HeroBot/Hero_Bot.cpp

        Classes/Skill/Passive/Passive.cpp
        Classes/Skill/Toggle/Toggle.cpp
        Classes/Skill/Active/Active.cpp

        Classes/Skill/SkillType/ShootBullet/ShootBullet.cpp
        Classes/Skill/SkillType/RunAnimation/RunAnimation.cpp

        Classes/Skill/TriggerCondition/OnDeath/OnDeath.cpp
        Classes/Skill/TriggerCondition/OnHit/OnHit.cpp
        Classes/Skill/TriggerCondition/OnAttack/OnAttack.cpp
        Classes/Skill/TriggerCondition/OnClick/OnClick.cpp
        Classes/Skill/TriggerCondition/AlwayActive/AlwayActive.cpp

        Classes/ChampionSkill/Hero/Normal_Attack.cpp

        Classes/Audio/SoundManager.cpp
     )
list(APPEND GAME_HEADER
     Classes/AppDelegate.h
     Classes/HelloWorldScene.h
        Classes/GameScene/MainMenuScene.h
        Classes/GameScene/PauseScene.h
        Classes/GameScene/GameOverScene.h
        Classes/GameScene/GameScene.h
        Classes/GameScene/BattleScene.h
        Classes/GameScene/ShopScene.h
        Classes/GameScene/Login.h

        Classes/User/User.h

        Classes/Champion/Champion.h
        Classes/Champion/ChampionStatus_Buff.h
        Classes/Champion/ChampionStatus_Debuff.h
        Classes/Champion/Hero/Hero.h

        Classes/GameObject/GameObject.h
        Classes/GameObject/AGameObject.h
        Classes/GameObject/Properties.h

        Classes/Extention/Statics_Attributes.h
        Classes/Extention/GameRandom.h
        Classes/Extention/ItemManager.h
        Classes/Extention/DamageManager.h
        Classes/Extention/Node_StringNTag.h
        Classes/Extention/InGameUI.h
        Classes/Extention/UserExtend.h
        Classes/Extention/ShopManager.h
        Classes/Extention/PlayerManager.h

        Classes/Item/Item.h
        Classes/Item/Weapon/Weapon.h

        Classes/DataManager/UserData_Manager.h
        Classes/DataManager/ChampionData_Manager.h
        Classes/DataManager/Database.h
        Classes/DataManager/ItemData_Manager.h

        Classes/Bullet/Bullet.h

        Classes/ObjectManager/BulletManager.h

        Classes/Physic/BulletPhysic.h
        Classes/Physic/BulletPhysic_Default.h

        Classes/GameFight/GameEnvironment.h
        Classes/GameFight/BattleElement.h

        Classes/Player/Player.h
        Classes/Player/Human/Human.h
        Classes/Player/Bot/Bot.h

        Classes/Factory/GameObjectFactory.h
        Classes/Factory/BulletPhysicFactory.h
        Classes/Factory/Bot_Factory.h
        Classes/Factory/SkillFactory.h
        Classes/Factory/ChampionSkillFacatory.h
        Classes/Factory/SkillTriggerCondition.h
        Classes/Factory/SkillTypeFactory.h
        Classes/Factory/PlayerFactory.h

        Classes/Map/Map.h

        Classes/sqLite3/sqlite3.h

        Classes/Inventory/Inventory.h

        Classes/AI/AI.h
        Classes/AI/HeroBot/Hero_Bot.h

        Classes/Skill/Skill.h
        Classes/Skill/Passive/Passive.h
        Classes/Skill/Toggle/Toggle.h
        Classes/Skill/Active/Active.h

        Classes/Skill/SkillType/SkillType.h
        Classes/Skill/SkillType/ShootBullet/ShootBullet.h
        Classes/Skill/SkillType/RunAnimation/RunAnimation.h

        Classes/Skill/TriggerCondition/TriggerCondition.h
        Classes/Skill/TriggerCondition/OnDeath/OnDeath.h
        Classes/Skill/TriggerCondition/OnHit/OnHit.h
        Classes/Skill/TriggerCondition/OnAttack/OnAttack.h
        Classes/Skill/TriggerCondition/OnClick/OnClick.h
        Classes/Skill/TriggerCondition/AlwayActive/AlwayActive.h

        Classes/ChampionSkill/ChampionSkill.h
        Classes/ChampionSkill/Hero/Normal_Attack.h

        Classes/Audio/SoundManager.h
     )

if(ANDROID)
    # change APP_NAME to the share library name for Android, it's value depend on AndroidManifest.xml
    set(APP_NAME MyGame)
    list(APPEND GAME_SOURCE
         proj.android/app/jni/hellocpp/main.cpp
         )
elseif(LINUX)
    list(APPEND GAME_SOURCE
         proj.linux/main.cpp
         )
elseif(WINDOWS)
    list(APPEND GAME_HEADER
         proj.win32/main.h
         proj.win32/resource.h
         )
    list(APPEND GAME_SOURCE
         proj.win32/main.cpp
         proj.win32/game.rc
         ${common_res_files}
         )
elseif(APPLE)
    if(IOS)
        list(APPEND GAME_HEADER
             proj.ios_mac/ios/AppController.h
             proj.ios_mac/ios/RootViewController.h
             )
        set(APP_UI_RES
            proj.ios_mac/ios/LaunchScreen.storyboard
            proj.ios_mac/ios/LaunchScreenBackground.png
            proj.ios_mac/ios/Images.xcassets
            )
        list(APPEND GAME_SOURCE
             proj.ios_mac/ios/main.m
             proj.ios_mac/ios/AppController.mm
             proj.ios_mac/ios/RootViewController.mm
             proj.ios_mac/ios/Prefix.pch
             ${APP_UI_RES}
             )
    elseif(MACOSX)
        set(APP_UI_RES
            proj.ios_mac/mac/Icon.icns
            proj.ios_mac/mac/Info.plist
            )
        list(APPEND GAME_SOURCE
             proj.ios_mac/mac/main.cpp
             proj.ios_mac/mac/Prefix.pch
             ${APP_UI_RES}
             )
    endif()
    list(APPEND GAME_SOURCE ${common_res_files})
endif()

# mark app complie info and libs info
set(all_code_files
    ${GAME_HEADER}
    ${GAME_SOURCE}
    )
if(NOT ANDROID)
    add_executable(${APP_NAME} ${all_code_files})
else()
    add_library(${APP_NAME} SHARED ${all_code_files})
    add_subdirectory(${COCOS2DX_ROOT_PATH}/cocos/platform/android ${ENGINE_BINARY_PATH}/cocos/platform)
    target_link_libraries(${APP_NAME} -Wl,--whole-archive cpp_android_spec -Wl,--no-whole-archive)
endif()

target_link_libraries(${APP_NAME} cocos2d)
target_include_directories(${APP_NAME}
        PRIVATE Classes
        PRIVATE ${COCOS2DX_ROOT_PATH}/cocos/audio/include/
)

# mark app resources
setup_cocos_app_config(${APP_NAME})
if(APPLE)
    set_target_properties(${APP_NAME} PROPERTIES RESOURCE "${APP_UI_RES}")

    if(MACOSX)
        set_xcode_property(${APP_NAME} INFOPLIST_FILE "${CMAKE_CURRENT_SOURCE_DIR}/proj.ios_mac/mac/Info.plist")
    elseif(IOS)
        set_xcode_property(${APP_NAME} INFOPLIST_FILE "${CMAKE_CURRENT_SOURCE_DIR}/proj.ios_mac/ios/Info.plist")
        set_xcode_property(${APP_NAME} ASSETCATALOG_COMPILER_APPICON_NAME "AppIcon")
    endif()

    # For code-signing, set the DEVELOPMENT_TEAM:
    #set_xcode_property(${APP_NAME} DEVELOPMENT_TEAM "GRLXXXX2K9")
elseif(WINDOWS)
    cocos_copy_target_dll(${APP_NAME})
endif()

if(LINUX OR WINDOWS)
    cocos_get_resource_path(APP_RES_DIR ${APP_NAME})
    cocos_copy_target_res(${APP_NAME} LINK_TO ${APP_RES_DIR} FOLDERS ${GAME_RES_FOLDER})
endif()
