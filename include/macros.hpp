#pragma once

#define DECLARE_INSTANCE_FIELD_NAME(type_, name_, namespaze_, klass_)\
private: \
struct ___FieldRegistrator_##name_ : ::custom_types::FieldRegistrator { \
    ___FieldRegistrator_##name_() { \
        ___TargetType::___TypeRegistration::addField(this); \
    } \
    constexpr const char* name() const override { \
        return #name_; \
    } \
    const Il2CppType* type() const override { \
        ::il2cpp_functions::Init(); \
        return ::il2cpp_functions::class_get_type(il2cpp_utils::GetClassFromName(namespaze_, klass_)); \
    } \
    constexpr uint16_t fieldAttributes() const override { \
        return FIELD_ATTRIBUTE_PUBLIC; \
    } \
    constexpr size_t size() const override { \
        return sizeof(type_); \
    } \
    int32_t offset() const override { \
        return offsetof(___TargetType, name_); \
    } \
}; \
static inline ___FieldRegistrator_##name_ ___##name_##_FieldRegistrator; \
public: \
type_ name_