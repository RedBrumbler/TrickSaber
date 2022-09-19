#include "Installers/MenuInstaller.hpp"

#include "UI/TrickSaberFlowCoordinator.hpp"
#include "UI/SettingsUI.hpp"

#include "lapiz/shared/utilities/ZenjectExtensions.hpp"

#include "Zenject/DiContainer.hpp"
#include "Zenject/ConcreteIdBinderGeneric_1.hpp"
#include "Zenject/FromBinderNonGeneric.hpp"

DEFINE_TYPE(TrickSaber::Installers, MenuInstaller);

using namespace Lapiz::Zenject::ZenjectExtensions;

namespace TrickSaber::Installers {
    void MenuInstaller::InstallBindings() {
        auto container = get_Container();

        FromNewComponentAsViewController(container->Bind<TrickSaber::UI::ViewControllers::BindingsViewController*>())->AsSingle();
        FromNewComponentAsViewController(container->Bind<TrickSaber::UI::ViewControllers::MiscViewController*>())->AsSingle();
        FromNewComponentAsViewController(container->Bind<TrickSaber::UI::ViewControllers::ThresholdViewController*>())->AsSingle();

        container->BindInterfacesAndSelfTo<TrickSaber::UI::SettingsUI*>()->AsSingle();
        FromNewComponentOnNewGameObject(container->BindInterfacesAndSelfTo<TrickSaber::UI::TrickSaberFlowCoordinator*>())->AsSingle();
    }
}