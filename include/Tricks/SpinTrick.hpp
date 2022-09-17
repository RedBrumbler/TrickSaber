#pragma once

#include "Trick.hpp"
#include "UnityEngine/Transform.hpp"
#include "custom-types/shared/coroutine.hpp"

DECLARE_CLASS_CUSTOM(TrickSaber::Tricks, SpinTrick, TrickSaber::Tricks::Trick,
    DECLARE_PRIVATE_FIELD(bool, _isVelocityDependent);
    DECLARE_PRIVATE_FIELD(UnityEngine::Transform*, _saberModelTransform);
    DECLARE_PRIVATE_FIELD(float, _spinSpeed);
    DECLARE_PRIVATE_FIELD(float, _largestSpinSpeed);
    DECLARE_PRIVATE_FIELD(float, _finalSpinSpeed);

    DECLARE_INSTANCE_METHOD(void, OnTrickStart);
    DECLARE_INSTANCE_METHOD(void, OnTrickEndRequested);
    DECLARE_INSTANCE_METHOD(void, OnTrickEndImmediately);
    DECLARE_INSTANCE_METHOD(void, OnInit);

    DECLARE_INSTANCE_METHOD(void, Update);
    DECLARE_CTOR(ctor);

    private:
        custom_types::Helpers::Coroutine LerpToOriginalRotation();
        custom_types::Helpers::Coroutine CompleteRotation();
)