#ifndef ASSETSBODY__H
#define ASSETSBODY__H

#include "Types.h"

class AssetBase
{
protected:
	bool m_IsLoaded = false;
	const char* m_Path;
	AssetID m_Id = 0;

	AssetBase() = default;
	AssetBase(const char* path) : m_Path(path) {}

public:
	void SetID(AssetID id) { m_Id = id; }
	AssetID GetID() { return m_Id; }

	void SetPath(const char* path) { m_Path = path; }
	const char* GetPath() { return m_Path; }

	bool IsLoaded() { return m_IsLoaded; }

public:
	virtual bool LoadData() = 0;
	virtual bool UnloadData() = 0;

	unsigned int GetAssetType() { return m_Id >> MaskStart; }
};

template<typename DataType>
class Asset : public AssetBase
{
protected:
	DataType* m_Data = nullptr;

public:
	Asset(const char* path) : AssetBase(path) {}
	
	DataType* GetData() { return m_Data; };
	void ValidateLoad() { m_IsLoaded = (m_Data!=nullptr); }
};

#endif //!ASSETSBODY__H
