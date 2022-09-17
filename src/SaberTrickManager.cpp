#include "SaberTrickManager.hpp"
#include "GlobalTrickManager.hpp"
#include "config.hpp"
#include "logging.hpp"

#include "Tricks/SpinTrick.hpp"
#include "Tricks/ThrowTrick.hpp"

#include "System/Action.hpp"

#include "custom-types/shared/delegate.hpp"

DEFINE_TYPE(TrickSaber, SaberTrickManager);
DEFINE_TYPE(TrickSaber, LeftSaberTrickManager);
DEFINE_TYPE(TrickSaber, RightSaberTrickManager);

namespace TrickSaber {
    void LeftSaberTrickManager::ctor() {
        DEBUG("LeftSaberTrickManager ctor");
        custom_types::InvokeBaseCtor(classof(SaberTrickManager*), this);
    }
    
    void RightSaberTrickManager::ctor() {
        DEBUG("RightSaberTrickManager ctor");
        custom_types::InvokeBaseCtor(classof(SaberTrickManager*), this);
    }
    
    void SaberTrickManager::ctor() {
        DEBUG("ctor");
        _tricks = TrickDictionary::New_ctor();
        _managerEnabled = true;
    }

    void SaberTrickManager::Inject(TrickSaber::MovementController* movementController, TrickSaber::InputHandling::InputManager* inputManager, TrickSaber::SaberControllerBearer* saberControllerBearer, GlobalNamespace::SaberType saberType, SaberTrickModel* saberTrickModel, GlobalNamespace::AudioTimeSyncController* audioTimeSyncController, TrickSaber::Tricks::TrickFactory* trickFactory) {
        _movementController = movementController;
        _inputManager = inputManager;
        _audioTimeSyncController = audioTimeSyncController;
        _saberTrickModel = saberTrickModel;

        auto saberPackage = saberControllerBearer->get(saberType);
        _saber = saberPackage->saber;
        _vrController = saberPackage->vrController;

        _trickFactory = trickFactory;
    }

    void SaberTrickManager::Init(GlobalTrickManager* globalTrickManager) {
        _globalTrickManager = globalTrickManager;

        DEBUG("Instantiated on {}", get_gameObject()->get_name());

        if (!_vrController)
        {
            ERROR("Controller not present");
            Cleanup();
            return;
        }

        if (get_isLeftSaber()) _globalTrickManager->leftSaberTrickManager = reinterpret_cast<LeftSaberTrickManager*>(this);
        else _globalTrickManager->rightSaberTrickManager = reinterpret_cast<RightSaberTrickManager*>(this);

        _movementController->Init(_vrController, this);

        _inputManager->Init(_saber->get_saberType(), _vrController->vrControllersInputManager);
        _inputManager->trickActivated += { &SaberTrickManager::OnTrickActivated, this };
        _inputManager->trickDeactivated += { &SaberTrickManager::OnTrickDeactivated, this };

        auto success = _saberTrickModel->Init(_saber);
        if (success) INFO("Got saber model");
        else {
            ERROR("Couldn't get saber model");
            Cleanup();
            return;
        }

        _movementController->set_enabled(true);

        AddTrick<Tricks::SpinTrick*>();
        AddTrick<Tricks::ThrowTrick*>();

        INFO("{} tricks initialized", _tricks->get_Count());

        if (_pauseController) {
            auto delegate = custom_types::MakeDelegate<System::Action*>(
                std::function<void()>(std::bind(&SaberTrickManager::EndAllTricks, this))
            );
            _pauseController->add_didResumeEvent(delegate);
        }

        INFO("Trick Manager initialized");
    }

    void SaberTrickManager::Cleanup() {
        auto values = _tricks->get_Values();
        auto iter = values->GetEnumerator();
        while (iter.MoveNext()) {
            UnityEngine::Object::DestroyImmediate(iter.get_Current());
        }
        iter.Dispose();

        UnityEngine::Object::DestroyImmediate(_movementController);
        UnityEngine::Object::DestroyImmediate(this);
    }

    void SaberTrickManager::Update() {
        _inputManager->Tick();
    }

    void SaberTrickManager::OnTrickDeactivated(TrickAction trickAction) {
        auto trick = _tricks->get_Item(trickAction);
        if (trick->_trickState != TrickState::Started) return;
        trick->EndTrick();
    }

    void SaberTrickManager::OnTrickActivated(TrickAction trickAction, float val) {
        if (!CanDoTrick()) return;
        auto trick = _tricks->get_Item(trickAction);
        trick->value = val;
        if (trick->_trickState != TrickState::Inactive) return;
        if (_audioTimeSyncController->get_state() ==
            GlobalNamespace::AudioTimeSyncController::State::Paused) return;
        trick->StartTrick();
    }

    void SaberTrickManager::OnTrickStart(TrickAction trickAction) {
        _globalTrickManager->OnTrickStarted(trickAction);
    }

    void SaberTrickManager::OnTrickEnding(TrickAction trickAction) {
        _globalTrickManager->OnTrickEndRequested(trickAction);
    }

    void SaberTrickManager::OnTrickEnd(TrickAction trickAction) {
        _globalTrickManager->OnTrickEnded(trickAction);
    }

    void SaberTrickManager::AddTrick(System::Type* type) {
        auto trick = _trickFactory->Create(type, get_gameObject());
        trick->Init(this, _movementController);
        trick->trickStarted += {&SaberTrickManager::OnTrickStart, this };
        trick->trickEnding += {&SaberTrickManager::OnTrickEnding, this };
        trick->trickEnded += {&SaberTrickManager::OnTrickEnd, this };
        _tricks->Add(trick->_trickAction, trick);
    }

    bool SaberTrickManager::IsTrickInState(TrickAction trickAction, TrickState state) {
        Tricks::Trick* trick = nullptr;
        if (_tricks->TryGetValue(trickAction, byref(trick)) && trick) {
            return trick->_trickState == state;
        }
        return false;
    }

    bool SaberTrickManager::IsDoingTrick() {
        auto values = _tricks->get_Values();
        auto iter = values->GetEnumerator();
        while (iter.MoveNext()) {
            if (iter.get_Current()->_trickState != TrickState::Inactive) return true;
        }
        iter.Dispose();

        return false;
    }

    void SaberTrickManager::EndAllTricks() {
        auto values = _tricks->get_Values();
        auto iter = values->GetEnumerator();
        while (iter.MoveNext()) {
            iter.get_Current()->OnTrickEndImmediately_base();
        }
        iter.Dispose();
    }

    bool SaberTrickManager::CanDoTrick() {
        return config.trickSaberEnabled &&
                _managerEnabled &&
                _globalTrickManager->CanDoTrick();
    }

    SaberTrickManager::TrickDictionary* SaberTrickManager::get_tricks() { return _tricks; }
    SaberTrickModel* SaberTrickManager::get_saberTrickModel() { return _saberTrickModel; }
    bool SaberTrickManager::get_managerEnabled() { return _managerEnabled; }
    void SaberTrickManager::set_managerEnabled(bool value) { _managerEnabled = value; }
    bool SaberTrickManager::get_isLeftSaber() { return _saber->get_saberType() == GlobalNamespace::SaberType::SaberA; }
}