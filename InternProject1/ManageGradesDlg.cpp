// ManageGradesDlg.cpp : implementation file
//

#include "pch.h"
#include "InternProject1.h"
#include "ManageGradesDlg.h"
#include "afxdialogex.h"

#include "ViewAllGradesDlg.h"

#include "CombinedGradeDlg.h"
#include "Utility.h"
#include "Storage.h"
#include "CGrade.h"

// ManageGradesDlg dialog

IMPLEMENT_DYNAMIC(ManageGradesDlg, CDialog)

ManageGradesDlg::ManageGradesDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_MANAGE_GRADES, pParent)
{

}

ManageGradesDlg::~ManageGradesDlg()
{
}

void ManageGradesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ManageGradesDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &ManageGradesDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &ManageGradesDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// ManageGradesDlg message handlers


void ManageGradesDlg::OnBnClickedButton1()
{
	ViewAllGradesDlg dlg;
	dlg.DoModal();
}

void ManageGradesDlg::OnBnClickedButton2()
{
	GRADE tmp;
/*
	Storage<GRADE> store{ gradesPath };
	BOOL isOK = TRUE;

	isOK = store.NextID(tmp.nID);

	if (!isOK)
	{
		int errorBox = MessageBox((LPCWSTR)L"Could not load storage.", NULL, MB_OK | MB_ICONWARNING);
		return;
	}
*/
	CombinedGradeDlg dlg{ eDialogMode_Add, tmp };
	dlg.DoModal();
}


