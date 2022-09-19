#include "SaberTrickModel.hpp"
#include "SpinTrickTrailMovement.hpp"

#include "logging.hpp"
#include "config.hpp"

#include "UnityEngine/WaitForSeconds.hpp"
#include "GlobalNamespace/SharedCoroutineStarter.hpp"

DEFINE_TYPE(TrickSaber, SaberTrickModel);

namespace TrickSaber {
    void SaberTrickModel::Inject(::Zenject::DiContainer* container, Lapiz::Sabers::LapizSaberFactory* lapizSaberFactory, Lapiz::Sabers::SaberModelManager* saberModelManager, GlobalNamespace::ColorManager* colorManager) {
        _saberFactory = lapizSaberFactory;
        _saberModelManager = saberModelManager;
        _colorManager = colorManager;

        _isMultiplayer = container->TryResolve<GlobalNamespace::MultiplayerPlayersManager*>();
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

    custom_types::Helpers::Coroutine SaberTrickModel::Init(GlobalNamespace::Saber* saber, bool& result) {
        _lapizSaber = _saberFactory->Spawn(saber->get_saberType());
        co_yield reinterpret_cast<System::Collections::IEnumerator*>(GlobalNamespace::SharedCoroutineStarter::get_instance()->StartCoroutine(custom_types::Helpers::CoroutineHelper::New(GetSaberModel(saber, _originalSaberModel))));

        if (!_originalSaberModel) {
            UnityEngine::Object::DestroyImmediate(_lapizSaber->get_gameObject());
            result = false;
            INFO("Couldn't find saber model, destroying trick model!");
            co_return;
        }

        _lapizSaber->SetColor(_colorManager->ColorForSaberType(saber->get_saberType()));

        _trickModel = _lapizSaber->get_gameObject();
        _saberTransform = _lapizSaber->get_transform();

        _trickModel->set_name(fmt::format("TrickModel {}", saber->get_saberType() == GlobalNamespace::SaberType::SaberA ? "SaberA" : "SaberB"));
        AddRigidbody(_trickModel);

        _trickModel->SetActive(false);

        if (!config.hitNotesDuringTrick || _isMultiplayer) {
            _lapizSaber->_saber->set_enabled(false);
        }

        saber->get_gameObject()->AddComponent<SpinTrickTrailMovement*>()->Init(saber, _originalSaberModel->GetComponent<GlobalNamespace::SaberModelController*>());
        result = true;
        co_return;
    }

    custom_types::Helpers::Coroutine SaberTrickModel::GetSaberModel(GlobalNamespace::Saber* saber, UnityEngine::GameObject*& result) {
        GlobalNamespace::SaberModelController* smc = nullptr; 
        
        static constexpr const float timeout = 2.0f;
        static constexpr const float interval = 0.3f;
        float time = 0;
        
        while (!smc && saber && saber->m_CachedPtr.m_value) {
            smc = saber->GetComponentInChildren<GlobalNamespace::SaberModelController*>(true);
            if (smc) {
                result = smc->get_gameObject();
                co_return;
            }

            if (time > timeout) break;

            time += interval;
            co_yield reinterpret_cast<System::Collections::IEnumerator*>(UnityEngine::WaitForSeconds::New_ctor(interval));
        }

        result = nullptr;
        co_return;
    }

    TrickSaber::Rigidbody* SaberTrickModel::get_rigidbody() { return _rigidbody; }
    UnityEngine::GameObject* SaberTrickModel::get_trickModel() { return _trickModel; }
    UnityEngine::GameObject* SaberTrickModel::get_originalSaberModel() { return _originalSaberModel; }
}