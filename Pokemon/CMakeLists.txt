#/****************************************************************************
# Copyright (c) 2013-2014 cocos2d-x.org
# Copyright (c) 2015-2017 Chukong Technologies Inc.
#
# http://www.cocos2d-x.org
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the Software), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED AS IS, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
# ****************************************************************************/

cmake_minimum_required(VERSION 3.6)

set(APP_NAME Pokemon)

project(${APP_NAME})

set(COCOS2DX_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cocos2d)
set(CMAKE_MODULE_PATH ${COCOS2DX_ROOT_PATH}/cmake/Modules/)

include(CocosBuildSet)
add_subdirectory(${COCOS2DX_ROOT_PATH}/cocos ${ENGINE_BINARY_PATH}/cocos/core)

# record sources, headers, resources...
set(GAME_SOURCE)
set(GAME_HEADER)

set(GAME_RES_FOLDER
    ${CMAKE_CURRENT_SOURCE_DIR}/Resources
    )
if(APPLE OR WINDOWS)
    cocos_mark_multi_resources(common_res_files RES_TO Resources FOLDERS ${GAME_RES_FOLDER})
endif()

# add cross-platforms source files and header files 
list(APPEND GAME_SOURCE
     Classes/AppDelegate.cpp
     Classes/HelloWorldScene.cpp
    Classes/Bag.cpp 
    Classes/Buttons.cpp 
    Classes/Item.cpp 
    Classes/Item/Ether.cpp 
    Classes/Item/FireStone.cpp 
    Classes/Item/LeafStone.cpp 
    Classes/Item/MaxPotion.cpp 
    Classes/Item/MaxRevive.cpp 
    Classes/Item/Potion.cpp 
    Classes/Item/Revive.cpp 
    Classes/Item/SuperPotion.cpp 
    Classes/Item/ThunderStone.cpp 
    Classes/Item/WaterStone.cpp 
    Classes/Map/Cave.cpp 
    Classes/Map/ChampionLeague.cpp 
    Classes/Map/City.cpp 
    Classes/Map/House.cpp 
    Classes/Map/Lab.cpp 
    Classes/Map/Lake.cpp 
    Classes/Map/PokemonCenter.cpp 
    Classes/Map/Route1.cpp 
    Classes/Map/Route2.cpp 
    Classes/Map/Town.cpp 
    Classes/Map/VictoryRoad.cpp 
    Classes/Model.cpp 
    Classes/MyObject.cpp 
    Classes/NPC.cpp 
    Classes/NPC/CaveNPC.cpp 
    Classes/NPC/ChampionNPC.cpp 
    Classes/NPC/CityNPC.cpp 
    Classes/NPC/KhuongDuyNPC.cpp 
    Classes/NPC/LakeNPC.cpp 
    Classes/NPC/MinhVuongNPC.cpp 
    Classes/NPC/RoadNPC.cpp 
    Classes/NPC/Route2NPC.cpp 
    Classes/NPC/RouteNPC.cpp 
    Classes/NPC/TanNgocNPC.cpp 
    Classes/NPC/TanTaiNPC.cpp 
    Classes/Pokemon.cpp 
    Classes/Pokemon/Bayleef.cpp 
    Classes/Pokemon/Beautifly.cpp 
    Classes/Pokemon/Blastoise.cpp 
    Classes/Pokemon/Celebi.cpp 
    Classes/Pokemon/Charizard.cpp 
    Classes/Pokemon/Charmander.cpp 
    Classes/Pokemon/Charmeleon.cpp 
    Classes/Pokemon/Chikorita.cpp 
    Classes/Pokemon/Dragonair.cpp 
    Classes/Pokemon/Dragonite.cpp 
    Classes/Pokemon/Eevee.cpp 
    Classes/Pokemon/Electrike.cpp 
    Classes/Pokemon/Entei.cpp 
    Classes/Pokemon/Farfetchd.cpp 
    Classes/Pokemon/Feebas.cpp 
    Classes/Pokemon/Flareon.cpp 
    Classes/Pokemon/Garchomp.cpp 
    Classes/Pokemon/Gardevoir.cpp 
    Classes/Pokemon/Greninja.cpp 
    Classes/Pokemon/Jolteon.cpp 
    Classes/Pokemon/Kirlia.cpp 
    Classes/Pokemon/Leafeon.cpp 
    Classes/Pokemon/Manectric.cpp 
    Classes/Pokemon/Meganium.cpp 
    Classes/Pokemon/Meowth.cpp 
    Classes/Pokemon/Milotic.cpp 
    Classes/Pokemon/Pidgeot.cpp 
    Classes/Pokemon/Pidgeotto.cpp 
    Classes/Pokemon/Pidgey.cpp 
    Classes/Pokemon/Pikachu.cpp 
    Classes/Pokemon/Ponyta.cpp 
    Classes/Pokemon/Raikou.cpp 
    Classes/Pokemon/Ralts.cpp 
    Classes/Pokemon/Salamence.cpp 
    Classes/Pokemon/Shaymin.cpp 
    Classes/Pokemon/Skymin.cpp 
    Classes/Pokemon/Snorlax.cpp 
    Classes/Pokemon/Squirtle.cpp 
    Classes/Pokemon/Suicune.cpp 
    Classes/Pokemon/Swellow.cpp 
    Classes/Pokemon/Taillow.cpp 
    Classes/Pokemon/Vaporeon.cpp 
    Classes/Pokemon/Voltorb.cpp 
    Classes/Pokemon/Vulpix.cpp 
    Classes/Pokemon/Wartortle.cpp 
    Classes/Popup.cpp 
    Classes/ResourceManager.cpp 
    Classes/Scene/BattleScene.cpp 
    Classes/Scene/Loading.cpp 
    Classes/Scene/MainMenu.cpp 
    Classes/Skill.cpp 
    Classes/Skill/Bite.cpp 
    Classes/Skill/BlastBurn.cpp 
    Classes/Skill/BodySlam.cpp 
    Classes/Skill/Bubble.cpp 
    Classes/Skill/DracoMeteor.cpp 
    Classes/Skill/DragonClaw.cpp 
    Classes/Skill/DragonCut.cpp 
    Classes/Skill/Ember.cpp 
    Classes/Skill/EnergyBall.cpp 
    Classes/Skill/FireBlast.cpp 
    Classes/Skill/FirePunch.cpp 
    Classes/Skill/Fly.cpp 
    Classes/Skill/Gust.cpp 
    Classes/Skill/Peck.cpp 
    Classes/Skill/QuickAttack.cpp 
    Classes/Skill/RazorLeaf.cpp 
    Classes/Skill/Scratch.cpp 
    Classes/Skill/LeafStorm.cpp 
    Classes/Skill/Spark.cpp 
    Classes/Skill/Surf.cpp 
    Classes/Skill/Tackle.cpp 
    Classes/Skill/Thunder.cpp 
    Classes/Skill/Thunderbolt.cpp 
    Classes/Skill/ThunderShock.cpp 
    Classes/Skill/LeechSeed.cpp 
    Classes/Skill/WaterGun.cpp 
    Classes/Skill/WaterPulse.cpp 
    Classes/Skill/WingAttack.cpp 
    Classes/Trainer.cpp
     )
list(APPEND GAME_HEADER
     Classes/AppDelegate.h
     Classes/HelloWorldScene.h
    Classes/Bag.h 
    Classes/Buttons.h 
    Classes/include_pokemon.h 
    Classes/include_skill.h 
    Classes/Item.h 
    Classes/Item/Ether.h 
    Classes/Item/FireStone.h 
    Classes/Item/LeafStone.h 
    Classes/Item/MaxPotion.h 
    Classes/Item/MaxRevive.h 
    Classes/Item/Potion.h 
    Classes/Item/Revive.h 
    Classes/Item/SuperPotion.h 
    Classes/Item/ThunderStone.h 
    Classes/Item/WaterStone.h 
    Classes/Map/Cave.h 
    Classes/Map/ChampionLeague.h 
    Classes/Map/City.h 
    Classes/Map/House.h 
    Classes/Map/Lab.h 
    Classes/Map/Lake.h 
    Classes/Map/PokemonCenter.h 
    Classes/Map/Route1.h 
    Classes/Map/Route2.h 
    Classes/Map/Town.h 
    Classes/Map/VictoryRoad.h 
    Classes/Model.h 
    Classes/MyObject.h 
    Classes/NPC.h 
    Classes/NPC/CaveNPC.h 
    Classes/NPC/ChampionNPC.h 
    Classes/NPC/CityNPC.h 
    Classes/NPC/KhuongDuyNPC.h 
    Classes/NPC/LakeNPC.h 
    Classes/NPC/MinhVuongNPC.h 
    Classes/NPC/RoadNPC.h 
    Classes/NPC/Route2NPC.h 
    Classes/NPC/RouteNPC.h 
    Classes/NPC/TanNgocNPC.h 
    Classes/NPC/TanTaiNPC.h 
    Classes/Pokemon.h 
    Classes/Pokemon/Bayleef.h 
    Classes/Pokemon/Beautifly.h 
    Classes/Pokemon/Blastoise.h 
    Classes/Pokemon/Celebi.h 
    Classes/Pokemon/Charizard.h 
    Classes/Pokemon/Charmander.h 
    Classes/Pokemon/Charmeleon.h 
    Classes/Pokemon/Chikorita.h 
    Classes/Pokemon/Dragonair.h 
    Classes/Pokemon/Dragonite.h 
    Classes/Pokemon/Eevee.h 
    Classes/Pokemon/Electrike.h 
    Classes/Pokemon/Entei.h 
    Classes/Pokemon/Farfetchd.h 
    Classes/Pokemon/Feebas.h 
    Classes/Pokemon/Flareon.h 
    Classes/Pokemon/Garchomp.h 
    Classes/Pokemon/Gardevoir.h 
    Classes/Pokemon/Greninja.h 
    Classes/Pokemon/Jolteon.h 
    Classes/Pokemon/Kirlia.h 
    Classes/Pokemon/Leafeon.h 
    Classes/Pokemon/Manectric.h 
    Classes/Pokemon/Meganium.h 
    Classes/Pokemon/Meowth.h 
    Classes/Pokemon/Milotic.h 
    Classes/Pokemon/Pidgeot.h 
    Classes/Pokemon/Pidgeotto.h 
    Classes/Pokemon/Pidgey.h 
    Classes/Pokemon/Pikachu.h 
    Classes/Pokemon/Ponyta.h 
    Classes/Pokemon/Raikou.h 
    Classes/Pokemon/Ralts.h 
    Classes/Pokemon/Salamence.h 
    Classes/Pokemon/Shaymin.h 
    Classes/Pokemon/Skymin.h 
    Classes/Pokemon/Snorlax.h 
    Classes/Pokemon/Squirtle.h 
    Classes/Pokemon/Suicune.h 
    Classes/Pokemon/Swellow.h 
    Classes/Pokemon/Taillow.h 
    Classes/Pokemon/Vaporeon.h 
    Classes/Pokemon/Voltorb.h 
    Classes/Pokemon/Vulpix.h 
    Classes/Pokemon/Wartortle.h 
    Classes/Popup.h 
    Classes/ResourceManager.h 
    Classes/Scene/BattleScene.h 
    Classes/Scene/Loading.h 
    Classes/Scene/MainMenu.h 
    Classes/Skill.h 
    Classes/Skill/Bite.h 
    Classes/Skill/BlastBurn.h 
    Classes/Skill/BodySlam.h 
    Classes/Skill/Bubble.h 
    Classes/Skill/DracoMeteor.h 
    Classes/Skill/DragonClaw.h 
    Classes/Skill/DragonCut.h 
    Classes/Skill/Ember.h 
    Classes/Skill/EnergyBall.h 
    Classes/Skill/FireBlast.h 
    Classes/Skill/FirePunch.h 
    Classes/Skill/Fly.h 
    Classes/Skill/Gust.h 
    Classes/Skill/Peck.h 
    Classes/Skill/QuickAttack.h 
    Classes/Skill/RazorLeaf.h 
    Classes/Skill/Scratch.h 
    Classes/Skill/LeafStorm.h 
    Classes/Skill/Spark.h 
    Classes/Skill/Surf.h 
    Classes/Skill/Tackle.h 
    Classes/Skill/Thunder.h 
    Classes/Skill/Thunderbolt.h 
    Classes/Skill/ThunderShock.h 
    Classes/Skill/LeechSeed.h 
    Classes/Skill/WaterGun.h 
    Classes/Skill/WaterPulse.h 
    Classes/Skill/WingAttack.h 
    Classes/Trainer.h
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
    set_target_properties(${APP_NAME} PROPERTIES RESOURCE ${APP_UI_RES})
    if(MACOSX)
        set_target_properties(${APP_NAME} PROPERTIES
                              MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/proj.ios_mac/mac/Info.plist
                              )
    elseif(IOS)
        cocos_pak_xcode(${APP_NAME} INFO_PLIST iOSBundleInfo.plist.in)
        set_xcode_property(${APP_NAME} ASSETCATALOG_COMPILER_APPICON_NAME AppIcon)
        set_xcode_property(${APP_NAME} DEVELOPMENT_TEAM )
        set_xcode_property(${APP_NAME} CODE_SIGN_IDENTITY iPhone Developer)
    endif()
elseif(WINDOWS)
    cocos_copy_target_dll(${APP_NAME})
endif()

if(LINUX OR WINDOWS)
    set(APP_RES_DIR $<TARGET_FILE_DIR:${APP_NAME}>/Resources)
    cocos_copy_target_res(${APP_NAME} COPY_TO ${APP_RES_DIR} FOLDERS ${GAME_RES_FOLDER})
endif()
