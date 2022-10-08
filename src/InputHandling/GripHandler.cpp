#include "InputHandling/GripHandler.hpp"

#include "GlobalNamespace/OVRInput.hpp"
#include "GlobalNamespace/OVRInput_Axis1D.hpp"

namespace TrickSaber::InputHandling {
    GripHandler::GripHandler(GlobalNamespace::OVRInput::Controller oculusController, UnityEngine::XR::InputDevice controllerInputDevice, float threshold, bool isReversed): InputHandler(threshold, isReversed) {
        _oculusController = oculusController;
        _controllerInputDevice = controllerInputDevice;
    }

    float GripHandler::GetInputValue() const {
        return GlobalNamespace::OVRInput::Get(GlobalNamespace::OVRInput::Axis1D::PrimaryHandTrigger, _oculusController);
    }
}