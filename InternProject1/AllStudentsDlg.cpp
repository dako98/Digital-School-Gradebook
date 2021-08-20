// AllStudentsDlg.cpp : implementation file
//

#include "pch.h"
#include "InternProject1.h"
#include "AllStudentsDlg.h"
#include "afxdialogex.h"

#include "CombinedStudentDlg.h"

#include "CStudent.h"
#include "Storage.h"
#include "Utility.h"


// AllStudentsDlg dialog

IMPLEMENT_DYNAMIC(AllStudentsDlg, CDialog)

AllStudentsDlg::AllStudentsDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_ALL_STUDENTS_DLG, pParent)
	, m_allStudentsListVal(_T(""))
{
}

AllStudentsDlg::~AllStudentsDlg()
{
}

BOOL AllStudentsDlg::PrintAllStudents()
{
	std::vector<STUDENT> allStudents;
	m_allStudentsList.ResetContent();
	StudentDatabaseInterface studentStore{ &databaseConnection };

	if (!studentStore.LoadAll(allStudents))
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

	PrintAllStudents();
}

void AllStudentsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, m_allStudentsList);
	DDX_LBString(pDX, IDC_LIST2, m_allStudentsListVal);
}


BEGIN_MESSAGE_MAP(AllStudentsDlg, CDialog)
	ON_BN_CLICKED(IDC_BTN_STUDENTS_EDIT,	&AllStudentsDlg::OnBnClickedButtonEdit)
	ON_BN_CLICKED(IDC_BTN_STUDENTS_ADD,		&AllStudentsDlg::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BTN_STUDENTS_REMOVE,	&AllStudentsDlg::OnBnClickedButtonRemove)
	ON_WM_CONTEXTMENU()
END_MESSAGE_MAP()


// AllStudentsDlg message handlers



void AllStudentsDlg::OnBnClickedButtonEdit()
{
	if (m_allStudentsList.GetCurSel() == LB_ERR)
	{
		return;
	}

	STUDENT tmp;
	StudentDatabaseInterface studentStore{ &databaseConnection };

	if (!studentStore.Load(m_allStudentsList.GetItemData(m_allStudentsList.GetCurSel()), tmp))
	{
		int errorBox = MessageBox((LPCWSTR)L"Could not load storage.", NULL, MB_OK | MB_ICONWARNING);
		return;
	}

	CombinedStudentDlg dlg{ eDialogMode_Edit, tmp };
	if (dlg.DoModal() == IDOK)
	{
		if (!studentStore.Edit(tmp))
		{
			int errorBox = MessageBox((LPCWSTR)L"Could not load storage.", NULL, MB_OK | MB_ICONWARNING);
			return;
		}
	}
	PrintAllStudents();
}



void AllStudentsDlg::OnBnClickedButtonAdd()
{
	STUDENT tmp;
	StudentDatabaseInterface studentStore{ &databaseConnection };

	CombinedStudentDlg dlg{ eDialogMode_Add, tmp };
	if (dlg.DoModal() == IDOK)
	{
		if (!studentStore.Add(tmp))
		{
			int errorBox = MessageBox((LPCWSTR)L"Could not load storage.", NULL, MB_OK | MB_ICONWARNING);
			return;
		}
	}
	PrintAllStudents();
}

void AllStudentsDlg::OnBnClickedButtonRemove()
{
	if (m_allStudentsList.GetCurSel() != LB_ERR)
	{
		STUDENT tmp;
		StudentDatabaseInterface studentStore{ &databaseConnection };

		if (!studentStore.Load(m_allStudentsList.GetItemData(m_allStudentsList.GetCurSel()), tmp))
		{
			int errorBox = MessageBox((LPCWSTR)L"Could not load storage.", NULL, MB_OK | MB_ICONWARNING);
			return;
		}

		CombinedStudentDlg dlg{ eDialogMode_Remove, tmp };
		if (dlg.DoModal() == IDOK)
		{
			if (!studentStore.Delete(tmp.nID))
			{
				int errorBox = MessageBox((LPCWSTR)L"Could not load storage.", NULL, MB_OK | MB_ICONWARNING);
				return;
			}
		}
		PrintAllStudents();
	}
}

void AllStudentsDlg::OnContextMenu(CWnd* pWnd, CPoint point)
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

	if (m_allStudentsList.GetCurSel() != LB_ERR)
	{

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

			STUDENT tmp;
			BOOL isOK = TRUE;
			StudentDatabaseInterface studentStore{ &databaseConnection };

			isOK = studentStore.Load(m_allStudentsList.GetItemData(m_allStudentsList.GetCurSel()), tmp);
			if (!isOK)
			{
				int errorBox = MessageBox((LPCWSTR)L"Could not load storage.", NULL, MB_OK | MB_ICONWARNING);
				return;
			}
			CombinedStudentDlg dlg{ eDialogMode_View, tmp };
			dlg.DoModal();

		}
		break;
		default:
			break;
		}
	}
}
