#include "AssetManager.h"

uint32_t AssetManager::s_TypeCount = 0;
std::unordered_map<const char*, std::shared_ptr<AssetArray>> AssetManager::s_AssetsRegister{};
std::unordered_map<const char*, uint32_t> AssetManager::s_TypeMask{};

AssetArray::AssetArray()
{
    mask = AssetManager::GetTypeMask<Asset>();
}

AssetID AssetArray::RegisterAsset(Asset* asset, bool autoLoad)
{
    // create ID
    uint32_t id = mask << MaskStart;
    if (!openIds.empty())
    {
        id += openIds.front();
        openIds.pop_front();
    }
    else
        id += count;
    count++;
    asset->m_Id = id;
    PathToID.insert({ asset->m_Path, asset->m_Id });
    m_Assets.insert({ asset->m_Id, asset });
    if (autoLoad)
        LoadAsset(asset);
    return asset->m_Id;
}

bool AssetArray::LoadAsset(Asset* asset)
{
    if (asset->m_IsLoaded)
    {
        assert(false && "asset already loaded");
        return false;
    }
    return asset->LoadData();
}

bool AssetArray::LoadAsset(const char* path)
{
    auto search = PathToID.find(path);
    if (search == PathToID.end())
    {
        assert(false && "Asset is not registered !");
        return false;
    }
    return m_Assets.find(search->second)->second->LoadData();
}

bool AssetArray::LoadAsset(AssetID asset)
{
    auto search = m_Assets.find(asset);
    if (search == m_Assets.end())
    {
        assert(false && "Asset is not registered !");
        return false;
    }
    return search->second->LoadData();
}

void* AssetArray::GetAsset(AssetID id)
{
    auto search = m_Assets.find(id);
    if (search == m_Assets.end())
    {
        assert(false && "Asset is not registered !");
        return nullptr;
    }
    return search->second;
}

void* AssetArray::GetAsset(const char* path)
{
    auto search = PathToID.find(path);
    if (search == PathToID.end())
    {
        assert(false && "Asset is not registered !");
        return nullptr;
    }
    return m_Assets.find(search->second)->second;
}