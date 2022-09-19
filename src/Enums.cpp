#include "Enums.hpp"

namespace TrickSaber {
    std::string ThumbstickDir_toString(const ThumbstickDir& value) {
        return fmt::format("{}", value);
    }

    ThumbstickDir ThumbstickDir_fromString(const std::string& value) {
        if (value == "Horizontal") return ThumbstickDir::Horizontal;
        else if (value == "Vertical") return ThumbstickDir::Vertical;
        return ThumbstickDir::Vertical;
    }

    std::string SpinDir_toString(const SpinDir& value) {
        return fmt::format("{}", value);
    }

    SpinDir SpinDir_fromString(const std::string& value) {
        if (value == "Forward") return SpinDir::Forward;
        else if (value == "Backward") return SpinDir::Backward;
        return SpinDir::Backward;
    }

    std::string TrickAction_toString(const TrickAction& value) {
        return fmt::format("{}", value);
    }

    TrickAction TrickAction_fromString(const std::string& value) {
        if (value == "None") return TrickAction::None;
        else if (value == "Spin") return TrickAction::Spin;
        else if (value == "Throw") return TrickAction::Throw;
        return TrickAction::None;
    }
}