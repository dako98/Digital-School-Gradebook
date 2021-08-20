// ManageSubjectsDlg.cpp : implementation file
//

#include "pch.h"
#include "InternProject1.h"
#include "ManageSubjectsDlg.h"
#include "afxdialogex.h"

#include "AllSubjectsDlg.h"
#include "CombinedSubjectDlg.h"
#include "Storage.h"
#include "CGrade.h"


// ManageSubjectsDlg dialog

IMPLEMENT_DYNAMIC(ManageSubjectsDlg, CDialog)

ManageSubjectsDlg::ManageSubjectsDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_MANAGE_SUBJECTS_DIALOG, pParent)
	, m_subjectStore(&databaseConnection)
{

}

ManageSubjectsDlg::~ManageSubjectsDlg()
{
}

void ManageSubjectsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ManageSubjectsDlg, CDialog)
	ON_BN_CLICKED(IDC_BTN_ALL_SUBJECTS, &ManageSubjectsDlg::OnBnClickedButtonViewAll)
	ON_BN_CLICKED(IDC_BTN_ADD_SUBJECT, &ManageSubjectsDlg::OnBnClickedButtonAdd)
END_MESSAGE_MAP()


// ManageSubjectsDlg message handlers


void ManageSubjectsDlg::OnBnClickedButtonViewAll()
{
	AllSubjectsDlg dlg;
	dlg.DoModal();
}


void ManageSubjectsDlg::OnBnClickedButtonAdd()
{

	BOOL isOK = TRUE;

	SUBJECT tmp;

	CombinedSubjectDlg dlg{ eDialogMode_Add, tmp };
	if (dlg.DoModal() == IDOK)
	{
		isOK = m_subjectStore.Add(tmp);
	}
	if (!isOK)
	{
		int errorBox = MessageBox((LPCWSTR)L"Could not load storage.", NULL, MB_OK | MB_ICONWARNING);
		return;
	}
}

