#include "AssetManager.h"

uint32_t AssetManager::s_TypeCount = 0;
std::unordered_map<const char*, std::shared_ptr<IAssetArray>> AssetManager::s_AssetsRegister{};
std::unordered_map<const char*, uint32_t> AssetManager::s_TypeMask{};
std::unordered_map<uint32_t, const char*> AssetManager::s_MaskToName{};

