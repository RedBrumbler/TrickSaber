#pragma once

#include "custom-types/shared/macros.hpp"
#include "System/Collections/Generic/Dictionary_2.hpp"
#include "System/Collections/Generic/HashSet_1.hpp"
#include "Enums.hpp"
#include "InputHandler.hpp"

#include <unordered_set>
#include <unordered_map>

#include "beatsaber-hook/shared/utils/gc-alloc.hpp"

namespace TrickSaber::InputHandling {

    struct TrickInputHandler {
        using TrickHandlerVector = std::vector<std::unique_ptr<InputHandler>>;
        using TrickHandlerVectorsMap = std::unordered_map<TrickAction, TrickHandlerVector>;
        TrickHandlerVectorsMap trickHandlerSets;

        TrickInputHandler();

        ///
        /// \param action
        /// \param handler Takes ownership of the pointer
        void Add(TrickSaber::TrickAction action, std::unique_ptr<InputHandler> handler);

        TrickHandlerVector *GetHandlers(TrickSaber::TrickAction action);
    };
}