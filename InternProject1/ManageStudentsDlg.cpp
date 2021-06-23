// ManageStudentsDlg.cpp : implementation file
//

#include "pch.h"
#include "InternProject1.h"
#include "ManageStudentsDlg.h"
#include "afxdialogex.h"

#include "Utility.h"
#include "Storage.h"
#include "CStudent.h"

#include "AllStudentsDlg.h"
#include "CombinedStudentDlg.h"
#include "StudentAverageDlg.h"
#include "ExcellentStudentsDlg.h"
#include "BirthdayersDlg.h"
#include "FailsDlg.h"


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
	ON_BN_CLICKED(IDC_ALL_STUDENTS, &ManageStudentsDlg::OnBnClickedAllStudents)
	ON_BN_CLICKED(IDC_BUTTON6, &ManageStudentsDlg::OnBnClickedButtonAverage)
	ON_BN_CLICKED(IDC_BUTTON5, &ManageStudentsDlg::OnBnClickedButtonExcellents)
	ON_BN_CLICKED(IDC_BUTTON1, &ManageStudentsDlg::OnBnClickedButtonBirthdayers)
	ON_BN_CLICKED(IDC_BUTTON7, &ManageStudentsDlg::OnBnClickedButtonFails)
END_MESSAGE_MAP()


// ManageStudentsDlg message handlers


void ManageStudentsDlg::OnBnClickedButton2()
{
	STUDENT tmp;
	Storage<STUDENT> store{ studentsPath };

	tmp.nID = store.LastID() + 1;
	
	CombinedStudentDlg dlg{ eDialogMode_Add, tmp };
	dlg.DoModal();
}

void ManageStudentsDlg::OnBnClickedAllStudents()
{
	AllStudentsDlg dlg;
	dlg.DoModal();
}

void ManageStudentsDlg::OnBnClickedButtonAverage()
{
	StudentAverageDlg dlg;
	dlg.DoModal();
}


void ManageStudentsDlg::OnBnClickedButtonExcellents()
{
	ExcellentStudentsDlg dlg;
	dlg.DoModal();
}


void ManageStudentsDlg::OnBnClickedButtonBirthdayers()
{
	DBTIMESTAMP now;
	COleDateTime::GetCurrentTime().GetAsDBTIMESTAMP(now);

	BirthdayersDlg dlg{now};
	dlg.DoModal();
}


void ManageStudentsDlg::OnBnClickedButtonFails()
{
	FailsDlg dlg;
	dlg.DoModal();
}
