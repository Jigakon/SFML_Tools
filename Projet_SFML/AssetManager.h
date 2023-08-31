#ifndef AssetManager__H
#define AssetManager__H

#include "AssetArray.h"

#include <unordered_map>
#include <list>
#include <cassert>
#include <memory>
#include <iostream>


class AssetManager
{
public:
    static std::unordered_map<const char*, std::shared_ptr<IAssetArray>> s_AssetsRegister;
    static std::unordered_map<const char*, uint32_t> s_TypeMask;
    static std::unordered_map<uint32_t, const char*> s_MaskToName;
    static uint32_t s_TypeCount;

    template<typename AssetType>
    static bool CreateAssetArray()
    {
        auto typeName = typeid(AssetType).name();
        auto search = s_AssetsRegister.find(typeName);
        if (search != s_AssetsRegister.end())
        {
            std::cout << "Asset type already registered !" << std::endl;
            return false;
        }
        auto mask = RegisterTypeMask<AssetType>();
        s_AssetsRegister.insert({ typeName, std::make_shared<AssetArray<AssetType>>(mask) });
        return true;
    }

    template<typename AssetType>
    static std::shared_ptr<AssetArray<AssetType>> GetAssetArray()
    {
        auto typeName = typeid(AssetType).name();
        return std::static_pointer_cast<AssetArray<AssetType>>(s_AssetsRegister[typeName]);
    }

    template<typename AssetType>
    static AssetID RegisterAsset(AssetType* asset, bool autoLoad = true)
    {
        auto typeName = typeid(AssetType).name();
        
        auto search = s_AssetsRegister.find(typeName);
        if (search == s_AssetsRegister.end())
        {
            std::cout << "Asset type array doesn't exist, please register type before..." << std::endl;
            return 0;
        }
        return search->second->RegisterAsset(asset, autoLoad);
    }

    template<typename AssetType>
    static bool LoadAsset(AssetID asset)
    {
        auto search = s_AssetsRegister.find(typeid(AssetType));
        if (search == s_AssetsRegister.end())
        {
            assert(false && "Asset type not registered !");
            return 0;
        }
        return search->second.get()->LoadAsset(asset);
    }

    template<typename AssetType>
    static bool UnloadAsset(AssetID asset)
    {
        return false;
    }

    template<typename AssetType>
    static AssetType* GetAsset(AssetID id)
    {
        return GetAssetArray<AssetType>()->GetAsset(id);
    }

    template<typename AssetType>
    static AssetBase* GetAsset(const char* path)
    {
        auto search = s_AssetsRegister.find(typeid(AssetType).name());
        if (search == s_AssetsRegister.end())
        {
            assert(false && "Asset type is not registered !");
            return nullptr;
        }
        return search->second.get()->GetAsset(path);
    }

    template<typename AssetType>
    static uint32_t GetTypeMask()
    {
        // search if this type is registered
        auto typeName = typeid(AssetType).name();
        auto type = s_TypeMask.find(typeName);
        if (type == s_TypeMask.end())
        {
            std::cout << "type already registered !" << std::endl;
            return UINT_MAX;
        }
        return type->second;
    }

    template<typename AssetType>
    static uint32_t RegisterTypeMask()
    {
        auto typeName = typeid(AssetType).name();
        auto type = s_TypeMask.find(typeName);
        if (type != s_TypeMask.end())
        {
            std::cout << "type already registered !" << std::endl;
            return type->second;
        }
        // it's not
        // auto add Type to mask
        s_TypeCount++;
        s_TypeMask.insert({ typeName, s_TypeCount - 1 });
        s_MaskToName.insert({ s_TypeCount - 1 , typeName });
        return s_TypeCount - 1;
    }

};

#endif //!AssetManager