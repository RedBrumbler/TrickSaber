#include "InputHandling/ThumbstickHandler.hpp"
#include "logging.hpp"

#include "UnityEngine/Input.hpp"

ConstString HorizontalLeftHand("HorizontalLeftHand");
ConstString HorizontalRightHand("HorizontalRightHand");
ConstString VerticalLeftHand("VerticalLeftHand");
ConstString VerticalRightHand("VerticalRightHand");

namespace TrickSaber::InputHandling {
    ThumbstickHandler::ThumbstickHandler(UnityEngine::XR::XRNode node, TrickSaber::ThumbstickDir thumbstickDir, float threshold, bool isReversed) : InputHandler(threshold, isReversed), 
    _inputString(
        thumbstickDir == TrickSaber::ThumbstickDir::Horizontal 
        ? (node == UnityEngine::XR::XRNode::LeftHand ? HorizontalLeftHand : HorizontalRightHand) 
        : (node == UnityEngine::XR::XRNode::LeftHand ? VerticalLeftHand : VerticalRightHand)
    )
    {}

    float ThumbstickHandler::GetInputValue() const {
        return UnityEngine::Input::GetAxis(_inputString);
    }
}