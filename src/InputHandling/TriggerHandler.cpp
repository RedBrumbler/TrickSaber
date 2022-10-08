#include "InputHandling/TriggerHandler.hpp"

#include "UnityEngine/Input.hpp"

namespace TrickSaber::InputHandling {
    TriggerHandler::TriggerHandler(UnityEngine::XR::XRNode node, float threshold, bool isReversed) : InputHandler(threshold, isReversed) {
        _inputString = il2cpp_utils::newcsstr(node == UnityEngine::XR::XRNode::LeftHand ? "TriggerLeftHand" : "TriggerRightHand");
    }

    float TriggerHandler::GetInputValue() const {
        return UnityEngine::Input::GetAxis(const_cast<Il2CppString*>(_inputString.ptr()));
    }
}