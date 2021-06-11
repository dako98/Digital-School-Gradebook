#include "pch.h"
#include "Utility.h"

int GetIndexByData(const int target, const CComboBox& comboBox)
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

void populateList(CComboBox& list, const std::vector<Teacher>& src)
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

void populateList(CComboBox& list, const std::vector<Student>& src)
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