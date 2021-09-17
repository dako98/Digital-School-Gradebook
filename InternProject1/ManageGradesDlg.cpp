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
	, m_gradeStore(&databaseConnection)

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
	ON_BN_CLICKED(IDC_BTN_ALL_GRADES, &ManageGradesDlg::OnBnClickedButtonAllGrades)
	ON_BN_CLICKED(IDC_BTN_ADD_GRADES, &ManageGradesDlg::OnBnClickedButtonAddGrade)
END_MESSAGE_MAP()


// ManageGradesDlg message handlers


void ManageGradesDlg::OnBnClickedButtonAllGrades()
{
	ViewAllGradesDlg dlg;
	dlg.DoModal();
}

void ManageGradesDlg::OnBnClickedButtonAddGrade()
{
	GRADE tmp;
	DBTIMESTAMP now;
	COleDateTime::GetCurrentTime().GetAsDBTIMESTAMP(now);
	tmp.dtDate.year		= now.year;
	tmp.dtDate.month	= now.month;
	tmp.dtDate.day		= now.day;
	tmp.dtDate.hour		= now.hour;
	tmp.dtDate.minute	= now.minute;
	tmp.dtDate.second	= now.second;

	CombinedGradeDlg dlg{ eDialogMode_Add, tmp };
	if (dlg.DoModal() == IDOK)
	{
		if (!m_gradeStore.Add(tmp))
		{
			int errorBox = MessageBox((LPCWSTR)L"Could not load storage.", NULL, MB_OK | MB_ICONWARNING);
			return;
		}
	}
}


