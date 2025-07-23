#include "play.hpp"

#include "miniaudio/miniaudio.h"
#include "rng.hpp"

#include <mutex>
#include <condition_variable>
#include <chrono>
#include <thread>
#include <iostream>

void PrintTime() {
    auto now = std::chrono::system_clock::now();
    std::time_t current_time = std::chrono::system_clock::to_time_t(now);
    std::tm* local_time = std::localtime(&current_time);
    std::cout << std::put_time(local_time, "%Y-%m-%d %H:%M:%S") << "\n";
}

void Cooldown() {
    constexpr int c_lower = 60 * 5;
    constexpr int c_upper = 60 * 10;
    int sec = rng::UniformInt(c_lower, c_upper);
    std::this_thread::sleep_for(std::chrono::seconds(sec));
}

struct PlaybackContext {
    ma_decoder* decoder;
    std::mutex mutex;
    std::condition_variable cv;
    bool playbackFinished;
};

static void data_callback(ma_device* pDevice, void* pOutput, const void*, ma_uint32 frameCount) {
    PlaybackContext* context = (PlaybackContext*)pDevice->pUserData;
    if (context == NULL || context->decoder == NULL) {
        return;
    }

    ma_uint64 framesRead;
    ma_result result = ma_decoder_read_pcm_frames(context->decoder, pOutput, frameCount, &framesRead);

    // Check if we've reached the end of the file
    if (result == MA_SUCCESS && framesRead < frameCount) {
        // End of file reached
        std::lock_guard<std::mutex> lock(context->mutex);
        context->playbackFinished = true;
        context->cv.notify_one();
    }
}

bool PlayMP3(const std::filesystem::path& path) {
    ma_result result;
    ma_decoder decoder;
    ma_device_config deviceConfig;
    ma_device device;
    PlaybackContext context;

    // Initialize context
    context.decoder = &decoder;
    context.playbackFinished = false;

    // Initialize decoder
    result = ma_decoder_init_file_w(path.c_str(), NULL, &decoder);
    if (result != MA_SUCCESS) {
        std::wcerr << "Failed to load MP3 file: " << path << '\n';
        return false;
    }

    // Configure the playback device
    deviceConfig = ma_device_config_init(ma_device_type_playback);
    deviceConfig.playback.format = decoder.outputFormat;
    deviceConfig.playback.channels = decoder.outputChannels;
    deviceConfig.sampleRate = decoder.outputSampleRate;
    deviceConfig.dataCallback = data_callback;
    deviceConfig.pUserData = &context;

    // Initialize the device
    result = ma_device_init(NULL, &deviceConfig, &device);
    if (result != MA_SUCCESS) {
        std::wcerr << "Failed to initialize playback device for " << path << '\n';
        ma_decoder_uninit(&decoder);
        return false;
    }

    // Start playback
    result = ma_device_start(&device);
    if (result != MA_SUCCESS) {
        std::wcerr << "Failed to start playback device for " << path << '\n';
        ma_device_uninit(&device);
        ma_decoder_uninit(&decoder);
        return false;
    }

    std::wcout << path.filename() << std::endl;

    // Wait for playback to finish
    {
        std::unique_lock<std::mutex> lock(context.mutex);
        context.cv.wait(lock, [&context] { return context.playbackFinished; });
    }

    // Clean up
    ma_device_uninit(&device);
    ma_decoder_uninit(&decoder);

    return true;
}
