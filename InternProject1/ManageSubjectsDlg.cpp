// ManageSubjectsDlg.cpp : implementation file
//

#include "pch.h"
#include "InternProject1.h"
#include "ManageSubjectsDlg.h"
#include "afxdialogex.h"

#include "AllSubjectsDlg.h"
#include "AddSubjectDlg.h"
#include "EditSubjectDlg.h"


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
	ON_BN_CLICKED(IDC_BUTTON3, &ManageSubjectsDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// ManageSubjectsDlg message handlers


void ManageSubjectsDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	AllSubjectsDlg dlg;
	dlg.DoModal();
}


void ManageSubjectsDlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	AddSubjectDlg dlg;
	dlg.DoModal();
}


void ManageSubjectsDlg::OnBnClickedButton3()
{
	// TODO: Add your control notification handler code here
	EditSubjectDlg dlg;
	dlg.DoModal();
}
