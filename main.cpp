#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;

namespace Bolonli {
    static bool noDeath() {
        return Mod::get()->getSettingValue<bool>("no-death");
    }

    static float speed() {
        return static_cast<float>(Mod::get()->getSettingValue<double>("speed"));
    }
}

/*
 * Main-menu entry point.
 *
 * On Android this uses the normal Geode touch button system, so it does not
 * require a hardware keyboard.
 */
class $modify(BolonliMenuLayer, MenuLayer) {
    bool init() {
        if (!MenuLayer::init())
            return false;

        auto menu = this->getChildByID("bottom-menu");
        if (!menu)
            return true;

        auto label = CCLabelBMFont::create("BOLONLI", "goldFont.fnt");
        label->setScale(0.42f);

        auto button = CCMenuItemSpriteExtra::create(
            label,
            this,
            menu_selector(BolonliMenuLayer::onBolonli)
        );

        button->setID("bolonli-button"_spr);
        menu->addChild(button);
        menu->updateLayout();

        return true;
    }

    void onBolonli(CCObject*) {
        auto noDeath = Bolonli::noDeath();
        auto speed = Bolonli::speed();

        FLAlertLayer::create(
            "BolonliMod",
            fmt::format(
                "No Death: <cy>{}</c><br>Game Speed: <cy>{:.2f}x</c><br><br>"
                "Change the cheats in the BolonliMod settings.",
                noDeath ? "ON" : "OFF",
                speed
            ),
            "OK"
        )->show();
    }
};

/*
 * No Death:
 * PlayLayer::destroyPlayer is the central death callback used by the game.
 * Returning without calling the original function prevents the normal death
 * sequence. This is intentionally a simple first Android build.
 */
class $modify(BolonliPlayLayer, PlayLayer) {
    void destroyPlayer(PlayerObject* player, GameObject* object) {
        if (Bolonli::noDeath()) {
            if (player) {
                // Keep the player active instead of entering the death flow.
                player->setVisible(true);
            }
            return;
        }

        PlayLayer::destroyPlayer(player, object);
    }

    /*
     * Speed control. 1.0 = normal. Values below 1 slow the game;
     * values above 1 speed it up.
     */
    void update(float dt) {
        auto multiplier = Bolonli::speed();

        if (multiplier <= 0.0f)
            multiplier = 1.0f;

        PlayLayer::update(dt * multiplier);
    }
};
