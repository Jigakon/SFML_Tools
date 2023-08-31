#ifndef AssetManager__H
#define AssetManager__H

#include <unordered_map>
#include <list>
#include <cassert>
#include <memory>
#include <iostream>

#define MaskStart 28

using AssetID = uint32_t;

class Asset
{
public:
    bool m_IsLoaded = false;
    const char* m_Path;
    AssetID m_Id = 0;

    Asset(const char* path) : m_Path(path) {}

    virtual bool LoadData() = 0;
    virtual bool UnloadData() = 0;
    virtual void* GetData() = 0;

    uint32_t GetAssetType() { return m_Id >> MaskStart; }
};

class AssetArray
{
public:
    std::unordered_map<const char*, AssetID> PathToID{};
    std::unordered_map<AssetID, Asset*> m_Assets{};
    uint32_t count = 0;
    std::list<uint32_t> openIds{};
    uint32_t mask;

    AssetArray();

    AssetID RegisterAsset(Asset* asset, bool autoLoad);

    bool LoadAsset(Asset* asset);
    bool LoadAsset(const char* path);
    bool LoadAsset(AssetID id);
    
    void* GetAsset(const char* path);
    void* GetAsset(AssetID id);
};

class AssetManager
{
public:
    static std::unordered_map<const char*, std::shared_ptr<AssetArray>> s_AssetsRegister;
    static std::unordered_map<const char*, uint32_t> s_TypeMask;
    static uint32_t s_TypeCount;

    template<typename AssetType>
    static AssetID RegisterAsset(Asset* asset, bool autoLoad = true)
    {
        auto typeName = typeid(AssetType).name();
        //create AssetArray if type not does not exist
        auto search = s_AssetsRegister.find(typeName);
        if (search == s_AssetsRegister.end())
        {
            auto assetArray = std::make_shared<AssetArray>();
            s_AssetsRegister.insert(std::make_pair(typeName, assetArray));
            assetArray->RegisterAsset(asset, autoLoad);
        }
        else
        {
            search->second->RegisterAsset(asset, autoLoad);
        }
        return asset->m_Id;
    }

    template<typename AssetType>
    static AssetID LoadAsset(Asset* asset)
    {
        auto search = s_AssetsRegister.find();
        if (search == s_AssetsRegister.end())
        {
            assert(false && "Asset type not registered !");
            return 0;
        }
        search->second.get()->LoadAsset(asset);
        return asset->m_Id;
    }
    
    template<typename AssetType>
    static AssetID UnloadAsset(Asset* asset)
    {
        
    }

    template<typename AssetType>
    static void* GetAsset(AssetID id)
    {
        auto search = s_AssetsRegister.find(typeid(AssetType).name());
        if (search == s_AssetsRegister.end())
        {
            assert(false && "Asset type is not registered !");
            return nullptr;
        }
        return (AssetType*)search->second.get()->GetAsset(id);
    }

    template<typename AssetType>
    static void* GetAsset(const char* path)
    {
        auto search = s_AssetsRegister.find(typeid(AssetType).name());
        if (search == s_AssetsRegister.end())
        {
            assert(false && "Asset type is not registered !");
            return nullptr;
        }
        return (AssetType*)search->second.get()->GetAsset(path);
    }

    template<typename Asset>
    static uint32_t GetTypeMask()
    {
        // search if this type is registered
        auto typeName = typeid(Asset).name();
        auto type = s_TypeMask.find(typeName);
        if (type != s_TypeMask.end())
            return type->second;
        // it's not
        // auto add Type to mask
        s_TypeCount++;
        s_TypeMask.insert({ typeName, s_TypeCount - 1 });
        return s_TypeCount - 1;
    }

};

#endif //!AssetManager