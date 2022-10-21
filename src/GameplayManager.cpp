#include "GameplayManager.hpp"
#include "logging.hpp"
#include "config.hpp"

#include "custom-types/shared/delegate.hpp"
#include "GlobalNamespace/LevelBar.hpp"
#include "UnityEngine/Transform.hpp"
#include "UnityEngine/RectTransform.hpp"
#include "UnityEngine/UI/Toggle_ToggleEvent.hpp"
#include "UnityEngine/Canvas.hpp"
#include "HMUI/CurvedTextMeshPro.hpp"

#include "bs-utils/shared/utils.hpp"

// this bad but I need to access that method T_T
#define protected public
#include "bsml/shared/BSML/Tags/Settings/ToggleSettingTag.hpp"
#undef protected

#include "bsml/shared/BSML/Components/Settings/ToggleSetting.hpp"


DEFINE_TYPE(TrickSaber, GameplayManager);

extern ModInfo modInfo;

namespace TrickSaber {
    void GameplayManager::ctor(::Zenject::DiContainer* container) {
        _pauseMenuManager = container->TryResolve<GlobalNamespace::PauseMenuManager*>();
    }

    void GameplayManager::DisableScoreSubmissionIfNeeded() {
        DisableScore(config.slowmoDuringThrow || config.hitNotesDuringTrick, fmt::format("slowmoDuringThrow: {}, hitNotesDuringTrick: {}", config.slowmoDuringThrow, config.hitNotesDuringTrick));
    }

    void GameplayManager::DisableScore(bool disable, StringW reason) {
        if (disable) {
            INFO("Disabling score submission: {}", reason);
            bs_utils::Submission::disable(modInfo);
        } else {
            bs_utils::Submission::enable(modInfo);
        }
    }

    void GameplayManager::Initialize() {
        if (config.trickSaberEnabled) DisableScoreSubmissionIfNeeded();
        // if TS not enabled, just allow scores
        else DisableScore(false, "");

        CreateCheckBox();
    }

    void GameplayManager::CreateCheckBox() {
        // disabling for now as it just breaks the mod if used lol
        return;
        if (!_pauseMenuManager || !_pauseMenuManager->m_CachedPtr.m_value) return;

        auto canvas = _pauseMenuManager->levelBar->get_transform()->get_parent()->get_parent()->GetComponent<UnityEngine::Canvas*>();
        if (!canvas) return;

        auto toggleObject = BSML::ToggleSettingTag().CreateObject(canvas->get_transform());

        auto rectTransform = reinterpret_cast<UnityEngine::RectTransform*>(toggleObject->get_transform());
        rectTransform->set_anchoredPosition({26, -15});
        rectTransform->set_sizeDelta({-130, 7});

        toggleObject->get_transform()->Find("NameText")->GetComponent<HMUI::CurvedTextMeshPro*>()->set_text("Tricksaber Enabled");

        auto toggleSetting = toggleObject->GetComponent<BSML::ToggleSetting*>();
        toggleSetting->set_Value(config.trickSaberEnabled);
        auto delegate = custom_types::MakeDelegate<UnityEngine::Events::UnityAction_1<bool>*>(
            std::function<void(bool)>(
                [&](bool value){
                    config.trickSaberEnabled = value;
                    // we never enable scores DURING gameplay, only ever disabling it. the only way to have allowed scores is if you start with TS disabled
                    DisableScoreSubmissionIfNeeded();
                }
            )
        );
        toggleSetting->toggle->onValueChanged->AddListener(delegate);
    }
}