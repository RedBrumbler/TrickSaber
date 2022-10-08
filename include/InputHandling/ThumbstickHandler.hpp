#pragma once

#include "custom-types/shared/macros.hpp"
#include "lapiz/shared/macros.hpp"
#include "InputHandler.hpp"
#include "UnityEngine/XR/XRNode.hpp"
#include "Enums.hpp"

#include "UnityEngine/Object.hpp"

namespace TrickSaber::InputHandling {
    struct ThumbstickHandler : public TrickSaber::InputHandling::InputHandler {
        Il2CppString* _inputString;

        float GetInputValue() const override;

        ThumbstickHandler(
                UnityEngine::XR::XRNode node, TrickSaber::ThumbstickDir thumbstickDir, float threshold,
                bool isReversed);
    };
}