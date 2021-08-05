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
	, m_studentAverageVal(0)
	, m_subjectAverageVal(0)
	, m_studentStore(_T("Students"), &databaseConnection)
	, m_gradeStore(_T("Grades"), &databaseConnection)
	, m_subjectStore(_T("Subjects"), &databaseConnection)
{
}

BOOL StudentAverageDlg::PrintAllStudents()
{
	BOOL isOK;

	std::vector<STUDENT> allStudents;
	isOK = m_studentStore.LoadAll(allStudents);

	CString currentRow;

	if (isOK)
	{
		for (const auto& student : allStudents)
		{
			currentRow.Format(_T("%d %s %s"),
				student.nID,
				CString{ student.szFirstName },
				CString{ student.szLastName });

			int index = m_studentDropList.AddString(currentRow);
			m_studentDropList.SetItemData(index, student.nID);
		}
	}
	return isOK;
}

BOOL StudentAverageDlg::PrintAllSubjects()
{
	BOOL isOK;
	std::vector<SUBJECT> allSubjects;
	isOK = m_subjectStore.LoadAll(allSubjects);

	CString currentRow;
	if (isOK)
	{
		for (const auto& subject : allSubjects)
		{
			currentRow.Format(_T("%d %s"),
				subject.nID,
				CString{ subject.szName });

			int index = m_subjectDropList.AddString(currentRow);
			m_subjectDropList.SetItemData(index, subject.nID);
		}
	}
	return isOK;
}


BOOL StudentAverageDlg::UpdateAverage()
{
	int index = m_studentDropList.GetCurSel();
	int studentID = -1;
	int subjectID = -1;
	BOOL isOK = TRUE;

	if (index != CB_ERR)
	{
		std::vector<GRADE> grades;
		isOK = m_gradeStore.LoadAll(grades);
		std::vector<GRADE> studentGrades;

		if (isOK)
		{

			studentID = m_studentDropList.GetItemData(index);

			index = m_subjectDropList.GetCurSel();

			if (index != CB_ERR)
			{
				subjectID = m_subjectDropList.GetItemData(index);
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

			float tmpStVal = (studentSum / (float)(studentCount > 0 ? studentCount : 1));
			float tmpSuVal = (subjectSum / (float)(subjectCount > 0 ? subjectCount : 1));

			m_studentAverageVal = (tmpStVal < GRADE::GRADES::INVALID + 1 ? 0 : GRADE::GRADES::INVALID + 1 + tmpStVal);
			m_subjectAverageVal = (tmpSuVal < GRADE::GRADES::INVALID + 1 ? 0 : GRADE::GRADES::INVALID + 1 + tmpSuVal);
		}
	}

	UpdateData(FALSE);

	return isOK;
}

BOOL StudentAverageDlg::OnInitDialog()
{
	if (!CDialog::OnInitDialog())
		return FALSE;

	BOOL isOK;

	// Load students
	isOK = PrintAllStudents();

	if (isOK)
	{
		// Load subjects
		isOK = PrintAllSubjects();
	}

	if (isOK)
	{
		// Update averages
		isOK = UpdateAverage();
	}

	return isOK;
}

StudentAverageDlg::~StudentAverageDlg()
{
}

void StudentAverageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_studentDropList);
	DDX_Control(pDX, IDC_COMBO2, m_subjectDropList);
	DDX_Control(pDX, IDC_EDIT1, m_studentAverage);
	DDX_Control(pDX, IDC_EDIT2, m_subjectAverage);
	DDX_Text(pDX, IDC_EDIT1, m_studentAverageVal);
	DDX_Text(pDX, IDC_EDIT2, m_subjectAverageVal);
}


BEGIN_MESSAGE_MAP(StudentAverageDlg, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBO1, &StudentAverageDlg::OnCbnSelchangeCombo1)
	ON_CBN_SELCHANGE(IDC_COMBO2, &StudentAverageDlg::OnCbnSelchangeCombo2)
END_MESSAGE_MAP()


// StudentAverageDlg message handlers


void StudentAverageDlg::OnCbnSelchangeCombo1()
{
	if (!UpdateAverage())
	{
		int errorBox = MessageBox((LPCWSTR)L"Error retrieving list.", NULL, MB_OK | MB_ICONWARNING);
	}
}


void StudentAverageDlg::OnCbnSelchangeCombo2()
{
	if (!UpdateAverage())
	{
		int errorBox = MessageBox((LPCWSTR)L"Error retrieving list.", NULL, MB_OK | MB_ICONWARNING);
	}
}
