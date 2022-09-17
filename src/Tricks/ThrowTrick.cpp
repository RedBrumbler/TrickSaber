#include "Tricks/ThrowTrick.hpp"
#include "config.hpp"
#include "logging.hpp"

#include "UnityEngine/ForceMode.hpp"
#include "UnityEngine/Transform.hpp"
#include "UnityEngine/WaitForEndOfFrame.hpp"
#include "sombrero/shared/MiscUtils.hpp"
#include "System/Collections/IEnumerator.hpp"

DEFINE_TYPE(TrickSaber::Tricks, ThrowTrick);

namespace TrickSaber::Tricks {
    void ThrowTrick::ctor() {
        static auto klass = classof(TrickSaber::Tricks::Trick*);
        ::custom_types::InvokeBaseCtor(klass, this);

        DEBUG("ctor");
        _controllerSnapThreshold = 0.3f;
        _velocityMultiplier = 1;
        _trickAction = TrickSaber::TrickAction::Throw;
    }
        
    void ThrowTrick::OnInit() {
        _controllerSnapThreshold = config.controllerSnapThreshold;
        _velocityMultiplier = config.throwVelocity;
    }

    void ThrowTrick::OnTrickStart() {
        _saberTrickModel->ChangeToTrickModel();
        _saberTrickModel->get_rigidbody()->set_isKinematic(false);

        auto finalVelocity = _movementController->GetAverageVelocity() * _velocityMultiplier;
        _saberTrickModel->get_rigidbody()->set_velocity(finalVelocity * 3);
        _saberRotSpeed = finalVelocity.get_magnitude();
        if (_movementController->get_angularVelocity().x > 0) _saberRotSpeed *= 150;
        else _saberRotSpeed *= -150;
        _saberTrickModel->get_rigidbody()->AddRelativeTorque(Sombrero::FastVector3::right() * _saberRotSpeed, UnityEngine::ForceMode::Acceleration);
    }

    void ThrowTrick::OnTrickEndRequested() {
        _saberTrickModel->get_rigidbody()->set_velocity({0, 0, 0});
        StartCoroutine(custom_types::Helpers::CoroutineHelper::New(ReturnSaber(config.returnSpeed)));
    }

    void ThrowTrick::OnTrickEndImmediately() {
        StopAllCoroutines();
        ThrowEnd();
    }

    void ThrowTrick::ThrowEnd() {
        _saberTrickModel->get_rigidbody()->set_isKinematic(true);
        _saberTrickModel->ChangeToActualSaber();
        Reset();
    }

    custom_types::Helpers::Coroutine ThrowTrick::ReturnSaber(float speed) {
        _saberTrickModel->get_rigidbody()->AddRelativeTorque(Sombrero::FastVector3::right() * speed * (_saberRotSpeed<0?-1:1) * config.returnSpinMultiplier, UnityEngine::ForceMode::VelocityChange);
        auto trickModelT = _saberTrickModel->get_trickModel()->get_transform();
        Sombrero::FastVector3 position = trickModelT->get_position();
        auto controllerPos = _movementController->get_controllerPosition();
        float distance = position.Distance(controllerPos);
        while (distance > _controllerSnapThreshold)
        {
            distance = position.Distance(controllerPos);
            auto direction = controllerPos - position;
            direction.NormalizeFast();
            float force;
            if (distance < 1.0f) force = 10.0f;
            else force = speed * distance;
            force = force < 0 ? 0 : (force > 200 ? 200 : force);
            _saberTrickModel->get_rigidbody()->set_velocity(direction * force);
            position = trickModelT->get_position();
            controllerPos = _movementController->get_controllerPosition();

            co_yield reinterpret_cast<System::Collections::IEnumerator*>(UnityEngine::WaitForEndOfFrame::New_ctor());
        }

        ThrowEnd();
        co_return;
    }
}