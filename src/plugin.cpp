#include "logger.h"
#include <format>
using logi = SKSE::log::info;

// Our class which received game events
//
// Must have a *public* class inheritance for templated BSTEventSink<EVENT TYPE>
// for each event type you would like to receive.
//
// Also must have a `ProcessEvent` function which received a const pointer to one of the <EVENT TYPE>
//
// `ProcessEvent` is used to... well... process the event! You can do whatever you want with it :)
//
// It is not required to make your class a singleton, but it is very helpful!
// Otherwise, you need to be aware of where your class instance is instantiated and keep it alive.
class EventProcessor {
    // Pretty typical singleton setup
    // *Private* constructor/destructor
    // And we *delete* the copy constructors and move constructors.
    EventProcessor() = default;
    ~EventProcessor() = default;
    EventProcessor(const EventProcessor&) = delete;
    EventProcessor(EventProcessor&&) = delete;
    EventProcessor& operator=(const EventProcessor&) = delete;
    EventProcessor& operator=(EventProcessor&&) = delete;

public:
    // Returns a reference to the one and only instance of EventProcessor :)
    //
    // Note: this is returned as a & reference. When you need this as a pointer, you'll want to use & (see below)
    static EventProcessor& GetSingleton() {
        static EventProcessor singleton;
        return singleton;
    }
    void setLogPath(std::string path) {
        m_logPath = std::move(path);
    }

    static void ProcessMessage(SKSE::MessagingInterface::Message* message)
    {
        if (message->type == SKSE::MessagingInterface::kDataLoaded)
        {
            auto pluginName = SKSE::PluginDeclaration::GetSingleton()->GetName();
            auto p = EventProcessor::GetSingleton().m_logPath;
            RE::ConsoleLog::GetSingleton()->Print(fmt::format("{} Log is written to {}", pluginName, p).c_str());
            logi("kDataLoaded message received, Info message sent to console");
        }

    }
private:
    std::string m_logPath;
};
SKSEPluginLoad(const SKSE::LoadInterface *skse) {
    SKSE::Init(skse);
    // Setup logging (e.g. using spdlog)
    auto path = SetupLog();
    EventProcessor::GetSingleton().setLogPath(path.string());
    SKSE::log::info("Plugin loaded");

    // This example prints "Hello, world!" to the Skyrim ~ console.
    // To view it, open the ~ console from the Skyrim Main Menu.
    SKSE::GetMessagingInterface()->RegisterListener(&EventProcessor::ProcessMessage);

    return true;
}