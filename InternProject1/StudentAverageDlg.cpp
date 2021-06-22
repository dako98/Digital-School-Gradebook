// StudentAverageDlg.cpp : implementation file
//

#include "pch.h"
#include "InternProject1.h"
#include "StudentAverageDlg.h"
#include "afxdialogex.h"

#include <vector>

#include "Utility.h"

#include "Storage.h"
#include "CStudent.h"
#include "CSubject.h"
#include "CGrade.h"

// StudentAverageDlg dialog

IMPLEMENT_DYNAMIC(StudentAverageDlg, CDialog)

StudentAverageDlg::StudentAverageDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_STUDENT_AVERAGE_GRADE, pParent)
	, studentAverageVal(0)
	, subjectAverageVal(0)
{

}

void StudentAverageDlg::PrintAllStudents()
{
	std::vector<STUDENT> allStudents;
	Storage<STUDENT> st(studentsPath);
	st.LoadAll(allStudents);

	CString currentRow;

	for (const auto& student : allStudents)
	{
		currentRow.Format(_T("%d %s %s"),
			student.nID,
			CString{ student.szFirstName },
			CString{ student.szLastName });

		int index = studentDropList.AddString(currentRow);
		studentDropList.SetItemData(index, student.nID);
	}
}

void StudentAverageDlg::PrintAllSubjects()
{
	std::vector<SUBJECT> allSubjects;
	Storage<SUBJECT> st(subjectsPath);
	st.LoadAll(allSubjects);

	CString currentRow;

	for (const auto& subject : allSubjects)
	{
		currentRow.Format(_T("%d %s"),
			subject.nID,
			CString{ subject.szName });

		int index = subjectDropList.AddString(currentRow);
		subjectDropList.SetItemData(index, subject.nID);
	}
}


void StudentAverageDlg::UpdateAverage()
{
	int index = studentDropList.GetCurSel();
	int studentID = -1;
	int subjectID = -1;

	if (index != CB_ERR)
	{
		std::vector<GRADE> grades;
		Storage<GRADE> gradeStore(gradesPath);
		gradeStore.LoadAll(grades);
		std::vector<GRADE> studentGrades;

		studentID = studentDropList.GetItemData(index);

		index = subjectDropList.GetCurSel();

		if (index != CB_ERR)
		{
			subjectID = subjectDropList.GetItemData(index);
		}

		int studentSum = 0, studentCount = 0, subjectSum = 0, subjectCount = 0;

		for (const auto& grade : grades)
		{
			if (grade.nStudentID == studentID)
			{
				studentSum += grade.value;
				studentCount++;

				if (grade.nSubjectID == subjectID)
				{
					subjectSum += grade.value;
					subjectCount++;
				}
			}
		}

		studentAverageVal = GRADE::GRADES::INVALID + 1 + (studentSum / (float)(studentCount > 0 ? studentCount : 1));
		subjectAverageVal = GRADE::GRADES::INVALID + 1 + (subjectSum / (float)(subjectCount > 0 ? subjectCount : 1));
	}
	UpdateData(FALSE);
}

BOOL StudentAverageDlg::OnInitDialog()
{
	if (!CDialog::OnInitDialog())
		return FALSE;

	// Load students
	PrintAllStudents();

	// Load subjects
	PrintAllSubjects();

	// Update averages
	UpdateAverage();

	return TRUE;
}

StudentAverageDlg::~StudentAverageDlg()
{
}

void StudentAverageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, studentDropList);
	DDX_Control(pDX, IDC_COMBO2, subjectDropList);
	DDX_Control(pDX, IDC_EDIT1, studentAverage);
	DDX_Control(pDX, IDC_EDIT2, subjectAverage);
	DDX_Text(pDX, IDC_EDIT1, studentAverageVal);
	DDX_Text(pDX, IDC_EDIT2, subjectAverageVal);
}


BEGIN_MESSAGE_MAP(StudentAverageDlg, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBO1, &StudentAverageDlg::OnCbnSelchangeCombo1)
	ON_CBN_SELCHANGE(IDC_COMBO2, &StudentAverageDlg::OnCbnSelchangeCombo2)
END_MESSAGE_MAP()


// StudentAverageDlg message handlers


void StudentAverageDlg::OnCbnSelchangeCombo1()
{
	UpdateAverage();
	// TODO: Add your control notification handler code here
}


void StudentAverageDlg::OnCbnSelchangeCombo2()
{
	UpdateAverage();
	// TODO: Add your control notification handler code here
}
