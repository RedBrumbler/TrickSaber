#include "InputHandling/TrickInputHandler.hpp"



namespace TrickSaber::InputHandling {
    TrickInputHandler::TrickInputHandler() = default;

    void TrickInputHandler::Add(TrickSaber::TrickAction action, std::unique_ptr<InputHandler> handler) {
        if (action == TrickSaber::TrickAction::None) return;

        trickHandlerSets[action].emplace_back(std::move(handler));

    }

    TrickInputHandler::TrickHandlerHashSet *TrickInputHandler::GetHandlers(TrickSaber::TrickAction action) {
        return &trickHandlerSets[action];
    }
}