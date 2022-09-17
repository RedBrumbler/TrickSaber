#include "InputHandling/TriggerHandler.hpp"

#include "UnityEngine/Input.hpp"

DEFINE_TYPE(TrickSaber::InputHandling, TriggerHandler);

namespace TrickSaber::InputHandling {
    void TriggerHandler::ctor(UnityEngine::XR::XRNode node, float threshold, bool isReversed) {
        static auto base = classof(InputHandler*);
        INVOKE_BASE_CTOR(base, threshold, isReversed);
        _inputString = node == UnityEngine::XR::XRNode::LeftHand ? "TriggerLeftHand" : "TriggerRightHand";
    }

    float TriggerHandler::GetInputValue() {
        return UnityEngine::Input::GetAxis(_inputString);
    }
}