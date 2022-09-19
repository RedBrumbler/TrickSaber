#pragma once

#include "UnityEngine/Rigidbody.hpp"
#include "UnityEngine/ForceMode.hpp"
#include "sombrero/shared/FastVector3.hpp"

/* This type definition just extends RigidBody with the icall resolved AddRelativeTorque method, this way not every function that ever adds torque will have to resolve the icall */
namespace TrickSaber {
    class Rigidbody;

    enum class RigidbodyInterpolation {
        None,
        Interpolate,
        Extrapolate
    };
}

template<>
struct ::il2cpp_utils::il2cpp_type_check::il2cpp_no_arg_class<TrickSaber::RigidbodyInterpolation> {
    static inline Il2CppClass* get() {
        return classof(int);
    }
};

NEED_NO_BOX(::TrickSaber::Rigidbody);
DEFINE_IL2CPP_ARG_TYPE(::TrickSaber::Rigidbody*, "UnityEngine", "Rigidbody");
namespace TrickSaber {
    class Rigidbody : public UnityEngine::Rigidbody {
        public:
            /* void Rigidbody_CUSTOM_AddRelativeTorque_Injected(ScriptingBackendNativeObjectPtrOpaque *param_1,Vector3f *param_2,int param_3) */
            void AddRelativeTorque(Sombrero::FastVector3 torque, UnityEngine::ForceMode mode = UnityEngine::ForceMode::Force) {
                using AddRelativeTorque_t = function_ptr_t<void, TrickSaber::Rigidbody*, Sombrero::FastVector3*, UnityEngine::ForceMode>;
                static auto addRelativeTorque = reinterpret_cast<AddRelativeTorque_t>(il2cpp_functions::resolve_icall("UnityEngine.Rigidbody::AddRelativeTorque_Injected"));
                addRelativeTorque(this, &torque, mode);
            }

            bool get_detectCollisions() {
                using get_detectCollisions_t = function_ptr_t<bool, TrickSaber::Rigidbody*>;
                static auto get_detectCollisions_f = reinterpret_cast<get_detectCollisions_t>(il2cpp_functions::resolve_icall("UnityEngine.Rigidbody::get_detectCollisions"));
                return get_detectCollisions_f(this);
            }

            void set_detectCollisions(bool value) {
                using set_detectCollisions_t = function_ptr_t<void, TrickSaber::Rigidbody*, bool>;
                static auto set_detectCollisions_f = reinterpret_cast<set_detectCollisions_t>(il2cpp_functions::resolve_icall("UnityEngine.Rigidbody::set_detectCollisions"));
                set_detectCollisions_f(this, value);
            }

            float get_maxAngularVelocity() {
                using get_maxAngularVelocity_t = function_ptr_t<float, TrickSaber::Rigidbody*>;
                static auto get_maxAngularVelocity_f = reinterpret_cast<get_maxAngularVelocity_t>(il2cpp_functions::resolve_icall("UnityEngine.Rigidbody::get_maxAngularVelocity"));
                return get_maxAngularVelocity_f(this);
            }

            void set_maxAngularVelocity(float value) {
                using set_maxAngularVelocity_t = function_ptr_t<void, TrickSaber::Rigidbody*, float>;
                static auto set_maxAngularVelocity_f = reinterpret_cast<set_maxAngularVelocity_t>(il2cpp_functions::resolve_icall("UnityEngine.Rigidbody::set_maxAngularVelocity"));
                set_maxAngularVelocity_f(this, value);
            }

            TrickSaber::RigidbodyInterpolation get_interpolation() {
                using get_interpolation_t = function_ptr_t<TrickSaber::RigidbodyInterpolation, TrickSaber::Rigidbody*>;
                static auto get_interpolation_f = reinterpret_cast<get_interpolation_t>(il2cpp_functions::resolve_icall("UnityEngine.Rigidbody::get_interpolation"));
                return get_interpolation_f(this);
            }

            void set_interpolation(TrickSaber::RigidbodyInterpolation value) {
                using set_interpolation_t = function_ptr_t<void, TrickSaber::Rigidbody*, TrickSaber::RigidbodyInterpolation>;
                static auto set_interpolation_f = reinterpret_cast<set_interpolation_t>(il2cpp_functions::resolve_icall("UnityEngine.Rigidbody::set_interpolation"));
                set_interpolation_f(this, value);
            }
    };
}

