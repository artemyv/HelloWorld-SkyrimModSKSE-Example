#include "logger.h"

using logi = SKSE::log::info;

SKSEPluginLoad(const SKSE::LoadInterface *skse) {
    SKSE::Init(skse);
    // Setup logging (e.g. using spdlog)
    SetupLog();

    SKSE::log::info("Plugin loaded");

    // This example prints "Hello, world!" to the Skyrim ~ console.
    // To view it, open the ~ console from the Skyrim Main Menu.
    SKSE::GetMessagingInterface()->RegisterListener([](SKSE::MessagingInterface::Message *message) {
        if (message->type == SKSE::MessagingInterface::kDataLoaded)
        {
            RE::ConsoleLog::GetSingleton()->Print("Hello, world!");
            logi("kDataLoaded message received, Hello, world! message sent to console");
        }
    });

    return true;
}