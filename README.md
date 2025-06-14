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
[2025-06-14 13:26:04.533] [log] [info] [plugin.cpp:214] Plugin initialization started
[2025-06-14 13:26:04.539] [log] [info] [ConfigReader.cpp:34] Log level changed to trace
[2025-06-14 13:26:06.043] [log] [trace] [plugin.cpp:147] --------------------------------[ kPostLoad start/end ]--------------------------------
[2025-06-14 13:26:10.622] [log] [trace] [plugin.cpp:151] --------------------------------[ kPostPostLoad start/end ]--------------------------------
[2025-06-14 13:26:53.478] [log] [trace] [plugin.cpp:170] --------------------------------[ kInputLoaded start/end ]--------------------------------
[2025-06-14 13:27:45.965] [log] [info] [plugin.cpp:181] --------------------------------[ kDataLoaded start ]--------------------------------
[2025-06-14 13:27:45.974] [log] [debug] [plugin.cpp:55] Info message sent to console
[2025-06-14 13:27:45.974] [log] [debug] [plugin.cpp:58] Registered to UI events
[2025-06-14 13:27:45.974] [log] [info] [plugin.cpp:63] QuickLootIE  0x3040000 3.4.0.0 is detected
[2025-06-14 13:27:45.974] [log] [trace] [plugin.cpp:65] QuickLootIE version uses API V1
[2025-06-14 13:27:45.974] [log] [info] [RequestClient.h:49] Successfully connected to plugin QuickLootIE (client version 1.0, server version 1.0)
[2025-06-14 13:27:45.974] [log] [info] [plugin.cpp:74] QuickLootIE API V1 is ready
[2025-06-14 13:27:45.974] [log] [info] [plugin.cpp:183] --------------------------------[ kDataLoaded end ]--------------------------------
[2025-06-14 13:28:33.661] [log] [trace] [plugin.cpp:155] --------------------------------[ kPreLoadGame start/end ]--------------------------------
[2025-06-14 13:28:43.938] [log] [trace] [plugin.cpp:159] --------------------------------[ kPostLoadGame start/end ]--------------------------------
[2025-06-14 13:28:46.739] [log] [trace] [plugin.cpp:96] QuickLootIE selected item in container 571732 by actor 20
[2025-06-14 13:28:46.739] [log] [trace] [plugin.cpp:99] Selected element: TwoHandAxe
[2025-06-14 13:28:57.914] [log] [trace] [plugin.cpp:96] QuickLootIE selected item in container 571732 by actor 20
[2025-06-14 13:28:57.914] [log] [trace] [plugin.cpp:99] Selected element: 
[2025-06-14 13:29:00.689] [log] [trace] [plugin.cpp:96] QuickLootIE selected item in container 571732 by actor 20
[2025-06-14 13:29:00.689] [log] [trace] [plugin.cpp:99] Selected element: TwoHandAxe
[2025-06-14 13:29:00.689] [log] [trace] [plugin.cpp:96] QuickLootIE selected item in container 571732 by actor 20
[2025-06-14 13:29:00.690] [log] [trace] [plugin.cpp:99] Selected element: 
[2025-06-14 13:29:01.696] [log] [trace] [plugin.cpp:96] QuickLootIE selected item in container 571732 by actor 20
[2025-06-14 13:29:01.696] [log] [trace] [plugin.cpp:99] Selected element: TwoHandAxe
[2025-06-14 13:29:03.022] [log] [info] [plugin.cpp:192] Journal menu opening
```

# CommonLibSSE NG

Because this uses [CommonLibSSE NG](https://github.com/CharmedBaryon/CommonLibSSE-NG), it supports Skyrim SE, AE, GOG, and VR.

[CommonLibSSE NG](https://github.com/CharmedBaryon/CommonLibSSE-NG) is a fork of the popular [powerof3 fork](https://github.com/powerof3/CommonLibSSE) of the _original_ `CommonLibSSE` library created by [Ryan McKenzie](https://github.com/Ryan-rsm-McKenzie) in [2018](https://github.com/Ryan-rsm-McKenzie/CommonLibSSE/commit/224773c424bdb8e36c761810cdff0fcfefda5f4a).

# Requirements

- [Visual Studio 2022](https://visualstudio.microsoft.com/) (_the free Community edition_)
- [`xmake`](https://xmake.io/)

