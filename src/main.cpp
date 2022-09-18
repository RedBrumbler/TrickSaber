#include "logging.hpp"
#include "hooking.hpp"

#include "custom-types/shared/register.hpp"
#include "lapiz/shared/zenject/Zenjector.hpp"
#include "lapiz/shared/AttributeRegistration.hpp"

#include "Installers/GameInstaller.hpp"
#include "Installers/AppInstaller.hpp"
#include "Installers/MenuInstaller.hpp"

#include "System/ArgumentNullException.hpp"

MAKE_AUTO_HOOK_FIND_INSTANCE(ArgumentNullException_ctor_0, classof(System::ArgumentNullException*), ".ctor", void, System::ArgumentNullException* self) {
    ERROR("Argument Null exception");
    ArgumentNullException_ctor_0(self);
}

MAKE_AUTO_HOOK_FIND_INSTANCE(ArgumentNullException_ctor_1, classof(System::ArgumentNullException*), ".ctor", void, System::ArgumentNullException* self, StringW paramName) {
    ERROR("Argument Null exception for param {}", paramName);
    SAFE_ABORT();
    ArgumentNullException_ctor_1(self, paramName);
}

MAKE_AUTO_HOOK_FIND_INSTANCE(ArgumentNullException_ctor_2, classof(System::ArgumentNullException*), ".ctor", void, System::ArgumentNullException* self, StringW paramName, StringW message) {
    ERROR("Argument Null exception for param {}: {}", paramName, message);
    ArgumentNullException_ctor_2(self, paramName, message);
}

ModInfo modInfo{MOD_ID, VERSION};

extern "C" void setup(ModInfo& info) {
    info = modInfo;
}

extern "C" void load() {
    il2cpp_functions::Init();
    custom_types::Register::AutoRegister();
    Lapiz::Attributes::AutoRegister();

    Hooks::InstallHooks(getLogger());

    auto zenjector = Lapiz::Zenject::Zenjector::Get();
    zenjector->Install<TrickSaber::Installers::AppInstaller*>(Lapiz::Zenject::Location::App);
    zenjector->Install<TrickSaber::Installers::MenuInstaller*>(Lapiz::Zenject::Location::Menu);
    zenjector->Install<TrickSaber::Installers::GameInstaller*>(Lapiz::Zenject::Location::StandardPlayer);
}