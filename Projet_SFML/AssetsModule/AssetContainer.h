#ifndef ASSETARRAY__H
#define ASSETARRAY__H

#include "AssetsBody.h"
#include "Types.h"

#include <unordered_map>
#include <list>
#include <cassert>
#include <memory>
#include <iostream>

// exist to be able to create a global container, a map, with all the assets containers
// register inside
class IAssetContainer
{
public:
    virtual ~IAssetContainer() = default;
};

// AssetType is the current Asset class used like Texture, Sound... inherit from Asset<DataType>

class AssetManager;
template<typename DataType>
class AssetContainer : public IAssetContainer
{
private:
    std::unordered_map<AssetID, Asset<DataType>*> m_Assets{};  // the literal asset storage, surely can be an ordered map
    std::unordered_map<const char*, AssetID> m_PathToID{};      // convenient map that permit an acces to the asset through his filepath
    std::list<uint32_t> m_OpenIds{};                            // here to not "waste" ids, not useful right now, allow kinda "unique" ID creation while I don't have proper unique ID generator
    uint32_t m_Count = 0;                                       // keep an eye on how much asset have been registered in this container
    uint32_t m_Mask;                                            // reserve 3 bits for now to different type of assets (can be modified in "Types.h")

public:
    AssetContainer() = default;
    AssetContainer(uint32_t mask) : m_Mask(mask){}

    // register the proper asset, and potentially load it
    // Stuck with the "AssetBase" for unknown reason, need to find a solution to avoir casting asset
    AssetID RegisterAsset(AssetBase* asset, bool autoLoad)
    {
        // create ID
        uint32_t id = m_Mask << MaskStart;
        if (!m_OpenIds.empty())
        {
            id += m_OpenIds.front();
            m_OpenIds.pop_front();
        }
        else
            id += m_Count;
        m_Count++;
        asset->SetID(id);
        m_PathToID.insert({ asset->GetPath(), id});
        
        // add the asset to the collection
        m_Assets.insert({ id, (Asset<DataType>*)asset });
        
        if (autoLoad)
            LoadAsset(id);
        
        return id;
    }

    //todo : UnregisterAsset

    bool LoadAsset(AssetID assetId)
    {
        // is the asset registered ?
        auto search = m_Assets.find(assetId);
        if (search == m_Assets.end())
        {
            assert(false && "Asset is not registered !");
            return false;
        }
        // it is, load it if it's not already
        auto asset = search->second;
        if (!asset->IsLoaded())
        {
            asset->LoadData();
            // this function better be called after the child LoadData method in the mother method but i don't know how to do it so here's my solution, crappy design 
            asset->ValidateLoad();
        }
        else
            std::cout << "Asset is already loaded !" << std::endl;

        return asset->IsLoaded();
    }

    // is making an other search, can be optimized but not really much a bottleneck
    bool LoadAsset(const char* path)
    {
        // find the asset ID if the asset is register
        auto search = m_PathToID.find(path);
        if (search == m_PathToID.end())
        {
            assert(false && "Asset is not registered !");
            return false;
        }
        // use this ID to load the asset
		return LoadAsset(search->second);
    }

	bool UnloadAsset(AssetID assetId)
	{
		auto search = m_Assets.find(assetId);
		if (search == m_Assets.end())
		{
			assert(false && "Asset is not registered !");
			return false;
		}
		auto asset = search->second;
		if (asset->IsLoaded())
		{
			asset->UnloadData();
            // same a LoadData
			asset->ValidateLoad();
		}
		else
			std::cout << "Asset is not loaded !" << std::endl;

		return asset->IsLoaded();
	}

    bool UnloadAsset(const char* path)
    {
		auto search = m_PathToID.find(path);
		if (search == m_PathToID.end())
		{
			assert(false && "Asset is not registered !");
			return false;
		}
		return UnloadAsset(search->second);
    }

    DataType* GetAsset(AssetID id)
    {
        auto search = m_Assets.find(id);
        if (search == m_Assets.end())
        {
            assert(false && "Asset is not registered !");
            return nullptr;
        }
        // cast needed, compiler does not convert properly the type otherwise
        return (DataType*)search->second;
    }


    DataType* GetAsset(const char* path)
    {
        auto search = m_PathToID.find(path);
        if (search == m_PathToID.end())
        {
            assert(false && "Asset is not registered !");
            return nullptr;
        }
        return GetAsset(search->second);
    }

    uint32_t GetMask() { return m_Mask; }
};

#endif //!ASSETARRAY__H