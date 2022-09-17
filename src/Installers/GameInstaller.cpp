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

        auto factoryBind = container->BindFactory<System::Type*, UnityEngine::GameObject*, Tricks::Trick*, Tricks::TrickFactory*>();
        /*
        static auto minfo = il2cpp_utils::FindMethod(factoryBind, "FromFactory");
        DEBUG("found minfo: {}", fmt::ptr(minfo));
        static auto fromFactoryMinfo = il2cpp_utils::MakeGenericMethod(minfo, std::vector<Il2CppClass*>{classof(Tricks::TrickCustomFactory*)});
        DEBUG("created fromFactoryMinfo: {}", fmt::ptr(fromFactoryMinfo));
        il2cpp_utils::RunMethod(factoryBind, fromFactoryMinfo);
        */
        factoryBind->FromFactory<Tricks::TrickCustomFactory*>();
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
                std::bind(&GameInstaller::GetSaber, this, std::placeholders::_1)
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

    UnityEngine::GameObject* GameInstaller::GetSaber(::Zenject::InjectContext* ctx) {
        DEBUG("GetSaber");
        auto saberManager = ctx->get_Container()->TryResolve<GlobalNamespace::SaberManager*>();

        if (!saberManager)
        {
            ERROR("Couldn't resolve SaberManager");
            return nullptr;
        }

        StringW saberType{ctx->get_Identifier()};

        return saberType == "SaberA"
            ? saberManager->leftSaber->get_gameObject()
            : saberManager->rightSaber->get_gameObject();
    }
}