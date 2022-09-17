#include "Tricks/Trick.hpp"
#include "logging.hpp"

#include "SaberTrickManager.hpp"

DEFINE_TYPE(TrickSaber::Tricks, Trick);
DEFINE_TYPE(TrickSaber::Tricks, TrickFactory);
DEFINE_TYPE(TrickSaber::Tricks, TrickCustomFactory);

namespace TrickSaber::Tricks {
    void Trick::Init(TrickSaber::SaberTrickManager* saberTrickManager, TrickSaber::MovementController* movementController) {
        _saberTrickManager = saberTrickManager;
        _movementController = movementController;
        _saberTrickModel = _saberTrickManager->get_saberTrickModel();
        OnInit_base();
    }

    void Trick::Awake() {
        set_enabled(false);
    }

    bool Trick::StartTrick() {
        if (_trickState != TrickSaber::TrickState::Inactive) return false;
        set_enabled(true);
        _trickState = TrickSaber::TrickState::Started;
        OnTrickStart_base();
        if (trickStarted.size() > 0) trickStarted.invoke(_trickAction);
        return true;
    }

    void Trick::EndTrick() {
        if (_trickState == TrickSaber::TrickState::Started)
        {
            set_enabled(false);
            _endRequested = true;
            _trickState = TrickSaber::TrickState::Ending;
            if (trickEnding.size() > 0) trickEnding.invoke(_trickAction);
            OnTrickEndRequested_base();
        }
    }

    void Trick::Reset() {
        _trickState = TrickSaber::TrickState::Inactive;
        _endRequested = false;
        if (trickEnded.size() > 0) trickEnded.invoke(_trickAction);
    }

    void Trick::OnTrickStart_base() {
        il2cpp_utils::RunMethod(this, "OnTrickStart");
    }

    void Trick::OnTrickEndRequested_base() {
        il2cpp_utils::RunMethod(this, "OnTrickEndRequested");
    }

    void Trick::OnTrickEndImmediately_base() {
        il2cpp_utils::RunMethod(this, "OnTrickEndImmediately");
    }

    void Trick::OnInit_base() {
        il2cpp_utils::RunMethod(this, "OnInit");
    }

    void TrickCustomFactory::ctor(::Zenject::DiContainer* container) {
        DEBUG("ctor");
        _container = container;
    }

    Trick* TrickCustomFactory::Create(System::Type* type, ::UnityEngine::GameObject* gameObject) {
        return reinterpret_cast<Trick*>(_container->InstantiateComponent(type, gameObject));
    }
}