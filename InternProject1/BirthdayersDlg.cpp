// BirthdayersDlg.cpp : implementation file
//

#include "pch.h"
#include "InternProject1.h"
#include "BirthdayersDlg.h"
#include "afxdialogex.h"

#include "Utility.h"

#include "Storage.h"
#include "CStudent.h"

// BirthdayersDlg dialog

IMPLEMENT_DYNAMIC(BirthdayersDlg, CDialog)

BirthdayersDlg::BirthdayersDlg(const DBTIMESTAMP& date)
	: CDialog(IDD_BIRTHDAYERS_DLG, nullptr)
	, m_date(date)
	, m_studentStore(&databaseConnection)
{
}

BOOL BirthdayersDlg::OnInitDialog()
{
	if (!CDialog::OnInitDialog())
	{
		return FALSE;
	}

	std::vector<STUDENT> allStudents;
	if (!m_studentStore.LoadAll(allStudents))
	{
		return FALSE;
	}

	DBTIMESTAMP now;
	COleDateTime::GetCurrentTime().GetAsDBTIMESTAMP(now);
	std::vector<STUDENT> birthdayers;

	for (const auto& student : allStudents)
	{
		if (student.dtBirthDate.day == now.day &&
			student.dtBirthDate.month == now.month)
		{
			birthdayers.push_back(student);
		}
	}

	CString currentRow;
	for (const auto& student : birthdayers)
	{
		currentRow.Format(_T("%d %s %s"),
			student.nID,
			CString{ student.szFirstName },
			CString{ student.szLastName });

		m_birthdayersList.AddString(currentRow);
	}

	return TRUE;
}

BirthdayersDlg::~BirthdayersDlg()
{
}

void BirthdayersDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_birthdayersList);
}


BEGIN_MESSAGE_MAP(BirthdayersDlg, CDialog)
END_MESSAGE_MAP()


// BirthdayersDlg message handlers
