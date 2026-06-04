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

    /** @brief returns the raw texture vector */
    const std::vector<std::string>& raw() const;

private:
    std::vector<std::string> data;

};