// AllTeachersDlg.cpp : implementation file
//

#include "pch.h"
#include "InternProject1.h"
#include "AllTeachersDlg.h"
#include "afxdialogex.h"

#include "CombinedTeacherDlg.h"


// AllTeachersDlg dialog

IMPLEMENT_DYNAMIC(AllTeachersDlg, CDialog)

AllTeachersDlg::AllTeachersDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_ALL_TEACHERS_DLG, pParent)
	, m_allTeachersListVal(_T(""))
{

}

AllTeachersDlg::~AllTeachersDlg()
{
}

void AllTeachersDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TEACHERS_LIST, m_allTeachersList);
	DDX_LBString(pDX, IDC_TEACHERS_LIST, m_allTeachersListVal);
}


BEGIN_MESSAGE_MAP(AllTeachersDlg, CDialog)
	ON_BN_CLICKED(IDC_BTN_TEACHERS_ADD, &AllTeachersDlg::OnBnClickedBtnTeachersAdd)
	ON_BN_CLICKED(IDC_BTN_TEACHERS_EDIT, &AllTeachersDlg::OnBnClickedBtnTeachersEdit)
	ON_BN_CLICKED(IDC_BTN_TEACHERS_REMOVE, &AllTeachersDlg::OnBnClickedBtnTeachersRemove)
	ON_WM_CONTEXTMENU()
END_MESSAGE_MAP()


BOOL AllTeachersDlg::OnInitDialog()
{
	if (!CDialog::OnInitDialog())
	{
		return FALSE;
	}

	return PrintAllTeachers();

}

BOOL AllTeachersDlg::PrintAllTeachers()
{
	std::vector<TEACHER> all;
	TeacherDatabaseInterface teacherStore{ &databaseConnection };
	m_allTeachersList.ResetContent();

	if (!teacherStore.LoadAll(all))
		return FALSE;

	CString currentRow;

	for (const auto& teacher : all)
	{
		currentRow.Format(_T("%d %s %s"),
			teacher.nID,
			CString{ teacher.szFirstName },
			CString{ teacher.szLastName });

		int index = m_allTeachersList.AddString(currentRow);
		m_allTeachersList.SetItemData(index, teacher.nID);
	}

	return TRUE;
}

// AllTeachersDlg message handlers

void AllTeachersDlg::OnBnClickedBtnTeachersAdd()
{
	// TODO: Add your control notification handler code here

	TEACHER tmp;
	TeacherDatabaseInterface teacherStore{ &databaseConnection };

	CombinedTeacherDlg dlg{ eDialogMode_Add, tmp };
	if (dlg.DoModal() == IDOK)
	{
		if (!teacherStore.Add(tmp))
		{
			int errorBox = MessageBox((LPCWSTR)L"Could not load storage.", NULL, MB_OK | MB_ICONWARNING);
			return;
		}
	}
	PrintAllTeachers();
}


void AllTeachersDlg::OnBnClickedBtnTeachersEdit()
{
	// TODO: Add your control notification handler code here
	if (m_allTeachersList.GetCurSel() != LB_ERR)
	{
		TEACHER tmp;
		TeacherDatabaseInterface teacherStore{ &databaseConnection };

		if (!teacherStore.Load(m_allTeachersList.GetItemData(m_allTeachersList.GetCurSel()), tmp))
		{
			int errorBox = MessageBox((LPCWSTR)L"Could not load storage.", NULL, MB_OK | MB_ICONWARNING);
			return;
		}

		CombinedTeacherDlg dlg{ eDialogMode_Edit, tmp };
		if (dlg.DoModal() == IDOK)
		{
			if (!teacherStore.Edit(tmp))
			{
				int errorBox = MessageBox((LPCWSTR)L"Could not load storage.", NULL, MB_OK | MB_ICONWARNING);
				return;
			}
		}
		PrintAllTeachers();
	}
}


void AllTeachersDlg::OnBnClickedBtnTeachersRemove()
{
	// TODO: Add your control notification handler code here
	if (m_allTeachersList.GetCurSel() != LB_ERR)
	{
		TEACHER tmp;
		TeacherDatabaseInterface teacherStore{ &databaseConnection };

		if (!teacherStore.Load(m_allTeachersList.GetItemData(m_allTeachersList.GetCurSel()), tmp))
		{
			int errorBox = MessageBox((LPCWSTR)L"Could not load storage.", NULL, MB_OK | MB_ICONWARNING);
			return;
		}

		CombinedTeacherDlg dlg{ eDialogMode_Remove, tmp };
		if (dlg.DoModal() == IDOK)
		{
			if (!teacherStore.Delete(tmp.nID))
			{
				int errorBox = MessageBox((LPCWSTR)L"Could not load storage.", NULL, MB_OK | MB_ICONWARNING);
				return;
			}
		}
		PrintAllTeachers();
	}
}


void AllTeachersDlg::OnContextMenu(CWnd* pWnd, CPoint point)
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
		OnBnClickedBtnTeachersAdd();
		break;

	case ID_POPUP_EDIT:
		OnBnClickedBtnTeachersEdit();
		break;

	case ID_POPUP_DELETE:
		OnBnClickedBtnTeachersRemove();
		break;

	case ID_POPUP_VIEW:
	{
		if (m_allTeachersList.GetCurSel() != LB_ERR)
		{
			TEACHER tmp;
			BOOL isOK = TRUE;
			TeacherDatabaseInterface teacherStore{ &databaseConnection };

			isOK = teacherStore.Load(m_allTeachersList.GetItemData(m_allTeachersList.GetCurSel()), tmp);
			if (!isOK)
			{
				int errorBox = MessageBox((LPCWSTR)L"Could not load storage.", NULL, MB_OK | MB_ICONWARNING);
				return;
			}
			CombinedTeacherDlg dlg{ eDialogMode_View, tmp };
			dlg.DoModal();
		}
	}
	break;
	default:
		break;
	}
}

