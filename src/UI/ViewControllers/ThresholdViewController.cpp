#include "UI/ViewControllers/ThresholdViewController.hpp"
#include "config.hpp"
#include "assets.hpp"

#include "bsml/shared/BSML.hpp"

DEFINE_TYPE(TrickSaber::UI::ViewControllers, ThresholdViewController);

namespace TrickSaber::UI::ViewControllers {
    void ThresholdViewController::DidActivate(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {
        if (!firstActivation) return;
        BSML::parse_and_construct(IncludedAssets::ThresholdView_bsml, get_transform(), this);
    }

    float ThresholdViewController::get_triggerThresh() { return config.triggerThreshold; }
    void ThresholdViewController::set_triggerThresh(float value) { config.triggerThreshold = value; }
    float ThresholdViewController::get_thumbTresh() { return config.thumbstickThreshold; }
    void ThresholdViewController::set_thumbTresh(float value) { config.thumbstickThreshold = value; }
    float ThresholdViewController::get_gripThresh() { return config.gripThreshold; }
    void ThresholdViewController::set_gripThresh(float value) { config.gripThreshold = value; }
    float ThresholdViewController::get_controllerSnapThresh() { return config.controllerSnapThreshold; }
    void ThresholdViewController::set_controllerSnapThresh(float value) { config.controllerSnapThreshold = value; }
}