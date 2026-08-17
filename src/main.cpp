#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;

class $modify(BolonliPlayLayer, PlayLayer) {
    void destroyPlayer(PlayerObject* player, GameObject* object) {
        if (Mod::get()->getSettingValue<bool>("no-death")) {
            // Встроенная функция GD для игнорирования урона.
            this->toggleIgnoreDamage(true);
            return;
        }

        PlayLayer::destroyPlayer(player, object);
    }
};
