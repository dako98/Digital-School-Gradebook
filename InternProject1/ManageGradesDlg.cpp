// ManageGradesDlg.cpp : implementation file
//

#include "pch.h"
#include "InternProject1.h"
#include "ManageGradesDlg.h"
#include "afxdialogex.h"

#include "AddGradeDlg.h"


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
END_MESSAGE_MAP()


// ManageGradesDlg message handlers


void ManageGradesDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	AddGradeDlg dlg;
	dlg.DoModal();
}
