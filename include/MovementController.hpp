#pragma once

#include "custom-types/shared/macros.hpp"
#include "macros.hpp"
#include "lapiz/shared/macros.hpp"

#include "UnityEngine/MonoBehaviour.hpp"
#include "GlobalNamespace/VRController.hpp"
#include "sombrero/shared/FastVector3.hpp"
#include "sombrero/shared/FastQuaternion.hpp"

namespace TrickSaber {
    class SaberTrickManager;
}

DECLARE_CLASS_CODEGEN(TrickSaber, MovementController, UnityEngine::MonoBehaviour,
    DECLARE_PRIVATE_FIELD(ArrayW<Sombrero::FastVector3>, _angularVelocityBuffer);
    DECLARE_PRIVATE_FIELD(int, _currentProbeIndex);
    DECLARE_PRIVATE_FIELD(Sombrero::FastVector3, _prevPos);
    DECLARE_PRIVATE_FIELD(Sombrero::FastQuaternion, _prevRot);

    DECLARE_PRIVATE_FIELD(ArrayW<Sombrero::FastVector3>, _velocityBuffer);
    DECLARE_PRIVATE_FIELD(Sombrero::FastVector3, _angularVelocity);
    DECLARE_INSTANCE_METHOD(Sombrero::FastVector3, get_angularVelocity);
    DECLARE_PRIVATE_FIELD(GlobalNamespace::VRController*, _controller);
    DECLARE_INSTANCE_METHOD(GlobalNamespace::VRController*, get_controller);

    DECLARE_PRIVATE_FIELD(Sombrero::FastVector3, _controllerPosition);
    DECLARE_INSTANCE_METHOD(Sombrero::FastVector3, get_controllerPosition);
    DECLARE_PRIVATE_FIELD(Sombrero::FastQuaternion, _controllerRotation);
    DECLARE_INSTANCE_METHOD(Sombrero::FastQuaternion, get_controllerRotation);
    DECLARE_INSTANCE_FIELD_NAME(SaberTrickManager*, _saberTrickManager, "TrickSaber", "SaberTrickManager");

    DECLARE_PRIVATE_FIELD(Sombrero::FastVector3, _velocity);
    DECLARE_INSTANCE_METHOD(Sombrero::FastVector3, get_velocity);

    DECLARE_INSTANCE_METHOD(Sombrero::FastVector3, get_localControllerPosition);
    DECLARE_INSTANCE_METHOD(void, set_localControllerPosition, Sombrero::FastVector3 value);

    DECLARE_INSTANCE_METHOD(Sombrero::FastQuaternion, get_localControllerRotation);
    DECLARE_INSTANCE_METHOD(void, set_localControllerRotation, Sombrero::FastQuaternion value);

    DECLARE_INSTANCE_METHOD(float, get_saberSpeed);

    DECLARE_INSTANCE_METHOD(Sombrero::FastVector3, GetAverageVelocity);
    DECLARE_INSTANCE_METHOD(Sombrero::FastVector3, GetAverageAngularVelocity);

    DECLARE_INSTANCE_METHOD(void, Awake);
    DECLARE_INSTANCE_METHOD(void, Update);
    DECLARE_PRIVATE_METHOD(void, AddProbe, Sombrero::FastVector3 vel, Sombrero::FastVector3 ang);
    DECLARE_PRIVATE_METHOD(Sombrero::FastVector3, GetAngularVelocity, Sombrero::FastQuaternion foreLastFrameRotation, Sombrero::FastQuaternion lastFrameRotation);

    DECLARE_CTOR(ctor);
    public:
        void Init(GlobalNamespace::VRController* vrController, SaberTrickManager* saberTrickManager);
        SaberTrickManager* get_saberTrickManager();
)