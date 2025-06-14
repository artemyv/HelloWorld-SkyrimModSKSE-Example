#define SUPPORT_QL_API_V2 1
#include <V1/QuickLootAPI.h>
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
    class EventProcessor : public RE::BSTEventSink<RE::MenuOpenCloseEvent> {
        // Pretty typical singleton setup
        // *Private* constructor/destructor
        // And we *delete* the copy constructors and move constructors.
        EventProcessor()                                 = default;
        ~EventProcessor()                                = default;
        EventProcessor(const EventProcessor&)            = delete;
        EventProcessor(EventProcessor&&)                 = delete;
        EventProcessor& operator=(const EventProcessor&) = delete;
        EventProcessor& operator=(EventProcessor&&)      = delete;

    public:
        // Returns a reference to the one and only instance of EventProcessor :)
        //
        // Note: this is returned as a & reference. When you need this as a pointer, you'll want to use & (see below)
        static EventProcessor& GetSingleton() {
            static EventProcessor singleton;
            return singleton;
        }
        bool sksePluginLoad(const SKSE::LoadInterface* skse);

        // C-style callbacks
        static inline void ProcessMessage(SKSE::MessagingInterface::Message* message) {
            GetSingleton().ProcessMessageInternal(message);
        }
        static inline void SelectHandlerV1(QuickLoot::SelectItemEvent* evt) {
            GetSingleton().OnQLDoSelect(evt->actor, evt->container, evt->elements, evt->elementsCount);
        };

#if SUPPORT_QL_API_V2
        static inline void SelectHandlerV2(QuickLoot::API::Events::SelectItemEvent* evt) {
            GetSingleton().OnQLDoSelect(evt->actor, evt->container, evt->stack);
        };
#endif

        // implementation of RE::BSTEventSink<RE::MenuOpenCloseEvent> interface
        RE::BSEventNotifyControl ProcessEvent(
            const RE::MenuOpenCloseEvent* event, RE::BSTEventSource<RE::MenuOpenCloseEvent>* eventSource
        ) override {
            if (event) {
                OnMenuOpenClose(event->opening, event->menuName);
            }

            return RE::BSEventNotifyControl::kContinue;
        }

    private:
        void ProcessMessageInternal(SKSE::MessagingInterface::Message* message);
        void OnDataLoaded();

        void OnQLDoSelect(
            RE::Actor* actor, RE::TESObjectREFR* container, const QuickLoot::Element* elements,
            std::uint32_t elementsCount
        );
#if SUPPORT_QL_API_V2
        void OnQLDoSelect(RE::Actor* actor, RE::TESObjectREFR* container, const QuickLoot::API::ItemStack* stack);
#endif

        // This function is called when the Journal menu is opened or closed
        void OnMenuOpenClose(bool opening, const RE::BSFixedString& menuName);

    private:
        std::string                m_logPath;
        const SKSE::LoadInterface* m_skse = nullptr;
    };
}
