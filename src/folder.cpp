#include "folder.hpp"

#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

fs::path FindMusicFolder(const char* argv0) {
    fs::path current = fs::absolute(argv0).parent_path();
    
    // Search upward in the directory tree
    while (!current.empty() && current.has_parent_path()) {
        fs::path musicPath = current / "music";
        if (fs::is_directory(musicPath)) {
            return musicPath;
        }
        current = current.parent_path();
    }
    
    return fs::path();
}

int GetMusicCount(const fs::path& MusicFolder) {
    std::wcout << MusicFolder << std::endl;
    std::cout << "==================================\n";
    int Count = 0;
    for (const auto& Entry : fs::directory_iterator(MusicFolder)) {
        if (fs::is_regular_file(Entry.status()) && Entry.path().extension() == ".mp3") {
            std::wcout << Entry.path().filename() << std::endl;
            ++Count;
        }
    }
    std::cout << "==================================\n";
    return Count;
}

fs::path GetMusic(const fs::path& MusicFolder, int Index) {
    for (const auto& Entry : fs::directory_iterator(MusicFolder)) {
        if (fs::is_regular_file(Entry.status()) && Entry.path().extension() == ".mp3") {
            --Index;
            if (Index == 0) {
                return Entry.path();
            }
        }
    }
    return fs::path();
}