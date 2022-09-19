#include "UI/ViewControllers/BindingsViewController.hpp"
#include "config.hpp"
#include "assets.hpp"

#include "bsml/shared/BSML.hpp"

DEFINE_TYPE(TrickSaber::UI::ViewControllers, BindingsViewController);

namespace TrickSaber::UI::ViewControllers {
    void BindingsViewController::DidActivate(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {
        if (!firstActivation) return;
        BSML::parse_and_construct(IncludedAssets::BindingsView_bsml, get_transform(), this);
    }

    void BindingsViewController::CheckMultiBinding() {
        std::unordered_set<TrickAction> boundActions;
        bool isMultiBinding = false;

        if (config.triggerAction != TrickAction::None && boundActions.find(config.triggerAction) != boundActions.end()) isMultiBinding = true;
        else boundActions.emplace(config.triggerAction);

        if (config.gripAction != TrickAction::None && boundActions.find(config.gripAction) != boundActions.end()) isMultiBinding = true;
        else boundActions.emplace(config.gripAction);

        if (config.thumbstickAction != TrickAction::None && boundActions.find(config.thumbstickAction) != boundActions.end()) isMultiBinding = true;
        else boundActions.emplace(config.thumbstickAction);

        set_multiBindingTextActive(isMultiBinding);
    }

    StringW BindingsViewController::get_version() {
        return VERSION;
    }

    StringW BindingsViewController::get_contactInfo() {
        return "My Discord : RedBrumbler#6295";
    }

    bool BindingsViewController::get_newerVersionAvailable() {
        // TODO: when lapiz supports it, implement this stuff
        return false;
    }

    StringW BindingsViewController::get_newerVersionText() {
        // TODO: when lapiz supports it, implement this stuff properly
        auto remoteVersion = VERSION;
        return fmt::format("Newer version available on Github ({})", remoteVersion);
    }

    bool BindingsViewController::get_multiBindingTextActive() {
        return _multiBindingTextActive;
    }

    void BindingsViewController::set_multiBindingTextActive(bool value) {
        _multiBindingTextActive = value;
        
        if (multiBindingTextLayout && multiBindingTextLayout->m_CachedPtr.m_value) 
            multiBindingTextLayout->get_gameObject()->SetActive(value);
    }


    StringW BindingsViewController::get_triggerAction() { return TrickAction_toString(config.triggerAction); }
    void BindingsViewController::set_triggerAction(StringW value) { 
        config.triggerAction = TrickAction_fromString(value);
        CheckMultiBinding();
    }

    StringW BindingsViewController::get_gripAction() { return TrickAction_toString(config.gripAction); }
    void BindingsViewController::set_gripAction(StringW value) { 
        config.gripAction = TrickAction_fromString(value);
        CheckMultiBinding();
    }

    StringW BindingsViewController::get_thumbAction() { return TrickAction_toString(config.thumbstickAction); }
    void BindingsViewController::set_thumbAction(StringW value) { 
        config.thumbstickAction = TrickAction_fromString(value); 
        CheckMultiBinding();
    }

    bool BindingsViewController::get_reverseTrigger() { return config.reverseTrigger; }
    void BindingsViewController::set_reverseTrigger(bool value) { config.reverseTrigger = value;}
    bool BindingsViewController::get_reverseGrip() { return config.reverseGrip; }
    void BindingsViewController::set_reverseGrip(bool value) { config.reverseGrip = value;}
    bool BindingsViewController::get_reverseThumbstick() { return config.reverseThumbstick; }
    void BindingsViewController::set_reverseThumbstick(bool value) { config.reverseThumbstick = value;}
}