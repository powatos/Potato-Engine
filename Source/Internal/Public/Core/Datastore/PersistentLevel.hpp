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

