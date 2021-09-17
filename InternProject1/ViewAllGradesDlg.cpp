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
	{
		return FALSE;
	}

	if (!PrintAllGrades())
	{
		return FALSE;
	}

	return TRUE;
}

ViewAllGradesDlg::~ViewAllGradesDlg()
{
}

BOOL ViewAllGradesDlg::PrintAllGrades()
{
	m_lsGrades.ResetContent();

	std::vector<GRADE>		allGrades;
	std::vector<STUDENT>	allStudents;
	std::vector<SUBJECT>	allSubjects;
	GradeDatabaseInterface		gradeStore{ &databaseConnection };
	StudentDatabaseInterface	studentStore{ &databaseConnection };
	SubjectDatabaseInterface	subjectStore{ &databaseConnection };

	if (!gradeStore.LoadAll(allGrades))
	{
		return FALSE;
	}

	if (!studentStore.LoadAll(allStudents))
	{
		return FALSE;
	}

	if (!subjectStore.LoadAll(allSubjects))
	{
		return FALSE;
	}

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

		int index = m_lsGrades.AddString(currentRow);
		m_lsGrades.SetItemData(index, grade.nID);
	}

	return TRUE;
}

void ViewAllGradesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_GRADES_LIST, m_lsGrades);
//	DDX_Control(pDX, IDC_LIST1, m_lsGrades);
}


BEGIN_MESSAGE_MAP(ViewAllGradesDlg, CDialog)
	ON_BN_CLICKED(IDC_BTN_GRADES_ADD,		&ViewAllGradesDlg::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BTN_GRADES_EDIT,		&ViewAllGradesDlg::OnBnClickedButtonEdit)
	ON_BN_CLICKED(IDC_BTN_GRADES_REMOVE,	&ViewAllGradesDlg::OnBnClickedButtonRemove)
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

	GradeDatabaseInterface		gradeStore{ &databaseConnection };

	CombinedGradeDlg dlg{ eDialogMode_Add, tmp };
	if (dlg.DoModal() == IDOK)
	{
		if (!gradeStore.Add(tmp))
		{
			int errorBox = MessageBox((LPCWSTR)L"Could not load storage.", NULL, MB_OK | MB_ICONWARNING);
			return;
		}
		PrintAllGrades();
	}
}


void ViewAllGradesDlg::OnBnClickedButtonEdit()
{
	if (m_lsGrades.GetCurSel() == LB_ERR)
	{
		return;
	}

		GRADE tmp;
		tmp.nID = m_lsGrades.GetItemData(m_lsGrades.GetCurSel());
		GradeDatabaseInterface		gradeStore{ &databaseConnection };

		if (!gradeStore.Load(tmp.nID, tmp))
		{
			int errorBox = MessageBox((LPCWSTR)L"Could not load storage.", NULL, MB_OK | MB_ICONWARNING);
			return;
		}

		CombinedGradeDlg dlg{ eDialogMode_Edit, tmp };
		if (dlg.DoModal() == IDOK)
		{
			if (!gradeStore.Edit(tmp))
			{
				int errorBox = MessageBox((LPCWSTR)L"Could not load storage.", NULL, MB_OK | MB_ICONWARNING);
				return;
			}

			PrintAllGrades();
		}
	}


void ViewAllGradesDlg::OnBnClickedButtonRemove()
{
	if (m_lsGrades.GetCurSel() == LB_ERR)
	{
		return;
	}

		GRADE tmp;
		tmp.nID = m_lsGrades.GetItemData(m_lsGrades.GetCurSel());
		GradeDatabaseInterface		gradeStore{ &databaseConnection };

		if (!gradeStore.Load(tmp.nID, tmp))
		{
			int errorBox = MessageBox((LPCWSTR)L"Could not load storage.", NULL, MB_OK | MB_ICONWARNING);
			return;
		}

		CombinedGradeDlg dlg{ eDialogMode_Remove, tmp };
		if (dlg.DoModal() == IDOK)
		{
			if (!gradeStore.Delete(tmp.nID))
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
		if (m_lsGrades.GetCurSel() != LB_ERR)
		{
			GRADE tmp;
			GradeDatabaseInterface		gradeStore{ &databaseConnection };

			if(!gradeStore.Load(m_lsGrades.GetItemData(m_lsGrades.GetCurSel()), tmp))
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
