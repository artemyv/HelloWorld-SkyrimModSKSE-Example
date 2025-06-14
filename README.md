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

```
[2025-06-14 09:41:48.709] [log] [info] [plugin.cpp:213] Plugin loaded
[2025-06-14 09:41:50.811] [log] [trace] [plugin.cpp:144] --------------------------------[ kPostLoad start/end ]--------------------------------
[2025-06-14 09:41:55.970] [log] [trace] [plugin.cpp:148] --------------------------------[ kPostPostLoad start/end ]--------------------------------
[2025-06-14 09:42:40.431] [log] [trace] [plugin.cpp:167] --------------------------------[ kInputLoaded start/end ]--------------------------------
[2025-06-14 09:43:35.925] [log] [info] [plugin.cpp:178] --------------------------------[ kDataLoaded start ]--------------------------------
[2025-06-14 09:43:35.925] [log] [debug] [plugin.cpp:52] Info message sent to console
[2025-06-14 09:43:35.925] [log] [debug] [plugin.cpp:55] Registered to UI events
[2025-06-14 09:43:35.925] [log] [info] [plugin.cpp:60] QuickLootIE  0x3040000 3.4.0.0 is detected
[2025-06-14 09:43:35.925] [log] [trace] [plugin.cpp:62] QuickLootIE version uses API V1
[2025-06-14 09:43:35.925] [log] [info] [RequestClient.h:49] Successfully connected to plugin QuickLootIE (client version 1.0, server version 1.0)
[2025-06-14 09:43:35.925] [log] [info] [plugin.cpp:71] QuickLootIE API V1 is ready
[2025-06-14 09:43:35.925] [log] [info] [plugin.cpp:180] --------------------------------[ kDataLoaded end ]--------------------------------
[2025-06-14 09:44:34.974] [log] [trace] [plugin.cpp:152] --------------------------------[ kPreLoadGame start/end ]--------------------------------
[2025-06-14 09:44:57.131] [log] [trace] [plugin.cpp:156] --------------------------------[ kPostLoadGame start/end ]--------------------------------
[2025-06-14 09:45:00.222] [log] [trace] [plugin.cpp:93] QuickLootIE selected item in container 571732 by actor 20
[2025-06-14 09:45:00.222] [log] [trace] [plugin.cpp:96] Selected element: TwoHandAxe
[2025-06-14 09:45:22.696] [log] [trace] [plugin.cpp:93] QuickLootIE selected item in container 571732 by actor 20
[2025-06-14 09:45:22.696] [log] [trace] [plugin.cpp:96] Selected element: 
[2025-06-14 09:45:25.514] [log] [trace] [plugin.cpp:93] QuickLootIE selected item in container 571732 by actor 20
[2025-06-14 09:45:25.514] [log] [trace] [plugin.cpp:96] Selected element: TwoHandAxe
[2025-06-14 09:45:25.514] [log] [trace] [plugin.cpp:93] QuickLootIE selected item in container 571732 by actor 20
[2025-06-14 09:45:25.514] [log] [trace] [plugin.cpp:96] Selected element: 
[2025-06-14 09:45:26.539] [log] [trace] [plugin.cpp:93] QuickLootIE selected item in container 571732 by actor 20
[2025-06-14 09:45:26.539] [log] [trace] [plugin.cpp:96] Selected element: TwoHandAxe
[2025-06-14 09:45:26.539] [log] [trace] [plugin.cpp:93] QuickLootIE selected item in container 571732 by actor 20
[2025-06-14 09:45:26.539] [log] [trace] [plugin.cpp:96] Selected element: 
[2025-06-14 09:45:34.135] [log] [trace] [plugin.cpp:93] QuickLootIE selected item in container 571732 by actor 20
[2025-06-14 09:45:34.135] [log] [trace] [plugin.cpp:96] Selected element: TwoHandAxe
[2025-06-14 09:45:34.135] [log] [trace] [plugin.cpp:93] QuickLootIE selected item in container 571732 by actor 20
[2025-06-14 09:45:34.135] [log] [trace] [plugin.cpp:96] Selected element: 
[2025-06-14 09:45:35.541] [log] [trace] [plugin.cpp:93] QuickLootIE selected item in container 571732 by actor 20
[2025-06-14 09:45:35.541] [log] [trace] [plugin.cpp:96] Selected element: TwoHandAxe
[2025-06-14 09:45:38.660] [log] [info] [plugin.cpp:189] Journal menu opening```

# CommonLibSSE NG

Because this uses [CommonLibSSE NG](https://github.com/CharmedBaryon/CommonLibSSE-NG), it supports Skyrim SE, AE, GOG, and VR.

[CommonLibSSE NG](https://github.com/CharmedBaryon/CommonLibSSE-NG) is a fork of the popular [powerof3 fork](https://github.com/powerof3/CommonLibSSE) of the _original_ `CommonLibSSE` library created by [Ryan McKenzie](https://github.com/Ryan-rsm-McKenzie) in [2018](https://github.com/Ryan-rsm-McKenzie/CommonLibSSE/commit/224773c424bdb8e36c761810cdff0fcfefda5f4a).

# Requirements

- [Visual Studio 2022](https://visualstudio.microsoft.com/) (_the free Community edition_)
- [`xmake`](https://xmake.io/)

