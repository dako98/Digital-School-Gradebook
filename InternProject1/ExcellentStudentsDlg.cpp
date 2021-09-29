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
	{
		return FALSE;
	}

	// Get all grades
	std::vector<GRADE> allGrades;
	if (!m_gradeStore.LoadAll(allGrades))
	{
		return FALSE;
	}

	
		// Filter grades
		std::unordered_set<int> excellentStudentIDs;

		// get grades count and sum for each student ID
		std::unordered_map<int, std::pair<int, int>> preAverageData;
		for (const auto& grade : allGrades)
		{
			preAverageData[grade.nStudentID].first++;
			preAverageData[grade.nStudentID].second += grade.value;
		}

		// calculate average for each student
		std::unordered_map<int, double> studentAverageGrade;
		for (const auto& student : preAverageData)
		{
			assert(student.second.first > 0);
			studentAverageGrade[student.first] = (double)student.second.second / student.second.first;
			// Note: No division by zero, because if there are no grades, the entry would not exist.
		}

		for (const auto& student : studentAverageGrade)
		{
			if ((student.second > (GRADE::B + abs(GRADE::A - GRADE::B) / 2.0)) ||
				(abs(student.second - (GRADE::B + abs(GRADE::A - GRADE::B) / 2.0)) < GRADE_EPS))
			{
				excellentStudentIDs.insert(student.first);
			}
		}

		// Print student names
		CString currentRow;
		STUDENT tmp;

		for (const auto& studentID : excellentStudentIDs)
		{
			if(! m_studentStore.Load(studentID, tmp))
			{
				return FALSE;
			}

			currentRow.Format(_T("%d %s %s"),
				tmp.nID,
				CString{ tmp.szFirstName },
				CString{ tmp.szLastName });

			m_excellentStudentsList.AddString(currentRow);
		}
	
	return TRUE;
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
