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
	, m_allStudentsListVal(_T(""))
	, m_studentStore(_T("Students"), &databaseConnection)
	, m_teacherStore(_T("Teachers"), &databaseConnection)
{
}

AllStudentsDlg::~AllStudentsDlg()
{
}

BOOL AllStudentsDlg::PrintAll()
{
	m_allStudentsList.ResetContent();

	if (m_studentsRadioBtn.GetCheck() == BST_CHECKED)
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

	isOK = m_studentStore.LoadAll(allStudents);
	if (isOK)
	{
		CString currentRow;

		for (const auto& student : allStudents)
		{
			currentRow.Format(_T("%d %s %s %s"),
				student.nID,
				CString{ student.szFirstName },
				CString{ student.szLastName },
				COleDateTime{ student.dtBirthDate }.Format());

			int index = m_allStudentsList.AddString(currentRow);
			m_allStudentsList.SetItemData(index, student.nID);
		}
	}
	return isOK;
}

BOOL AllStudentsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_studentsRadioBtn.SetCheck(true);

	BOOL isOK = TRUE;

	isOK = PrintAll();

	return isOK;
}

void AllStudentsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, m_allStudentsList);
	DDX_LBString(pDX, IDC_LIST2, m_allStudentsListVal);
	DDX_Control(pDX, IDC_RADIO4, m_studentsRadioBtn);
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
	m_allStudentsList.ResetContent();
	BOOL isOK = PrintAll();

	if (!isOK)
	{
		int errorBox = MessageBox((LPCWSTR)L"Could not load storage.", NULL, MB_OK | MB_ICONWARNING);
		return;
	}
}

void AllStudentsDlg::OnBnClickedRadio5()
{
	m_allStudentsList.ResetContent();
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

	isOK = m_teacherStore.LoadAll(all);

	if (isOK)
	{
		CString currentRow;

		for (const auto& student : all)
		{
			currentRow.Format(_T("%d %s %s"),
				student.nID,
				CString{ student.szFirstName },
				CString{ student.szLastName });

			int index = m_allStudentsList.AddString(currentRow);
			m_allStudentsList.SetItemData(index, student.nID);
		}
	}
	return isOK;
}


void AllStudentsDlg::OnBnClickedButtonEdit()
{
	if (m_allStudentsList.GetCurSel() != LB_ERR)
	{
		BOOL isOK = TRUE;

		if (m_studentsRadioBtn.GetCheck() == BST_CHECKED)
		{
			STUDENT tmp;

			isOK = m_studentStore.Load(m_allStudentsList.GetItemData(m_allStudentsList.GetCurSel()), tmp);
			if (!isOK)
			{
				int errorBox = MessageBox((LPCWSTR)L"Could not load storage.", NULL, MB_OK | MB_ICONWARNING);
				return;
			}

			CombinedStudentDlg dlg{ eDialogMode_Edit, tmp };
			if (dlg.DoModal() == IDOK)
			{
				isOK = m_studentStore.Edit(tmp);
			}
			if (!isOK)
			{
				int errorBox = MessageBox((LPCWSTR)L"Could not load storage.", NULL, MB_OK | MB_ICONWARNING);
				return;
			}

		}
		else
		{
			TEACHER tmp;

			isOK = m_teacherStore.Load(m_allStudentsList.GetItemData(m_allStudentsList.GetCurSel()), tmp);
			if (!isOK)
			{
				int errorBox = MessageBox((LPCWSTR)L"Could not load storage.", NULL, MB_OK | MB_ICONWARNING);
				return;
			}

			CombinedTeacherDlg dlg{ eDialogMode_Edit, tmp };
			if (dlg.DoModal() == IDOK)
			{
				isOK = m_teacherStore.Edit(tmp);
			}
			if (!isOK)
			{
				int errorBox = MessageBox((LPCWSTR)L"Could not load storage.", NULL, MB_OK | MB_ICONWARNING);
				return;
			}
		}

		PrintAll();
	}
}


void AllStudentsDlg::OnBnClickedButtonAdd()
{
	BOOL isOK = TRUE;
	if (m_studentsRadioBtn.GetCheck() == BST_CHECKED)
	{
		STUDENT tmp;

		CombinedStudentDlg dlg{ eDialogMode_Add, tmp };
		if (dlg.DoModal() == IDOK)
		{
			isOK = m_studentStore.Add(tmp);
		}
		if (!isOK)
		{
			int errorBox = MessageBox((LPCWSTR)L"Could not load storage.", NULL, MB_OK | MB_ICONWARNING);
			return;
		}
	}
	else
	{
		TEACHER tmp;

		CombinedTeacherDlg dlg{ eDialogMode_Add, tmp };
		if (dlg.DoModal() == IDOK)
		{
			isOK = m_teacherStore.Add(tmp);
		}
		if (!isOK)
		{
			int errorBox = MessageBox((LPCWSTR)L"Could not load storage.", NULL, MB_OK | MB_ICONWARNING);
			return;
		}
	}

	PrintAll();
}


void AllStudentsDlg::OnBnClickedButtonRemove()
{
	if (m_allStudentsList.GetCurSel() != LB_ERR)
	{
		BOOL isOK = TRUE;

		if (m_studentsRadioBtn.GetCheck() == BST_CHECKED)
		{
			STUDENT tmp;

			isOK = m_studentStore.Load(m_allStudentsList.GetItemData(m_allStudentsList.GetCurSel()), tmp);
			if (!isOK)
			{
				int errorBox = MessageBox((LPCWSTR)L"Could not load storage.", NULL, MB_OK | MB_ICONWARNING);
				return;
			}

			CombinedStudentDlg dlg{ eDialogMode_Remove, tmp };
			if (dlg.DoModal() == IDOK)
			{
				isOK = m_studentStore.Delete(tmp.nID);
			}
			if (!isOK)
			{
				int errorBox = MessageBox((LPCWSTR)L"Could not load storage.", NULL, MB_OK | MB_ICONWARNING);
				return;
			}
		}
		else
		{
			TEACHER tmp;

			isOK = m_teacherStore.Load(m_allStudentsList.GetItemData(m_allStudentsList.GetCurSel()), tmp);
			if (!isOK)
			{
				int errorBox = MessageBox((LPCWSTR)L"Could not load storage.", NULL, MB_OK | MB_ICONWARNING);
				return;
			}

			CombinedTeacherDlg dlg{ eDialogMode_Remove, tmp };
			if (dlg.DoModal() == IDOK)
			{
				isOK = m_teacherStore.Delete(tmp.nID);
			}
			if (!isOK)
			{
				int errorBox = MessageBox((LPCWSTR)L"Could not load storage.", NULL, MB_OK | MB_ICONWARNING);
				return;
			}
		}
		PrintAll();
	}
}
