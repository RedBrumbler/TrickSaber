#pragma once

#include "custom-types/shared/macros.hpp"
#include "lapiz/shared/macros.hpp"
#include "TrickInputHandler.hpp"
#include "GlobalNamespace/SaberType.hpp"
#include "GlobalNamespace/VRControllersInputManager.hpp"
#include "System/Collections/Generic/HashSet_1.hpp"

DECLARE_CLASS_CODEGEN(TrickSaber::InputHandling, InputManager, Il2CppObject,
    DECLARE_PRIVATE_FIELD(TrickInputHandler*, _trickInputHandler);

    DECLARE_CTOR(ctor);
    DECLARE_INSTANCE_METHOD(void, Init, GlobalNamespace::SaberType saberType, GlobalNamespace::VRControllersInputManager* vrControllersInputManager);
    DECLARE_INSTANCE_METHOD(void, Tick);
    public:
        UnorderedEventCallback<TrickSaber::TrickAction, float> trickActivated;
        UnorderedEventCallback<TrickSaber::TrickAction> trickDeactivated;
    private:
        bool CheckHandlersDown(TrickInputHandler::TrickHandlerHashSet* handlers, float& val);
        bool CheckHandlersUp(TrickInputHandler::TrickHandlerHashSet* handlers);
)