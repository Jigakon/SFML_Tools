#ifndef ASSETARRAY__H
#define ASSETARRAY__H

#include <unordered_map>
#include <list>
#include <cassert>
#include <memory>
#include <iostream>
#include <functional>

#define MaskStart 28

using AssetID = unsigned int;

class AssetBase
{
public:
    bool m_IsLoaded = false;
    const char* m_Path;
    AssetID m_Id = 0;

    AssetBase() = default;
    AssetBase(const char* path) : m_Path(path) {}

    virtual bool LoadData() = 0;
    virtual bool UnloadData() = 0;

    uint32_t GetAssetType() { return m_Id >> MaskStart; }
};

template<typename AssetType>
class Asset : public AssetBase
{
public:
    AssetType* m_Data = nullptr;

    Asset(const char* path) : AssetBase(path) { m_Data = new AssetType(); }
    AssetType* GetData() { return m_Data; };
};

class IAssetArray
{
public:
    virtual AssetID RegisterAsset(AssetBase* asset, bool autoLoad) = 0;
    virtual AssetBase* GetAsset(AssetID id) = 0;
    virtual AssetBase* GetAsset(const char* path) = 0;
};

class AssetManager;
template<typename AssetType>
class AssetArray : public IAssetArray
{
public:
    std::unordered_map<const char*, AssetID> PathToID{};
    std::unordered_map<AssetID, Asset<AssetType>*> m_Assets{};
    uint32_t count = 0;
    std::list<uint32_t> openIds{};
    uint32_t mask;

    AssetArray() = default;
    AssetArray(uint32_t masK) : mask(masK){}

    std::function<bool()> LoadDataCallback;
    std::function<bool()> UnloadDataCallback;

    AssetID RegisterAsset(AssetBase* asset, bool autoLoad) override
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
        
        auto assetTyped = (Asset<AssetType>*)asset;
        m_Assets.insert({ asset->m_Id, assetTyped });
        
        if (autoLoad)
            asset->LoadData();
        
        return asset->m_Id;
    }

    bool LoadAsset(AssetID asset)
    {
        auto search = m_Assets.find(asset);
        if (search == m_Assets.end())
        {
            assert(false && "Asset is not registered !");
            return false;
        }
        return search->second->LoadData();
    }

    bool LoadAsset(const char* path)
    {
        auto search = PathToID.find(path);
        if (search == PathToID.end())
        {
            assert(false && "Asset is not registered !");
            return false;
        }
        return m_Assets.find(search->second)->second->LoadData();
    }

    AssetType* GetAsset(AssetID id)
    {
        auto search = m_Assets.find(id);
        if (search == m_Assets.end())
        {
            assert(false && "Asset is not registered !");
            return nullptr;
        }
        return (AssetType*)search->second;
    }

    AssetBase* GetAsset(const char* path)
    {
        auto search = PathToID.find(path);
        if (search == PathToID.end())
        {
            assert(false && "Asset is not registered !");
            return nullptr;
        }
        return (AssetType*)m_Assets.find(search->second)->second;
    }
};

#endif //!ASSETARRAY__H