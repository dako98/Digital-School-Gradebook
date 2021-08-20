// ExcellentStudentsDlg.cpp : implementation file
//

#include "pch.h"
#include "InternProject1.h"
#include "ExcellentStudentsDlg.h"
#include "afxdialogex.h"

#include <unordered_set>

#include "Utility.h"

#include "CGrade.h"
#include "CStudent.h"


// ExcellentStudentsDlg dialog

IMPLEMENT_DYNAMIC(ExcellentStudentsDlg, CDialog)

ExcellentStudentsDlg::ExcellentStudentsDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_EXCELLENT_STUDENTS, pParent)
	, m_studentStore(&databaseConnection)
	, m_gradeStore(&databaseConnection)
{
}

BOOL ExcellentStudentsDlg::OnInitDialog()
{
	if (!CDialog::OnInitDialog())
		return FALSE;

	BOOL isOK;

	// Get all grades
	std::vector<GRADE> allGrades;
	isOK = m_gradeStore.LoadAll(allGrades);

	if (isOK)
	{
		// Filter grades
		std::unordered_set<int> excellentStudentIDs;
		std::unordered_set<int> nonexcellentStudentIDs;
		for (const auto& grade : allGrades)
		{
			if (grade.value == GRADE::GRADES::A)
			{
				if (nonexcellentStudentIDs.find(grade.nStudentID) == nonexcellentStudentIDs.end())
				{
					excellentStudentIDs.insert(grade.nStudentID);
				}
			}
			else
			{
				excellentStudentIDs.erase(grade.nStudentID);
				nonexcellentStudentIDs.insert(grade.nStudentID);
			}
		}

		// Print student names
		CString currentRow;
		STUDENT tmp;

		for (const auto& studentID : excellentStudentIDs)
		{
			isOK = m_studentStore.Load(studentID, tmp);

			if (!isOK)
			{
				break;
			}

			currentRow.Format(_T("%d %s %s"),
				tmp.nID,
				CString{ tmp.szFirstName },
				CString{ tmp.szLastName });

			m_excellentStudentsList.AddString(currentRow);
		}
	}
	return isOK;
}

ExcellentStudentsDlg::~ExcellentStudentsDlg()
{
}

void ExcellentStudentsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EXCELLENT_STUDENTS_LIST, m_excellentStudentsList);
}


BEGIN_MESSAGE_MAP(ExcellentStudentsDlg, CDialog)
END_MESSAGE_MAP()


// ExcellentStudentsDlg message handlers
