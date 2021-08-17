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

ViewAllGradesDlg::ViewAllGradesDlg(CWnd* pParent)
	: CDialog(IDD_ALL_GRADES_DLG, pParent)
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
	GradeDatabaseInterface		gradeStore	{ &databaseConnection };
	StudentDatabaseInterface	studentStore{ &databaseConnection };
	SubjectDatabaseInterface	subjectStore{ &databaseConnection };

	isOK = gradeStore.LoadAll(allGrades);

	if (isOK)
	{
		isOK = studentStore.LoadAll(allStudents);

		if (isOK)
		{
			subjectStore.LoadAll(allSubjects);
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
	DDX_Control(pDX, IDC_LIST1, m_lsGrades);
}


BEGIN_MESSAGE_MAP(ViewAllGradesDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &ViewAllGradesDlg::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON2, &ViewAllGradesDlg::OnBnClickedButtonEdit)
	ON_BN_CLICKED(IDC_BUTTON3, &ViewAllGradesDlg::OnBnClickedButtonRemove)
	ON_WM_CONTEXTMENU()
END_MESSAGE_MAP()


// ViewAllGradesDlg message handlers


void ViewAllGradesDlg::OnBnClickedButtonAdd()
{
	GRADE tmp;
	DBTIMESTAMP now;
	COleDateTime::GetCurrentTime().GetAsDBTIMESTAMP(now);
	tmp.dtDate.year		= now.year;
	tmp.dtDate.month	= now.month;
	tmp.dtDate.day		= now.day;
	tmp.dtDate.hour		= now.hour;
	tmp.dtDate.minute	= now.minute;
	tmp.dtDate.second	= now.second;

	BOOL isOK = TRUE;
	GradeDatabaseInterface		gradeStore{ &databaseConnection };

	CombinedGradeDlg dlg{ eDialogMode_Add, tmp };
	if (dlg.DoModal() == IDOK)
	{
		isOK = gradeStore.Add(tmp);
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
		tmp.nID = m_gradesList.GetItemData(m_gradesList.GetCurSel());
		GradeDatabaseInterface		gradeStore{ &databaseConnection };

		isOK = gradeStore.Load(tmp.nID, tmp);
		if (!isOK)
		{
			int errorBox = MessageBox((LPCWSTR)L"Could not load storage.", NULL, MB_OK | MB_ICONWARNING);
			return;
		}

		CombinedGradeDlg dlg{ eDialogMode_Edit, tmp };
		if (dlg.DoModal() == IDOK)
		{
			isOK = gradeStore.Edit(tmp);
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
		tmp.nID = m_gradesList.GetItemData(m_gradesList.GetCurSel());
		GradeDatabaseInterface		gradeStore{ &databaseConnection };

		isOK = gradeStore.Load(tmp.nID, tmp);
		if (!isOK)
		{
			int errorBox = MessageBox((LPCWSTR)L"Could not load storage.", NULL, MB_OK | MB_ICONWARNING);
			return;
		}

		CombinedGradeDlg dlg{ eDialogMode_Remove, tmp };
		if (dlg.DoModal() == IDOK)
		{
			isOK = gradeStore.Delete(tmp.nID);
		}
		if (!isOK)
		{
			int errorBox = MessageBox((LPCWSTR)L"Could not load storage.", NULL, MB_OK | MB_ICONWARNING);
			return;
		}

		PrintAllGrades();
	}
}


void ViewAllGradesDlg::OnContextMenu(CWnd* pWnd, CPoint point)
{
	// TODO: Add your message handler code here
	if ((point.x == -1) && (point.y == -1))
	{
		// Keystroke invocation
		CRect rect;

		GetClientRect(rect);
		ClientToScreen(rect);

		point = rect.TopLeft();
		point.Offset(5, 5);
	}

	CMenu menu;
	VERIFY(menu.LoadMenu(IDR_SUBJECT));

	CMenu* pPopup = menu.GetSubMenu(0);
	ASSERT(pPopup != NULL);
	CWnd* pWndPopupOwner = this;

	while (pWndPopupOwner->GetStyle() & WS_CHILD)
		pWndPopupOwner = pWndPopupOwner->GetParent();

	int response = pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON | TPM_RETURNCMD,
		point.x,
		point.y,
		pWndPopupOwner);

	switch (response)
	{

	case ID_POPUP_ADD:
		OnBnClickedButtonAdd();
		break;

	case ID_POPUP_EDIT:
		OnBnClickedButtonEdit();
		break;

	case ID_POPUP_DELETE:
		OnBnClickedButtonRemove();
		break;

	case ID_POPUP_VIEW:
	{
		if (m_gradesList.GetCurSel() != LB_ERR)
		{
			GRADE tmp;
			BOOL isOK = TRUE;
			GradeDatabaseInterface		gradeStore{ &databaseConnection };

			isOK = gradeStore.Load(m_gradesList.GetItemData(m_gradesList.GetCurSel()), tmp);
			if (!isOK)
			{
				int errorBox = MessageBox((LPCWSTR)L"Could not load storage.", NULL, MB_OK | MB_ICONWARNING);
				return;
			}
			CombinedGradeDlg dlg{ eDialogMode_View, tmp };
			dlg.DoModal();
		}
	}
	break;
	default:
		break;
	}
}
