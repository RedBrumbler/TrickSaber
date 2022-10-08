#pragma once

#include "custom-types/shared/macros.hpp"
#include "lapiz/shared/macros.hpp"
#include "InputHandler.hpp"
#include "GlobalNamespace/OVRInput.hpp"
#include "UnityEngine/XR/InputDevice.hpp"
#include "Enums.hpp"

namespace TrickSaber::InputHandling {
struct GripHandler : public TrickSaber::InputHandling::InputHandler {
    UnityEngine::XR::InputDevice _controllerInputDevice;
    GlobalNamespace::OVRInput::Controller _oculusController;

    float GetInputValue() const override;

    GripHandler(GlobalNamespace::OVRInput::Controller oculusController,
             UnityEngine::XR::InputDevice controllerInputDevice, float threshold, bool isReversed);

};
}