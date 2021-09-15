// AllStudentClassesDlg.cpp : implementation file
//

#include "pch.h"
#include "InternProject1.h"
#include "AllStudentClassesDlg.h"
#include "afxdialogex.h"

#include "Utility.h"

#include "CStudentClassDatabaseInterface.h"
#include "CombinedClassDlg.h"


// AllStudentClassesDlg dialog

IMPLEMENT_DYNAMIC(AllStudentClassesDlg, CDialog)

AllStudentClassesDlg::AllStudentClassesDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_ALL_STUDENT_CLASSES, pParent)
{

}

BOOL AllStudentClassesDlg::OnInitDialog()
{
	if (!CDialog::OnInitDialog())
	{
		return FALSE;
	}

	if (!PrintAllStudentClasses())
	{
		return FALSE;
	}



	return TRUE;
}

AllStudentClassesDlg::~AllStudentClassesDlg()
{
}

BOOL AllStudentClassesDlg::PrintAllStudentClasses()
{
	m_allStudentClassesList.ResetContent();

	StudentClassDatabaseInterface studentClassesStore(&databaseConnection);
	std::vector<STUDENT_CLASS> allStudentClasses;

	if (!studentClassesStore.LoadAll(allStudentClasses))
	{
		return FALSE;
	}
	CString currentRow;

	for (const auto& studentClass : allStudentClasses)
	{

	CString currentTeacherName;
	IDtoNameMapper(&databaseConnection, _T("Teachers"), _T("ID"), _T("LastName"), studentClass.nTeacherNumber, currentTeacherName);

	currentRow.Format(_T("%d %s %s"),
		studentClass.nID,
		CString{ studentClass.szName },
		currentTeacherName);

		int index = m_allStudentClassesList.AddString(currentRow);
		m_allStudentClassesList.SetItemData(index, studentClass.nID);
	}


	return TRUE;
}

void AllStudentClassesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ALL_STUDENT_CLASSES_LIST, m_allStudentClassesList);
}


BEGIN_MESSAGE_MAP(AllStudentClassesDlg, CDialog)
	ON_BN_CLICKED(IDC_BTN_ADD_STUDENT_CLASS, &AllStudentClassesDlg::OnBnClickedBtnAddStudentClass)
	ON_BN_CLICKED(IDC_BTN_EDIT_STUDENT_CLASS, &AllStudentClassesDlg::OnBnClickedBtnEditStudentClass)
	ON_BN_CLICKED(IDC_BTN_REMOVE_STUDENT_CLASS, &AllStudentClassesDlg::OnBnClickedBtnRemoveStudentClass)
	ON_WM_CONTEXTMENU()
END_MESSAGE_MAP()


// AllStudentClassesDlg message handlers


void AllStudentClassesDlg::OnBnClickedBtnAddStudentClass()
{
	// TODO: Add your control notification handler code here
	STUDENT_CLASS tmp;
	StudentClassDatabaseInterface studentClassStore{ &databaseConnection };

	CombinedClassDlg dlg{ eDialogMode_Add, tmp };
	if (dlg.DoModal() == IDOK)
	{
		if (!studentClassStore.Add(tmp))
		{
			int errorBox = MessageBox((LPCWSTR)L"Could not load storage.", NULL, MB_OK | MB_ICONWARNING);
			return;
		}
	}
	PrintAllStudentClasses();
}


void AllStudentClassesDlg::OnBnClickedBtnEditStudentClass()
{
	// TODO: Add your control notification handler code here
	if (m_allStudentClassesList.GetCurSel() == LB_ERR)
	{
		return;
	}

	STUDENT_CLASS tmp;
	StudentClassDatabaseInterface studentClassStore{ &databaseConnection };

	if (!studentClassStore.Load(m_allStudentClassesList.GetItemData(m_allStudentClassesList.GetCurSel()), tmp))
	{
		int errorBox = MessageBox((LPCWSTR)L"Could not load storage.", NULL, MB_OK | MB_ICONWARNING);
		return;
	}

	CombinedClassDlg dlg{ eDialogMode_Edit, tmp };
	if (dlg.DoModal() == IDOK)
	{
		if (!studentClassStore.Edit(tmp))
		{
			int errorBox = MessageBox((LPCWSTR)L"Could not load storage.", NULL, MB_OK | MB_ICONWARNING);
			return;
		}
	}
	PrintAllStudentClasses();
}


void AllStudentClassesDlg::OnBnClickedBtnRemoveStudentClass()
{
	// TODO: Add your control notification handler code here
	if (m_allStudentClassesList.GetCurSel() != LB_ERR)
	{
		STUDENT_CLASS tmp;
		StudentClassDatabaseInterface studentClassStore{ &databaseConnection };

		if (!studentClassStore.Load(m_allStudentClassesList.GetItemData(m_allStudentClassesList.GetCurSel()), tmp))
		{
			int errorBox = MessageBox((LPCWSTR)L"Could not load storage.", NULL, MB_OK | MB_ICONWARNING);
			return;
		}

		CombinedClassDlg dlg{ eDialogMode_Remove, tmp };
		if (dlg.DoModal() == IDOK)
		{

			StudentDatabaseInterface studentStore(&databaseConnection);
			CString filter;
			filter.Format(_T("[ClassID] = %d"), tmp.nID);
			std::vector<STUDENT> studentsInClass;
			
			if (!studentStore.LoadWhere(filter, studentsInClass))
			{
				int errorBox = MessageBox((LPCWSTR)L"Could not check students in class.", NULL, MB_OK | MB_ICONWARNING);
				return;
			}

			if (studentsInClass.size() != 0)
			{
				int errorBox = MessageBox((LPCWSTR)L"Please transfer students to another class and try again.", NULL, MB_OK | MB_ICONWARNING);
				return;
			}

			if (!studentClassStore.Delete(tmp.nID))
			{
				int errorBox = MessageBox((LPCWSTR)L"Could not load storage.", NULL, MB_OK | MB_ICONWARNING);
				return;
			}
		}
		PrintAllStudentClasses();
	}
}


void AllStudentClassesDlg::OnContextMenu(CWnd* pWnd, CPoint point)
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

	if (m_allStudentClassesList.GetCurSel() != LB_ERR)
	{

		int response = pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON | TPM_RETURNCMD,
			point.x,
			point.y,
			pWndPopupOwner);

		switch (response)
		{
		case ID_POPUP_ADD:
			OnBnClickedBtnAddStudentClass();
			break;

		case ID_POPUP_EDIT:
			OnBnClickedBtnEditStudentClass();
			break;

		case ID_POPUP_DELETE:
			OnBnClickedBtnRemoveStudentClass();
			break;

		case ID_POPUP_VIEW:
		{
			STUDENT_CLASS tmp;
			StudentClassDatabaseInterface studentsClassStore{ &databaseConnection };

			if (!studentsClassStore.Load(m_allStudentClassesList.GetItemData(m_allStudentClassesList.GetCurSel()), tmp))
			{
				int errorBox = MessageBox((LPCWSTR)L"Could not load storage.", NULL, MB_OK | MB_ICONWARNING);
				return;
			}
			CombinedClassDlg dlg{ eDialogMode_View, tmp };
			dlg.DoModal();
		}
		break;
		default:
			break;
		}
	}
}
