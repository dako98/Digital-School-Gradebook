// FailsDlg.cpp : implementation file
//

#include "pch.h"
#include "InternProject1.h"
#include "FailsDlg.h"
#include "afxdialogex.h"

#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "Utility.h"

#include "Storage.h"
#include "CGrade.h"
#include "CSubject.h"
#include "CStudent.h"


// FailsDlg dialog

IMPLEMENT_DYNAMIC(FailsDlg, CDialog)

FailsDlg::FailsDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_FAILS, pParent)
{

}

struct studentStr
{
	struct subject
	{
		int gradeSum = 0;
		int gradesCount = 0;
	};
	std::unordered_map<int, subject> subject;
};

BOOL FailsDlg::OnInitDialog()
{
	if (!CDialog::OnInitDialog())
		return FALSE;

	// Load all grades
	Storage<GRADE> gradeStore(gradesPath);
	std::vector<GRADE> allGrades;
	gradeStore.LoadAll(allGrades);

	// Struct[map - studentID] { subject[map - subjectID]{ gradesSum, gradesCount } }


	// first -> studentID
	// second -> subjects structure
	std::unordered_map<int, studentStr> students;

	// first -> studentID
	// second -> subjects IDs
	std::unordered_map<int, std::unordered_set<int>> consecutiveBads;

	for (const auto& grade : allGrades)
	{
		auto curr = &students[grade.nStudentID].subject[grade.nSubjectID];

		curr->gradeSum += grade.value;
		curr->gradesCount++;

		if (grade.value == GRADE::GRADES::F)
		{
			consecutiveBads[grade.nStudentID].insert(grade.nSubjectID);
		}
	}

	// first -> studentID
	// second -> failed subjects IDs
	std::unordered_map<int, std::unordered_set<int>> fails;



	for (const auto& student : students)
	{
		for (const auto& subject : student.second.subject)
		{
			float average = subject.second.gradeSum / (float)(subject.second.gradesCount > 0 ? subject.second.gradesCount : 1);

			if (average < GRADE::GRADES::D)
			{
				fails[student.first].insert(subject.first);
			}
		}
	}

	Storage<STUDENT> studentStore(studentsPath);
	Storage<SUBJECT> subjectStore(subjectsPath);

	CString currentRow;

	// Print fails
	for (const auto& student : fails)
	{
		STUDENT tmpSt;
		SUBJECT tmpSu;
		studentStore.Load(student.first, tmpSt);

		for (const auto& subject : student.second)
		{
			subjectStore.Load(subject, tmpSu);

			currentRow.Format(_T("%d %s %s %s"),
				student.first,
				CString{ tmpSt.szFirstName },
				CString{ tmpSt.szLastName },
				CString{ tmpSu.szName });

			failsList.AddString(currentRow);
		}
	}

	// Print bad grades
	for (const auto& student : consecutiveBads)
	{
		STUDENT tmpSt;
		SUBJECT tmpSu;
		studentStore.Load(student.first, tmpSt);

		if (student.second.size() >= 3)
		{

			for (const auto& subject : student.second)
			{
				subjectStore.Load(subject, tmpSu);

				currentRow.Format(_T("%d %s %s %s"),
					student.first,
					CString{ tmpSt.szFirstName },
					CString{ tmpSt.szLastName },
					CString{ tmpSu.szName });

				badGradesList.AddString(currentRow);
			}
		}
	}
	return TRUE;
}

FailsDlg::~FailsDlg()
{
}

void FailsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, failsList);
	DDX_Control(pDX, IDC_LIST2, badGradesList);
}


BEGIN_MESSAGE_MAP(FailsDlg, CDialog)
END_MESSAGE_MAP()


// FailsDlg message handlers
