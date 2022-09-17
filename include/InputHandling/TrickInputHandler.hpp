#pragma once

#include "custom-types/shared/macros.hpp"
#include "System/Collections/Generic/Dictionary_2.hpp"
#include "System/Collections/Generic/HashSet_1.hpp"
#include "Enums.hpp"
#include "InputHandler.hpp"

DECLARE_CLASS_CODEGEN(TrickSaber::InputHandling, TrickInputHandler, Il2CppObject,
    using TrickHandlerHashSet = System::Collections::Generic::HashSet_1<InputHandler*>;
    using TrickHandlerSetsDictionary = System::Collections::Generic::Dictionary_2<TrickSaber::TrickAction, TrickHandlerHashSet*>;
    DECLARE_INSTANCE_FIELD(TrickHandlerSetsDictionary*, trickHandlerSets);

    DECLARE_INSTANCE_METHOD(void, Add, TrickSaber::TrickAction action, InputHandler* handler);
    DECLARE_INSTANCE_METHOD(TrickHandlerHashSet*, GetHandlers, TrickSaber::TrickAction action);
    DECLARE_CTOR(ctor);
)