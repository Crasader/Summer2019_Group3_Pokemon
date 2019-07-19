LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := MyGame_shared

LOCAL_MODULE_FILENAME := libMyGame

LOCAL_SRC_FILES := $(LOCAL_PATH)/hellocpp/main.cpp \
                   $(LOCAL_PATH)/../../../Classes/AppDelegate.cpp \
                   $(LOCAL_PATH)/../../../Classes/HelloWorldScene.cpp \
                   $(LOCAL_PATH)/../../../Classes/Bag.cpp \
    $(LOCAL_PATH)/../../../Classes/Buttons.cpp \
    $(LOCAL_PATH)/../../../Classes/Item.cpp \
    $(LOCAL_PATH)/../../../Classes/Map/House.cpp \
    $(LOCAL_PATH)/../../../Classes/Map/Lab.cpp \
    $(LOCAL_PATH)/../../../Classes/Map/Lake.cpp \
    $(LOCAL_PATH)/../../../Classes/Map/PokemonCenter.cpp \
    $(LOCAL_PATH)/../../../Classes/Map/Route1.cpp \
    $(LOCAL_PATH)/../../../Classes/Map/Town.cpp \
    $(LOCAL_PATH)/../../../Classes/MyObject.cpp \
    $(LOCAL_PATH)/../../../Classes/NPC.cpp \
    $(LOCAL_PATH)/../../../Classes/NPC/CaveNPC.cpp \
    $(LOCAL_PATH)/../../../Classes/NPC/ChampionNPC.cpp \
    $(LOCAL_PATH)/../../../Classes/NPC/CityNPC.cpp \
    $(LOCAL_PATH)/../../../Classes/NPC/KhuongDuyNPC.cpp \
    $(LOCAL_PATH)/../../../Classes/NPC/LakeNPC.cpp \
    $(LOCAL_PATH)/../../../Classes/NPC/MinhVuongNPC.cpp \
    $(LOCAL_PATH)/../../../Classes/NPC/RouteNPC.cpp \
    $(LOCAL_PATH)/../../../Classes/NPC/TanNgocNPC.cpp \
    $(LOCAL_PATH)/../../../Classes/NPC/TanTaiNPC.cpp \
    $(LOCAL_PATH)/../../../Classes/Pokemon.cpp \
    $(LOCAL_PATH)/../../../Classes/Pokemon/Bayleef.cpp \
    $(LOCAL_PATH)/../../../Classes/Pokemon/Beautifly.cpp \
    $(LOCAL_PATH)/../../../Classes/Pokemon/Blastoise.cpp \
    $(LOCAL_PATH)/../../../Classes/Pokemon/Celebi.cpp \
    $(LOCAL_PATH)/../../../Classes/Pokemon/Charizard.cpp \
    $(LOCAL_PATH)/../../../Classes/Pokemon/Charmander.cpp \
    $(LOCAL_PATH)/../../../Classes/Pokemon/Charmeleon.cpp \
    $(LOCAL_PATH)/../../../Classes/Pokemon/Chikorita.cpp \
    $(LOCAL_PATH)/../../../Classes/Pokemon/Dragonair.cpp \
    $(LOCAL_PATH)/../../../Classes/Pokemon/Dragonite.cpp \
    $(LOCAL_PATH)/../../../Classes/Pokemon/Eevee.cpp \
    $(LOCAL_PATH)/../../../Classes/Pokemon/Electrike.cpp \
    $(LOCAL_PATH)/../../../Classes/Pokemon/Entei.cpp \
    $(LOCAL_PATH)/../../../Classes/Pokemon/Farfetchd.cpp \
    $(LOCAL_PATH)/../../../Classes/Pokemon/Feebas.cpp \
    $(LOCAL_PATH)/../../../Classes/Pokemon/Flareon.cpp \
    $(LOCAL_PATH)/../../../Classes/Pokemon/Garchomp.cpp \
    $(LOCAL_PATH)/../../../Classes/Pokemon/Gardevoir.cpp \
    $(LOCAL_PATH)/../../../Classes/Pokemon/Greninja.cpp \
    $(LOCAL_PATH)/../../../Classes/Pokemon/Jolteon.cpp \
    $(LOCAL_PATH)/../../../Classes/Pokemon/Kirlia.cpp \
    $(LOCAL_PATH)/../../../Classes/Pokemon/Leafeon.cpp \
    $(LOCAL_PATH)/../../../Classes/Pokemon/Manectric.cpp \
    $(LOCAL_PATH)/../../../Classes/Pokemon/Meganium.cpp \
    $(LOCAL_PATH)/../../../Classes/Pokemon/Meowth.cpp \
    $(LOCAL_PATH)/../../../Classes/Pokemon/Milotic.cpp \
    $(LOCAL_PATH)/../../../Classes/Pokemon/Pidgeot.cpp \
    $(LOCAL_PATH)/../../../Classes/Pokemon/Pidgeotto.cpp \
    $(LOCAL_PATH)/../../../Classes/Pokemon/Pidgey.cpp \
    $(LOCAL_PATH)/../../../Classes/Pokemon/Pikachu.cpp \
    $(LOCAL_PATH)/../../../Classes/Pokemon/Ponyta.cpp \
    $(LOCAL_PATH)/../../../Classes/Pokemon/Raikou.cpp \
    $(LOCAL_PATH)/../../../Classes/Pokemon/Ralts.cpp \
    $(LOCAL_PATH)/../../../Classes/Pokemon/Salamence.cpp \
    $(LOCAL_PATH)/../../../Classes/Pokemon/Shaymin.cpp \
    $(LOCAL_PATH)/../../../Classes/Pokemon/Skymin.cpp \
    $(LOCAL_PATH)/../../../Classes/Pokemon/Snorlax.cpp \
    $(LOCAL_PATH)/../../../Classes/Pokemon/Squirtle.cpp \
    $(LOCAL_PATH)/../../../Classes/Pokemon/Suicune.cpp \
    $(LOCAL_PATH)/../../../Classes/Pokemon/Swellow.cpp \
    $(LOCAL_PATH)/../../../Classes/Pokemon/Taillow.cpp \
    $(LOCAL_PATH)/../../../Classes/Pokemon/Vaporeon.cpp \
    $(LOCAL_PATH)/../../../Classes/Pokemon/Voltorb.cpp \
    $(LOCAL_PATH)/../../../Classes/Pokemon/Vulpix.cpp \
    $(LOCAL_PATH)/../../../Classes/Pokemon/Wartortle.cpp \
    $(LOCAL_PATH)/../../../Classes/Popup.cpp \
    $(LOCAL_PATH)/../../../Classes/ResourceManager.cpp \
    $(LOCAL_PATH)/../../../Classes/Scene/BattleScene.cpp \
    $(LOCAL_PATH)/../../../Classes/Scene/BuyItem.cpp \
    $(LOCAL_PATH)/../../../Classes/Scene/Loading.cpp \
    $(LOCAL_PATH)/../../../Classes/Scene/MainMenu.cpp \
    $(LOCAL_PATH)/../../../Classes/Scene/MyBag.cpp \
    $(LOCAL_PATH)/../../../Classes/Skill.cpp \
    $(LOCAL_PATH)/../../../Classes/Skill/Bite.cpp \
    $(LOCAL_PATH)/../../../Classes/Skill/BlastBurn.cpp \
    $(LOCAL_PATH)/../../../Classes/Skill/BodySlam.cpp \
    $(LOCAL_PATH)/../../../Classes/Skill/Bubble.cpp \
    $(LOCAL_PATH)/../../../Classes/Skill/DracoMeteor.cpp \
    $(LOCAL_PATH)/../../../Classes/Skill/DragonClaw.cpp \
    $(LOCAL_PATH)/../../../Classes/Skill/DragonCut.cpp \
    $(LOCAL_PATH)/../../../Classes/Skill/Ember.cpp \
    $(LOCAL_PATH)/../../../Classes/Skill/EnergyBall.cpp \
    $(LOCAL_PATH)/../../../Classes/Skill/FireBlast.cpp \
    $(LOCAL_PATH)/../../../Classes/Skill/FirePunch.cpp \
    $(LOCAL_PATH)/../../../Classes/Skill/Fly.cpp \
    $(LOCAL_PATH)/../../../Classes/Skill/Gust.cpp \
    $(LOCAL_PATH)/../../../Classes/Skill/Peck.cpp \
    $(LOCAL_PATH)/../../../Classes/Skill/QuickAttack.cpp \
    $(LOCAL_PATH)/../../../Classes/Skill/RazorLeaf.cpp \
    $(LOCAL_PATH)/../../../Classes/Skill/Scratch.cpp \
    $(LOCAL_PATH)/../../../Classes/Skill/SolarBeam.cpp \
    $(LOCAL_PATH)/../../../Classes/Skill/Spark.cpp \
    $(LOCAL_PATH)/../../../Classes/Skill/Surf.cpp \
    $(LOCAL_PATH)/../../../Classes/Skill/Tackle.cpp \
    $(LOCAL_PATH)/../../../Classes/Skill/Thunder.cpp \
    $(LOCAL_PATH)/../../../Classes/Skill/Thunderbolt.cpp \
    $(LOCAL_PATH)/../../../Classes/Skill/ThunderShock.cpp \
    $(LOCAL_PATH)/../../../Classes/Skill/VineWhip.cpp \
    $(LOCAL_PATH)/../../../Classes/Skill/WaterGun.cpp \
    $(LOCAL_PATH)/../../../Classes/Skill/WaterPulse.cpp \
    $(LOCAL_PATH)/../../../Classes/Skill/WingAttack.cpp \
    $(LOCAL_PATH)/../../../Classes/Trainer.cpp \

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../Classes

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cc_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module, cocos)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
