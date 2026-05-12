#pragma once

#include <fstream>
#include <filesystem>

struct Vector2;

struct PersistentLevel
{
    PersistentLevel(const std::string& saveFileName);
    ~PersistentLevel() = default;

    // @returns if all static actors were loaded successfully
    bool LoadStaticActors();

    template <typename Type>
    Type GetData(std::string key) const;

    template <typename Type>
    void WriteData(std::string key, Type value);

    int GetIntData( std::string key );
    float GetFloatData( std::string key );
    std::string GetStringData( std::string key );
    Vector2 GetVector2Data( std::string key );


    void WriteIntData( std::string key, int value );
    void WriteFloatData( std::string key, float value );
    void WriteStringData( std::string key, std::string value );
    void WriteVector2Data( std::string key, const Vector2& value );

private:
    std::filesystem::path saveFileAbsPath;
};


template <typename Type>
Type PersistentLevel::GetData(std::string key) const {
    if      constexpr (std::is_same_v<Type, int>) {
        return GetIntData(key);
    }
    else if constexpr (std::is_same_v<Type, float>) {
        return GetFloatData(key);
    }
    else if constexpr (std::is_same_v<Type, std::string>) {
        return GetStringData(key);
    }
    else if constexpr (std::is_same_v<Type, Vector2>) {
        return GetVector2Data(key);
    }
}

template <typename Type>
void PersistentLevel::WriteData(std::string key, Type value) {
    if      constexpr (std::is_same_v<Type, int>) {
        WriteIntData(key, value);
    }
    else if constexpr (std::is_same_v<Type, float>) {
        WriteFloatData(key, value);
    }
    else if constexpr (std::is_same_v<Type, std::string>) {
        WriteStringData(key, value);
    }
    else if constexpr (std::is_same_v<Type, Vector2>) {
        WriteVector2Data(key, value);
    }
}