#pragma once
#include <imgui.h>
#include <cstdint>
#include <string>



class Texture
{
public:
    Texture(std::string path);
    ~Texture();

    bool Loaded = false;

    uint32_t Load();
    void Unload();
    ImVec2 Size;
    uint32_t inline GetTextureId() { return m_RendererId; }
private:
    std::string m_FilePath;
    uint32_t m_RendererId;
};