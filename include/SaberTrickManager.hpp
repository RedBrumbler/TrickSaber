#pragma once

#include "custom-types/shared/macros.hpp"
#include "custom-types/shared/coroutine.hpp"
#include "lapiz/shared/macros.hpp"
#include "UnityEngine/MonoBehaviour.hpp"
#include "GlobalNamespace/VRController.hpp"
#include "GlobalNamespace/Saber.hpp"
#include "GlobalNamespace/PauseController.hpp"
#include "GlobalNamespace/AudioTimeSyncController.hpp"

#include "SaberTrickModel.hpp"
#include "Tricks/Trick.hpp"
#include "InputHandling/InputManager.hpp"
#include "Enums.hpp"
#include "SaberControllerBearer.hpp"
#include "MovementController.hpp"

#include "System/Collections/Generic/Dictionary_2.hpp"

namespace TrickSaber {
    class GlobalTrickManager;
}

DECLARE_CLASS_CODEGEN(TrickSaber, SaberTrickManager, UnityEngine::MonoBehaviour,
    using TrickDictionary = System::Collections::Generic::Dictionary_2<::TrickSaber::TrickAction, ::Il2CppObject*>;
    DECLARE_PRIVATE_FIELD(TrickDictionary*, _tricks);
    DECLARE_INSTANCE_METHOD(TrickDictionary*, get_tricks);
    DECLARE_PRIVATE_FIELD(SaberTrickModel*, _saberTrickModel);
    DECLARE_INSTANCE_METHOD(SaberTrickModel*, get_saberTrickModel);
    DECLARE_PRIVATE_FIELD(bool, _managerEnabled);
    DECLARE_INSTANCE_METHOD(bool, get_managerEnabled);
    DECLARE_INSTANCE_METHOD(void, set_managerEnabled, bool value);
    DECLARE_INSTANCE_METHOD(bool, get_isLeftSaber);
    DECLARE_PRIVATE_FIELD(GlobalNamespace::VRController*, _vrController);
    DECLARE_PRIVATE_FIELD(GlobalNamespace::Saber*, _saber);
    DECLARE_INSTANCE_FIELD_NAME(GlobalTrickManager*, _globalTrickManager, "TrickSaber", "GlobalTrickManager");
    DECLARE_INSTANCE_FIELD(GlobalNamespace::PauseController*, _pauseController);
    DECLARE_PRIVATE_FIELD(TrickSaber::MovementController*, _movementController);
    DECLARE_PRIVATE_FIELD(TrickSaber::InputHandling::InputManager*, _inputManager);
    DECLARE_PRIVATE_FIELD(GlobalNamespace::AudioTimeSyncController*, _audioTimeSyncController);
    DECLARE_PRIVATE_FIELD(TrickSaber::Tricks::TrickCustomFactory*, _trickFactory);
    DECLARE_PRIVATE_FIELD(::Zenject::DiContainer*, _container);
    DECLARE_PRIVATE_FIELD(bool, _inited);

    DECLARE_INJECT_METHOD(void, Inject, Zenject::DiContainer* container, TrickSaber::MovementController* movementController, TrickSaber::InputHandling::InputManager* inputManager, TrickSaber::SaberControllerBearer* saberControllerBearer, GlobalNamespace::SaberType saberType, SaberTrickModel* saberTrickModel, GlobalNamespace::AudioTimeSyncController* audioTimeSyncController/*, TrickSaber::Tricks::TrickCustomFactory* trickFactory*/);
    DECLARE_PRIVATE_METHOD(void, Cleanup);
    DECLARE_PRIVATE_METHOD(void, Update);
    DECLARE_PRIVATE_METHOD(void, OnTrickDeactivated, TrickAction trickAction);
    DECLARE_PRIVATE_METHOD(void, OnTrickActivated, TrickAction trickAction, float val);
    DECLARE_PRIVATE_METHOD(void, OnTrickStart, TrickAction trickAction);
    DECLARE_PRIVATE_METHOD(void, OnTrickEnding, TrickAction trickAction);
    DECLARE_PRIVATE_METHOD(void, OnTrickEnd, TrickAction trickAction);
    DECLARE_INSTANCE_METHOD(bool, IsTrickInState, TrickAction trickAction, TrickState state);
    DECLARE_INSTANCE_METHOD(bool, IsDoingTrick);
    DECLARE_INSTANCE_METHOD(void, EndAllTricks);
    DECLARE_INSTANCE_METHOD(bool, CanDoTrick);
    DECLARE_PRIVATE_METHOD(Tricks::Trick*, GetTrick, TrickAction trickAction);

    DECLARE_CTOR(ctor);
    public:
        void Init(GlobalTrickManager* globalTrickManager);
    private:
        template<typename T>
        requires(std::is_convertible_v<T, TrickSaber::Tricks::Trick*>)
        void AddTrick() {
            AddTrick(csTypeOf(T));
        }

        void AddTrick(System::Type* type);

        custom_types::Helpers::Coroutine InitAsync();
)

// named type because inject with ID is stupid
DECLARE_CLASS_CUSTOM(TrickSaber, LeftSaberTrickManager, TrickSaber::SaberTrickManager,
    DECLARE_CTOR(ctor);
)

// named type because inject with ID is stupid
DECLARE_CLASS_CUSTOM(TrickSaber, RightSaberTrickManager, TrickSaber::SaberTrickManager,
    DECLARE_CTOR(ctor);
)

