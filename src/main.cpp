#include "play.hpp"
#include "rng.hpp"
#include "folder.hpp"

#include <iostream>
#include <locale>
#include <filesystem>

int main(int argc, char* argv[]) {
    std::setlocale(LC_ALL, "");
    rng::Init();

    auto MusicFolder = FindMusicFolder(argv[0]);
    if (MusicFolder.empty()) {
        std::cerr << "Cannot find music directory\n";
        return -1;
    }
    int MusicCount = GetMusicCount(MusicFolder);

    for (;;) {
        PrintTime();
        PlayMP3(GetMusic(MusicFolder, rng::UniformInt(1, MusicCount)));
        Cooldown();
    }
}