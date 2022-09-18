#pragma once

#include "custom-types/shared/macros.hpp"
#include "lapiz/shared/macros.hpp"
#include "Zenject/IInitializable.hpp"
#include "GlobalNamespace/ColorManager.hpp"

DECLARE_CLASS_CODEGEN_INTERFACES(TrickSaber, GameplayManager, Il2CppObject, classof(::Zenject::IInitializable*),
    DECLARE_OVERRIDE_METHOD(void, Initialize, il2cpp_utils::il2cpp_type_check::MetadataGetter<&::Zenject::IInitializable::Initialize>::get());
    DECLARE_DEFAULT_CTOR();
)