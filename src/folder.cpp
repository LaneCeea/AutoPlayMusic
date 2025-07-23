#include "folder.hpp"

#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

fs::path FindMusicFolder(const char* argv0) {
    fs::path ExecPath = fs::absolute(argv0);

    fs::path MusicPath = ExecPath.parent_path().parent_path() / "music";
    if (fs::is_directory(MusicPath)) {
        return MusicPath;
    }
    
    MusicPath = ExecPath.parent_path() / "music";
    if (fs::is_directory(MusicPath)) {
        return MusicPath;
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