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
	: CDialog(IDD_ALL_SUBJECTS, pParent)
	, m_store(_T("Subjects"), &databaseConnection)
{

}

AllSubjectsDlg::~AllSubjectsDlg()
{
}

BOOL AllSubjectsDlg::PrintAll()
{
	subjectsList.ResetContent();

	BOOL isOK = TRUE;

	std::vector<SUBJECT> all;
//	Storage<SUBJECT> su{ subjectsPath };
	isOK = m_store.LoadAll(all);

	if (isOK)
	{
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
	}
	return isOK;
}

BOOL AllSubjectsDlg::OnInitDialog()
{
	if(!CDialog::OnInitDialog())
		return FALSE;

	BOOL isOK = TRUE;

	isOK = PrintAll();

	return isOK;
}

void AllSubjectsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, subjectsList);
}


BEGIN_MESSAGE_MAP(AllSubjectsDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &AllSubjectsDlg::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON2, &AllSubjectsDlg::OnBnClickedButtonEdit)
	ON_BN_CLICKED(IDC_BUTTON3, &AllSubjectsDlg::OnBnClickedButtonRemove)
END_MESSAGE_MAP()


// AllSubjectsDlg message handlers


void AllSubjectsDlg::OnBnClickedButtonAdd()
{
	SUBJECT tmp;
//	Storage<SUBJECT> store{ subjectsPath };
	BOOL isOK = TRUE;

//	isOK = m_store.NextID(tmp.nID);

	if (!isOK)
	{
		int errorBox = MessageBox((LPCWSTR)L"Could not load storage.", NULL, MB_OK | MB_ICONWARNING);
		return;
	}

	CombinedSubjectDlg dlg{ eDialogMode_Add, tmp };
	dlg.DoModal();

	PrintAll();
}


void AllSubjectsDlg::OnBnClickedButtonEdit()
{
	if (subjectsList.GetCurSel() != LB_ERR)
	{
		SUBJECT tmp;
//		Storage<SUBJECT> store{ subjectsPath };
		BOOL isOK = TRUE;

		isOK = m_store.Load(subjectsList.GetItemData(subjectsList.GetCurSel()), tmp);

		if (!isOK)
		{
			int errorBox = MessageBox((LPCWSTR)L"Could not load storage.", NULL, MB_OK | MB_ICONWARNING);
			return;
		}

		CombinedSubjectDlg dlg{ eDialogMode_Edit, tmp };
		dlg.DoModal();

		PrintAll();
	}
}


void AllSubjectsDlg::OnBnClickedButtonRemove()
{
	if (subjectsList.GetCurSel() != LB_ERR)
	{
		SUBJECT tmp;
//		Storage<SUBJECT> store{ subjectsPath };
		BOOL isOK = TRUE;

		isOK = m_store.Load(subjectsList.GetItemData(subjectsList.GetCurSel()), tmp);

		if (!isOK)
		{
			int errorBox = MessageBox((LPCWSTR)L"Could not load storage.", NULL, MB_OK | MB_ICONWARNING);
			return;
		}

		CombinedSubjectDlg dlg{ eDialogMode_Remove, tmp };
		dlg.DoModal();

		PrintAll();
	}
}
