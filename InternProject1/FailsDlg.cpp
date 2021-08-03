// FailsDlg.cpp : implementation file
//

#include "pch.h"
#include "InternProject1.h"
#include "FailsDlg.h"
#include "afxdialogex.h"

#include <vector>
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
	, m_studentStore(_T("Students"), &databaseConnection)
	, m_subjectStore(_T("Subjects"), &databaseConnection)
	, m_gradeStore(_T("Grades"), &databaseConnection)
{

}

BOOL FailsDlg::OnInitDialog()
{
	if (!CDialog::OnInitDialog())
		return FALSE;

	BOOL isOK;

	// Load all grades
//	Storage<GRADE> gradeStore{ gradesPath };
	std::vector<GRADE> allGrades;
	isOK = m_gradeStore.LoadAll(allGrades);

	if (isOK)
	{

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

		CString currentRow;

		// Print fails
		for (const auto& student : fails)
		{
			STUDENT tmpSt;
			SUBJECT tmpSu;
			isOK = m_studentStore.Load(student.first, tmpSt);

			if (isOK)
			{
				for (const auto& subject : student.second)
				{
					isOK = m_subjectStore.Load(subject, tmpSu);

					if (!isOK)
					{
						break;
					}

					currentRow.Format(_T("%d %s %s %s"),
						student.first,
						CString{ tmpSt.szFirstName },
						CString{ tmpSt.szLastName },
						CString{ tmpSu.szName });

					failsList.AddString(currentRow);
				}

				if (!isOK)
				{
					break;
				}
			}
		}

		if (isOK)
		{
			// Print bad grades
			for (const auto& student : consecutiveBads)
			{
				STUDENT tmpSt;
				SUBJECT tmpSu;
				isOK = m_studentStore.Load(student.first, tmpSt);

				if (isOK && student.second.size() >= 3)
				{

					for (const auto& subject : student.second)
					{
						isOK = m_subjectStore.Load(subject, tmpSu);

						if (!isOK)
						{
							break;
						}

						currentRow.Format(_T("%d %s %s %s"),
							student.first,
							CString{ tmpSt.szFirstName },
							CString{ tmpSt.szLastName },
							CString{ tmpSu.szName });

						badGradesList.AddString(currentRow);
					}

					if (!isOK)
					{
						break;
					}
				}
			}
		}
	}

	return isOK;
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
