#pragma once

#include <vector>
#include "Teacher.h"
#include "Student.h"
#include "CGrade.h"

static int GetIndexByData(const int target, const CComboBox& comboBox)
{
	int result = CB_ERR;
	int length = comboBox.GetCount();

	for (size_t i = 0; i < length; i++)
	{
		if (comboBox.GetItemData(i) == target)
		{
			result = i;
			break;
		}
	}

	return result;
}

static void populateList(CComboBox& list, const std::vector<Teacher>& src)
{
	list.ResetContent();
	CString currentRow;

	int index = 0;
	for (const Teacher& teacher : src)
	{
		currentRow.Format(_T("%d %s"), teacher.GetID(), teacher.getName());

		int i = list.AddString(currentRow);
		list.SetItemData(i, index);
		index++;
	}
	if (src.size() > 0)
	{
		list.SetCurSel(0);
	}
}

static void populateList(CComboBox& list, const std::vector<Student>& src)
{
	list.ResetContent();
	CString currentRow;

	int index = 0;
	for (const Student& student : src)
	{
		currentRow.Format(_T("%d %s"), student.GetNumber(), student.getName());

		int i = list.AddString(currentRow);
		list.SetItemData(i, index);
		index++;
	}
	if (src.size() > 0)
	{
		list.SetCurSel(0);
	}
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