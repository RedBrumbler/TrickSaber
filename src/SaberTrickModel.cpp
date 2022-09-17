#include "SaberTrickModel.hpp"
#include "logging.hpp"
#include "config.hpp"

DEFINE_TYPE(TrickSaber, SaberTrickModel);

namespace TrickSaber {
    void SaberTrickModel::Inject(Lapiz::Sabers::LapizSaberFactory* lapizSaberFactory, GlobalNamespace::ColorManager* colorManager) {
        _saberFactory = lapizSaberFactory;
        _colorManager = colorManager;

        _isMultiplayer = _multiplayerPlayersManager;
    }

    void SaberTrickModel::ChangeToActualSaber() {
        _originalSaberModel->SetActive(true);
        _trickModel->SetActive(false);
    }

    void SaberTrickModel::ChangeToTrickModel() {
        _trickModel->SetActive(true);
        _saberTransform->set_position(_originalSaberModel->get_transform()->get_position());
        _saberTransform->set_rotation(_originalSaberModel->get_transform()->get_rotation());
        _originalSaberModel->SetActive(false);
    }

    void SaberTrickModel::AddRigidbody(UnityEngine::GameObject* gameObject) {
        _rigidbody = gameObject->AddComponent<TrickSaber::Rigidbody*>();
        _rigidbody->set_useGravity(false);
        _rigidbody->set_isKinematic(true);
        _rigidbody->set_detectCollisions(false);
        _rigidbody->set_maxAngularVelocity(800);
        _rigidbody->set_interpolation(TrickSaber::RigidbodyInterpolation::Interpolate);
    }

    bool SaberTrickModel::Init(GlobalNamespace::Saber* saber) {
        _lapizSaber = _saberFactory->Spawn(saber->get_saberType());

        _originalSaberModel = GetSaberModel(saber);

        if (!_originalSaberModel)
        {
            UnityEngine::Object::DestroyImmediate(_lapizSaber->get_gameObject());
            return false;
        }

        _lapizSaber->SetColor(_colorManager->ColorForSaberType(saber->get_saberType()));

        _trickModel = _lapizSaber->get_gameObject();
        _saberTransform = _lapizSaber->get_transform();

        _trickModel->set_name(fmt::format("TrickModel {}", saber->get_saberType() == GlobalNamespace::SaberType::SaberA ? "SaberA" : "SaberB"));
        AddRigidbody(_trickModel);

        _trickModel->SetActive(false);

        if (!config.hitNotesDuringTrick || _isMultiplayer)
        {
            _lapizSaber->_saber->set_enabled(false);
        }

        return true;
    }

    UnityEngine::GameObject* SaberTrickModel::GetSaberModel(GlobalNamespace::Saber* saber) {
        auto smc = saber->GetComponentInChildren<GlobalNamespace::SaberModelController*>();
        if (smc) return smc->get_gameObject();
        return nullptr;
    }

    TrickSaber::Rigidbody* SaberTrickModel::get_rigidbody() { return _rigidbody; }
    UnityEngine::GameObject* SaberTrickModel::get_trickModel() { return _trickModel; }
    UnityEngine::GameObject* SaberTrickModel::get_originalSaberModel() { return _originalSaberModel; }
}