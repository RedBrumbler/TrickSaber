#include "UI/TrickSaberFlowCoordinator.hpp"
#include "config.hpp"

#include "HMUI/ViewController_AnimationDirection.hpp"
#include "HMUI/ViewController_AnimationType.hpp"

DEFINE_TYPE(TrickSaber::UI, TrickSaberFlowCoordinator);

namespace TrickSaber::UI {
    void TrickSaberFlowCoordinator::Inject(GlobalNamespace::MainFlowCoordinator* mainFlowCoordinator, ViewControllers::BindingsViewController* bindingsViewController, ViewControllers::MiscViewController* miscViewController, ViewControllers::ThresholdViewController* thresholdViewController) {
        _mainFlowCoordinator = mainFlowCoordinator;
        _bindingsViewController = bindingsViewController;
        _miscViewController = miscViewController;
        _thresholdViewController = thresholdViewController;
    }

    void TrickSaberFlowCoordinator::DidActivate(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {
        if (!firstActivation) return;
        set_showBackButton(true);
        SetTitle("TrickSaber", HMUI::ViewController::AnimationType::In);
        ProvideInitialViewControllers(_bindingsViewController, _miscViewController, _thresholdViewController, nullptr, nullptr);
    }

    void TrickSaberFlowCoordinator::DidDeactivate(bool removedFromHierarchy, bool screenSystemDisabling) {
    }

    void TrickSaberFlowCoordinator::BackButtonWasPressed(HMUI::ViewController* topViewController) {
        parentFlowCoordinator->DismissFlowCoordinator(this, HMUI::ViewController::AnimationDirection::Horizontal, nullptr, false);
    }

}