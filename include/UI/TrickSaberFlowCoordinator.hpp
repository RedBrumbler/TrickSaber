#pragma once

#include "custom-types/shared/macros.hpp"
#include "lapiz/shared/macros.hpp"

#include "HMUI/FlowCoordinator.hpp"
#include "HMUI/ViewController.hpp"
#include "GlobalNamespace/MainFlowCoordinator.hpp"

#include "ViewControllers/BindingsViewController.hpp"
#include "ViewControllers/MiscViewController.hpp"
#include "ViewControllers/ThresholdViewController.hpp"

DECLARE_CLASS_CODEGEN(TrickSaber::UI, TrickSaberFlowCoordinator, HMUI::FlowCoordinator,
    DECLARE_PRIVATE_FIELD(GlobalNamespace::MainFlowCoordinator*, _mainFlowCoordinator);
    DECLARE_PRIVATE_FIELD(ViewControllers::BindingsViewController*, _bindingsViewController);
    DECLARE_PRIVATE_FIELD(ViewControllers::MiscViewController*, _miscViewController);
    DECLARE_PRIVATE_FIELD(ViewControllers::ThresholdViewController*, _thresholdViewController);

    DECLARE_INJECT_METHOD(void, Inject, GlobalNamespace::MainFlowCoordinator* mainFlowCoordinator, ViewControllers::BindingsViewController* bindingsViewController, ViewControllers::MiscViewController* miscViewController, ViewControllers::ThresholdViewController* thresholdViewController);
    DECLARE_OVERRIDE_METHOD(void, DidActivate, il2cpp_utils::il2cpp_type_check::MetadataGetter<&HMUI::FlowCoordinator::DidActivate>::get(), bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling);
    DECLARE_OVERRIDE_METHOD(void, DidDeactivate, il2cpp_utils::il2cpp_type_check::MetadataGetter<&HMUI::FlowCoordinator::DidDeactivate>::get(), bool removedFromHierarchy, bool screenSystemDisabling);
    DECLARE_OVERRIDE_METHOD(void, BackButtonWasPressed, il2cpp_utils::il2cpp_type_check::MetadataGetter<&HMUI::FlowCoordinator::BackButtonWasPressed>::get(), HMUI::ViewController* topViewController);
)