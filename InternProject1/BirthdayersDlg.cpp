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
	: CDialog(IDD_BIRTHDAYERS, nullptr)
	, date(date)
	, studentStore(new StudentDatabaseInterface(_T("Students"), &databaseConnection))
{
}

BOOL BirthdayersDlg::OnInitDialog()
{
	if (!CDialog::OnInitDialog())
		return FALSE;

	BOOL isOK = TRUE;

	std::vector<STUDENT> allStudents;
//	Storage<STUDENT> studentStore{ studentsPath };
	isOK = studentStore->LoadAll(allStudents);

	if (isOK)
	{
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

			birthdayersList.AddString(currentRow);
		}
	}
	return isOK;
}

BirthdayersDlg::~BirthdayersDlg()
{
}

void BirthdayersDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, birthdayersList);
}


BEGIN_MESSAGE_MAP(BirthdayersDlg, CDialog)
END_MESSAGE_MAP()


// BirthdayersDlg message handlers
