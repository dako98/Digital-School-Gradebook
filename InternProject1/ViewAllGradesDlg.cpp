// ViewAllGradesDlg.cpp : implementation file
//

#include "pch.h"
#include "InternProject1.h"
#include "ViewAllGradesDlg.h"
#include "afxdialogex.h"

#include <vector>
#include <unordered_map>

#include "CombinedGradeDlg.h"

#include "CGrade.h"
#include "CStudent.h"
#include "CSubject.h"
#include "Storage.h"
#include "Utility.h"


// ViewAllGradesDlg dialog

IMPLEMENT_DYNAMIC(ViewAllGradesDlg, CDialog)

ViewAllGradesDlg::ViewAllGradesDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_ALL_GRADES, pParent)
	, m_gradeStore(_T("Grades"), &databaseConnection)
	, m_studentStore(_T("Students"), &databaseConnection)
	, m_subjectStore(_T("Subjects"), &databaseConnection)
{

}

BOOL ViewAllGradesDlg::OnInitDialog()
{
	if (!CDialog::OnInitDialog())
		return FALSE;

	BOOL isOK = TRUE;

	isOK = PrintAllGrades();

	return isOK;
}

ViewAllGradesDlg::~ViewAllGradesDlg()
{
}

BOOL ViewAllGradesDlg::PrintAllGrades()
{
	m_gradesList.ResetContent();

	BOOL isOK;

	std::vector<GRADE> allGrades;
	std::vector<STUDENT> allStudents;
	std::vector<SUBJECT> allSubjects;

//	Storage<GRADE> gr{ gradesPath };
//	Storage<STUDENT> st{ studentsPath };
//	Storage<SUBJECT> su{ subjectsPath };

	isOK = m_gradeStore.LoadAll(allGrades);

	if (isOK)
	{
		isOK = m_studentStore.LoadAll(allStudents);

		if (isOK)
		{
			m_subjectStore.LoadAll(allSubjects);
		}
	}

	if (isOK)
	{
		std::unordered_map<int, std::pair<CString, CString>> studentNameMap;
		std::unordered_map<int, CString> subjectNameMap;

		for (const auto& student : allStudents)
		{
			studentNameMap[student.nID] = std::make_pair<CString, CString>(CString{ student.szFirstName }, CString{ student.szLastName });
		}
		for (const auto& subject : allSubjects)
		{
			subjectNameMap[subject.nID] = CString{ subject.szName };
		}

		CString currentRow;

		for (const auto& grade : allGrades)
		{
			currentRow.Format(_T("%d %s %s %s"),
				grade.nID,
				studentNameMap[grade.nStudentID].first,
				subjectNameMap[grade.nSubjectID],
				MapGradeName(grade.value));

			int index = m_gradesList.AddString(currentRow);
			m_gradesList.SetItemData(index, grade.nID);
		}
	}

	return isOK;
}

void ViewAllGradesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GRADES_LIST, m_gradesList);
}


BEGIN_MESSAGE_MAP(ViewAllGradesDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &ViewAllGradesDlg::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON2, &ViewAllGradesDlg::OnBnClickedButtonEdit)
	ON_BN_CLICKED(IDC_BUTTON3, &ViewAllGradesDlg::OnBnClickedButtonRemove)
END_MESSAGE_MAP()


// ViewAllGradesDlg message handlers


void ViewAllGradesDlg::OnBnClickedButtonAdd()
{
	GRADE tmp;
//	Storage<GRADE> store{ gradesPath };
	BOOL isOK = TRUE;

//	isOK = gradeStore->NextID(tmp.nID);


	CombinedGradeDlg dlg{ eDialogMode_Add, tmp };
	if (dlg.DoModal() == IDOK)
	{
		isOK = m_gradeStore.Add(tmp);
	}
	if (!isOK)
	{
		int errorBox = MessageBox((LPCWSTR)L"Could not load storage.", NULL, MB_OK | MB_ICONWARNING);
		return;
	}

	PrintAllGrades();
}


void ViewAllGradesDlg::OnBnClickedButtonEdit()
{
	if (m_gradesList.GetCurSel() != LB_ERR)
	{
		BOOL isOK = TRUE;

		GRADE tmp;
//		Storage<GRADE> studentStore{ gradesPath };
		tmp.nID = m_gradesList.GetItemData(m_gradesList.GetCurSel());

		isOK = m_gradeStore.Load(tmp.nID, tmp);
		if (!isOK)
		{
			int errorBox = MessageBox((LPCWSTR)L"Could not load storage.", NULL, MB_OK | MB_ICONWARNING);
			return;
		}

		CombinedGradeDlg dlg{ eDialogMode_Edit, tmp };
		if (dlg.DoModal() == IDOK)
		{
			isOK = m_gradeStore.Edit(tmp);
		}
		if (!isOK)
		{
			int errorBox = MessageBox((LPCWSTR)L"Could not load storage.", NULL, MB_OK | MB_ICONWARNING);
			return;
		}

		PrintAllGrades();
	}
}


void ViewAllGradesDlg::OnBnClickedButtonRemove()
{
	if (m_gradesList.GetCurSel() != LB_ERR)
	{
		BOOL isOK = TRUE;

		GRADE tmp;
//		Storage<GRADE> studentStore{ gradesPath };
		tmp.nID = m_gradesList.GetItemData(m_gradesList.GetCurSel());

		isOK = m_gradeStore.Load(tmp.nID, tmp);
		if (!isOK)
		{
			int errorBox = MessageBox((LPCWSTR)L"Could not load storage.", NULL, MB_OK | MB_ICONWARNING);
			return;
		}

		CombinedGradeDlg dlg{ eDialogMode_Remove, tmp };
		if (dlg.DoModal() == IDOK)
		{
			isOK = m_gradeStore.Delete(tmp.nID);
		}
		if (!isOK)
		{
			int errorBox = MessageBox((LPCWSTR)L"Could not load storage.", NULL, MB_OK | MB_ICONWARNING);
			return;
		}

		PrintAllGrades();
	}
}
