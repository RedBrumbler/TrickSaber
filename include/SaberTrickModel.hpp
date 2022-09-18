#pragma once

#include "custom-types/shared/macros.hpp"
#include "lapiz/shared/macros.hpp"
#include "lapiz/shared/sabers/LapizSaberFactory.hpp"
#include "lapiz/shared/sabers/SaberModelManager.hpp"
#include "lapiz/shared/sabers/LapizSaber.hpp"

#include "GlobalNamespace/ColorManager.hpp"
#include "GlobalNamespace/MultiplayerPlayersManager.hpp"
#include "Rigidbody.hpp"
#include "UnityEngine/MonoBehaviour.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Transform.hpp"

#include "System/Threading/Tasks/Task_1.hpp"

DECLARE_CLASS_CODEGEN(TrickSaber, SaberTrickModel, Il2CppObject,
    DECLARE_PRIVATE_FIELD(TrickSaber::Rigidbody*, _rigidbody);
    DECLARE_PRIVATE_FIELD(UnityEngine::GameObject*, _trickModel);
    DECLARE_PRIVATE_FIELD(UnityEngine::GameObject*, _originalSaberModel);
    DECLARE_PRIVATE_FIELD(Lapiz::Sabers::LapizSaberFactory*, _saberFactory);
    DECLARE_PRIVATE_FIELD(Lapiz::Sabers::SaberModelManager*, _saberModelManager);
    DECLARE_PRIVATE_FIELD(GlobalNamespace::ColorManager*, _colorManager);
    DECLARE_PRIVATE_FIELD(Lapiz::Sabers::LapizSaber*, _lapizSaber);
    DECLARE_PRIVATE_FIELD(UnityEngine::Transform*, _saberTransform);
    DECLARE_PRIVATE_FIELD(bool, _isMultiplayer);

    DECLARE_INJECT_METHOD(void, Inject, ::Zenject::DiContainer* container, Lapiz::Sabers::LapizSaberFactory* lapizSaberFactory, Lapiz::Sabers::SaberModelManager* saberModelManager, GlobalNamespace::ColorManager* colorManager);

    DECLARE_INSTANCE_METHOD(TrickSaber::Rigidbody*, get_rigidbody);
    DECLARE_INSTANCE_METHOD(UnityEngine::GameObject*, get_trickModel);
    DECLARE_INSTANCE_METHOD(UnityEngine::GameObject*, get_originalSaberModel);
    DECLARE_INSTANCE_METHOD(void, ChangeToActualSaber);
    DECLARE_INSTANCE_METHOD(void, ChangeToTrickModel);
    DECLARE_INSTANCE_METHOD(void, AddRigidbody, UnityEngine::GameObject* gameObject);

    DECLARE_INSTANCE_METHOD(bool, Init, GlobalNamespace::Saber* saber);
    DECLARE_INSTANCE_METHOD(UnityEngine::GameObject*, GetSaberModel, GlobalNamespace::Saber* saber);

    DECLARE_DEFAULT_CTOR();
)