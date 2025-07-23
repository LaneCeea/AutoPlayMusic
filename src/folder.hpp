#pragma once

#include <string_view>
#include <filesystem>

std::filesystem::path FindMusicFolder(const char* argv0);
int GetMusicCount(const std::filesystem::path& MusicFolder);
std::filesystem::path GetMusic(const std::filesystem::path& MusicFolder, int Index);