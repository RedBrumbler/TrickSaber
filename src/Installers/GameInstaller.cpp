#include "Installers/GameInstaller.hpp"
#include "logging.hpp"

#include "custom-types/shared/delegate.hpp"
#include "lapiz/shared/arrayutils.hpp"

#include "GameplayManager.hpp"
#include "GlobalTrickManager.hpp"
#include "MovementController.hpp"
#include "SaberControllerBearer.hpp"
#include "SaberTrickModel.hpp"
#include "InputHandling/InputManager.hpp"
#include "Tricks/Trick.hpp"

#include "GlobalNamespace/SaberManager.hpp"
#include "Zenject/FromBinderNonGeneric.hpp"
#include "Zenject/ConcreteBinderGeneric_1.hpp"
#include "Zenject/ConcreteIdBinderGeneric_1.hpp"
#include "Zenject/FactoryToChoiceIdBinder_3.hpp"
#include "Zenject/BindInfo.hpp"
#include "Zenject/InjectUtil.hpp"
#include "System/Func_2.hpp"

DEFINE_TYPE(TrickSaber::Installers, GameInstaller);

namespace TrickSaber::Installers {
    void GameInstaller::InstallBindings() {
        DEBUG("InstallBindings");
        auto container = get_Container();

        container->BindInterfacesAndSelfTo<GameplayManager*>()->AsSingle();
        container->BindInterfacesAndSelfTo<GlobalTrickManager*>()->AsSingle();

        container->Bind<MovementController*>()->FromNewComponentSibling()->AsTransient();
        container->Bind<InputHandling::InputManager*>()->AsTransient();

        using TParam1 = ::System::Type*;
        using TParam2 = ::UnityEngine::GameObject*;
        using TContract = ::TrickSaber::Tricks::Trick*;
        using TFactory = Tricks::TrickFactory*;
        using TSubFactory = Tricks::TrickCustomFactory*;
        
        /*
        try {
        DEBUG("FactoryBind");
        static_assert(std::is_convertible_v<TFactory, ::Zenject::PlaceholderFactory_3<TParam1, TParam2, TContract>*>);
        static auto* ___internal_bindfactory__method = THROW_UNLESS((::il2cpp_utils::FindMethod(container, "BindFactory", std::vector<Il2CppClass*>{::il2cpp_utils::il2cpp_type_check::il2cpp_no_arg_class<TParam1>::get(), ::il2cpp_utils::il2cpp_type_check::il2cpp_no_arg_class<TParam2>::get(), ::il2cpp_utils::il2cpp_type_check::il2cpp_no_arg_class<TContract>::get(), ::il2cpp_utils::il2cpp_type_check::il2cpp_no_arg_class<TFactory>::get()}, ::std::vector<const Il2CppType*>{})));
        DEBUG("___internal_bindfactory__method: {}", fmt::ptr(___internal_bindfactory__method));
        DEBUG("argc: {}", ___internal_bindfactory__method->parameters_count);
        DEBUG("is_generic: {}", ___internal_bindfactory__method->is_generic);
        DEBUG("is_inflated: {}", ___internal_bindfactory__method->is_inflated);
        DEBUG("name: {}", ___internal_bindfactory__method->name);
        DEBUG("genericMethod: {}", fmt::ptr(___internal_bindfactory__method->genericMethod));
        DEBUG("genericMethod is_method: {}", ___internal_bindfactory__method->genericContainer->is_method);
        DEBUG("genericMethod argc: {}", ___internal_bindfactory__method->genericContainer->type_argc);
        
        static auto* ___generic_bindfactory_method = THROW_UNLESS((::il2cpp_utils::MakeGenericMethod(___internal_bindfactory__method, std::vector<Il2CppClass*>{::il2cpp_utils::il2cpp_type_check::il2cpp_no_arg_class<TParam1>::get(), ::il2cpp_utils::il2cpp_type_check::il2cpp_no_arg_class<TParam2>::get(), ::il2cpp_utils::il2cpp_type_check::il2cpp_no_arg_class<TContract>::get()})));
        auto boundFactory = ::il2cpp_utils::RunMethodRethrow<::Zenject::FactoryToChoiceIdBinder_3<TParam1, TParam2, TContract>*, false>(container, ___generic_bindfactory_method);

        DEBUG("FromFactory");
        static_assert(std::is_convertible_v<std::remove_pointer_t<TSubFactory>, ::Zenject::IFactory_3<TParam1, TParam2, TContract>>);
        static auto* ___internal_fromfactory__method = THROW_UNLESS((::il2cpp_utils::FindMethod(boundFactory, "FromFactory", std::vector<Il2CppClass*>{::il2cpp_utils::il2cpp_type_check::il2cpp_no_arg_class<TSubFactory>::get()}, ::std::vector<const Il2CppType*>{})));
        static auto* ___generic_fromfactory__method = THROW_UNLESS(::il2cpp_utils::MakeGenericMethod(___internal_fromfactory__method, std::vector<Il2CppClass*>{::il2cpp_utils::il2cpp_type_check::il2cpp_no_arg_class<TSubFactory>::get()}));
        ::il2cpp_utils::RunMethodRethrow<::Zenject::ConditionCopyNonLazyBinder*, false>(boundFactory, ___generic_fromfactory__method);
        } catch (il2cpp_utils::RunMethodException e) {
            ERROR("RunMethodException: {}", e.what());
        } catch (std::runtime_error e) {
            ERROR("Runtime Error: {}", e.what());
        }
        */
        auto factoryBind = container->BindIFactory<TParam1, TParam2, TContract>();
        //auto factoryBind = container->BindFactory<::System::Type*, ::UnityEngine::GameObject*, ::TrickSaber::Tricks::Trick*, ::TrickSaber::Tricks::TrickFactory*>();
        static auto minfo = il2cpp_utils::FindMethod(factoryBind, "FromFactory");
        DEBUG("found minfo: {}", fmt::ptr(minfo));
        static auto fromFactoryMinfo = il2cpp_utils::MakeGenericMethod(minfo, std::vector<Il2CppClass*>{classof(TSubFactory)});
        DEBUG("created fromFactoryMinfo: {}", fmt::ptr(fromFactoryMinfo));
        il2cpp_utils::RunMethod(factoryBind, fromFactoryMinfo);
        //DEBUG("FromFactory");
        //factoryBind->FromFactory<TSubFactory>();
        container->Bind<SaberControllerBearer*>()->AsSingle();
        //TODO: make SaberTrickManagers non-Monobehaviours

        BindTrickManager(GlobalNamespace::SaberType::SaberA);
        BindTrickManager(GlobalNamespace::SaberType::SaberB);

        container->Bind<SaberTrickModel*>()->AsTransient();

    }

    void GameInstaller::BindTrickManager(GlobalNamespace::SaberType saberType) {
        DEBUG("BindTrickManager: {}", saberType);
        auto func = custom_types::MakeDelegate<System::Func_2<::Zenject::InjectContext*, UnityEngine::GameObject*>*>(
            std::function<::UnityEngine::GameObject*(::Zenject::InjectContext*)>(
                std::bind(&GameInstaller::GetSaber, this, std::placeholders::_1, saberType)
            )
        );
        
        if (saberType == GlobalNamespace::SaberType::SaberA) {
            auto cachedResult = get_Container()
                ->Bind<LeftSaberTrickManager*>()
                ->FromNewComponentOn(func)
                ->AsCached();

            cachedResult->BindInfo->Arguments->Clear();
            auto pair = ::Zenject::InjectUtil::CreateTypePair<GlobalNamespace::SaberType>(saberType);
            cachedResult->BindInfo->Arguments->Add(pair);
        } else {
            auto cachedResult = get_Container()
                ->Bind<RightSaberTrickManager*>()
                ->FromNewComponentOn(func)
                ->AsCached();

            cachedResult->BindInfo->Arguments->Clear();
            auto pair = ::Zenject::InjectUtil::CreateTypePair<GlobalNamespace::SaberType>(saberType);
            cachedResult->BindInfo->Arguments->Add(pair);
        }
    }

    UnityEngine::GameObject* GameInstaller::GetSaber(::Zenject::InjectContext* ctx, GlobalNamespace::SaberType saberType) {
        DEBUG("GetSaber");
        auto saberManager = ctx->get_Container()->TryResolve<GlobalNamespace::SaberManager*>();

        if (!saberManager)
        {
            ERROR("Couldn't resolve SaberManager");
            return nullptr;
        }

        return saberType == GlobalNamespace::SaberType::SaberA
            ? saberManager->leftSaber->get_gameObject()
            : saberManager->rightSaber->get_gameObject();
    }
}