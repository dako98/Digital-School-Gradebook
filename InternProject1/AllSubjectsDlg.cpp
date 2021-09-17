// AllSubjectsDlg.cpp : implementation file
//

#include "pch.h"
#include "InternProject1.h"
#include "AllSubjectsDlg.h"
#include "afxdialogex.h"

#include <vector>

#include "Storage.h"
#include "CSubject.h"
#include "CombinedSubjectDlg.h"


// AllSubjectsDlg dialog

IMPLEMENT_DYNAMIC(AllSubjectsDlg, CDialog)

AllSubjectsDlg::AllSubjectsDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_ALL_SUBJECTS_DLG, pParent)
{

}

AllSubjectsDlg::~AllSubjectsDlg()
{
}

BOOL AllSubjectsDlg::PrintAllSubjects()
{
	subjectsList.ResetContent();

	std::vector<SUBJECT> all;
	SubjectDatabaseInterface subjectStore{ &databaseConnection };

	if (!subjectStore.LoadAll(all))
	{
		return FALSE;
	}

	CString currentRow;

	for (const auto& subject : all)
	{
		currentRow.Format(_T("%d %s %s"),
			subject.nID,
			CString{ subject.szName },
			CString{ subject.szRoom });

		int index = subjectsList.AddString(currentRow);
		subjectsList.SetItemData(index, subject.nID);
	}

	return TRUE;
}

BOOL AllSubjectsDlg::OnInitDialog()
{
	if(!CDialog::OnInitDialog())
		return FALSE;

	return PrintAllSubjects();
}

void AllSubjectsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SUBJECTS_LIST, subjectsList);
}


BEGIN_MESSAGE_MAP(AllSubjectsDlg, CDialog)
	ON_BN_CLICKED(IDC_BTN_SUBJECTS_ADD,		&AllSubjectsDlg::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BTN_SUBJECTS_EDIT,	&AllSubjectsDlg::OnBnClickedButtonEdit)
	ON_BN_CLICKED(IDC_BTN_SUBJECTS_REMOVE,	&AllSubjectsDlg::OnBnClickedButtonRemove)
	ON_WM_CONTEXTMENU()
END_MESSAGE_MAP()


// AllSubjectsDlg message handlers


void AllSubjectsDlg::OnBnClickedButtonAdd()
{
	SUBJECT tmp;

	SubjectDatabaseInterface subjectStore{ &databaseConnection };

	CombinedSubjectDlg dlg{ eDialogMode_Add, tmp };
	if (dlg.DoModal() == IDOK)
	{
		if (!subjectStore.Add(tmp))
		{
			int errorBox = MessageBox((LPCWSTR)L"Could not load storage.", NULL, MB_OK | MB_ICONWARNING);
			return;
		}
	}
	PrintAllSubjects();
}


void AllSubjectsDlg::OnBnClickedButtonEdit()
{
	if (subjectsList.GetCurSel() == LB_ERR)
	{
		return;
	}

	SUBJECT tmp;

	SubjectDatabaseInterface subjectStore{ &databaseConnection };

	if (!subjectStore.Load(subjectsList.GetItemData(subjectsList.GetCurSel()), tmp))
	{
		int errorBox = MessageBox((LPCWSTR)L"Could not load storage.", NULL, MB_OK | MB_ICONWARNING);
		return;
	}

	CombinedSubjectDlg dlg{ eDialogMode_Edit, tmp };
	if (dlg.DoModal() == IDOK)
	{
		if (!subjectStore.Edit(tmp))
		{
			int errorBox = MessageBox((LPCWSTR)L"Could not load storage.", NULL, MB_OK | MB_ICONWARNING);
			return;
		}
	}

	PrintAllSubjects();
}


void AllSubjectsDlg::OnBnClickedButtonRemove()
{
	if (subjectsList.GetCurSel() == LB_ERR)
	{
		return;
	}

	SUBJECT tmp;

	SubjectDatabaseInterface subjectStore{ &databaseConnection };

	if (!subjectStore.Load(subjectsList.GetItemData(subjectsList.GetCurSel()), tmp))
	{
		int errorBox = MessageBox((LPCWSTR)L"Could not load storage.", NULL, MB_OK | MB_ICONWARNING);
		return;
	}

	CombinedSubjectDlg dlg{ eDialogMode_Remove, tmp };
	if (dlg.DoModal() == IDOK)
	{
		if (!subjectStore.Delete(tmp.nID))
		{
			int errorBox = MessageBox((LPCWSTR)L"Could not load storage.", NULL, MB_OK | MB_ICONWARNING);
			return;
		}

		PrintAllSubjects();
	}
}

void AllSubjectsDlg::OnContextMenu(CWnd* pWnd, CPoint point)
{
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
		if (subjectsList.GetCurSel() != LB_ERR)
		{
			SUBJECT tmp;

			SubjectDatabaseInterface subjectStore{ &databaseConnection };

			if (!subjectStore.Load(subjectsList.GetItemData(subjectsList.GetCurSel()), tmp))
			{
				int errorBox = MessageBox((LPCWSTR)L"Could not load storage.", NULL, MB_OK | MB_ICONWARNING);
				return;
			}
			CombinedSubjectDlg dlg{ eDialogMode_View, tmp };
			dlg.DoModal();
		}
	}
	break;
	default:
		break;
	}
}