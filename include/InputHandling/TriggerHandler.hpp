#pragma once

#include "custom-types/shared/macros.hpp"
#include "lapiz/shared/macros.hpp"
#include "InputHandler.hpp"
#include "UnityEngine/XR/XRNode.hpp"

#include "UnityEngine/Object.hpp"

namespace TrickSaber::InputHandling {
    struct TriggerHandler : public TrickSaber::InputHandling::InputHandler {
        SafePtr<Il2CppString> _inputString;

        float GetInputValue() const override;

        TriggerHandler(UnityEngine::XR::XRNode node, float threshold, bool isReversed);
    };
}