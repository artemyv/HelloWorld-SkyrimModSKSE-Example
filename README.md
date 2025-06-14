# SKSE "Hello, world!"

Playground for creating C++ SKSE plugin for Skyrim!

---

- [SKSE "Hello, world!"](#skse-hello-world)
- [What does it do?](#what-does-it-do)
- [CommonLibSSE NG](#commonlibsse-ng)
- [Requirements](#requirements)

# What does it do?

Version 0.0.1 will print log location to console
And will show several game events.
If available - it will try to register to QuickLootIE Select event using API V1 
(mod version upto 3.4.1 supported)
For some elements even the item type name is printed to log
Version 0.0.2 will read desired log level from json config, by default info 
level is used

```
[2025-06-14 16:10:50.892] [log] [info] [EventProcessor.cpp:16] Plugin initialization started
[2025-06-14 16:10:50.899] [log] [info] [ConfigReader.cpp:34] Log level changed to trace
[2025-06-14 16:10:53.007] [log] [trace] [EventProcessor.cpp:35] --------------------------------[ kPostLoad start/end ]--------------------------------
[2025-06-14 16:10:58.235] [log] [trace] [EventProcessor.cpp:40] --------------------------------[ kPostPostLoad start/end ]--------------------------------
[2025-06-14 16:11:43.628] [log] [trace] [EventProcessor.cpp:63] --------------------------------[ kInputLoaded start/end ]--------------------------------
[2025-06-14 16:12:53.344] [log] [info] [EventProcessor.cpp:74] --------------------------------[ kDataLoaded start ]--------------------------------
[2025-06-14 16:12:53.344] [log] [debug] [EventProcessor.cpp:87] Info message sent to console
[2025-06-14 16:12:53.344] [log] [debug] [EventProcessor.cpp:90] Registered to UI events
[2025-06-14 16:12:53.344] [log] [info] [EventProcessor.cpp:95] QuickLootIE  0x3040000 3.4.0.0 is detected
[2025-06-14 16:12:53.344] [log] [trace] [EventProcessor.cpp:97] QuickLootIE version uses API V1
[2025-06-14 16:12:53.344] [log] [info] [RequestClient.h:49] Successfully connected to plugin QuickLootIE (client version 1.0, server version 1.0)
[2025-06-14 16:12:53.344] [log] [info] [EventProcessor.cpp:106] QuickLootIE API V1 is ready
[2025-06-14 16:12:53.344] [log] [info] [EventProcessor.cpp:76] --------------------------------[ kDataLoaded end ]--------------------------------
[2025-06-14 16:13:50.590] [log] [trace] [EventProcessor.cpp:46] --------------------------------[ kPreLoadGame start/end ]--------------------------------
[2025-06-14 16:14:12.724] [log] [trace] [EventProcessor.cpp:50] --------------------------------[ kPostLoadGame start/end ]--------------------------------
[2025-06-14 16:14:15.849] [log] [trace] [EventProcessor.cpp:128] QuickLootIE selected item in container 571732 by actor 20
[2025-06-14 16:14:15.849] [log] [trace] [EventProcessor.cpp:130] Selected element: TwoHandAxe
[2025-06-14 16:14:16.670] [log] [trace] [EventProcessor.cpp:128] QuickLootIE selected item in container 571732 by actor 20
[2025-06-14 16:14:16.670] [log] [trace] [EventProcessor.cpp:130] Selected element: 
[2025-06-14 16:14:19.838] [log] [trace] [EventProcessor.cpp:128] QuickLootIE selected item in container 571732 by actor 20
[2025-06-14 16:14:19.838] [log] [trace] [EventProcessor.cpp:130] Selected element: TwoHandAxe
[2025-06-14 16:14:19.839] [log] [trace] [EventProcessor.cpp:128] QuickLootIE selected item in container 571732 by actor 20
[2025-06-14 16:14:19.839] [log] [trace] [EventProcessor.cpp:130] Selected element: 
[2025-06-14 16:14:21.034] [log] [trace] [EventProcessor.cpp:128] QuickLootIE selected item in container 571732 by actor 20
[2025-06-14 16:14:21.034] [log] [trace] [EventProcessor.cpp:130] Selected element: TwoHandAxe
[2025-06-14 16:14:22.560] [log] [info] [EventProcessor.cpp:149] Journal menu opening
```

# CommonLibSSE NG

Because this uses [CommonLibSSE NG](https://github.com/CharmedBaryon/CommonLibSSE-NG), it supports Skyrim SE, AE, GOG, and VR.

[CommonLibSSE NG](https://github.com/CharmedBaryon/CommonLibSSE-NG) is a fork of the popular [powerof3 fork](https://github.com/powerof3/CommonLibSSE) of the _original_ `CommonLibSSE` library created by [Ryan McKenzie](https://github.com/Ryan-rsm-McKenzie) in [2018](https://github.com/Ryan-rsm-McKenzie/CommonLibSSE/commit/224773c424bdb8e36c761810cdff0fcfefda5f4a).

# Requirements

- [Visual Studio 2022](https://visualstudio.microsoft.com/) (_the free Community edition_)
- [`xmake`](https://xmake.io/)

