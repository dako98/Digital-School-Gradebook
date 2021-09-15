// CombinedClassDlg.cpp : implementation file
//

#include "pch.h"
#include "InternProject1.h"
#include "CombinedClassDlg.h"
#include "afxdialogex.h"
#include "CTeacher.h"
#include "CTeacherDatabaseInterface.h"
#include "CStudentClass.h"


// CombinedClassDlg dialog

IMPLEMENT_DYNAMIC(CombinedClassDlg, CDialog)

CombinedClassDlg::CombinedClassDlg(DialogMode dialogMode, STUDENT_CLASS& data)
	: CDialog(IDD_COMBINED_CLASS, nullptr)
	, m_eDialogMode(dialogMode)
	, m_data(data)
	, m_tmp(m_data)
{

}

BOOL CombinedClassDlg::OnInitDialog()
{
	if (!CDialog::OnInitDialog())
	{
		return FALSE;
	}


	// fill teachers list
	TeacherDatabaseInterface teacherStore(&databaseConnection);
	std::vector<TEACHER> allTeachers;
	if (!teacherStore.LoadAll(allTeachers))
	{
		return FALSE;
	}

	CString currentRow;

	for (const auto& teacher : allTeachers)
	{
		currentRow.Format(_T("%d %s %s"),
			teacher.nID,
			CString{ teacher.szFirstName },
			CString{ teacher.szLastName });

		int index = m_teachersDropdown.AddString(currentRow);
		m_teachersDropdown.SetItemData(index, teacher.nID);
	}

	m_className.SetWindowTextW(m_data.szName);

	switch (m_eDialogMode)
	{
	case eDialogMode_Add:

		m_teachersDropdown.EnableWindow(TRUE);
		m_className.EnableWindow(TRUE);

		break;
	case eDialogMode_Edit:

		m_teachersDropdown.EnableWindow(TRUE);
		m_className.EnableWindow(FALSE);
		m_teachersDropdown.SetCurSel(GetIndexByData(m_data.nTeacherNumber, m_teachersDropdown));


		break;
	case eDialogMode_Remove:
	case eDialogMode_View:

		m_teachersDropdown.EnableWindow(FALSE);
		m_className.EnableWindow(FALSE);
		m_teachersDropdown.SetCurSel(GetIndexByData(m_data.nTeacherNumber, m_teachersDropdown));


		break;
	case eDialogMode_None:
	default:
		throw std::invalid_argument{ "Invalid window state." };
		break;
	}



	return TRUE;
}

CombinedClassDlg::~CombinedClassDlg()
{
}

void CombinedClassDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_COMBINED_CLASS_TEACHERS, m_teachersDropdown);
	DDX_Control(pDX, IDC_EDIT_COMBINED_CLASS_NAME, m_className);
}


BEGIN_MESSAGE_MAP(CombinedClassDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CombinedClassDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CombinedClassDlg message handlers


void CombinedClassDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	UpdateData();

	m_tmp.nTeacherNumber = m_teachersDropdown.GetItemData(m_teachersDropdown.GetCurSel());

	if (m_eDialogMode != DialogMode::eDialogMode_Remove)
	{

		CString buff;

		m_className.GetWindowTextW(buff);

		if (buff.GetLength() <= STUDENT_CLASS::MAX_NAME_SIZE)
		{
			StrCpyW(m_tmp.szName, buff);
		}
		else
		{
			StrCpyW(m_tmp.szName, _T(""));
		}

		if (m_tmp.Validate())
		{
			m_data = m_tmp;
			CDialog::OnOK();
		}
		else
		{
			int errorBox = MessageBox((LPCWSTR)L"Error! Check your input.", NULL, MB_OK | MB_ICONWARNING);
		}
	}
	else
	{
		m_data = m_tmp;
		CDialog::OnOK();
	}
}
