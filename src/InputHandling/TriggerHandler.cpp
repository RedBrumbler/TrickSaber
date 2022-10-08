#include "InputHandling/TriggerHandler.hpp"

#include "UnityEngine/Input.hpp"

ConstString TriggerLeftHand("TriggerLeftHand");
ConstString TriggerRightHand("TriggerRightHand");

namespace TrickSaber::InputHandling {
    TriggerHandler::TriggerHandler(UnityEngine::XR::XRNode node, float threshold, bool isReversed) : InputHandler(threshold, isReversed), _inputString(node == UnityEngine::XR::XRNode::LeftHand ? TriggerLeftHand : TriggerRightHand) {
        
    }

    float TriggerHandler::GetInputValue() const {
        return UnityEngine::Input::GetAxis(_inputString);
    }
}