#pragma once

#include "prime_defines.h"
#include "prime_assert.h"

namespace prime {

    enum DataType : u8
    {
        DataTypeNone,
        DataTypeInt,
        DataTypeInt2,
        DataTypeInt3,
        DataTypeInt4,
        DataTypeFloat, 
        DataTypeFloat2, 
        DataTypeFloat3, 
        DataTypeFloat4,
        DataTypeMat3, 
        DataTypeMat4,
        DataTypeBool,

        DataTypeMax
    };

	PINLINE u8 GetDataTypeSize(DataType type)
	{
		switch (type)
		{
		case DataTypeInt:
		case DataTypeFloat: {
			return 4;
		}

		case DataTypeInt2:
		case DataTypeFloat2: {
			return 8;
		}

		case DataTypeInt3:
		case DataTypeFloat3: {
			return 12;
		}

		case DataTypeInt4:
		case DataTypeFloat4: {
			return 16;
		}

		case DataTypeMat3:     return 4 * 3 * 3;
		case DataTypeMat4:     return 4 * 4 * 4;
		case DataTypeBool:     return 1;
		}

		PASSERT_MSG(false, "Invalid DataType")
		return 0;
	}

	PINLINE u8 GetDataTypeCount(DataType type)
	{
		switch (type)
		{
		case DataTypeFloat:
		case DataTypeInt:
		case DataTypeBool: {
			return 1;
		}
			
		case DataTypeFloat2:
		case DataTypeInt2: {
			return 2;
		}

		case DataTypeFloat3:
		case DataTypeInt3: {
			return 3;
		}

		case DataTypeFloat4:
		case DataTypeInt4: {
			return 4;
		}

		
		case DataTypeMat3:     return 9;
		case DataTypeMat4:     return 16;
		}

		PASSERT_MSG(false, "Invalid DataType");
		return 0;
	}
}
