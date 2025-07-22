#include "folder.hpp"

#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

int GetMusicCount(const fs::path& MusicFolder) {
    std::cout << "========== Music Folder ==========\n";
    int Count = 0;
    for (const auto& Entry : fs::directory_iterator(MusicFolder)) {
        if (fs::is_regular_file(Entry.status()) && Entry.path().extension() == ".mp3") {
            std::wcout << Entry.path() << std::endl;
            ++Count;
        }
    }
    std::cout << "==================================\n";
    return Count;
}

std::string GetMusic(const fs::path& MusicFolder, int Index) {
    for (const auto& Entry : fs::directory_iterator(MusicFolder)) {
        if (fs::is_regular_file(Entry.status()) && Entry.path().extension() == ".mp3") {
            --Index;
            if (Index == 0) {
                return Entry.path().string();
            }
        }
    }
    return std::string();
}