#include "InputHandling/TrickInputHandler.hpp"

DEFINE_TYPE(TrickSaber::InputHandling, TrickInputHandler);

namespace TrickSaber::InputHandling {
    void TrickInputHandler::ctor() {
        trickHandlerSets = TrickHandlerSetsDictionary::New_ctor();

        trickHandlerSets->Add(TrickSaber::TrickAction::Throw, TrickHandlerHashSet::New_ctor());
        trickHandlerSets->Add(TrickSaber::TrickAction::Spin, TrickHandlerHashSet::New_ctor());
    }
    
    void TrickInputHandler::Add(TrickSaber::TrickAction action, InputHandler* handler) {
        if (action == TrickSaber::TrickAction::None) return;
        TrickHandlerHashSet* set = nullptr;
        if (trickHandlerSets->TryGetValue(action, byref(set))) {
            set->Add(handler);
        }
    }

    TrickInputHandler::TrickHandlerHashSet* TrickInputHandler::GetHandlers(TrickSaber::TrickAction action) {
        TrickHandlerHashSet* set = nullptr;
        if (trickHandlerSets->TryGetValue(action, byref(set))) {
            return set;
        }
        return nullptr;
    }
}