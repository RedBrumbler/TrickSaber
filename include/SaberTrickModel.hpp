#pragma once

#include "custom-types/shared/macros.hpp"
#include "custom-types/shared/coroutine.hpp"
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
        DECLARE_PRIVATE_FIELD(Lapiz::Sabers::SaberModelManager*, _saberModelManager);
        DECLARE_PRIVATE_FIELD(Lapiz::Sabers::LapizSaber*, _lapizSaber);
        DECLARE_PRIVATE_FIELD(UnityEngine::Transform*, _saberTransform);
        DECLARE_PRIVATE_FIELD(UnityEngine::Transform*, _originalParent);
        DECLARE_PRIVATE_FIELD(bool, _isMultiplayer);

        DECLARE_INJECT_METHOD(void, Inject, ::Zenject::DiContainer* container, Lapiz::Sabers::SaberModelManager* saberModelManager);

        DECLARE_INSTANCE_METHOD(TrickSaber::Rigidbody*, get_rigidbody);
        DECLARE_INSTANCE_METHOD(UnityEngine::GameObject*, get_trickModel);
        DECLARE_INSTANCE_METHOD(UnityEngine::GameObject*, get_originalSaberModel);
        DECLARE_INSTANCE_METHOD(void, ChangeToActualSaber);
        DECLARE_INSTANCE_METHOD(void, ChangeToTrickModel);
        DECLARE_INSTANCE_METHOD(void, AddRigidbody, UnityEngine::GameObject* gameObject);

        DECLARE_DEFAULT_CTOR();
    public:
        custom_types::Helpers::Coroutine Init(GlobalNamespace::Saber* saber, bool& result);
        custom_types::Helpers::Coroutine GetSaberModel(GlobalNamespace::Saber* saber, UnityEngine::GameObject*& result);
)