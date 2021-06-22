// ManageStudentsDlg.cpp : implementation file
//

#include "pch.h"
#include "InternProject1.h"
#include "ManageStudentsDlg.h"
#include "afxdialogex.h"

#include "AddStudentDlg.h"
#include "EditStudentDlg.h"
#include "AllStudentsDlg.h"
#include "RemoveStudentDlg.h"

#include "CombinedStudentDlg.h"
#include "StudentAverageDlg.h"
#include "ExcellentStudentsDlg.h"
#include "BirthdayersDlg.h"
#include "FailsDlg.h"
#include "Utility.h"


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
//	ON_BN_CLICKED(IDC_BUTTON3, &ManageStudentsDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_ALL_STUDENTS, &ManageStudentsDlg::OnBnClickedAllStudents)
	ON_BN_CLICKED(IDC_BUTTON3, &ManageStudentsDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &ManageStudentsDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON6, &ManageStudentsDlg::OnBnClickedButtonAverage)
	ON_BN_CLICKED(IDC_BUTTON5, &ManageStudentsDlg::OnBnClickedButtonExcellents)
	ON_BN_CLICKED(IDC_BUTTON1, &ManageStudentsDlg::OnBnClickedButtonBirthdayers)
	ON_BN_CLICKED(IDC_BUTTON7, &ManageStudentsDlg::OnBnClickedButtonFails)
END_MESSAGE_MAP()


// ManageStudentsDlg message handlers


void ManageStudentsDlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	//AddStudentDlg dlg;
	CombinedStudentDlg dlg(eDialogMode_Add, STUDENT());
//	dlg.DoModal();
}


void ManageStudentsDlg::OnBnClickedButton3()
{
	// TODO: Add your control notification handler code here
//	EditStudentDlg dlg;
	CombinedStudentDlg dlg(eDialogMode_Edit, STUDENT());
//	dlg.DoModal();
}


void ManageStudentsDlg::OnBnClickedAllStudents()
{

	// TODO: Add your control notification handler code here
	AllStudentsDlg dlg;
//	CombinedStudentDlg dlg(eDialogMode_View);
	dlg.DoModal();
}


void ManageStudentsDlg::OnBnClickedButton4()
{
	// TODO: Add your control notification handler code here
//	RemoveStudentDlg dlg;
	CombinedStudentDlg dlg(eDialogMode_Remove, STUDENT());
//	dlg.DoModal();
}


void ManageStudentsDlg::OnBnClickedButtonAverage()
{
	// TODO: Add your control notification handler code here
	StudentAverageDlg dlg;
	dlg.DoModal();
}


void ManageStudentsDlg::OnBnClickedButtonExcellents()
{
	// TODO: Add your control notification handler code here
	ExcellentStudentsDlg dlg;
	dlg.DoModal();
}


void ManageStudentsDlg::OnBnClickedButtonBirthdayers()
{
	// TODO: Add your control notification handler code here
	BirthdayersDlg dlg;
	dlg.DoModal();
}


void ManageStudentsDlg::OnBnClickedButtonFails()
{
	FailsDlg dlg;
	dlg.DoModal();
	// TODO: Add your control notification handler code here
}
