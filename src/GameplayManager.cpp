#include "GameplayManager.hpp"
#include "logging.hpp"
#include "config.hpp"

#include "custom-types/shared/delegate.hpp"
#include "GlobalNamespace/LevelBar.hpp"
#include "UnityEngine/Transform.hpp"
#include "UnityEngine/RectTransform.hpp"
#include "UnityEngine/Canvas.hpp"

DEFINE_TYPE(TrickSaber, GameplayManager);

extern ModInfo modInfo;

namespace TrickSaber {
    void GameplayManager::ctor(::Zenject::DiContainer* container) {
        _pauseMenuManager = container->TryResolve<GlobalNamespace::PauseMenuManager*>();
    }

    void GameplayManager::DisableScoreSubmissionIfNeeded() {
        DisableScore(config.slowmoDuringThrow || config.hitNotesDuringTrick, fmt::format("slowmoDuringThro: {}, hitNotesDuringTrick: {}", config.slowmoDuringThrow, config.hitNotesDuringTrick));
    }

    void GameplayManager::DisableScore(bool disable, StringW reason) {
        if (disable) {
            INFO("Disabling score submission: {}", reason);
            // FIXME: actually use bs utils to do this
            //bs_utils::Submission::Disable(modInfo);
        } else {
            //bs_utils::Submission::Enable(modInfo);
        }
    }

    void GameplayManager::Initialize() {
        DisableScoreSubmissionIfNeeded();
        CreateCheckBox();
    }

    void GameplayManager::CreateCheckBox() {
        if (!_pauseMenuManager || !_pauseMenuManager->m_CachedPtr.m_value) return;

        auto canvas = _pauseMenuManager->levelBar->get_transform()->get_parent()->get_parent()->GetComponent<UnityEngine::Canvas*>();
        if (!canvas) return;

        // FIXME: add BSML dep
        /*
        auto toggleObject = BSML::ToggleSettingTag().CreateObject(canvas->get_transform());

        auto rectTransform = reinterpret_cast<UnityEngine::RectTransform*>(toggleObject->get_transform());
        rectTransform-set_anchoredPosition({26, -15});
        rectTransform->set_sizeDelta({-130, 7});

        toggleObject->get_transform()->Find("NameText")->GetComponent<HMUI::CurvedTextMeshPro*>()->set_text("Tricksaber Enabled");

        auto toggleSetting = toggleObject->GetComponent<BSML::ToggleSetting*>();
        toggleSetting->set_Value(config.trickSaberEnabled);
        auto delegate = custom_types::MakeDelegate<System::Action_1<bool>*>(
            std::function<void(bool)>(
                [](bool value){
                    config.trickSaberEnabled = value;
                }
            )
        );
        toggleSetting->toggle->get_onValueChanged()->AddListener(delegate);
        */
    }
}