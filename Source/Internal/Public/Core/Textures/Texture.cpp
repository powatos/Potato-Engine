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

    std::wifstream file(filePath);
    if (!file.is_open()) {
        LOG_DEFAULT(LogType::ERROR, "Could not open texture file at {}", filePath.string());
        return;
    }

    file.imbue(std::locale(file.getloc(), new std::codecvt_utf8<wchar_t>));

    std::wstring line;
    while (std::getline(file, line)) {
        data.push_back(line);
    }
}

const std::vector<std::wstring>& Texture::raw_vec() const {
    return data;
}
const std::wstring Texture::raw() const {
    std::wstring str{};
    for (const std::wstring& line : data) {
        str += line;
        str += '\n';
    }

    return str;
}
