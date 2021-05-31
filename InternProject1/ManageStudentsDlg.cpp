// ManageStudentsDlg.cpp : implementation file
//

#include "pch.h"
#include "InternProject1.h"
#include "ManageStudentsDlg.h"
#include "afxdialogex.h"

#include "AddStudentDlg.h"
#include "EditStudentDlg.h"
#include "AllStudentsDlg.h"


// ManageStudentsDlg dialog

IMPLEMENT_DYNAMIC(ManageStudentsDlg, CDialog)

ManageStudentsDlg::ManageStudentsDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_MANAGESTUDENTS, pParent)
{

}

ManageStudentsDlg::~ManageStudentsDlg()
{
}

void ManageStudentsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ManageStudentsDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON2, &ManageStudentsDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &ManageStudentsDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_ALL_STUDENTS, &ManageStudentsDlg::OnBnClickedAllStudents)
END_MESSAGE_MAP()


// ManageStudentsDlg message handlers


void ManageStudentsDlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	AddStudentDlg dlg;
	dlg.DoModal();
}


void ManageStudentsDlg::OnBnClickedButton3()
{
	// TODO: Add your control notification handler code here
	EditStudentDlg dlg;
	dlg.DoModal();
}


void ManageStudentsDlg::OnBnClickedAllStudents()
{

	// TODO: Add your control notification handler code here
	AllStudentsDlg dlg;
	dlg.DoModal();
}
