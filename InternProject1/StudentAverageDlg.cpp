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
#include "CStudentClassDatabaseInterface.h"


std::array<CString, 5> colData = { _T("Class"), _T("Number"), _T("First name"), _T("Last name"), _T("Average grade") };

// StudentAverageDlg dialog

IMPLEMENT_DYNAMIC(StudentAverageDlg, CDialog)

StudentAverageDlg::StudentAverageDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_STUDENT_AVERAGE_GRADE, pParent)
	, m_studentAverageVal(0)
	, m_subjectAverageVal(0)
	, m_studentStore(&databaseConnection)
	, m_gradeStore(&databaseConnection)
	, m_subjectStore(&databaseConnection)
{
}

BOOL StudentAverageDlg::PrintStudentsAverage()
{
	int nCount = m_studentsList.GetItemCount();

	// Delete all of the items from the list view control.
	for (int i = 0; i < nCount; i++)
	{
		m_studentsList.DeleteItem(0);
	}

	int nColumnCount = m_studentsList.GetHeaderCtrl()->GetItemCount();

	// Delete all of the columns.
	for (int i = 0; i < nColumnCount; i++)
	{
		m_studentsList.DeleteColumn(0);
	}

	ListView_SetExtendedListViewStyle(m_studentsList, LVS_EX_GRIDLINES);

	std::vector<STUDENT>		allStudents;
	std::vector<STUDENT_CLASS>	allClasses;
	std::vector<GRADE>			allGrades;

	std::unordered_map<int, CString> classNames;
	unsigned int studentsCount;

	StudentDatabaseInterface		studentStore{ &databaseConnection };
	StudentClassDatabaseInterface	classesStore{ &databaseConnection };
	GradeDatabaseInterface			gradeStore	{ &databaseConnection };

	if (!studentStore.LoadAll(allStudents) ||
		!gradeStore.LoadAll(allGrades))
	{
		return FALSE;
	}

	studentsCount = allStudents.size();

	classesStore.LoadAll(allClasses);
	std::vector<int> allClassesIds;
	allClassesIds.reserve(allClasses.size());
	for (const auto& _class : allClasses)
	{
		allClassesIds.push_back(_class.nID);
	}

	int colsCount = colData.size();
	for (int i = 0; i < colsCount; ++i)
	{
		m_studentsList.InsertColumn(i, colData[i], LVCFMT_CENTER, 80);
	}

	CString text;

	//	std::vector <CString> classNames;
	IDtoNameMapper(&databaseConnection, _T("Classes"), _T("ID"), _T("Name"), allClassesIds, classNames);

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

	for (size_t i = 0; i < studentsCount; i++)
	{
		text.Format(_T("%d"), i + 1);
		m_studentsList.InsertItem(0, text);
	}

	for (int i = 0; i < studentsCount; ++i)
	{
		text.Format(_T("%s"), classNames[allStudents[i].classID]);
		m_studentsList.SetItemText(i, 0, text);

		text.Format(_T("%d"), allStudents[i].numberInClass);
		m_studentsList.SetItemText(i, 1, text);

		text.Format(_T("%s"), allStudents[i].szFirstName);
		m_studentsList.SetItemText(i, 2, text);

		text.Format(_T("%s"), allStudents[i].szLastName);
		m_studentsList.SetItemText(i, 3, text);

		if (studentAverageGrade[allStudents[i].nID] < GRADE_EPS)
		{
			m_studentsList.SetItemText(i, 4, _T("-"));
		}
		else
		{
			text.Format(_T("%g"), studentAverageGrade[allStudents[i].nID] + (2 - GRADE::F));
			m_studentsList.SetItemText(i, 4, text);
		}
	}
	return TRUE;
}

BOOL StudentAverageDlg::PrintClassesAverage()
{
	int nCount = m_classesList.GetItemCount();

	// Delete all of the items from the list view control.
	for (int i = 0; i < nCount; i++)
	{
		m_classesList.DeleteItem(0);
	}

	int nColumnCount = m_classesList.GetHeaderCtrl()->GetItemCount();

	// Delete all of the columns.
	for (int i = 0; i < nColumnCount; i++)
	{
		m_classesList.DeleteColumn(0);
	}



	ListView_SetExtendedListViewStyle(m_classesList, LVS_EX_GRIDLINES);

	std::vector<STUDENT>		allStudents;
	std::vector<STUDENT_CLASS>	allClasses;
	std::vector<GRADE>			allGrades;

	std::unordered_map<int, CString> classNames;
	unsigned int studentsCount;

	StudentDatabaseInterface		studentStore{ &databaseConnection };
	StudentClassDatabaseInterface	classesStore{ &databaseConnection };
	GradeDatabaseInterface			gradeStore	{ &databaseConnection };

	if (!studentStore.LoadAll(allStudents) ||
		!gradeStore.LoadAll(allGrades) ||
		!classesStore.LoadAll(allClasses))
	{
		return FALSE;
	}

	studentsCount = allStudents.size();

	std::vector<int>	allClassesIds;
	allClassesIds.reserve(allClasses.size());
	for (const auto& _class : allClasses)
	{
		allClassesIds.push_back(_class.nID);
	}

	int colsCount = allClasses.size();
	for (int i = 0; i < colsCount; ++i)
	{
		m_classesList.InsertColumn(i, allClasses[i].szName, LVCFMT_CENTER, 80);
	}

	CString text;

	// get grades count and sum for each student ID
	std::unordered_map<int, std::pair<int, int>> preAverageData;
	for (const auto& grade : allGrades)
	{
		STUDENT st;
		for (auto& student : allStudents)
		{
			if (student.nID == grade.nStudentID)
			{
				st = student;
				break;
			}
		}

		preAverageData[st.classID].first++;
		preAverageData[st.classID].second += grade.value;
	}

	// calculate average for each class
	std::unordered_map<int, double> classAverageGrade;
	for (const auto& _class : preAverageData)
	{
		assert(_class.second.first > 0);
		classAverageGrade[_class.first] = (double)_class.second.second / _class.second.first;
		// Note: No division by zero, because if there are no grades, the entry would not exist.
	}

	m_classesList.InsertItem(0, _T(""));

	for (int i = 0; i < colsCount; ++i)
	{
		if (classAverageGrade[allClasses[i].nID] < GRADE_EPS)
		{
			m_classesList.SetItemText(0, i, _T("-"));
		}
		else
		{
			text.Format(_T("%g"), classAverageGrade[allClasses[i].nID] + (2 - GRADE::F));
			m_classesList.SetItemText(0, i, text);
		}
	}

	return TRUE;
}

BOOL StudentAverageDlg::PrintSchoolAverage()
{
	double average;
	int sum = 0;
	std::vector<GRADE> allGrades;
	GradeDatabaseInterface gradeStore{ &databaseConnection };
	if (!gradeStore.LoadAll(allGrades))
	{
		return FALSE;
	}

	for (const auto& grade : allGrades)
	{
		sum += grade.value;
	}
	average = (double)sum / allGrades.size();
	CString text;
	if (average < GRADE_EPS)
	{
		m_schoolAverageGrade.SetWindowText(_T("-"));
	}
	else
	{
		text.Format(_T("%g"), average + (2 - GRADE::F));
	}

	m_schoolAverageGrade.SetWindowText(text);
	return TRUE;
}

BOOL StudentAverageDlg::OnInitDialog()
{
	if (!CDialog::OnInitDialog())
	{
		return FALSE;
	}
	
	if (!PrintStudentsAverage())
	{
		return FALSE;
	}

	if (!PrintClassesAverage())
	{
		return FALSE;
	}

	if (!PrintSchoolAverage())
	{
		return FALSE;
	}

	return TRUE;
}

StudentAverageDlg::~StudentAverageDlg()
{
}

void StudentAverageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STUDENTS_LIST, m_studentsList);
	DDX_Control(pDX, IDC_CLASSES_LIST, m_classesList);
	DDX_Control(pDX, IDC_SCHOOL_AVERAGE_EDIT, m_schoolAverageGrade);
}


BEGIN_MESSAGE_MAP(StudentAverageDlg, CDialog)
	ON_CBN_SELCHANGE(IDD_STUDENT_AVERAGE_GRADE_STUDENT_COMBO, &StudentAverageDlg::OnCbnSelchangeStudent)
	ON_CBN_SELCHANGE(IDD_STUDENT_AVERAGE_GRADE_SUBJECT_COMBO, &StudentAverageDlg::OnCbnSelchangeSubject)
END_MESSAGE_MAP()


// StudentAverageDlg message handlers


void StudentAverageDlg::OnCbnSelchangeStudent()
{
}


void StudentAverageDlg::OnCbnSelchangeSubject()
{
}
