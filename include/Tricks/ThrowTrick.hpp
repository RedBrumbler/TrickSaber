#pragma once

#include "Trick.hpp"
#include "custom-types/shared/coroutine.hpp"

DECLARE_CLASS_CUSTOM(TrickSaber::Tricks, ThrowTrick, TrickSaber::Tricks::Trick,
    DECLARE_PRIVATE_FIELD(float, _controllerSnapThreshold);
    DECLARE_PRIVATE_FIELD(float, _saberRotSpeed);
    DECLARE_PRIVATE_FIELD(float, _velocityMultiplier);

    DECLARE_INSTANCE_METHOD(void, OnTrickStart);
    DECLARE_INSTANCE_METHOD(void, OnTrickEndRequested);
    DECLARE_INSTANCE_METHOD(void, OnTrickEndImmediately);
    DECLARE_INSTANCE_METHOD(void, OnInit);

    DECLARE_PRIVATE_METHOD(void, ThrowEnd);
    DECLARE_CTOR(ctor);
    public:
        custom_types::Helpers::Coroutine ReturnSaber(float speed);
)