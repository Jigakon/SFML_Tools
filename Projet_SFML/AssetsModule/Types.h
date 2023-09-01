#ifndef ASSETSTYPES__H
#define ASSETSTYPES__H

#define ReservedBitsForAssetMask 3
#define TotalBitsOfUINT 31

#define MaskStart (TotalBitsOfUINT - ReservedBitsForAssetMask)

using AssetID = unsigned int;

#endif //!ASSETSTYPES__H
