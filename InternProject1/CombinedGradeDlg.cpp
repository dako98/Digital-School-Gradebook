// CombinedGradeDlg.cpp : implementation file
//

#include "pch.h"
#include "InternProject1.h"
#include "CombinedGradeDlg.h"
#include "afxdialogex.h"

#include "CStudent.h"
#include "CSubject.h"
#include "Utility.h"


// CombinedGradeDlg dialog

IMPLEMENT_DYNAMIC(CombinedGradeDlg, CDialog)

CombinedGradeDlg::CombinedGradeDlg(DialogMode eMode, const GRADE& data)
	: CDialog(IDD_GRADES_COMBINED, nullptr)
	, m_eDialogMode(eMode)
	, gradeIDVal(0)
	, tmp(data)
	, gradeStore(new GradeDatabaseInterface(_T("Grades"), &databaseConnection))
	, studentStore(new StudentDatabaseInterface(_T("Students"), &databaseConnection))
	, subjectStore(new SubjectDatabaseInterface(_T("Subjects"), &databaseConnection))
{
}

BOOL CombinedGradeDlg::PrintAllStudents()
{
	BOOL isOK;

	std::vector<STUDENT> allStudents;
//	Storage<STUDENT> st{ studentsPath };
	isOK = studentStore->LoadAll(allStudents);

	if (isOK)
	{
		CString currentRow;

		for (const auto& student : allStudents)
		{
			currentRow.Format(_T("%d %s %s"),
				student.nID,
				CString{ student.szFirstName },
				CString{ student.szLastName });

			int index = studentDropdown.AddString(currentRow);
			studentDropdown.SetItemData(index, student.nID);
		}
	}
	return isOK;
}

BOOL CombinedGradeDlg::PrintAllSubjects()
{
	BOOL isOK;

	std::vector<SUBJECT> allStudents;
//	Storage<SUBJECT> st{ subjectsPath };
	isOK = subjectStore->LoadAll(allStudents);

	if (isOK)
	{
		CString currentRow;

		for (const auto& student : allStudents)
		{
			currentRow.Format(_T("%d %s"),
				student.nID,
				CString{ student.szName });

			int index = subjectDropdown.AddString(currentRow);
			subjectDropdown.SetItemData(index, student.nID);
		}
	}
	return isOK;
}

BOOL CombinedGradeDlg::OnInitDialog()
{
	if (!CDialog::OnInitDialog())
		return FALSE;

	BOOL isOK;


	if (m_eDialogMode != DialogMode::eDialogMode_Add)
	{
		gradeIDVal = tmp.nID;
	}
	else
	{
//		gradeStore->NextID(gradeIDVal);
	}

	// Load all students
	isOK = PrintAllStudents();

	if (isOK)
	{
		// Select student
		studentDropdown.SetCurSel(GetIndexByData(tmp.nStudentID, studentDropdown));

		// Load all subjects
		isOK = PrintAllSubjects();
	}

	if (isOK)
	{
		// Select subject
		subjectDropdown.SetCurSel(GetIndexByData(tmp.nSubjectID, subjectDropdown));


		// Load all grade values
		for (size_t i = GRADE::GRADES::INVALID + 1; i < GRADE::GRADES::COUNT; i++)
		{
			int index = gradeDropdown.AddString(MapGradeName(i));
			gradeDropdown.SetItemData(index, i);
		}

		// Select grade value
		gradeDropdown.SetCurSel(GetIndexByData(tmp.value, gradeDropdown));

		// Select date
		gradeDateVal = tmp.dtDate;
	}

	UpdateData(FALSE);

	switch (m_eDialogMode)
	{
	case DialogMode::eDialogMode_Remove:

		studentDropdown.EnableWindow(FALSE);
		subjectDropdown.EnableWindow(FALSE);
		gradeDropdown.EnableWindow(FALSE);
		gradeDate.EnableWindow(FALSE);

		break;

	case DialogMode::eDialogMode_Add:

		studentDropdown.EnableWindow(TRUE);
		subjectDropdown.EnableWindow(TRUE);
		gradeDropdown.EnableWindow(TRUE);
		gradeDate.EnableWindow(TRUE);

		UpdateData(FALSE);

		break;

	case DialogMode::eDialogMode_Edit:

		studentDropdown.EnableWindow(FALSE);
		subjectDropdown.EnableWindow(TRUE);
		gradeDropdown.EnableWindow(TRUE);
		gradeDate.EnableWindow(TRUE);
		break;

	default:
		throw std::exception{ "Invalid window state." };
		break;
	}
	return isOK;
}

CombinedGradeDlg::~CombinedGradeDlg()
{
}

void CombinedGradeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, gradeIDVal);
	DDX_Control(pDX, IDC_GRADES_STUDENT_COMBO, studentDropdown);
	DDX_Control(pDX, IDC_COMBO2, subjectDropdown);
	DDX_Control(pDX, IDC_COMBO3, gradeDropdown);
	DDX_Control(pDX, IDC_GRADE_DATETIMEPICKER1, gradeDate);
	DDX_DateTimeCtrl(pDX, IDC_GRADE_DATETIMEPICKER1, gradeDateVal);
}


BEGIN_MESSAGE_MAP(CombinedGradeDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CombinedGradeDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CombinedGradeDlg message handlers


void CombinedGradeDlg::OnBnClickedOk()
{
	UpdateData();

	BOOL isOK = TRUE;
	GRADE st;

	st.nID = gradeIDVal;
	st.nStudentID = studentDropdown.GetItemData(studentDropdown.GetCurSel());
	st.nSubjectID = subjectDropdown.GetItemData(subjectDropdown.GetCurSel());
	st.value = gradeDropdown.GetItemData(gradeDropdown.GetCurSel());
	gradeDateVal.GetAsDBTIMESTAMP(st.dtDate);


	switch (m_eDialogMode)
	{
	case DialogMode::eDialogMode_Add:

		isOK = gradeStore->Add(st);
		break;

	case DialogMode::eDialogMode_Edit:

		isOK = gradeStore->Edit(st);
		break;

	case DialogMode::eDialogMode_Remove:

		isOK = gradeStore->Delete(st.nID);
		break;

	default:

		break;
	}

	if (!isOK)
	{
		int errorBox = MessageBox((LPCWSTR)L"Error! Check your input.", NULL, MB_OK | MB_ICONWARNING);
		return;
	}
	CDialog::OnOK();
}
