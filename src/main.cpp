#include "play.hpp"
#include "rng.hpp"
#include "folder.hpp"

#include <iostream>
#include <locale>
#include <filesystem>

int main() {
    std::setlocale(LC_ALL, "");
    rng::Init();

    std::filesystem::path MusicFolder("music");
    if (!std::filesystem::is_directory(MusicFolder)) {
        std::cerr << "Directory " << MusicFolder << "does not exist!\n";
        return -1;
    }
    int MusicCount = GetMusicCount(MusicFolder);

    for (;;) {
        PrintTime();
        PlayMP3(GetMusic(MusicFolder, rng::UniformInt(1, MusicCount)));
        Cooldown();
    }
}