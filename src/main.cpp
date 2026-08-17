#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;

class $modify(BolonliPlayLayer, PlayLayer) {
    void update(float dt) {
        float speed = static_cast<float>(
            Mod::get()->getSettingValue<double>("speed")
        );

        // Защита от некорректных значений
        speed = std::clamp(speed, 0.25f, 3.0f);

        PlayLayer::update(dt * speed);
    }

    void destroyPlayer(PlayerObject* player, GameObject* object) {
        if (Mod::get()->getSettingValue<bool>("no-death")) {
            this->toggleIgnoreDamage(true);
            return;
        }

        PlayLayer::destroyPlayer(player, object);
    }
};
