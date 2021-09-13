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
extern unsigned short   DigitsCount(INT32 x) noexcept;

template <class T>
extern unsigned int     DigitsCount(T number, unsigned short radix);

template <class T, class U>
void XOR(T& A, const U& B) noexcept(sizeof(A) == sizeof(B) && sizeof(A) % sizeof(unsigned char) == 0)
{
	unsigned char* pA = (unsigned char*)(&A);
	const unsigned char* const pLast = pA + 1;
	unsigned char* pB = (unsigned char*)(&B);

	while (pA < pLast)
	{
		*pA++ ^= *pB++;
	}
}

template <class T, class U>
void* XOR2(T& A, U& B) noexcept(sizeof(A) == sizeof(B))
{
	XOR(A, B);
	std::memcpy(&B, &A, max(sizeof(A), sizeof(B)));
	return &A;
}

template <class T>
void Clear(T& st) noexcept
{
	XOR(st, st);
//	SecureZeroMemory(&st, sizeof(st));
}