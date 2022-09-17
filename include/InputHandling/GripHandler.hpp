#pragma once

#include "custom-types/shared/macros.hpp"
#include "lapiz/shared/macros.hpp"
#include "InputHandler.hpp"
#include "GlobalNamespace/OVRInput.hpp"
#include "UnityEngine/XR/InputDevice.hpp"
#include "Enums.hpp"

DECLARE_CLASS_CUSTOM(TrickSaber::InputHandling, GripHandler, TrickSaber::InputHandling::InputHandler,
    DECLARE_PRIVATE_FIELD(UnityEngine::XR::InputDevice, _controllerInputDevice);
    DECLARE_PRIVATE_FIELD(GlobalNamespace::OVRInput::Controller, _oculusController);

    DECLARE_INSTANCE_METHOD(float, GetInputValue);

    DECLARE_CTOR(ctor, GlobalNamespace::OVRInput::Controller oculusController, UnityEngine::XR::InputDevice controllerInputDevice, float threshold, bool isReversed);

)