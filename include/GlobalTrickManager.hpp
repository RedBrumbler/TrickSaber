#pragma once

#include "custom-types/shared/macros.hpp"
#include "custom-types/shared/coroutine.hpp"
#include "lapiz/shared/macros.hpp"

#include "UnityEngine/AudioSource.hpp"
#include "UnityEngine/Coroutine.hpp"
#include "GlobalNamespace/BeatmapObjectManager.hpp"
#include "GlobalNamespace/GameplayCoreSceneSetupData.hpp"
#include "GlobalNamespace/AudioTimeSyncController.hpp"
#include "GlobalNamespace/IDifficultyBeatmap.hpp"
#include "GlobalNamespace/NoteController.hpp"
#include "System/IDisposable.hpp"

#include "SaberTrickManager.hpp"

#include "Zenject/IInitializable.hpp"

#define INTERFACES { classof(::Zenject::IInitializable*), classof(::System::IDisposable*) }

___DECLARE_TYPE_WRAPPER_INHERITANCE(TrickSaber, GlobalTrickManager, Il2CppTypeEnum::IL2CPP_TYPE_CLASS, Il2CppObject, "TrickSaber", INTERFACES, 0, nullptr,
    DECLARE_PRIVATE_FIELD(UnityEngine::Coroutine*, _noteTimer);
    DECLARE_PRIVATE_FIELD(UnityEngine::AudioSource*, _audioSource);
    DECLARE_INSTANCE_METHOD(UnityEngine::AudioSource*, get_audioSource);

    DECLARE_INSTANCE_FIELD(GlobalNamespace::BeatmapObjectManager*, beatmapObjectManager);
    DECLARE_INSTANCE_FIELD(LeftSaberTrickManager*, leftSaberTrickManager);
    DECLARE_INSTANCE_FIELD(RightSaberTrickManager*, rightSaberTrickManager);

    DECLARE_INSTANCE_METHOD(bool, get_enabled);
    DECLARE_INSTANCE_METHOD(void, set_enabled, bool value);
    DECLARE_INSTANCE_FIELD(bool, saberClashCheckerEnabled);

    DECLARE_PRIVATE_FIELD(GlobalNamespace::IDifficultyBeatmap*, _iDifficultyBeatmap);
    DECLARE_PRIVATE_FIELD(GlobalNamespace::AudioTimeSyncController*, _audioTimeSyncController);
    DECLARE_PRIVATE_FIELD(float, _slowmoStepAmount);
    DECLARE_PRIVATE_FIELD(bool, _isMultiplayer);
    DECLARE_PRIVATE_FIELD(UnityEngine::Coroutine*, _applySlowmoCoroutine);
    DECLARE_PRIVATE_FIELD(UnityEngine::Coroutine*, _endSlowmoCoroutine);
    DECLARE_PRIVATE_FIELD(bool, _slowmoApplied);
    DECLARE_PRIVATE_FIELD(float, _endSlowmoTarget);
    DECLARE_PRIVATE_FIELD(float, _originalTimeScale);
    DECLARE_PRIVATE_FIELD(float, _timeSinceLastNote);

    DECLARE_OVERRIDE_METHOD(void, Initialize, il2cpp_utils::il2cpp_type_check::MetadataGetter<&::Zenject::IInitializable::Initialize>::get()); 
    DECLARE_OVERRIDE_METHOD(void, Dispose, il2cpp_utils::il2cpp_type_check::MetadataGetter<&::System::IDisposable::Dispose>::get()); 
    DECLARE_INSTANCE_METHOD(void, OnTrickStarted, TrickAction trickAction);
    DECLARE_INSTANCE_METHOD(void, OnTrickEndRequested, TrickAction trickAction);
    DECLARE_INSTANCE_METHOD(void, OnTrickEnded, TrickAction trickAction);
    DECLARE_PRIVATE_METHOD(void, SetTimescale, float timescale);
    DECLARE_INSTANCE_METHOD(bool, CanDoTrick);
    DECLARE_PRIVATE_METHOD(void, OnNoteWasSpawned, GlobalNamespace::NoteController* noteController);
    DECLARE_INSTANCE_METHOD(bool, IsTrickInState, TrickAction trickAction, TrickState state);
    DECLARE_INSTANCE_METHOD(bool, IsDoingTrick);


    DECLARE_CTOR(ctor, ::Zenject::DiContainer* container, GlobalNamespace::AudioTimeSyncController* audioTimeSyncController, GlobalNamespace::GameplayCoreSceneSetupData* gameplayCoreSceneSetup, LeftSaberTrickManager* leftSaberTrickManager, RightSaberTrickManager* rightSaberTrickManager);

    private:
        custom_types::Helpers::Coroutine ApplySlowmoSmooth(float amount, float originalTimescale);
        custom_types::Helpers::Coroutine EndSlowmoSmooth();
        custom_types::Helpers::Coroutine NoteSpawnTimer();

)
