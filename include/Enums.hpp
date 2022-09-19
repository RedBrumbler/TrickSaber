#pragma once

#include "beatsaber-hook/shared/utils/il2cpp-utils.hpp"
#include <string_view>
#include <fmt/core.h>

namespace TrickSaber {
    // TODO: define ToString methods for all these
    enum class VRSystem {
        Oculus,
        SteamVR
    };

    enum class ThumbstickDir {
        Horizontal,
        Vertical
    };

    std::string ThumbstickDir_toString(const ThumbstickDir& value);
    ThumbstickDir ThumbstickDir_fromString(const std::string& value);

    enum class SpinDir {
        Forward,
        Backward
    };

    std::string SpinDir_toString(const SpinDir& value);
    SpinDir SpinDir_fromString(const std::string& value);

    enum class TrickAction {
        None,
        Throw,
        Spin
    };

    std::string TrickAction_toString(const TrickAction& value);
    TrickAction TrickAction_fromString(const std::string& value);

    enum class TrickState {
        Inactive,
        Started,
        Ending
    };
}

/* Basically tell il2cpp type check that these enums are ints for all C# intents and purposes */
template<>
struct ::il2cpp_utils::il2cpp_type_check::il2cpp_no_arg_class<TrickSaber::TrickState> {
    static inline Il2CppClass* get() {
        return classof(int);
    }
};
static_assert(sizeof(TrickSaber::TrickState) == sizeof(int));

template<>
struct ::il2cpp_utils::il2cpp_type_check::il2cpp_no_arg_class<TrickSaber::VRSystem> {
    static inline Il2CppClass* get() {
        return classof(int);
    }
};
static_assert(sizeof(TrickSaber::VRSystem) == sizeof(int));

template<>
struct ::il2cpp_utils::il2cpp_type_check::il2cpp_no_arg_class<TrickSaber::ThumbstickDir> {
    static inline Il2CppClass* get() {
        return classof(int);
    }
};
static_assert(sizeof(TrickSaber::ThumbstickDir) == sizeof(int));

template<>
struct ::il2cpp_utils::il2cpp_type_check::il2cpp_no_arg_class<TrickSaber::SpinDir> {
    static inline Il2CppClass* get() {
        return classof(int);
    }
};
static_assert(sizeof(TrickSaber::SpinDir) == sizeof(int));

template<>
struct ::il2cpp_utils::il2cpp_type_check::il2cpp_no_arg_class<TrickSaber::TrickAction> {
    static inline Il2CppClass* get() {
        return classof(int);
    }
};
static_assert(sizeof(TrickSaber::TrickAction) == sizeof(int));

template <> struct fmt::formatter<::TrickSaber::VRSystem> : formatter<string_view> {
    // parse is inherited from formatter<string_view>.
    template <typename FormatContext>
    auto format(::TrickSaber::VRSystem s, FormatContext& ctx) {
        switch (s) {
            case ::TrickSaber::VRSystem::Oculus: return formatter<string_view>::format("Oculus", ctx);
            case ::TrickSaber::VRSystem::SteamVR: return formatter<string_view>::format("SteamVR", ctx);
            default: return formatter<string_view>::format("Unknown", ctx);
        }
    }
};

template <> struct fmt::formatter<::TrickSaber::ThumbstickDir> : formatter<string_view> {
    // parse is inherited from formatter<string_view>.
    template <typename FormatContext>
    auto format(::TrickSaber::ThumbstickDir s, FormatContext& ctx) {
        switch (s) {
            case ::TrickSaber::ThumbstickDir::Horizontal: return formatter<string_view>::format("Horizontal", ctx);
            case ::TrickSaber::ThumbstickDir::Vertical: return formatter<string_view>::format("Vertical", ctx);
            default: return formatter<string_view>::format("Unknown", ctx);
        }
    }
};

template <> struct fmt::formatter<::TrickSaber::SpinDir> : formatter<string_view> {
    // parse is inherited from formatter<string_view>.
    template <typename FormatContext>
    auto format(::TrickSaber::SpinDir s, FormatContext& ctx) {
        switch (s) {
            case ::TrickSaber::SpinDir::Forward: return formatter<string_view>::format("Forward", ctx);
            case ::TrickSaber::SpinDir::Backward: return formatter<string_view>::format("Backward", ctx);
            default: return formatter<string_view>::format("Unknown", ctx);
        }
    }
};

template <> struct fmt::formatter<::TrickSaber::TrickAction> : formatter<string_view> {
    // parse is inherited from formatter<string_view>.
    template <typename FormatContext>
    auto format(::TrickSaber::TrickAction s, FormatContext& ctx) {
        switch (s) {
            case ::TrickSaber::TrickAction::None: return formatter<string_view>::format("None", ctx);
            case ::TrickSaber::TrickAction::Throw: return formatter<string_view>::format("Throw", ctx);
            case ::TrickSaber::TrickAction::Spin: return formatter<string_view>::format("Spin", ctx);
            default: return formatter<string_view>::format("Unknown", ctx);
        }
    }
};

template <> struct fmt::formatter<::TrickSaber::TrickState> : formatter<string_view> {
    // parse is inherited from formatter<string_view>.
    template <typename FormatContext>
    auto format(::TrickSaber::TrickState s, FormatContext& ctx) {
        switch (s) {
            case ::TrickSaber::TrickState::Inactive: return formatter<string_view>::format("Inactive", ctx);
            case ::TrickSaber::TrickState::Started: return formatter<string_view>::format("Started", ctx);
            case ::TrickSaber::TrickState::Ending: return formatter<string_view>::format("Ending", ctx);
            default: return formatter<string_view>::format("Unknown", ctx);
        }
    }
};
