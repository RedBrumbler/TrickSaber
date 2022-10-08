#include "InputHandling/InputManager.hpp"
#include "InputHandling/TriggerHandler.hpp"
#include "InputHandling/GripHandler.hpp"
#include "InputHandling/ThumbstickHandler.hpp"
#include "config.hpp"

#include "GlobalNamespace/OVRInput.hpp"
#include "UnityEngine/XR/XRNode.hpp"
#include "UnityEngine/XR/InputDevices.hpp"
#include "UnityEngine/XR/InputDevice.hpp"
#include "UnityEngine/XR/InputTracking.hpp"

DEFINE_TYPE(TrickSaber::InputHandling, InputManager);

namespace TrickSaber::InputHandling {
    void InputManager::ctor() {
        INVOKE_CTOR();
    }

    void InputManager::Init(GlobalNamespace::SaberType saberType, GlobalNamespace::VRControllersInputManager* vrControllersInputManager) {
        GlobalNamespace::OVRInput::Controller oculusController;
        UnityEngine::XR::XRNode node;
        if (saberType == GlobalNamespace::SaberType::SaberA)
        {
            oculusController = GlobalNamespace::OVRInput::Controller::LTouch;
            node = UnityEngine::XR::XRNode::LeftHand;
        }
        else
        {
            oculusController = GlobalNamespace::OVRInput::Controller::RTouch;
            node = UnityEngine::XR::XRNode::RightHand;
        }

        using GetDeviceIdAtXRNode = function_ptr_t<uint64_t, UnityEngine::XR::XRNode>;
        static auto getDeviceIdAtXRNode = reinterpret_cast<GetDeviceIdAtXRNode>(il2cpp_functions::resolve_icall("UnityEngine.XR.InputTracking::GetDeviceIdAtXRNode"));
        auto controllerInputDevice = UnityEngine::XR::InputDevice(getDeviceIdAtXRNode(node), true);
        auto dir = config.thumbstickDirection;

        auto triggerHandler = new TriggerHandler(node, config.triggerThreshold, config.reverseTrigger);
        auto gripHandler = new GripHandler(oculusController, controllerInputDevice, config.gripThreshold, config.reverseGrip);
        auto thumbstickAction = new ThumbstickHandler(node, dir, config.thumbstickThreshold, config.reverseThumbstick);

        _trickInputHandler.Add(config.triggerAction, std::unique_ptr<InputHandler>(triggerHandler));
        _trickInputHandler.Add(config.gripAction, std::unique_ptr<InputHandler>(gripHandler));
        _trickInputHandler.Add(config.thumbstickAction, std::unique_ptr<InputHandler>(thumbstickAction));
    }

    // Using ITickable seems to result in GetHandlers returning no handlers (?!?)
    // So we need to manually tick
    void InputManager::Tick() {

        for (auto const& [trickAction, handlers] : _trickInputHandler.trickHandlerSets) {
            float val = 0.0f;
            if (CheckHandlersDown(handlers, val))
                trickActivated.invoke(trickAction, val);
            else if (CheckHandlersUp(handlers)) trickDeactivated.invoke(trickAction);
        }
    }

    bool InputManager::CheckHandlersDown(TrickInputHandler::TrickHandlerHashSet const& handlers, float& val) {
        val = 0;
        if (handlers.empty()) return false;
        bool output = true;
        for (auto const& handler : handlers) {
            float handlerValue = 0.0f;
            output &= handler->Activated(handlerValue);
            val += handlerValue;
        }

        if (output) val /= handlers.size();

        return output;
    }

    bool InputManager::CheckHandlersUp(TrickInputHandler::TrickHandlerHashSet const&  handlers) {
        for (auto const& handler : handlers) {
            if (handler->Deactivated()) {
                return true;
            }
        }
        return false;
    }

}