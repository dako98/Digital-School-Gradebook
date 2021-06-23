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
	ON_BN_CLICKED(IDC_BUTTON1, &ManageSubjectsDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &ManageSubjectsDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// ManageSubjectsDlg message handlers


void ManageSubjectsDlg::OnBnClickedButton1()
{
	AllSubjectsDlg dlg;
	dlg.DoModal();
}


void ManageSubjectsDlg::OnBnClickedButton2()
{
	SUBJECT tmp;
	Storage<SUBJECT> store{ subjectsPath };
	BOOL isOK = TRUE;

	isOK = store.NextID(tmp.nID);

	if (!isOK)
	{
		int errorBox = MessageBox((LPCWSTR)L"Could not load storage.", NULL, MB_OK | MB_ICONWARNING);
		return;
	}

	CombinedSubjectDlg dlg{ eDialogMode_Add, tmp };
	dlg.DoModal();
}

