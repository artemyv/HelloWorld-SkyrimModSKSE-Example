#include "EventProcessor.h"

SKSEPluginLoad(const SKSE::LoadInterface* skse) {
    return HelloSkyrim::EventProcessor::GetSingleton().sksePluginLoad(skse);
}