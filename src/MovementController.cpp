#include "MovementController.hpp"
#include "config.hpp"
#include "logging.hpp"

#include "UnityEngine/Time.hpp"
#include "UnityEngine/Transform.hpp"

DEFINE_TYPE(TrickSaber, MovementController);

using namespace Sombrero;

namespace TrickSaber {
    void MovementController::ctor() {
        _velocityBuffer = ArrayW<FastVector3>(config.velocityBufferSize);
        _angularVelocityBuffer = ArrayW<FastVector3>(config.velocityBufferSize);

        _prevPos = FastVector3::zero();
        _prevRot = FastQuaternion::identity();
        _angularVelocity = FastVector3::zero();
        _controllerPosition = FastVector3::zero();
        _controllerRotation = FastQuaternion::identity();
        _velocity = FastVector3::zero();
    }

    FastVector3 MovementController::GetAverageVelocity() {
        FastVector3 avg = FastVector3::zero();
        for (const auto& v : _velocityBuffer) avg += v;
        return avg / _velocityBuffer.size();
    }

    FastVector3 MovementController::GetAverageAngularVelocity() {
        FastVector3 avg = FastVector3::zero();
        for (const auto& v : _angularVelocityBuffer) avg += v;
        return avg / _angularVelocityBuffer.size();
    }

    void MovementController::Init(GlobalNamespace::VRController* vrController, SaberTrickManager* saberTrickManager) {
        _controller = vrController;
        _saberTrickManager = saberTrickManager;
        set_enabled(true);
    }

    void MovementController::Awake() {
        set_enabled(false);
    }

    void MovementController::Update() {
        if (_controller->get_enabled()) {
            _controllerPosition = _controller->get_position();
            _controllerRotation = _controller->get_rotation();
            _velocity = (_controllerPosition - _prevPos) / UnityEngine::Time::get_deltaTime();
            _angularVelocity = GetAngularVelocity(_prevRot, _controllerRotation);
            AddProbe(_velocity, _angularVelocity);
            _prevPos = _controllerPosition;
            _prevRot = _controllerRotation;
        }
    }

    void MovementController::AddProbe(FastVector3 vel, FastVector3 ang) {
        if (_currentProbeIndex > _velocityBuffer.size() - 1) _currentProbeIndex = 0;
        _velocityBuffer[_currentProbeIndex] = vel;
        _angularVelocityBuffer[_currentProbeIndex] = ang;
        _currentProbeIndex++;
    }

    FastVector3 MovementController::GetAngularVelocity(FastQuaternion foreLastFrameRotation, FastQuaternion lastFrameRotation) {
        auto q = lastFrameRotation * FastQuaternion::Inverse(foreLastFrameRotation);
        if (std::abs(q.w) > 1023.5f / 1024.0f)
            return FastVector3::zero();
        float gain;
        if (q.w < 0.0f)
        {
            auto angle = std::acosf(-q.w);
            gain = (float) (-2.0f * angle / (std::sin(angle) * UnityEngine::Time::get_deltaTime()));
        }
        else
        {
            auto angle = std::acosf(q.w);
            gain = (float) (2.0f * angle / (std::sin(angle) * UnityEngine::Time::get_deltaTime()));
        }

        return FastVector3(q.x * gain, q.y * gain, q.z * gain);
    }

    FastVector3 MovementController::get_angularVelocity() {
        return _angularVelocity;
    }

    GlobalNamespace::VRController* MovementController::get_controller() {
        return _controller;
    }

    FastVector3 MovementController::get_controllerPosition() {
        return _controllerPosition;
    }

    FastQuaternion MovementController::get_controllerRotation() {
        return _controllerRotation;
    }

    SaberTrickManager* MovementController::get_saberTrickManager() {
        return _saberTrickManager;
    }

    FastVector3 MovementController::get_velocity() {
        return _velocity;
    }

    FastVector3 MovementController::get_localControllerPosition() {
        return _controller->get_transform()->get_localPosition();
    }

    void MovementController::set_localControllerPosition(FastVector3 value) {
        _controller->get_transform()->set_localPosition(value);
    }

    FastQuaternion MovementController::get_localControllerRotation() {
        return _controller->get_transform()->get_localRotation();
    }

    void MovementController::set_localControllerRotation(FastQuaternion value) {
        _controller->get_transform()->set_localRotation(value);
    }

    float MovementController::get_saberSpeed() {
        return _velocity.Magnitude();
    }
}