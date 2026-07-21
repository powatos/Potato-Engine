/** @file Texture.cpp */

#include <codecvt>
#include <locale>
#include <fstream>

#include "Core/Data/DataManager.hpp"

#include "Debug/Log.hpp"

#include "utfcpp/utf8/unchecked.h"

#include "Texture.hpp"

Texture::Texture() : Rotation(0.f) {

}

Texture::Texture(const std::string& textureFile) : Texture() { 
    // pull file
    path filePath = DataManager::GetDataDir() / "Textures" / textureFile;
    if (!std::filesystem::exists(filePath)) {
        LOG_DEFAULT(LogType::ERROR, "Texture file not found at {}", filePath.string());
        return;
    }

    std::ifstream file(filePath);
    if (!file.is_open()) {
        LOG_DEFAULT(LogType::ERROR, "Could not open texture file at {}", filePath.string());
        return;
    }

    std::string line;

    int y{0};
    int maxX{-1};
    while (std::getline(file, line)) {
        std::wstring wline;
        utf8::unchecked::utf8to16(line.begin(), line.end(), std::back_inserter(wline));
        data.push_back(wline);
        ++y;
        if (static_cast<int>(wline.size()) > maxX) { maxX = static_cast<int>(wline.length()); }
    }

    BoundingBox = Vector2(maxX, y);

    for (const std::wstring& wline : data) {
        cachedStr += wline;
        cachedStr += '\n';
    }
}
Texture::Texture(const Texture& other) : Texture() {
    // copy all members
    data = other.data;
    cachedStr = other.cachedStr;
    
    BoundingBox = other.BoundingBox;
    Rotation = other.Rotation;
}

const std::vector<std::wstring>& Texture::raw_vec() const {
    return data;
}
const std::wstring& Texture::raw() const {
    return cachedStr;
}

const Vector2& Texture::GetBoundingBox() const {
    return BoundingBox;
}

float Texture::GetRotation() const { 
    return Rotation; 
}
void Texture::SetRotation(float rotation) {
    // Normalize rotation to [0, 360)
    rotation = fmodf(rotation, 360.0f);
    if (rotation < 0.0f) { rotation += 360.0f; }
    Rotation = rotation;
}
void Texture::AddLocalRotation(float rotation) {
    SetRotation(GetRotation() + rotation);
}

Texture::operator bool() const {
    return !raw().empty();
}