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
	, m_studentStore(&databaseConnection)
	, m_teacherStore(&databaseConnection)
{
}

AllStudentsDlg::~AllStudentsDlg()
{
}

BOOL AllStudentsDlg::PrintAll()
{
	m_allStudentsList.ResetContent();

	if (m_rbnStudents.GetCheck() == BST_CHECKED)
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
	std::vector<STUDENT> allStudents;

	if (!m_studentStore.LoadAll(allStudents))
	{
		return FALSE;
	}

	CString currentRow;

	for (const auto& student : allStudents)
	{
		currentRow.Format(_T("%d %s %s %s"),
			student.nID,
			CString{ student.szFirstName },
			CString{ student.szLastName },
			COleDateTime{ student.dtBirthDate.year,
			student.dtBirthDate.month,
			student.dtBirthDate.day,
			0,0,0 }.Format());

		int index = m_allStudentsList.AddString(currentRow);
		m_allStudentsList.SetItemData(index, student.nID);
	}

	return TRUE;
}

BOOL AllStudentsDlg::OnInitDialog()
{
	if (!CDialog::OnInitDialog())
	{
		return FALSE;
	}

	m_rbnStudents.SetCheck(true);

	return PrintAll();
}

void AllStudentsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, m_allStudentsList);
	DDX_LBString(pDX, IDC_LIST2, m_allStudentsListVal);
	DDX_Control(pDX, IDC_RADIO4, m_rbnStudents);
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
	
	if (!PrintAll())
	{
		int errorBox = MessageBox((LPCWSTR)L"Could not load storage.", NULL, MB_OK | MB_ICONWARNING);
		return;
	}
}

void AllStudentsDlg::OnBnClickedRadio5()
{
	m_allStudentsList.ResetContent();
	
	if (!PrintAll())
	{
		int errorBox = MessageBox((LPCWSTR)L"Could not load storage.", NULL, MB_OK | MB_ICONWARNING);
		return;
	}
}

BOOL AllStudentsDlg::PrintAllTeachers()
{
	std::vector<TEACHER> all;

	if (!m_teacherStore.LoadAll(all))
		return FALSE;

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

	return TRUE;
}


void AllStudentsDlg::OnBnClickedButtonEdit()
{
	if (m_allStudentsList.GetCurSel() == LB_ERR)
	{
		return;
	}

	if (m_rbnStudents.GetCheck() == BST_CHECKED)
	{
		STUDENT tmp;

		if (!m_studentStore.Load(m_allStudentsList.GetItemData(m_allStudentsList.GetCurSel()), tmp))
		{
			int errorBox = MessageBox((LPCWSTR)L"Could not load storage.", NULL, MB_OK | MB_ICONWARNING);
			return;
		}

		CombinedStudentDlg dlg{ eDialogMode_Edit, tmp };
		if (dlg.DoModal() == IDOK)
		{
			if (!m_studentStore.Edit(tmp))
			{
				int errorBox = MessageBox((LPCWSTR)L"Could not load storage.", NULL, MB_OK | MB_ICONWARNING);
				return;
			}
		}

	}
	else
	{
		TEACHER tmp;

		if (!m_teacherStore.Load(m_allStudentsList.GetItemData(m_allStudentsList.GetCurSel()), tmp))
		{
			int errorBox = MessageBox((LPCWSTR)L"Could not load storage.", NULL, MB_OK | MB_ICONWARNING);
			return;
		}

		CombinedTeacherDlg dlg{ eDialogMode_Edit, tmp };
		if (dlg.DoModal() == IDOK)
		{
			if (!m_teacherStore.Edit(tmp))
			{
				int errorBox = MessageBox((LPCWSTR)L"Could not load storage.", NULL, MB_OK | MB_ICONWARNING);
				return;
			}
		}
	}

	PrintAll();
}



void AllStudentsDlg::OnBnClickedButtonAdd()
{

	if (m_rbnStudents.GetCheck() == BST_CHECKED)
	{
		STUDENT tmp;

		CombinedStudentDlg dlg{ eDialogMode_Add, tmp };
		if (dlg.DoModal() == IDOK)
		{
			if (!m_studentStore.Add(tmp))
			{
				int errorBox = MessageBox((LPCWSTR)L"Could not load storage.", NULL, MB_OK | MB_ICONWARNING);
				return;
			}
		}
	}
	else
	{
		TEACHER tmp;

		CombinedTeacherDlg dlg{ eDialogMode_Add, tmp };
		if (dlg.DoModal() == IDOK)
		{
			if (!m_teacherStore.Add(tmp))
			{
				int errorBox = MessageBox((LPCWSTR)L"Could not load storage.", NULL, MB_OK | MB_ICONWARNING);
				return;
			}
		}
	}

	PrintAll();
}

// @done ѕромених и на другите места и isOK стана излишно.
void AllStudentsDlg::OnBnClickedButtonRemove()
{
	if (m_allStudentsList.GetCurSel() != LB_ERR)
	{
		if (m_rbnStudents.GetCheck() == BST_CHECKED)
		{
			STUDENT tmp;

			if (!m_studentStore.Load(m_allStudentsList.GetItemData(m_allStudentsList.GetCurSel()), tmp))
			{
				int errorBox = MessageBox((LPCWSTR)L"Could not load storage.", NULL, MB_OK | MB_ICONWARNING);
				return;
			}

			CombinedStudentDlg dlg{ eDialogMode_Remove, tmp };
			if (dlg.DoModal() == IDOK)
			{
				if (!m_studentStore.Delete(tmp.nID))
				{
					int errorBox = MessageBox((LPCWSTR)L"Could not load storage.", NULL, MB_OK | MB_ICONWARNING);
					return;
				}
			}
		}
		else
		{
			TEACHER tmp;

			if (!m_teacherStore.Load(m_allStudentsList.GetItemData(m_allStudentsList.GetCurSel()), tmp))
			{
				int errorBox = MessageBox((LPCWSTR)L"Could not load storage.", NULL, MB_OK | MB_ICONWARNING);
				return;
			}

			CombinedTeacherDlg dlg{ eDialogMode_Remove, tmp };
			if (dlg.DoModal() == IDOK)
			{
				if (!m_teacherStore.Delete(tmp.nID))
				{
					int errorBox = MessageBox((LPCWSTR)L"Could not load storage.", NULL, MB_OK | MB_ICONWARNING);
					return;
				}
			}
		}
		PrintAll();
	}
}