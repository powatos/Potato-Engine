/** @file TextureManager.cpp */

#include "Core/Data/DataManager.hpp"

#include "Debug/Debug.hpp"

#include "TextureManager.hpp"

TextureManager::TextureManager() {

    path texturesDir = DataManager::GetDataDir() / "Textures";
    if (!std::filesystem::exists(texturesDir)) {
        LOG_DEFAULT(LogType::ERROR, "Textures directory not found at {}", texturesDir.string());
        return;
    }

    for (const std::filesystem::directory_entry& entry : std::filesystem::recursive_directory_iterator(texturesDir)) {
        const path p = entry.path();

        if (entry.exists() && entry.is_regular_file() && p.extension() == ".txt") {
            RegisterTexture(p.filename().stem().string());
        } else {
            LOG_DEFAULT(LogType::WARNING, "Invalid texture file found at {}", p.string());
        }
    }
}

void TextureManager::BeginPlay() {

}

void TextureManager::RegisterTexture(const std::string& textureFileName) {
    textures.emplace(textureFileName, textureFileName + ".txt");
}
Texture& TextureManager::GetTexture(const std::string& name) {
    return textures.at(name);
}
bool TextureManager::HasTexture(const std::string& name) const {
    return textures.find(name) != textures.end();
}