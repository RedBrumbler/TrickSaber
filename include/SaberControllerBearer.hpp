#pragma once

#include "custom-types/shared/macros.hpp"
#include "lapiz/shared/macros.hpp"

#include "GlobalNamespace/SaberType.hpp"
#include "GlobalNamespace/Saber.hpp"
#include "GlobalNamespace/VRController.hpp"
#include "GlobalNamespace/SaberManager.hpp"
#include "GlobalNamespace/PlayerVRControllersManager.hpp"

DECLARE_CLASS_CODEGEN(TrickSaber, SaberControllerPackage, Il2CppObject,
    DECLARE_INSTANCE_FIELD(GlobalNamespace::Saber*, saber);
    DECLARE_INSTANCE_FIELD(GlobalNamespace::VRController*, vrController);

    DECLARE_CTOR(ctor, GlobalNamespace::Saber* saber, GlobalNamespace::VRController* vrController);
)

DECLARE_CLASS_CODEGEN(TrickSaber, SaberControllerBearer, Il2CppObject,
    DECLARE_PRIVATE_FIELD(SaberControllerPackage*, _left);
    DECLARE_PRIVATE_FIELD(SaberControllerPackage*, _right);

    DECLARE_CTOR(ctor, GlobalNamespace::SaberManager* saberManager, GlobalNamespace::PlayerVRControllersManager* playerVRControllersManager);
    DECLARE_INSTANCE_METHOD(SaberControllerPackage*, get, GlobalNamespace::SaberType saberType);
)