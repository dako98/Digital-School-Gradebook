// CombinedScheduleClassDlg.cpp : implementation file
//

#include "pch.h"
#include "InternProject1.h"
#include "CombinedScheduleClassDlg.h"
#include "afxdialogex.h"


// CombinedScheduleClassDlg dialog

IMPLEMENT_DYNAMIC(CombinedScheduleClassDlg, CDialog)

CombinedScheduleClassDlg::CombinedScheduleClassDlg(DialogMode eMode, ScheduleClass& data)
	: CDialog(IDD_COMBINED_SCHEDULED_CLASS, nullptr)
	, m_dialogMode(eMode)
	, m_scheduledClassStore(&databaseConnection)
	, m_subjectStore(&databaseConnection)
	, m_data(data)
{

}

BOOL CombinedScheduleClassDlg::OnInitDialog()
{
	if(!CDialog::OnInitDialog())
	{
		return FALSE;
	}
	BOOL isOK = TRUE;

	std::vector<SUBJECT> allSubjects;

	switch (m_dialogMode)
	{
	case eDialogMode_Add:
	{
		CString text;
		isOK = m_subjectStore.LoadAll(allSubjects);

		for (const auto& subject : allSubjects)
		{
			text.Format(_T("%d %s"), subject.nID, subject.szName);
			int index = subjectsList.AddString(text);
			subjectsList.SetItemData(index, subject.nID);
		}

		subjectsList.EnableWindow(TRUE);
	}
		break;

	case eDialogMode_Remove:
	{
		SUBJECT tmp;
		m_subjectStore.Load(m_data.nSubjectID, tmp);
		subjectsList.AddString(tmp.szName);
		subjectsList.SetCurSel(0);
		subjectsList.EnableWindow(FALSE);
	}
		break;

	case eDialogMode_None:
	case eDialogMode_Edit:
	case eDialogMode_View:

	default:
		ASSERT(FALSE, "Invalid window state.");
		break;
	}

	return isOK;
}

CombinedScheduleClassDlg::~CombinedScheduleClassDlg()
{
}

void CombinedScheduleClassDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, subjectsList);
}


BEGIN_MESSAGE_MAP(CombinedScheduleClassDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CombinedScheduleClassDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CombinedScheduleClassDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CombinedScheduleClassDlg message handlers


void CombinedScheduleClassDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	if (subjectsList.GetCurSel() != CB_ERR)
	{
		int id = subjectsList.GetItemData(subjectsList.GetCurSel());
		m_data.nSubjectID = id;
	}
	CDialog::OnOK();
}


void CombinedScheduleClassDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	m_data.nSubjectID = -1;
	CDialog::OnCancel();
}
