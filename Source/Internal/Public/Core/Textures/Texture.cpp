/** @file Texture.cpp */

#include <codecvt>
#include <locale>
#include <fstream>

#include "Core/Data/DataManager.hpp"

#include "Debug/Debug.hpp"

#include "Texture.hpp"

Texture::Texture(const std::string& textureFile) {
    // pull file
    // populate data vector
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
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;

    int y{0};
    int maxX{-1};
    while (std::getline(file, line)) {
        std::wstring wline = converter.from_bytes(line); 
        data.push_back(wline);
        ++y;
        if (static_cast<int>(wline.size()) > maxX) { maxX = wline.length(); }
    }

    BoundingBox = Vector2(maxX, y);

    for (const std::wstring& line : data) {
        cachedStr += line;
        cachedStr += '\n';
    }
}
Texture::Texture(const Texture& other) {
    data = other.data;
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