#include "EventProcessor.h"


#include <format>

#include "Config/ConfigReader.h"
#include "logger.h"

bool HelloSkyrim::EventProcessor::sksePluginLoad(const SKSE::LoadInterface* skse) {
    SKSE::Init(skse);

    m_skse = skse;
    // Setup logging (e.g. using spdlog)
    m_logPath = HelloSkyrim::SetupLog().string();

    SKSE::log::info("Plugin initialization started");

    // read json config file
    HelloSkyrim::Config::ConfigReader::SetUp();

    // register message handler
    SKSE::GetMessagingInterface()->RegisterListener(&HelloSkyrim::EventProcessor::ProcessMessage);

    return true;
}

void HelloSkyrim::EventProcessor::ProcessMessageInternal(SKSE::MessagingInterface::Message* message) {
    switch (message->type) {
            // Descriptions are taken from the original skse64 library
            // See:
            // https://github.com/ianpatt/skse64/blob/09f520a2433747f33ae7d7c15b1164ca198932c3/skse64/PluginAPI.h#L193-L212

        case SKSE::MessagingInterface::kPostLoad:
            //"kPostLoad: sent to registered plugins once all plugins have been loaded"
            logger::trace("--------------------------------[ kPostLoad start/end ]--------------------------------");
            break;
        case SKSE::MessagingInterface::kPostPostLoad:
            // kPostPostLoad:  sent right after kPostLoad to facilitate the correct dispatching/registering of
            // messages/listeners
            logger::trace(
                "--------------------------------[ kPostPostLoad start/end ]--------------------------------"
            );
            break;
        case SKSE::MessagingInterface::kPreLoadGame:
            // kPreLoadGame:  sent right before the game is loaded
            logger::trace("--------------------------------[ kPreLoadGame start/end ]--------------------------------");
            break;
        case SKSE::MessagingInterface::kPostLoadGame:
            // kPostLoadGame:  sent after the game has been loaded
            logger::trace(
                "--------------------------------[ kPostLoadGame start/end ]--------------------------------"
            );
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
            OnDataLoaded();
            logger::info("--------------------------------[ kDataLoaded end ]--------------------------------");
            break;
    }
}

void HelloSkyrim::EventProcessor::OnDataLoaded() {
    // This is where you can do things when the game has finished loading all of the data files.
    // For example, you can register your papyrus scripts here.
    auto pluginName = SKSE::PluginDeclaration::GetSingleton()->GetName();

    RE::ConsoleLog::GetSingleton()->Print(fmt::format("{} Log is written to {}", pluginName, m_logPath).c_str());
    logger::debug("Info message sent to console");

    RE::UI::GetSingleton()->AddEventSink(this);
    logger::debug("Registered to UI events");

    const auto info = m_skse->GetPluginInfo("QuickLootIE");
    if (info) {
        const auto v = REL::Version::unpack(info->version);
        logger::info("QuickLootIE {:#10x} {} is detected", info->version, v.string("."));
        if (v < REL::Version(4, 0, 0)) {
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
            if (!QuickLoot::API::QuickLootAPI::Init(pluginName.data())) {
                logger::error("QuickLootAPI V2 is not ready");
                return;
            }
            QuickLoot::API::QuickLootAPI::RegisterSelectItemHandler(SelectHandlerV2);
        }
#endif
    } else {
        logger::warn("QuickLootIE is not loaded");
    }
}

void HelloSkyrim::EventProcessor::OnQLDoSelect(
    RE::Actor* actor, RE::TESObjectREFR* container, const QuickLoot::Element* elements, std::uint32_t elementsCount
) {
    // This is where you can do things when QuickLootIE selects an item. API V1
    // For example, you can log the selected item or perform some action.
    logger::trace("QuickLootIE selected item in container {} by actor {}", container->GetFormID(), actor->GetFormID());
    for (std::uint32_t i = 0; i < elementsCount; ++i) {
        if (elements[i].object) logger::trace("Selected element: {}", elements[i].object->GetObjectTypeName());
    }
}

#if SUPPORT_QL_API_V2
void HelloSkyrim::EventProcessor::OnQLDoSelect(
    RE::Actor* actor, RE::TESObjectREFR* container, const QuickLoot::API::ItemStack* stack
) {
    // This is where you can do things when QuickLootIE selects an item. API V2
    // For example, you can log the selected item or perform some action.
    logger::trace("QuickLootIE selected item in container {} by actor {}", container->GetFormID(), actor->GetFormID());
    // Stack contains members
    //	RE::InventoryEntryData* entry;
    //   RE::TESObjectREFR* dropRef;
}
#endif

void HelloSkyrim::EventProcessor::OnMenuOpenClose(bool opening, const RE::BSFixedString& menuName) {
    if (menuName == RE::JournalMenu::MENU_NAME) {
        logger::info("Journal menu {}", opening ? "opening" : "closing");
    }
}
