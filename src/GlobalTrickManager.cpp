#include "GlobalTrickManager.hpp"
#include "config.hpp"
#include "logging.hpp"

#include "UnityEngine/Time.hpp"
#include "UnityEngine/WaitForFixedUpdate.hpp"
#include "GlobalNamespace/SharedCoroutineStarter.hpp"

DEFINE_TYPE(TrickSaber, GlobalTrickManager);

namespace TrickSaber {
    void GlobalTrickManager::ctor(::Zenject::DiContainer* container, GlobalNamespace::AudioTimeSyncController* audioTimeSyncController, GlobalNamespace::GameplayCoreSceneSetupData* gameplayCoreSceneSetup, LeftSaberTrickManager* leftSaberTrickManager, RightSaberTrickManager* rightSaberTrickManager) {
        DEBUG("ctor");
        saberClashCheckerEnabled = true;

        _audioTimeSyncController = audioTimeSyncController;
        _iDifficultyBeatmap = gameplayCoreSceneSetup->difficultyBeatmap;
        _slowmoStepAmount = config.slowmoStepAmount;
        this->leftSaberTrickManager = leftSaberTrickManager;
        this->rightSaberTrickManager = rightSaberTrickManager;

        _isMultiplayer = container->TryResolve<GlobalNamespace::MultiplayerPlayersManager*>();
    }
    
    void GlobalTrickManager::Initialize() {
        if (leftSaberTrickManager) leftSaberTrickManager->Init(this);
        else ERROR("leftSaberTrickManager was null!");
        if (rightSaberTrickManager) rightSaberTrickManager->Init(this);
        else ERROR("leftSaberTrickManager was null!");
    } 

    void GlobalTrickManager::OnTrickStarted(TrickAction trickAction) {
        saberClashCheckerEnabled = false;
        if (trickAction == TrickAction::Throw && config.slowmoDuringThrow && !_isMultiplayer && !_slowmoApplied)
        {
            auto timeScale = _audioTimeSyncController->timeScale;
            if (_endSlowmoCoroutine != nullptr)
            {
                GlobalNamespace::SharedCoroutineStarter::get_instance()->StopCoroutine(_endSlowmoCoroutine);
                timeScale = _endSlowmoTarget;
            }
            _applySlowmoCoroutine = GlobalNamespace::SharedCoroutineStarter::get_instance()->StartCoroutine(custom_types::Helpers::CoroutineHelper::New(ApplySlowmoSmooth(config.slowmoAmount, timeScale)));
            _slowmoApplied = true;
        }
    }

    void GlobalTrickManager::OnTrickEndRequested(TrickAction trickAction) {
        if (trickAction == TrickAction::Throw) {
            if (config.slowmoDuringThrow && !_isMultiplayer && !IsTrickInState(trickAction, TrickState::Started) && _slowmoApplied) {
                if (_applySlowmoCoroutine) GlobalNamespace::SharedCoroutineStarter::get_instance()->StopCoroutine(_applySlowmoCoroutine);
                _endSlowmoCoroutine = GlobalNamespace::SharedCoroutineStarter::get_instance()->StartCoroutine(custom_types::Helpers::CoroutineHelper::New(EndSlowmoSmooth()));
                _slowmoApplied = false;
            }
        }
    }

    void GlobalTrickManager::OnTrickEnded(TrickAction trickAction) {
        if(!IsDoingTrick()) saberClashCheckerEnabled = true;
    }

    void GlobalTrickManager::SetTimescale(float timescale) {
        _audioTimeSyncController->timeScale = timescale;
        get_audioSource()->set_pitch(timescale);
    }

    bool GlobalTrickManager::CanDoTrick() {
        if (!config.disableIfNotesOnScreen) return true;
        if (_timeSinceLastNote > 20 / _iDifficultyBeatmap->get_noteJumpMovementSpeed()) return true;
        return false;
    }

    void GlobalTrickManager::OnNoteWasSpawned(GlobalNamespace::NoteController* noteController) {
        _timeSinceLastNote = 0;
    }

    bool GlobalTrickManager::IsTrickInState(TrickAction trickAction, TrickState state) {
        return leftSaberTrickManager->IsTrickInState(trickAction, state) ||
                rightSaberTrickManager->IsTrickInState(trickAction, state);
    }

    bool GlobalTrickManager::IsDoingTrick() {
        return leftSaberTrickManager->IsDoingTrick() || rightSaberTrickManager->IsDoingTrick();
    }

    custom_types::Helpers::Coroutine GlobalTrickManager::ApplySlowmoSmooth(float amount, float originalTimescale) {
        float timeScale = _audioTimeSyncController->timeScale;
        _originalTimeScale = originalTimescale;
        float targetTimeScale = _originalTimeScale - amount;
        if (targetTimeScale < 0.1f) targetTimeScale = 0.1f;
        while (timeScale > targetTimeScale)
        {
            timeScale -= _slowmoStepAmount;
            SetTimescale(timeScale);
            co_yield reinterpret_cast<System::Collections::IEnumerator*>(UnityEngine::WaitForFixedUpdate::New_ctor());
        }

        SetTimescale(targetTimeScale);
    }

    custom_types::Helpers::Coroutine GlobalTrickManager::EndSlowmoSmooth() {
        float timeScale = _audioTimeSyncController->timeScale;
        float targetTimeScale = _originalTimeScale;
        _endSlowmoTarget = targetTimeScale;
        while (timeScale < targetTimeScale)
        {
            timeScale += _slowmoStepAmount;
            SetTimescale(timeScale);
            co_yield reinterpret_cast<System::Collections::IEnumerator*>(UnityEngine::WaitForFixedUpdate::New_ctor());
        }

        SetTimescale(targetTimeScale);
    }

    custom_types::Helpers::Coroutine GlobalTrickManager::NoteSpawnTimer() {
        while(true) {
            _timeSinceLastNote += UnityEngine::Time::get_deltaTime();
            co_yield nullptr;
        }
    }

    UnityEngine::AudioSource* GlobalTrickManager::get_audioSource() {
        if (!_audioSource || !_audioSource->m_CachedPtr.m_value)
            _audioSource = _audioTimeSyncController->audioSource;
        return _audioSource;
    }

    bool GlobalTrickManager::get_enabled() {
        if (!leftSaberTrickManager || !rightSaberTrickManager) return false;
        return leftSaberTrickManager->get_managerEnabled() || rightSaberTrickManager->get_managerEnabled();
    }

    void GlobalTrickManager::set_enabled(bool value) {
        if (!leftSaberTrickManager || !rightSaberTrickManager) return;
        leftSaberTrickManager->set_managerEnabled(value);
        rightSaberTrickManager->set_managerEnabled(value);
    }
}