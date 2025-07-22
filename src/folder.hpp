#pragma once

#include <string_view>
#include <filesystem>

int GetMusicCount(const std::filesystem::path& MusicFolder);
std::string GetMusic(const std::filesystem::path& MusicFolder, int Index);