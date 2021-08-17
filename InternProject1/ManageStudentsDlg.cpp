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
#include "AllTeachersDlg.h"
#include "CombinedStudentDlg.h"
#include "StudentAverageDlg.h"
#include "ExcellentStudentsDlg.h"
#include "BirthdayersDlg.h"
#include "FailsDlg.h"


// ManageStudentsDlg dialog

IMPLEMENT_DYNAMIC(ManageStudentsDlg, CDialog)

ManageStudentsDlg::ManageStudentsDlg()
	: CDialog(IDD_MANAGESTUDENTS)
	, m_studentStore(&databaseConnection)
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
	ON_BN_CLICKED(IDC_BUTTON3, &ManageStudentsDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// ManageStudentsDlg message handlers


void ManageStudentsDlg::OnBnClickedButton2()
{
	BOOL isOK = TRUE;

	STUDENT tmp;

	CombinedStudentDlg dlg{ eDialogMode_Add, tmp };
	if (dlg.DoModal() == IDOK)
	{
		isOK = m_studentStore.Add(tmp);
	}
	if (!isOK)
	{
		int errorBox = MessageBox((LPCWSTR)L"Could not load storage.", NULL, MB_OK | MB_ICONWARNING);
		return;
	}
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


void ManageStudentsDlg::OnBnClickedButton3()
{
	AllTeachersDlg dlg;
	dlg.DoModal();
}
