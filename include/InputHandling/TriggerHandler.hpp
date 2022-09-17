#pragma once

#include "custom-types/shared/macros.hpp"
#include "lapiz/shared/macros.hpp"
#include "InputHandler.hpp"
#include "UnityEngine/XR/XRNode.hpp"

DECLARE_CLASS_CUSTOM(TrickSaber::InputHandling, TriggerHandler, TrickSaber::InputHandling::InputHandler,
    DECLARE_PRIVATE_FIELD(StringW, _inputString);
    DECLARE_INSTANCE_METHOD(float, GetInputValue);

    DECLARE_CTOR(ctor, UnityEngine::XR::XRNode node, float threshold, bool isReversed);

)