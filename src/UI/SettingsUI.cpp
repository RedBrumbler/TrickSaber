#include "UI/SettingsUI.hpp"
#include "logging.hpp"

#include "bsml/shared/Helpers/getters.hpp"
#include "bsml/shared/BSML/MenuButtons/MenuButtons.hpp"
#include "bsml/shared/BSML.hpp"

#include "HMUI/ViewController_AnimationDirection.hpp"

DEFINE_TYPE(TrickSaber::UI, SettingsUI);

namespace TrickSaber::UI {
    void SettingsUI::ctor(GlobalNamespace::MainFlowCoordinator* mainFlowCoordinator, TrickSaberFlowCoordinator* trickSaberFlowCoordinator) {
        DEBUG("ctor");
        _trickSaberFlowCoordinator = trickSaberFlowCoordinator;
        _mainFlowCoordinator = mainFlowCoordinator;
        _menuButton = BSML::MenuButton::Make_new("Trick Saber", "Change your tricks!", std::bind(&SettingsUI::ShowFlow, this));
    }

    void SettingsUI::ShowFlow() {
        _mainFlowCoordinator->YoungestChildFlowCoordinatorOrSelf()->PresentFlowCoordinator(_trickSaberFlowCoordinator, nullptr, HMUI::ViewController::AnimationDirection::Horizontal, false, false);
    }

    void SettingsUI::Initialize() {
        DEBUG("Init");
        BSML::Register::RegisterMenuButton(_menuButton);
    }

    void SettingsUI::Dispose() {
        DEBUG("Dispose");
        BSML::Register::UnRegisterMenuButton(_menuButton);
    }
}