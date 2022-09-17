#include "SaberControllerBearer.hpp"

DEFINE_TYPE(TrickSaber, SaberControllerPackage);
DEFINE_TYPE(TrickSaber, SaberControllerBearer);

namespace TrickSaber {
    void SaberControllerPackage::ctor(GlobalNamespace::Saber* saber, GlobalNamespace::VRController* vrController) {
        this->saber = saber;
        this->vrController = vrController;
    }

    void SaberControllerBearer::ctor(GlobalNamespace::SaberManager* saberManager, GlobalNamespace::PlayerVRControllersManager* playerVRControllersManager) {
        _left = SaberControllerPackage::New_ctor(saberManager->leftSaber,
            playerVRControllersManager->leftHandVRController);

        _right = SaberControllerPackage::New_ctor(saberManager->rightSaber,
            playerVRControllersManager->rightHandVRController);
    }

    SaberControllerPackage* SaberControllerBearer::get(GlobalNamespace::SaberType saberType) {
        return saberType == GlobalNamespace::SaberType::SaberA ? _left : _right;
    }
}