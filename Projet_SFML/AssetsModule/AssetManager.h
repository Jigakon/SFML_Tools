#ifndef AssetManager__H
#define AssetManager__H

#include "AssetContainer.h"
#include "Types.h"

#include <unordered_map>
#include <list>
#include <cassert>
#include <memory>
#include <iostream>


class AssetManager
{
private:
    static std::unordered_map<const char*, std::shared_ptr<IAssetContainer>> s_AssetsRegister;
    static std::unordered_map<const char*, uint32_t> s_TypeMask;
    static std::unordered_map<uint32_t, const char*> s_MaskToName;
    static uint32_t s_TypeCount;

public:
    // Create the container of a given Asset Type
    template<typename DataType>
    static bool CreateAssetContainer()
    {
        // search if the asset type is alreday register and created in the global container
        auto typeName = typeid(DataType).name();
        auto search = s_AssetsRegister.find(typeName);
        if (search != s_AssetsRegister.end())
        {
            std::cout << "Asset type already registered !" << std::endl;
            return false;
        }
        // it's not, create the mask and create the container then register the container in the global container
        auto mask = RegisterTypeMask<DataType>();
        s_AssetsRegister.insert({ typeName, std::make_shared<AssetContainer<DataType>>(mask) });
        return true;
    }

private:
    // convinence method, used to get the right container from the global container and verify if it's a valid type
    template<typename DataType>
    static std::shared_ptr<AssetContainer<DataType>> GetAssetContainer()
    {
        // is the type registered ?
        auto search = s_AssetsRegister.find(typeid(DataType).name());
        if (search == s_AssetsRegister.end())
        {
            assert(false && "Asset type container does not exist !");
            return nullptr;
        }
        return std::static_pointer_cast<AssetContainer<DataType>>(search->second);
    }

public:
    // link the user function to the system functions

    template<typename DataType>
    static AssetID RegisterAsset(DataType* asset, bool autoLoad = true)
    {
        return GetAssetContainer<DataType>()->RegisterAsset(asset, autoLoad);
    }

    template<typename DataType>
    static bool LoadAsset(AssetID id)
    {
        return GetAssetContainer<DataType>()->LoadAsset(id);
    }

    template<typename DataType>
    static bool UnloadAsset(AssetID id)
    {
        return GetAssetContainer<DataType>()->UnloadAsset(id);
    }

    template<typename DataType>
    static DataType* GetAsset(AssetID id)
    {
        return GetAssetContainer<DataType>()->GetAsset(id);
    }

    template<typename DataType>
    static AssetBase* GetAsset(const char* path)
    {
        return GetAssetContainer<DataType>()->GetAsset(path);
    }

    template<typename DataType>
    static uint32_t GetTypeMask()
    {
        // search if this type is registered
        auto type = s_TypeMask.find(typeid(DataType).name());
        if (type == s_TypeMask.end())
        {
            std::cout << "type is not registered !" << std::endl;
            return UINT_MAX;
        }
        // return mask
        return type->second;
    }

    template<typename DataType>
    static uint32_t RegisterTypeMask()
    {
        // is the type already registered ?
        auto typeName = typeid(DataType).name();
        auto type = s_TypeMask.find(typeName);
        if (type != s_TypeMask.end())
        {
            std::cout << "type already registered !" << std::endl;
            // return the current registered mask
            return type->second;
        }
        // it's not
        // add Type to the list

        // todo : if the asset type is removed from the container, keep it in a list to reuse it

        s_TypeCount++;
        s_TypeMask.insert({ typeName, s_TypeCount - 1 });
        s_MaskToName.insert({ s_TypeCount - 1 , typeName });
        return s_TypeCount - 1;
    }

};

#endif //!AssetManager