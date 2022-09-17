#include "Installers/AppInstaller.hpp"

DEFINE_TYPE(TrickSaber::Installers, AppInstaller);

namespace TrickSaber::Installers {
    void AppInstaller::InstallBindings() {
        auto container = get_Container();
    }
}