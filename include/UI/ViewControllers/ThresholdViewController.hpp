#pragma once
#include "custom-types/shared/macros.hpp"
#include "lapiz/shared/macros.hpp"
#include "bsml/shared/macros.hpp"

#include "HMUI/ViewController.hpp"

DECLARE_CLASS_CODEGEN(TrickSaber::UI::ViewControllers, ThresholdViewController, HMUI::ViewController,
    DECLARE_OVERRIDE_METHOD(void, DidActivate, il2cpp_utils::il2cpp_type_check::MetadataGetter<&HMUI::ViewController::DidActivate>::get(), bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling);

    DECLARE_BSML_PROPERTY(float, triggerThresh);
    DECLARE_BSML_PROPERTY(float, thumbTresh);
    DECLARE_BSML_PROPERTY(float, gripThresh);
    DECLARE_BSML_PROPERTY(float, controllerSnapThresh);
)