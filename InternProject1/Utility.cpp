#include "pch.h"
#include "Utility.h"
#include <algorithm>
#include "CGrade.h"
#include <limits>

const char* const databaseConnectionString = "Driver={ODBC Driver 17 for SQL Server}; Server=(localdb)\\MSSQLLocalDB; Database=Test1;";

inline int GetIndexByData(const int target, const CComboBox& comboBox)
{
	int result = CB_ERR;
	int length = comboBox.GetCount();

	for (int i = 0; i < length; i++)
	{
		if (comboBox.GetItemData(i) == target)
		{
			result = i;
			break;
		}
	}

	return result;
}

inline int GetIndexByData(const int target, const CListBox& listBox)
{
	int result = LB_ERR;
	int length = listBox.GetCount();

	for (int i = 0; i < length; i++)
	{
		if (listBox.GetItemData(i) == target)
		{
			result = i;
			break;
		}
	}

	return result;
}

CString MapGradeName(const int value)
{
	CString name;

	switch (value)
	{
	case GRADE::GRADES::A:	name = "Excellent";	break;
	case GRADE::GRADES::B:	name = "Very good";	break;
	case GRADE::GRADES::C:	name = "Good";		break;
	case GRADE::GRADES::D:	name = "Average";	break;
	case GRADE::GRADES::F:	name = "Bad";		break;

	default:
		name = "";
		ASSERT(false && "Invalid grade.");
		break;
	}

	return name;
}

inline unsigned short DigitsCount(INT32 x)
{
    /**
    * Source: https://stackoverflow.com/questions/1489830/efficient-way-to-determine-number-of-digits-in-an-integer
    */
 
    if (x == INT32_MAX) return 10 + 1;
    if (x < 0) return DigitsCount(-x) + 1;

    if (x >= 10000) {
        if (x >= 10000000) {
            if (x >= 100000000) {
                if (x >= 1000000000)
                    return 10;
                return 9;
            }
            return 8;
        }
        if (x >= 100000) {
            if (x >= 1000000)
                return 7;
            return 6;
        }
        return 5;
    }
    if (x >= 100) {
        if (x >= 1000)
            return 4;
        return 3;
    }
    if (x >= 10)
        return 2;
    return 1;
}

template <class T>
unsigned int DigitsCount(T number, unsigned short radix = 10)
{
	assert(radix > 2, "Only positive radixes greater than 1 are supported.");

	unsigned int digits = 1;
	while (number /= radix)
	{
		++digits;
	}

	return digits;
}
