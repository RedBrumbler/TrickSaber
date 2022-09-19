#include "UI/ViewControllers/MiscViewController.hpp"
#include "config.hpp"
#include "assets.hpp"

#include "UnityEngine/RectTransform.hpp"
#include "UnityEngine/Vector2.hpp"
#include "bsml/shared/BSML.hpp"

DEFINE_TYPE(TrickSaber::UI::ViewControllers, MiscViewController);

namespace TrickSaber::UI::ViewControllers {
    void MiscViewController::DidActivate(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {
        if (!firstActivation) return;
        BSML::parse_and_construct(IncludedAssets::MiscView_bsml, get_transform(), this);
    }

    void MiscViewController::PostParse() {
        if (scrollable && scrollable->m_CachedPtr.m_value && scrollable->get_name() == "BSMLScrollableSettingsContainer")
        {
            auto rect = reinterpret_cast<UnityEngine::RectTransform*>(scrollable);
            rect->set_anchoredPosition({0, 0});
            rect->set_sizeDelta({-4, -4});
        }
    }
    
    StringW MiscViewController::get_thumbstickDir() { return ThumbstickDir_toString(config.thumbstickDirection); }
    void MiscViewController::set_thumbstickDir(StringW value) { config.thumbstickDirection = ThumbstickDir_fromString(value); }
    bool MiscViewController::get_isSpeedVelocityDependent() { return config.isSpeedVelocityDependent; }
    void MiscViewController::set_isSpeedVelocityDependent(bool value) { config.isSpeedVelocityDependent = value; }
    float MiscViewController::get_spinSpeed() { return config.spinSpeed; }
    void MiscViewController::set_spinSpeed(float value) { config.spinSpeed = value; }
    StringW MiscViewController::get_spinDir() { return SpinDir_toString(config.spinDirection); }
    void MiscViewController::set_spinDir(StringW value) { config.spinDirection = SpinDir_fromString(value); }
    float MiscViewController::get_throwVelocity() { return config.throwVelocity; }
    void MiscViewController::set_throwVelocity(float value) { config.throwVelocity = value; }
    float MiscViewController::get_returnSpeed() { return config.returnSpeed; }
    void MiscViewController::set_returnSpeed(float value) { config.returnSpeed = value; }
    bool MiscViewController::get_slowmoDuringThrow() { return config.slowmoDuringThrow; }
    void MiscViewController::set_slowmoDuringThrow(bool value) { config.slowmoDuringThrow = value; }
    bool MiscViewController::get_disableIfNotesOnScreen() { return config.disableIfNotesOnScreen; }
    void MiscViewController::set_disableIfNotesOnScreen(bool value) { config.disableIfNotesOnScreen = value; }
    bool MiscViewController::get_hitNotesDuringTrick() { return config.hitNotesDuringTrick; }
    void MiscViewController::set_hitNotesDuringTrick(bool value) { config.hitNotesDuringTrick = value; }
}