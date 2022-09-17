#pragma once

#include "custom-types/shared/macros.hpp"
#include "lapiz/shared/macros.hpp"
#include "macros.hpp"
#include "UnityEngine/MonoBehaviour.hpp"
#include "UnityEngine/GameObject.hpp"
#include "System/Type.hpp"

#include "Zenject/DiContainer.hpp"
#include "Zenject/Factory_3.hpp"
#include "Zenject/IFactory_3.hpp"
#include "Zenject/PlaceholderFactory_3.hpp"

#include "MovementController.hpp"
#include "SaberTrickModel.hpp"
#include "Enums.hpp"

namespace TrickSaber {
    class SaberTrickManager;
}

DECLARE_CLASS_CODEGEN(TrickSaber::Tricks, Trick, UnityEngine::MonoBehaviour,
    DECLARE_INSTANCE_FIELD(bool, _endRequested);
    DECLARE_INSTANCE_FIELD(::TrickSaber::TrickState, _trickState);
    DECLARE_INSTANCE_FIELD(::TrickSaber::TrickAction, _trickAction);
    DECLARE_INSTANCE_FIELD(TrickSaber::MovementController*, _movementController);
    DECLARE_INSTANCE_FIELD_NAME(SaberTrickManager*, _saberTrickManager, "TrickSaber", "SaberTrickManager");
    DECLARE_INSTANCE_FIELD(TrickSaber::SaberTrickModel*, _saberTrickModel);
    DECLARE_INSTANCE_FIELD(float, value);
    DECLARE_INSTANCE_FIELD(StringW, get_name);

    DECLARE_INSTANCE_METHOD(void, Awake);
    DECLARE_INSTANCE_METHOD(bool, StartTrick);
    DECLARE_INSTANCE_METHOD(void, EndTrick);
    DECLARE_INSTANCE_METHOD(void, Reset);

    /* These methods just call the same name method without _base on this type, pseudo virtual methods if you will */
    DECLARE_INSTANCE_METHOD(void, OnTrickStart_base);
    DECLARE_INSTANCE_METHOD(void, OnTrickEndRequested_base);
    DECLARE_INSTANCE_METHOD(void, OnTrickEndImmediately_base);
    DECLARE_INSTANCE_METHOD(void, OnInit_base);

    DECLARE_DEFAULT_CTOR();
    DECLARE_SIMPLE_DTOR();

    public:
        void Init(TrickSaber::SaberTrickManager* saberTrickManager, TrickSaber::MovementController* movementController);
        UnorderedEventCallback<::TrickSaber::TrickAction> trickStarted;
        UnorderedEventCallback<::TrickSaber::TrickAction> trickEnding;
        UnorderedEventCallback<::TrickSaber::TrickAction> trickEnded;
)


using Trick_PlaceholderFactory_Base = ::Zenject::PlaceholderFactory_3<::System::Type*, ::UnityEngine::GameObject*, ::TrickSaber::Tricks::Trick*>;

DECLARE_CLASS_CODEGEN(TrickSaber::Tricks, TrickFactory, Trick_PlaceholderFactory_Base, 
    DECLARE_CTOR(ctor);
)

using Trick_CustomFactory_Base = ::Zenject::IFactory_3<::System::Type*, ::UnityEngine::GameObject*, ::TrickSaber::Tricks::Trick*>;

template<>
struct ::il2cpp_utils::il2cpp_type_check::MetadataGetter<static_cast<::TrickSaber::Tricks::Trick* (Trick_CustomFactory_Base::*)(::System::Type*, ::UnityEngine::GameObject*)>(&Trick_CustomFactory_Base::Create)> {
    static const MethodInfo* get() {
        // TODO: finish this
        static auto* type = &::il2cpp_utils::GetClassFromName("System", "Type")->byval_arg;
        static auto* gameObject = &::il2cpp_utils::GetClassFromName("UnityEngine", "GameObject")->byval_arg;
        return ::il2cpp_utils::FindMethod(classof(Trick_CustomFactory_Base*), "Create", std::vector<Il2CppClass*>(), ::std::vector<const Il2CppType*>{type, gameObject});
    }
};

DECLARE_CLASS_CODEGEN(TrickSaber::Tricks, TrickCustomFactory, Trick_PlaceholderFactory_Base, 
    DECLARE_PRIVATE_FIELD(::Zenject::DiContainer*, _container);
    DECLARE_CTOR(ctor, ::Zenject::DiContainer* container);

    DECLARE_OVERRIDE_METHOD(::TrickSaber::Tricks::Trick*, Create, il2cpp_utils::il2cpp_type_check::MetadataGetter<&Trick_CustomFactory_Base::Create>::get(), ::System::Type* type, ::UnityEngine::GameObject* gameObject);
)