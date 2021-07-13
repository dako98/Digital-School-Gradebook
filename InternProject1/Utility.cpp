#include "pch.h"
#include "Utility.h"
#include <algorithm>
#include "CGrade.h"

int GetIndexByData(const int target, const CComboBox& comboBox)
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