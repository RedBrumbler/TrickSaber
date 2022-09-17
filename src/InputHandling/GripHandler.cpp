#include "InputHandling/GripHandler.hpp"

#include "GlobalNamespace/OVRInput.hpp"
#include "GlobalNamespace/OVRInput_Axis1D.hpp"

DEFINE_TYPE(TrickSaber::InputHandling, GripHandler);

namespace TrickSaber::InputHandling {
    void GripHandler::ctor(GlobalNamespace::OVRInput::Controller oculusController, UnityEngine::XR::InputDevice controllerInputDevice, float threshold, bool isReversed) {
        static auto base = classof(InputHandler*);
        INVOKE_BASE_CTOR(base, threshold, isReversed);

        _oculusController = oculusController;
        _controllerInputDevice = controllerInputDevice;
    }

    float GripHandler::GetInputValue() {
        return GlobalNamespace::OVRInput::Get(GlobalNamespace::OVRInput::Axis1D::PrimaryHandTrigger, _oculusController);
    }
}