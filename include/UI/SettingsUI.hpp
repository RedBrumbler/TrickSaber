#pragma once

#include "custom-types/shared/macros.hpp"
#include "lapiz/shared/macros.hpp"

#include "TrickSaberFlowCoordinator.hpp"
#include "Zenject/IInitializable.hpp"
#include "System/IDisposable.hpp"

#include "bsml/shared/BSML/MenuButtons/MenuButton.hpp"

#define SETTINGSUI_INTERFACES { classof(::System::IDisposable*), classof(::Zenject::IInitializable*) }

___DECLARE_TYPE_WRAPPER_INHERITANCE(TrickSaber::UI, SettingsUI, Il2CppTypeEnum::IL2CPP_TYPE_CLASS, Il2CppObject, "TrickSaber::UI", SETTINGSUI_INTERFACES, 0, nullptr, 
    DECLARE_PRIVATE_FIELD(TrickSaberFlowCoordinator*, _trickSaberFlowCoordinator);
    DECLARE_PRIVATE_FIELD(GlobalNamespace::MainFlowCoordinator*, _mainFlowCoordinator);
    DECLARE_PRIVATE_FIELD(BSML::MenuButton*, _menuButton);
    
    DECLARE_CTOR(ctor, GlobalNamespace::MainFlowCoordinator* mainFlowCoordinator, TrickSaberFlowCoordinator* trickSaberFlowCoordinator);
    DECLARE_INSTANCE_METHOD(void, ShowFlow);
    DECLARE_OVERRIDE_METHOD(void, Initialize, il2cpp_utils::il2cpp_type_check::MetadataGetter<&::Zenject::IInitializable::Initialize>::get());
    DECLARE_OVERRIDE_METHOD(void, Dispose, il2cpp_utils::il2cpp_type_check::MetadataGetter<&::System::IDisposable::Dispose>::get());
)

#undef SETTINGSUI_INTERFACES
