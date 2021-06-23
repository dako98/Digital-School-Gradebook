// AllStudentsDlg.cpp : implementation file
//

#include "pch.h"
#include "InternProject1.h"
#include "AllStudentsDlg.h"
#include "afxdialogex.h"

#include "CombinedStudentDlg.h"
#include "CombinedTeacherDlg.h"

#include "CStudent.h"
#include "CTeacher.h"
#include "Storage.h"
#include "Utility.h"


// AllStudentsDlg dialog

IMPLEMENT_DYNAMIC(AllStudentsDlg, CDialog)

AllStudentsDlg::AllStudentsDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_ALL_STUDENTS, pParent)
	, allStudentsListVal(_T(""))
{
}

AllStudentsDlg::~AllStudentsDlg()
{
}

BOOL AllStudentsDlg::PrintAll()
{
	allStudentsList.ResetContent();

	if (studentsRadioBtn.GetCheck() == BST_CHECKED)
	{
		return PrintAllStudents();
	}
	else
	{
		return PrintAllTeachers();
	}
}

BOOL AllStudentsDlg::PrintAllStudents()
{
	BOOL isOK;

	std::vector<STUDENT> allStudents;
	Storage<STUDENT> st(studentsPath);
	isOK = st.LoadAll(allStudents);

	if (isOK)
	{
		CString currentRow;

		for (const auto& student : allStudents)
		{
			currentRow.Format(_T("%d %s %s %s"),
				student.nID,
				CString{ student.szFirstName },
				CString{ student.szLastName },
				COleDateTime(student.dtBirthDate).Format());

			int index = allStudentsList.AddString(currentRow);
			allStudentsList.SetItemData(index, student.nID);
		}
	}
	return isOK;
}

BOOL AllStudentsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	studentsRadioBtn.SetCheck(true);

	PrintAll();

	return 0;
}

void AllStudentsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, allStudentsList);
	DDX_LBString(pDX, IDC_LIST2, allStudentsListVal);
	DDX_Control(pDX, IDC_RADIO4, studentsRadioBtn);
}


BEGIN_MESSAGE_MAP(AllStudentsDlg, CDialog)
	ON_BN_CLICKED(IDC_RADIO4, &AllStudentsDlg::OnBnClickedRadio4)
	ON_BN_CLICKED(IDC_RADIO5, &AllStudentsDlg::OnBnClickedRadio5)
	ON_BN_CLICKED(IDC_BUTTON1, &AllStudentsDlg::OnBnClickedButtonEdit)
	ON_BN_CLICKED(IDC_BUTTON3, &AllStudentsDlg::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON2, &AllStudentsDlg::OnBnClickedButtonRemove)
END_MESSAGE_MAP()


// AllStudentsDlg message handlers


void AllStudentsDlg::OnBnClickedRadio4()
{
	allStudentsList.ResetContent();
	BOOL isOK = PrintAll();

	if (!isOK)
	{
		int errorBox = MessageBox((LPCWSTR)L"Could not load storage.", NULL, MB_OK | MB_ICONWARNING);
		return;
	}
}

void AllStudentsDlg::OnBnClickedRadio5()
{
	allStudentsList.ResetContent();
	BOOL isOK = PrintAll();
	
	if (!isOK)
	{
		int errorBox = MessageBox((LPCWSTR)L"Could not load storage.", NULL, MB_OK | MB_ICONWARNING);
		return;
	}
}

BOOL AllStudentsDlg::PrintAllTeachers()
{
	BOOL isOK;

	std::vector<TEACHER> all;
	Storage<TEACHER> st{ teachersPath };
	isOK = st.LoadAll(all);

	if (isOK)
	{
		CString currentRow;

		for (const auto& student : all)
		{
			currentRow.Format(_T("%d %s %s"),
				student.nID,
				CString{ student.szFirstName },
				CString{ student.szLastName });

			int index = allStudentsList.AddString(currentRow);
			allStudentsList.SetItemData(index, student.nID);
		}
	}
	return isOK;
}


void AllStudentsDlg::OnBnClickedButtonEdit()
{
	if (allStudentsList.GetCurSel() != LB_ERR)
	{
		BOOL isOK = TRUE;

		if (studentsRadioBtn.GetCheck() == BST_CHECKED)
		{
			STUDENT tmp;
			Storage<STUDENT> studentStore{ studentsPath };

			isOK = studentStore.Load(allStudentsList.GetItemData(allStudentsList.GetCurSel()), tmp);

			if (!isOK)
			{
				int errorBox = MessageBox((LPCWSTR)L"Could not load storage.", NULL, MB_OK | MB_ICONWARNING);
				return;
			}

			CombinedStudentDlg dlg{ eDialogMode_Edit, tmp };
			dlg.DoModal();
		}
		else
		{
			TEACHER tmp;
			Storage<TEACHER> store{ teachersPath };

			isOK = store.Load(allStudentsList.GetItemData(allStudentsList.GetCurSel()), tmp);

			if (!isOK)
			{
				int errorBox = MessageBox((LPCWSTR)L"Could not load storage.", NULL, MB_OK | MB_ICONWARNING);
				return;
			}

			CombinedTeacherDlg dlg{ eDialogMode_Edit, tmp };
			dlg.DoModal();
		}

		PrintAll();
	}
}


void AllStudentsDlg::OnBnClickedButtonAdd()
{
	BOOL isOK = TRUE;
	if (studentsRadioBtn.GetCheck() == BST_CHECKED)
	{
		STUDENT tmp;
		Storage<STUDENT> store{ studentsPath };

//		tmp.nID = store.LastID() + 1;
		isOK = store.NextID(tmp.nID);

		if (!isOK)
		{
			int errorBox = MessageBox((LPCWSTR)L"Could not load storage.", NULL, MB_OK | MB_ICONWARNING);
			return;
		}

		CombinedStudentDlg dlg{ eDialogMode_Add, tmp };
		dlg.DoModal();
	}
	else
	{
		TEACHER tmp;
		Storage<TEACHER> store{ teachersPath };

//		tmp.nID = store.LastID() + 1;
		isOK = store.NextID(tmp.nID);

		if (!isOK)
		{
			int errorBox = MessageBox((LPCWSTR)L"Could not load storage.", NULL, MB_OK | MB_ICONWARNING);
			return;
		}

		CombinedTeacherDlg dlg{ eDialogMode_Add, tmp };
		dlg.DoModal();
	}

	PrintAll();
}


void AllStudentsDlg::OnBnClickedButtonRemove()
{
	if (allStudentsList.GetCurSel() != LB_ERR)
	{
		BOOL isOK = TRUE;

		if (studentsRadioBtn.GetCheck() == BST_CHECKED)
		{
			STUDENT tmp;
			Storage<STUDENT> studentStore{ studentsPath };

			isOK = studentStore.Load(allStudentsList.GetItemData(allStudentsList.GetCurSel()), tmp);

			if (!isOK)
			{
				int errorBox = MessageBox((LPCWSTR)L"Could not load storage.", NULL, MB_OK | MB_ICONWARNING);
				return;
			}

			CombinedStudentDlg dlg{ eDialogMode_Remove, tmp };
			dlg.DoModal();
		}
		else
		{
			TEACHER tmp;
			Storage<TEACHER> store(teachersPath);

			isOK = store.Load(allStudentsList.GetItemData(allStudentsList.GetCurSel()), tmp);

			if (!isOK)
			{
				int errorBox = MessageBox((LPCWSTR)L"Could not load storage.", NULL, MB_OK | MB_ICONWARNING);
				return;
			}

			CombinedTeacherDlg dlg{ eDialogMode_Remove, tmp };
			dlg.DoModal();
		}
		PrintAll();
	}
}
