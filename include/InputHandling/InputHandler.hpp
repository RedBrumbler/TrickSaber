#pragma once

#include "custom-types/shared/macros.hpp"

DECLARE_CLASS_CODEGEN(TrickSaber::InputHandling, InputHandler, Il2CppObject,
    DECLARE_INSTANCE_FIELD(bool, isUpTriggered);
    DECLARE_INSTANCE_FIELD(float, threshold);
    DECLARE_INSTANCE_FIELD(bool, isReversed);

    DECLARE_INSTANCE_METHOD(float, GetInputValue_base);
    DECLARE_INSTANCE_METHOD(float, GetActivationValue, float val);
    DECLARE_INSTANCE_METHOD(bool, Deactivated);

    DECLARE_CTOR(ctor, float threshold, bool isReversed);
    public:
        bool Activated(float& val);

)