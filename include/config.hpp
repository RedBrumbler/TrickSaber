#pragma once
#include "Enums.hpp"

struct config_t {
    bool trickSaberEnabled = true;
    TrickSaber::TrickAction triggerAction = TrickSaber::TrickAction::Throw;
    TrickSaber::TrickAction gripAction = TrickSaber::TrickAction::None;
    TrickSaber::TrickAction thumbstickAction = TrickSaber::TrickAction::Spin;
    bool reverseTrigger = false;
    bool reverseGrip = false;
    bool reverseThumbstick = false;
    TrickSaber::ThumbstickDir thumbstickDirection = TrickSaber::ThumbstickDir::Horizontal;
    float triggerThreshold = 0.8f;
    float gripThreshold = 0.8f;
    float thumbstickThreshold = 0.8f;
    float controllerSnapThreshold = 0.3f;
    bool isSpeedVelocityDependent = false;
    float spinSpeed = 1.0f;
    TrickSaber::SpinDir spinDirection = TrickSaber::SpinDir::Backward;
    float throwVelocity = 1.0f;
    float returnSpeed = 10.0f;
    float returnSpinMultiplier = 1.0f;
    /* DisablesScoring */
    bool slowmoDuringThrow = false;
    float slowmoAmount = 0.2f;
    bool completeRotationMode = false;
    bool disableIfNotesOnScreen = false;
    /* DisablesScoring */
    bool hitNotesDuringTrick = false;
    int velocityBufferSize = 5;
    float slowmoStepAmount = 0.02f;
};

extern config_t config;
void SaveConfig();
bool LoadConfig();