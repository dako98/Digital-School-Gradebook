#pragma once

extern const char* const databaseConnectionString;

enum DialogMode
{
	eDialogMode_None = 0,

	eDialogMode_Add,
	eDialogMode_Edit,
	eDialogMode_Remove,
	eDialogMode_View
};

extern int		        GetIndexByData(const int target, const CComboBox& comboBox);
extern int              GetIndexByData(const int target, const CListBox& listBox);
extern CString	        MapGradeName(const int value);
extern unsigned short   DigitsCount(INT32 x);

template <class T>
extern unsigned int     DigitsCount(T number, unsigned short radix);
