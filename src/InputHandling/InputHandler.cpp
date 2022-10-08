#include "InputHandling/InputHandler.hpp"

namespace TrickSaber::InputHandling {
    InputHandler::InputHandler(float threshold, bool isReversed) :
            threshold(threshold),
            isReversed(isReversed), isUpTriggered(false) {}

    float InputHandler::GetActivationValue(float val) const {
        float value = std::abs(val);
        if (isReversed) return 1.0f - value;
        return value;
    }

    bool InputHandler::Deactivated() const {
        if (GetActivationValue(GetInputValue()) < threshold && !isUpTriggered) {
            isUpTriggered = true;
            return true;
        }

        return false;
    }

    bool InputHandler::Activated(float &val) const {
        auto value = GetInputValue();
        auto activationValue = GetActivationValue(value);
        val = 0;

        if (activationValue > threshold) {
            val = isReversed ? activationValue : value;
            isUpTriggered = false;
            return true;
        }

        return false;
    }
}