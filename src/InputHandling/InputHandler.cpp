#include "InputHandling/InputHandler.hpp"

DEFINE_TYPE(TrickSaber::InputHandling, InputHandler);

namespace TrickSaber::InputHandling {
    void InputHandler::ctor(float threshold, bool isReversed) {
        this->threshold = threshold;
        this->isReversed = isReversed;
    }
    
    float InputHandler::GetInputValue_base() {
        return il2cpp_utils::RunMethod<float>(this, "GetInputValue").value_or(0.0f);
    }

    float InputHandler::GetActivationValue(float val) {
        float value = std::abs(val);
        if (isReversed) return 1.0f - value;
        return value;
    }

    bool InputHandler::Deactivated() {
        if (GetActivationValue(GetInputValue_base()) < threshold && !isUpTriggered)
        {
            isUpTriggered = true;
            return true;
        }

        return false;
    }

    bool InputHandler::Activated(float& val) {
        auto value = GetInputValue_base();
        auto activationValue = GetActivationValue(value);
        val = 0;

        if (activationValue > threshold)
        {
            val = isReversed ? activationValue : value;
            isUpTriggered = false;
            return true;
        }

        return false;
    }


}