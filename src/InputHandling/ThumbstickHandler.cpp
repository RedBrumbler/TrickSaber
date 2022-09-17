#include "InputHandling/ThumbstickHandler.hpp"
#include "logging.hpp"

#include "UnityEngine/Input.hpp"

DEFINE_TYPE(TrickSaber::InputHandling, ThumbstickHandler);

namespace TrickSaber::InputHandling {
    void ThumbstickHandler::ctor(UnityEngine::XR::XRNode node, TrickSaber::ThumbstickDir thumbstickDir, float threshold, bool isReversed) {
        static auto base = classof(InputHandler*);
        INVOKE_BASE_CTOR(base, threshold, isReversed);
        _inputString = fmt::format("{}{}",
            thumbstickDir == TrickSaber::ThumbstickDir::Horizontal ? "Horizontal" : "Vertical",
            node == UnityEngine::XR::XRNode::LeftHand ? "LeftHand" : "RightHand"
        );
    }

    float ThumbstickHandler::GetInputValue() {
        return UnityEngine::Input::GetAxis(_inputString);
    }
}