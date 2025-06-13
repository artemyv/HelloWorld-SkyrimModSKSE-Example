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
If available - it will try to register to QuickLootIE Select event
For some elements even the item type name is printed to log

```
[2025-06-13 13:04:07.428] [log] [info] [plugin.cpp:177] Plugin loaded
[2025-06-13 13:04:09.580] [log] [info] [plugin.cpp:108] --------------------------------[ kPostLoad start/end ]--------------------------------
[2025-06-13 13:04:14.759] [log] [info] [plugin.cpp:112] --------------------------------[ kPostPostLoad start/end ]--------------------------------
[2025-06-13 13:05:00.018] [log] [info] [plugin.cpp:131] --------------------------------[ kInputLoaded start/end ]--------------------------------
[2025-06-13 13:05:55.730] [log] [info] [plugin.cpp:142] --------------------------------[ kDataLoaded start ]--------------------------------
[2025-06-13 13:05:55.730] [log] [info] [plugin.cpp:50] Info message sent to console
[2025-06-13 13:05:55.730] [log] [info] [plugin.cpp:53] Registered to UI events
[2025-06-13 13:05:55.730] [log] [info] [plugin.cpp:58] QuickLootIE  0x3040000 3.4.0.0 is loaded
[2025-06-13 13:05:55.730] [log] [info] [RequestClient.h:49] Successfully connected to plugin QuickLootIE (client version 1.0, server version 1.0)
[2025-06-13 13:05:55.730] [log] [info] [plugin.cpp:144] --------------------------------[ kDataLoaded end ]--------------------------------
[2025-06-13 13:07:11.871] [log] [info] [plugin.cpp:116] --------------------------------[ kPreLoadGame start/end ]--------------------------------
[2025-06-13 13:07:34.375] [log] [info] [plugin.cpp:120] --------------------------------[ kPostLoadGame start/end ]--------------------------------
[2025-06-13 13:07:37.461] [log] [info] [plugin.cpp:77] QuickLootIE selected item in container 571732 by actor 20
[2025-06-13 13:07:37.461] [log] [info] [plugin.cpp:80] Selected element: TwoHandAxe
[2025-06-13 13:07:42.196] [log] [info] [plugin.cpp:77] QuickLootIE selected item in container 571732 by actor 20
[2025-06-13 13:07:42.196] [log] [info] [plugin.cpp:80] Selected element: 
[2025-06-13 13:07:43.283] [log] [info] [plugin.cpp:77] QuickLootIE selected item in container 571732 by actor 20
[2025-06-13 13:07:43.284] [log] [info] [plugin.cpp:80] Selected element: 
[2025-06-13 13:07:48.123] [log] [info] [plugin.cpp:77] QuickLootIE selected item in container 571732 by actor 20
[2025-06-13 13:07:48.123] [log] [info] [plugin.cpp:80] Selected element: TwoHandAxe
[2025-06-13 13:07:48.123] [log] [info] [plugin.cpp:77] QuickLootIE selected item in container 571732 by actor 20
[2025-06-13 13:07:48.123] [log] [info] [plugin.cpp:80] Selected element: 
[2025-06-13 13:07:49.731] [log] [info] [plugin.cpp:77] QuickLootIE selected item in container 571732 by actor 20
[2025-06-13 13:07:49.731] [log] [info] [plugin.cpp:80] Selected element: 
[2025-06-13 13:07:50.155] [log] [info] [plugin.cpp:77] QuickLootIE selected item in container 571732 by actor 20
[2025-06-13 13:07:50.155] [log] [info] [plugin.cpp:80] Selected element: TwoHandAxe
[2025-06-13 13:07:52.793] [log] [info] [plugin.cpp:153] Journal menu opening
```

# CommonLibSSE NG

Because this uses [CommonLibSSE NG](https://github.com/CharmedBaryon/CommonLibSSE-NG), it supports Skyrim SE, AE, GOG, and VR.

[CommonLibSSE NG](https://github.com/CharmedBaryon/CommonLibSSE-NG) is a fork of the popular [powerof3 fork](https://github.com/powerof3/CommonLibSSE) of the _original_ `CommonLibSSE` library created by [Ryan McKenzie](https://github.com/Ryan-rsm-McKenzie) in [2018](https://github.com/Ryan-rsm-McKenzie/CommonLibSSE/commit/224773c424bdb8e36c761810cdff0fcfefda5f4a).

# Requirements

- [Visual Studio 2022](https://visualstudio.microsoft.com/) (_the free Community edition_)
- [`xmake`](https://xmake.io/)

