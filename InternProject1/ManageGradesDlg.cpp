// ManageGradesDlg.cpp : implementation file
//

#include "pch.h"
#include "InternProject1.h"
#include "ManageGradesDlg.h"
#include "afxdialogex.h"

#include "AddGradeDlg.h"
#include "EditGradeDlg.h"
#include "ViewAllGradesDlg.h"

#include "CombinedGradeDlg.h"
#include "Utility.h"


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
	ON_BN_CLICKED(IDC_BUTTON3, &ManageGradesDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON2, &ManageGradesDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// ManageGradesDlg message handlers


void ManageGradesDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	ViewAllGradesDlg dlg;
	dlg.DoModal();
}

void ManageGradesDlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
//	AddGradeDlg dlg;
//	CombinedGradeDlg dlg(eDialogMode_Add,)
//	dlg.DoModal();
}

void ManageGradesDlg::OnBnClickedButton3()
{
	// TODO: Add your control notification handler code here
//	EditGradeDlg dlg;
//	dlg.DoModal();
}


