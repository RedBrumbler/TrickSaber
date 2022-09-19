#include "Tricks/SpinTrick.hpp"
#include "config.hpp"
#include "logging.hpp"

#include "UnityEngine/Time.hpp"
#include "UnityEngine/WaitForEndOfFrame.hpp"
#include "sombrero/shared/FastQuaternion.hpp"

DEFINE_TYPE(TrickSaber::Tricks, SpinTrick);

namespace TrickSaber::Tricks {
    void SpinTrick::ctor() {
        static auto klass = classof(TrickSaber::Tricks::Trick*);
        ::custom_types::InvokeBaseCtor(klass, this);

        DEBUG("ctor");
        _trickAction = TrickSaber::TrickAction::Spin;
    }

    void SpinTrick::OnInit() {
        _saberModelTransform = _saberTrickModel->get_originalSaberModel()->get_transform();
        _isVelocityDependent = config.isSpeedVelocityDependent;
    }

    void SpinTrick::OnTrickStart() {
        _largestSpinSpeed = 0;
        if (_isVelocityDependent) {
            auto angularVelocity = _movementController->GetAverageAngularVelocity();
            _spinSpeed = std::abs(angularVelocity.x) + std::abs(angularVelocity.y);
            angularVelocity = Sombrero::FastQuaternion::Inverse(_movementController->get_controllerRotation()) * angularVelocity;
            if (angularVelocity.x < 0) _spinSpeed *= -1;
        } else {
            auto speed = 30;
            if (config.spinDirection == TrickSaber::SpinDir::Backward) speed *= -1;
            _spinSpeed = speed;
        }

        _spinSpeed *= config.spinSpeed;
    }

    void SpinTrick::Update() {
        _finalSpinSpeed = _spinSpeed;
        if (!_isVelocityDependent) _finalSpinSpeed *= (float) Sombrero::power(value, 3);
        if (std::abs(_finalSpinSpeed) > std::abs(_largestSpinSpeed)) _largestSpinSpeed = _finalSpinSpeed;
        _saberModelTransform->Rotate(Sombrero::FastVector3::right() * _finalSpinSpeed);
    }

    void SpinTrick::OnTrickEndRequested() {
        StartCoroutine(custom_types::Helpers::CoroutineHelper::New(config.completeRotationMode ? CompleteRotation() : LerpToOriginalRotation()));
    }

    void SpinTrick::OnTrickEndImmediately() {
        _saberModelTransform->set_localRotation(Sombrero::FastQuaternion::identity());
        OnSpinEnd();
    }

    void SpinTrick::OnSpinEnd() {
        Reset();
    }

    custom_types::Helpers::Coroutine SpinTrick::LerpToOriginalRotation() {
        static auto identityQ = Sombrero::FastQuaternion::identity();
        auto rot = _saberModelTransform->get_localRotation();
        while (Sombrero::FastQuaternion::Angle(rot, identityQ) > 5.0f)
        {

            rot = Sombrero::FastQuaternion::Lerp(rot, identityQ, UnityEngine::Time::get_deltaTime() * 20);
            _saberModelTransform->set_localRotation(rot);
            co_yield reinterpret_cast<System::Collections::IEnumerator*>(UnityEngine::WaitForEndOfFrame::New_ctor());
        }

        _saberModelTransform->set_localRotation(identityQ);
        OnSpinEnd();
        co_return;
    }

    custom_types::Helpers::Coroutine SpinTrick::CompleteRotation() {
        auto minSpeed = 8;
        auto largestSpinSpeed = _largestSpinSpeed;

        if (std::abs(largestSpinSpeed) < minSpeed)
        {
            largestSpinSpeed = largestSpinSpeed < 0 ? -minSpeed : minSpeed;
        }

        static auto identityQ = Sombrero::FastQuaternion::identity();
        auto threshold = std::abs(largestSpinSpeed) + 0.1f;
        auto angle = Sombrero::FastQuaternion::Angle(_saberModelTransform->get_localRotation(), identityQ);
        while (angle > threshold)
        {
            _saberModelTransform->Rotate(Sombrero::FastVector3::right() * largestSpinSpeed);
            angle = Sombrero::FastQuaternion::Angle(_saberModelTransform->get_localRotation(), identityQ);
            co_yield reinterpret_cast<System::Collections::IEnumerator*>(UnityEngine::WaitForEndOfFrame::New_ctor());
        }

        _saberModelTransform->set_localRotation(identityQ);
        OnSpinEnd();
        co_return;
    }
}