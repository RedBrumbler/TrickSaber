#pragma once
#include "custom-types/shared/macros.hpp"
#include "lapiz/shared/macros.hpp"
#include "bsml/shared/macros.hpp"

#include "HMUI/ViewController.hpp"
#include "UnityEngine/Transform.hpp"

DECLARE_CLASS_CODEGEN(TrickSaber::UI::ViewControllers, MiscViewController, HMUI::ViewController,
    DECLARE_INSTANCE_FIELD(UnityEngine::Transform*, scrollable);
    DECLARE_OVERRIDE_METHOD(void, DidActivate, il2cpp_utils::il2cpp_type_check::MetadataGetter<&HMUI::ViewController::DidActivate>::get(), bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling);

    DECLARE_INSTANCE_METHOD(void, PostParse);

    BSML_OPTIONS_LIST_OBJECT(spinDirEnum, "Forward", "Backward");
    BSML_OPTIONS_LIST_OBJECT(dirEnum, "Horizontal", "Vertical");

    DECLARE_BSML_PROPERTY(bool, trickSaberEnabled);
    DECLARE_BSML_PROPERTY(StringW, thumbstickDir);
    DECLARE_BSML_PROPERTY(bool, isSpeedVelocityDependent);
    DECLARE_BSML_PROPERTY(float, spinSpeed);
    DECLARE_BSML_PROPERTY(StringW, spinDir);
    DECLARE_BSML_PROPERTY(float, throwVelocity);
    DECLARE_BSML_PROPERTY(float, returnSpeed);
    DECLARE_BSML_PROPERTY(bool, slowmoDuringThrow);
    DECLARE_BSML_PROPERTY(bool, disableIfNotesOnScreen);
    DECLARE_BSML_PROPERTY(bool, hitNotesDuringTrick);
)