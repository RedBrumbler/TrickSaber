#pragma once

#include "custom-types/shared/macros.hpp"
#include "lapiz/shared/macros.hpp"
#include "Zenject/IInitializable.hpp"
#include "Zenject/DiContainer.hpp"
#include "GlobalNamespace/PauseMenuManager.hpp"

DECLARE_CLASS_CODEGEN_INTERFACES(TrickSaber, GameplayManager, Il2CppObject, classof(::Zenject::IInitializable*),
    DECLARE_PRIVATE_FIELD(GlobalNamespace::PauseMenuManager*, _pauseMenuManager);
    DECLARE_INSTANCE_METHOD(void, DisableScoreSubmissionIfNeeded);
    DECLARE_INSTANCE_METHOD(void, DisableScore, bool disable, StringW reason);
    DECLARE_INSTANCE_METHOD(void, CreateCheckBox);
    DECLARE_OVERRIDE_METHOD(void, Initialize, il2cpp_utils::il2cpp_type_check::MetadataGetter<&::Zenject::IInitializable::Initialize>::get());
    
    DECLARE_CTOR(ctor, ::Zenject::DiContainer* container);
)