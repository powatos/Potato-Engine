/** @file Texture.cpp */

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
    while (std::getline(file, line)) {
        data.push_back(line);
    }
}

const std::vector<std::string>& Texture::raw() const {
    return data;
}
