#pragma once

#include "custom-types/shared/macros.hpp"

namespace TrickSaber::InputHandling {
    struct InputHandler {
        InputHandler(float threshold, bool isReversed);
        InputHandler(InputHandler&&) = default; // move by default
        virtual ~InputHandler() = default;

        float threshold;
        bool isReversed;
        mutable bool isUpTriggered;

        [[nodiscard]] virtual float GetInputValue() const = 0;
        [[nodiscard]] float GetActivationValue(float val) const;
        [[nodiscard]] bool Deactivated() const;
        [[nodiscard]] bool Activated(float &val) const;

    };
}