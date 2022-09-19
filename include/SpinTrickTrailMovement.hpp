#pragma once

#include "custom-types/shared/macros.hpp"
#include "UnityEngine/MonoBehaviour.hpp"
#include "UnityEngine/Transform.hpp"
#include "GlobalNamespace/Saber.hpp"
#include "GlobalNamespace/SaberMovementData.hpp"
#include "GlobalNamespace/SaberModelController.hpp"

DECLARE_CLASS_CODEGEN(TrickSaber, SpinTrickTrailMovement, UnityEngine::MonoBehaviour,
    DECLARE_INSTANCE_FIELD(UnityEngine::Transform*, _topTransform);
    DECLARE_INSTANCE_FIELD(UnityEngine::Transform*, _botTransform);
    DECLARE_INSTANCE_FIELD(GlobalNamespace::SaberMovementData*, _trailMovementData);
    DECLARE_INSTANCE_METHOD(void, Init, GlobalNamespace::Saber* saber, GlobalNamespace::SaberModelController* saberModelController);
    DECLARE_INSTANCE_METHOD(void, Update);
)