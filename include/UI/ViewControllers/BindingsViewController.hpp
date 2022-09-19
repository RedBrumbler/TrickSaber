#pragma once
#include "custom-types/shared/macros.hpp"
#include "lapiz/shared/macros.hpp"
#include "bsml/shared/macros.hpp"

#include "HMUI/ViewController.hpp"
#include "UnityEngine/Transform.hpp"

DECLARE_CLASS_CODEGEN(TrickSaber::UI::ViewControllers, BindingsViewController, HMUI::ViewController,
    DECLARE_INSTANCE_FIELD(UnityEngine::Transform*, multiBindingTextLayout);
    DECLARE_OVERRIDE_METHOD(void, DidActivate, il2cpp_utils::il2cpp_type_check::MetadataGetter<&HMUI::ViewController::DidActivate>::get(), bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling);
    DECLARE_INSTANCE_METHOD(void, CheckMultiBinding);

    BSML_OPTIONS_LIST_OBJECT(trickActionEnum, "None", "Spin", "Throw");

    DECLARE_INSTANCE_METHOD(StringW, get_version);
    DECLARE_INSTANCE_METHOD(StringW, get_contactInfo);
    DECLARE_INSTANCE_METHOD(bool, get_newerVersionAvailable);
    DECLARE_INSTANCE_METHOD(StringW, get_newerVersionText);

    DECLARE_BSML_PROPERTY(bool, multiBindingTextActive);
    DECLARE_BSML_PROPERTY(StringW, triggerAction);
    DECLARE_BSML_PROPERTY(StringW, gripAction);
    DECLARE_BSML_PROPERTY(StringW, thumbAction);
    DECLARE_BSML_PROPERTY(bool, reverseTrigger);
    DECLARE_BSML_PROPERTY(bool, reverseGrip);
    DECLARE_BSML_PROPERTY(bool, reverseThumbstick);

)