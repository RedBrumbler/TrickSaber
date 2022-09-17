#include "config.hpp"
#include "beatsaber-hook/shared/config/config-utils.hpp"
#include "logging.hpp"

config_t config;

Configuration& get_config() {
    static Configuration config({MOD_ID, VERSION});
    config.Load();
    return config;
}

#define Save(identifier) doc.AddMember(#identifier, config.identifier, allocator)
#define SaveEnum(identifier) doc.AddMember(#identifier, static_cast<int>(config.identifier), allocator)

void SaveConfig() {
    INFO("Saving Configuration...");
    rapidjson::Document& doc = get_config().config;

    doc.RemoveAllMembers();
    doc.SetObject();

    rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();

    Save(trickSaberEnabled);
    SaveEnum(triggerAction);
    SaveEnum(gripAction);
    SaveEnum(thumbstickAction);
    Save(reverseTrigger);
    Save(reverseGrip);
    Save(reverseThumbstick);
    SaveEnum(thumbstickDirection);
    Save(triggerThreshold);
    Save(gripThreshold);
    Save(thumbstickThreshold);
    Save(controllerSnapThreshold);
    Save(isSpeedVelocityDependent);
    Save(spinSpeed);
    SaveEnum(spinDirection);
    Save(throwVelocity);
    Save(returnSpeed);
    Save(returnSpinMultiplier);
    Save(slowmoDuringThrow);
    Save(slowmoAmount);
    Save(completeRotationMode);
    Save(disableIfNotesOnScreen);
    Save(hitNotesDuringTrick);
    Save(velocityBufferSize);
    Save(slowmoStepAmount);

    get_config().Write();
    INFO("Saved Configuration!");
}

#define GET_INT(identifier)                                         \
    auto identifier##_itr = doc.FindMember(#identifier);            \
    if (identifier##_itr != doc.MemberEnd())                        \
        config.identifier = identifier##_itr->value.GetInt();       \
    else                                                            \
        foundEverything = false;

#define GET_ENUM(enum, identifier)                                                  \
    auto identifier##_itr = doc.FindMember(#identifier);                            \
    if (identifier##_itr != doc.MemberEnd())                                        \
        config.identifier = static_cast<enum>(identifier##_itr->value.GetInt());    \
    else                                                                            \
        foundEverything = false;

#define GET_FLOAT(identifier)                                       \
    auto identifier##_itr = doc.FindMember(#identifier);            \
    if (identifier##_itr != doc.MemberEnd())                        \
        config.identifier = identifier##_itr->value.GetFloat();     \
    else                                                            \
        foundEverything = false;

#define GET_STRING(identifier)                                                          \
    auto identifier##_itr = doc.FindMember(#identifier);                                \
    if (identifier##_itr != doc.MemberEnd())                                            \
        config.identifier = std::string_view(identifier##_itr->value.GetString());      \
    else                                                                                \
        foundEverything = false;

#define GET_BOOL(identifier)                                            \
    auto identifier##_itr = doc.FindMember(#identifier);                \
    if (identifier##_itr != doc.MemberEnd())                            \
        config.identifier = identifier##_itr->value.GetBool();          \
    else                                                                \
        foundEverything = false;

bool LoadConfig() {
    INFO("Loading Configuration...");
    bool foundEverything = true;
    rapidjson::Document& doc = get_config().config;

    GET_BOOL(trickSaberEnabled);
    GET_ENUM(TrickSaber::TrickAction, triggerAction);
    GET_ENUM(TrickSaber::TrickAction, gripAction);
    GET_ENUM(TrickSaber::TrickAction, thumbstickAction);
    GET_BOOL(reverseTrigger);
    GET_BOOL(reverseGrip);
    GET_BOOL(reverseThumbstick);
    GET_ENUM(TrickSaber::ThumbstickDir, thumbstickDirection);
    GET_FLOAT(triggerThreshold);
    GET_FLOAT(gripThreshold);
    GET_FLOAT(thumbstickThreshold);
    GET_FLOAT(controllerSnapThreshold);
    GET_BOOL(isSpeedVelocityDependent);
    GET_FLOAT(spinSpeed);
    GET_ENUM(TrickSaber::SpinDir, spinDirection);
    GET_FLOAT(throwVelocity);
    GET_FLOAT(returnSpeed);
    GET_FLOAT(returnSpinMultiplier);
    GET_BOOL(slowmoDuringThrow);
    GET_FLOAT(slowmoAmount);
    GET_BOOL(completeRotationMode);
    GET_BOOL(disableIfNotesOnScreen);
    GET_BOOL(hitNotesDuringTrick);
    GET_INT(velocityBufferSize);
    GET_FLOAT(slowmoStepAmount);

    if (foundEverything)
        INFO("Loaded Configuration!");
    return foundEverything;
}