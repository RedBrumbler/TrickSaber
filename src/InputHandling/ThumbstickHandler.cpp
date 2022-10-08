#include "InputHandling/ThumbstickHandler.hpp"
#include "logging.hpp"

#include "UnityEngine/Input.hpp"

namespace TrickSaber::InputHandling {
    ThumbstickHandler::ThumbstickHandler(UnityEngine::XR::XRNode node, TrickSaber::ThumbstickDir thumbstickDir, float threshold, bool isReversed) : InputHandler(threshold, isReversed) {
        _inputString = il2cpp_utils::newcsstr(fmt::format("{}{}",
            thumbstickDir == TrickSaber::ThumbstickDir::Horizontal ? "Horizontal" : "Vertical",
            node == UnityEngine::XR::XRNode::LeftHand ? "LeftHand" : "RightHand"
        ));
    }

    float ThumbstickHandler::GetInputValue() const {
        return UnityEngine::Input::GetAxis(const_cast<Il2CppString*>(_inputString.ptr()));
    }
}