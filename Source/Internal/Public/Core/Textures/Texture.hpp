/** @file Texture.hpp */
#pragma once

#include <string>
#include <vector>

/**
 * @brief Texture struct for representing an actor texture
 */
struct Texture
{
    /** 
     * @brief Constructs a texture object from texture
     * @param textureFile Name of texture file in the Textures directory
     */
    Texture(const std::string& textureFile);

    Texture() = default;

    /** @brief returns the raw texture vector */
    const std::vector<std::wstring>& raw_vec() const;
    /** @brief returns the raw texture string */
    const std::wstring raw() const;

    /**
     * @brief bool overload that checks if Texture is valid
     * @returns true if the texture is valid
     */
    explicit operator bool() {
        return raw().empty();
    }

private:
    std::vector<std::wstring> data;

};