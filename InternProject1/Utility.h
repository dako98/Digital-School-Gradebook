#pragma once

#include <vector>
#include "CGrade.h"

static int GetIndexByData(const int target, const CComboBox& comboBox)
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

enum DialogMode
{
	eDialogMode_None = 0,
	eDialogMode_Add,
	eDialogMode_Edit,
	eDialogMode_Remove,
	eDialogMode_View
};

static const char* const studentsPath	=	"Students.txt";
static const char* const teachersPath	=	"Teachers.txt";
static const char* const subjectsPath	=	"Subjects.txt";
static const char* const gradesPath		=	"Grades.txt";

static CString MapGradeName(const int value)
{
	CString name;

	switch (value)
	{
	case GRADE::GRADES::A:		name = "Excellent";
		break;
	case GRADE::GRADES::B:		name = "Very good";
		break;
	case GRADE::GRADES::C:		name = "Good";
		break;
	case GRADE::GRADES::D:		name = "Average";
		break;
	case GRADE::GRADES::F:		name = "Bad";
		break;

	default:
		name = "";
		break;
	}

	return name;
}