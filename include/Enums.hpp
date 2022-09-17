#pragma once

#include "beatsaber-hook/shared/utils/il2cpp-utils.hpp"

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

    enum class SpinDir {
        Forward,
        Backward
    };

    enum class TrickAction {
        None,
        Throw,
        Spin
    };

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
