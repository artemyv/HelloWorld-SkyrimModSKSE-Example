#include "logger.h"
#include "Config/ConfigReader.h"
#include <format>
#include <V1/QuickLootAPI.h>
//#define SUPPORT_QL_API_V2 1
#if SUPPORT_QL_API_V2
#include <V2/QuickLootAPI.h>
#endif


namespace HelloSkyrim {
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
        logger::debug("Info message sent to console");

        RE::UI::GetSingleton()->AddEventSink(this);
        logger::debug("Registered to UI events");

        const auto info = m_skse->GetPluginInfo("QuickLootIE");
        if (info) {
            const auto v =  REL::Version::unpack( info->version);
            logger::info("QuickLootIE {:#10x} {} is detected", info->version, v.string("."));
            if(v < REL::Version(4, 0, 0)) {
                logger::trace("QuickLootIE version uses API V1");
                QuickLoot::QuickLootAPI::Init();
                if (!QuickLoot::QuickLootAPI::IsReady()) {
                    logger::error("QuickLootAPI V1 is not ready");
                    return;
                }
                if (!QuickLoot::QuickLootAPI::RegisterSelectItemHandler(SelectHandlerV1)) {
                    logger::error("SelectHandler for QuickLootAPI not registered");
                }
                logger::info("QuickLootIE API V1 is ready");
            }
#if SUPPORT_QL_API_V2
            else {
                logger::info("QuickLootIE version uses API V2");
                if (!QuickLoot::API::QuickLootAPI::Init( SKSE::PluginDeclaration::GetSingleton()->GetName().data())) {
                    logger::error("QuickLootAPI V2 is not ready");
                    return;
                }
                QuickLoot::API::QuickLootAPI::RegisterSelectItemHandler(SelectHandlerV2) ;
            }
#endif
        } else {
            logger::warn("QuickLootIE is not loaded");
        }

    }

    void OnQLDoSelect(RE::Actor* actor, RE::TESObjectREFR* container, const QuickLoot::Element *elements, std::uint32_t elementsCount)
    {
        // This is where you can do things when QuickLootIE selects an item.
        // For example, you can log the selected item or perform some action.
        logger::trace("QuickLootIE selected item in container {} by actor {}", container->GetFormID(), actor->GetFormID());
        for (std::uint32_t i = 0; i < elementsCount; ++i) {
            if(elements[i].object)
                logger::trace("Selected element: {}", elements[i].object->GetObjectTypeName());
        }
    }

#if SUPPORT_QL_API_V2
    void OnQLDoSelect(RE::Actor* actor, RE::TESObjectREFR* container, const QuickLoot::API::ItemStack *stack)
    {
        // This is where you can do things when QuickLootIE selects an item.
        // For example, you can log the selected item or perform some action.
        logger::trace("QuickLootIE selected item in container {} by actor {}", container->GetFormID(), actor->GetFormID());
        //Stack contains members
        //	RE::InventoryEntryData* entry;
		//  RE::TESObjectREFR* dropRef;
    }   
#endif

    static inline void SelectHandlerV1(QuickLoot::SelectItemEvent* evt)
	{
		EventProcessor::GetSingleton().OnQLDoSelect(evt->actor, evt->container, evt->elements, evt->elementsCount);
	};

#if SUPPORT_QL_API_V2
   	static inline void SelectHandlerV2( QuickLoot::API::Events::SelectItemEvent* evt)
	{
		EventProcessor::GetSingleton().OnQLDoSelect(evt->actor, evt->container, evt->stack);
	};
#endif    

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
            logger::trace("--------------------------------[ kPostLoad start/end ]--------------------------------");
            break;
        case SKSE::MessagingInterface::kPostPostLoad:
            // kPostPostLoad:  sent right after kPostLoad to facilitate the correct dispatching/registering of messages/listeners
            logger::trace("--------------------------------[ kPostPostLoad start/end ]--------------------------------");
            break;
        case SKSE::MessagingInterface::kPreLoadGame:
            // kPreLoadGame:  sent right before the game is loaded
            logger::trace("--------------------------------[ kPreLoadGame start/end ]--------------------------------");
            break;
        case SKSE::MessagingInterface::kPostLoadGame:
            // kPostLoadGame:  sent after the game has been loaded
            logger::trace("--------------------------------[ kPostLoadGame start/end ]--------------------------------");
            break;
        case SKSE::MessagingInterface::kSaveGame:
            // kSaveGame:  sent when the game is saved
            logger::trace("--------------------------------[ kSaveGame start/end ]--------------------------------");
            break;
        case SKSE::MessagingInterface::kDeleteGame:
            // kDeleteGame:  sent when the game is deleted
            logger::trace("--------------------------------[ kDeleteGame start/end ]--------------------------------");
            break;
        case SKSE::MessagingInterface::kInputLoaded:
            logger::trace("--------------------------------[ kInputLoaded start/end ]--------------------------------");
            break;
        case SKSE::MessagingInterface::kNewGame:
            // kNewGame:  sent when a new game is started
            logger::trace("--------------------------------[ kNewGame start/end ]--------------------------------");
            break;
        case SKSE::MessagingInterface::kDataLoaded:
            // kDataLoaded: sent after the data handler has loaded all its forms

            // This message is sent when the game has finished loading all of the data files.
            // This is a good time to register your papyrus scripts, etc.
            logger::info("--------------------------------[ kDataLoaded start ]--------------------------------");
            EventProcessor::GetSingleton().OnDataLoaded();
			logger::info("--------------------------------[ kDataLoaded end ]--------------------------------");
            break;

        }
    }

    void OnMenuOpenClose(bool opening, const RE::BSFixedString& menuName)
    {
        if ( menuName == RE::JournalMenu::MENU_NAME) {
			logger::info("Journal menu {}", opening ? "opening" : "closing");
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
}
SKSEPluginLoad(const SKSE::LoadInterface *skse) {
    SKSE::Init(skse);

    // Setup logging (e.g. using spdlog)
    auto path = HelloSkyrim::SetupLog();
    SKSE::log::info("Plugin initialization started");

    HelloSkyrim::Config::ConfigReader::SetUp();
    HelloSkyrim::EventProcessor::GetSingleton().setLoadInterface(skse);
    HelloSkyrim::EventProcessor::GetSingleton().setLogPath(path.string());

    // This example prints "Hello, world!" to the Skyrim ~ console.
    // To view it, open the ~ console from the Skyrim Main Menu.
    SKSE::GetMessagingInterface()->RegisterListener(&HelloSkyrim::EventProcessor::ProcessMessage);

    return true;
}