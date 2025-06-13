#include "logger.h"
#include <format>
#include <QuickLootAPI.h>

using logi = SKSE::log::info;
using loge = SKSE::log::error;
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
class EventProcessor : public RE::BSTEventSink<RE::MenuOpenCloseEvent>{
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
    void setLoadInterface(const SKSE::LoadInterface *skse)
    {
        m_skse = skse;
    }
    void OnDataLoaded() {
        // This is where you can do things when the game has finished loading all of the data files.
        // For example, you can register your papyrus scripts here.
        auto pluginName = SKSE::PluginDeclaration::GetSingleton()->GetName();
        auto p = EventProcessor::GetSingleton().m_logPath;
        RE::ConsoleLog::GetSingleton()->Print(fmt::format("{} Log is written to {}", pluginName, p).c_str());
        logi("Info message sent to console");

        RE::UI::GetSingleton()->AddEventSink(this);
        logi("Registered to UI events");

        const auto info = m_skse->GetPluginInfo("QuickLootIE");
        if (info) {
            const auto v =  REL::Version::unpack( info->version);
            logi("QuickLootIE {:#10x} {} is loaded", info->version, v.string("."));
            QuickLoot::QuickLootAPI::Init();
            if (!QuickLoot::QuickLootAPI::IsReady()) {
                loge("QuickLootAPI is not ready");
                return;
            }
       		if (!QuickLoot::QuickLootAPI::RegisterSelectItemHandler(SelectHandler)) {
	    		loge("SelectHandler for QuickLootAPI not registered");
            }
        } else {
            loge("QuickLootIE is not loaded");
        }

    }

    void OnQLDoSelect(RE::Actor* actor, RE::TESObjectREFR* container, const QuickLoot::Element *elements, std::uint32_t elementsCount)
    {
        // This is where you can do things when QuickLootIE selects an item.
        // For example, you can log the selected item or perform some action.
        logi("QuickLootIE selected item in container {} by actor {}", container->GetFormID(), actor->GetFormID());
        for (std::uint32_t i = 0; i < elementsCount; ++i) {
            if(elements[i].object)
                logi("Selected element: {}", elements[i].object->GetObjectTypeName());
        }
    }
   	static inline void SelectHandler(QuickLoot::SelectItemEvent* evt)
	{
		EventProcessor::GetSingleton().OnQLDoSelect(evt->actor, evt->container, evt->elements, evt->elementsCount);
	};

    static void ProcessMessage(SKSE::MessagingInterface::Message* message)
    {
        switch (message->type) {
        // Descriptions are taken from the original skse64 library
        // See:
        // https://github.com/ianpatt/skse64/blob/09f520a2433747f33ae7d7c15b1164ca198932c3/skse64/PluginAPI.h#L193-L212
        /* add case for each type 
        	kPostLoad,
			kPostPostLoad,
			kPreLoadGame,
			kPostLoadGame,
			kSaveGame,
			kDeleteGame,
			kInputLoaded,
			kNewGame,
			kDataLoaded,

        */
        case SKSE::MessagingInterface::kPostLoad:
            //"kPostLoad: sent to registered plugins once all plugins have been loaded"
            logi("--------------------------------[ kPostLoad start/end ]--------------------------------");
            break;
        case SKSE::MessagingInterface::kPostPostLoad:
            // kPostPostLoad:  sent right after kPostLoad to facilitate the correct dispatching/registering of messages/listeners
            logi("--------------------------------[ kPostPostLoad start/end ]--------------------------------");
            break;
        case SKSE::MessagingInterface::kPreLoadGame:
            // kPreLoadGame:  sent right before the game is loaded
            logi("--------------------------------[ kPreLoadGame start/end ]--------------------------------");
            break;
        case SKSE::MessagingInterface::kPostLoadGame:
            // kPostLoadGame:  sent after the game has been loaded
            logi("--------------------------------[ kPostLoadGame start/end ]--------------------------------");
            break;
        case SKSE::MessagingInterface::kSaveGame:
            // kSaveGame:  sent when the game is saved
            logi("--------------------------------[ kSaveGame start/end ]--------------------------------");
            break;
        case SKSE::MessagingInterface::kDeleteGame:
            // kDeleteGame:  sent when the game is deleted
            logi("--------------------------------[ kDeleteGame start/end ]--------------------------------");
            break;
        case SKSE::MessagingInterface::kInputLoaded:
            logi("--------------------------------[ kInputLoaded start/end ]--------------------------------");
            break;
        case SKSE::MessagingInterface::kNewGame:
            // kNewGame:  sent when a new game is started
            logi("--------------------------------[ kNewGame start/end ]--------------------------------");
            break;
        case SKSE::MessagingInterface::kDataLoaded:
            // kDataLoaded: sent after the data handler has loaded all its forms

            // This message is sent when the game has finished loading all of the data files.
            // This is a good time to register your papyrus scripts, etc.
            logi("--------------------------------[ kDataLoaded start ]--------------------------------");
            EventProcessor::GetSingleton().OnDataLoaded();
			logi("--------------------------------[ kDataLoaded end ]--------------------------------");
            break;

        }
    }

    void OnMenuOpenClose(bool opening, const RE::BSFixedString& menuName)
    {
        if ( menuName == RE::JournalMenu::MENU_NAME) {
			logi("Journal menu {}", opening ? "opening" : "closing");
		}
    }
    RE::BSEventNotifyControl ProcessEvent(const RE::MenuOpenCloseEvent* event, RE::BSTEventSource<RE::MenuOpenCloseEvent>* eventSource) override
    {
        if (event) {
			OnMenuOpenClose(event->opening, event->menuName);
		}

		return RE::BSEventNotifyControl::kContinue;       
    }

private:
    std::string m_logPath;
    const SKSE::LoadInterface *m_skse = nullptr;
};

SKSEPluginLoad(const SKSE::LoadInterface *skse) {
    SKSE::Init(skse);

    EventProcessor::GetSingleton().setLoadInterface(skse);
    // Setup logging (e.g. using spdlog)
    auto path = SetupLog();
    EventProcessor::GetSingleton().setLogPath(path.string());
    SKSE::log::info("Plugin loaded");

    // This example prints "Hello, world!" to the Skyrim ~ console.
    // To view it, open the ~ console from the Skyrim Main Menu.
    SKSE::GetMessagingInterface()->RegisterListener(&EventProcessor::ProcessMessage);

    return true;
}