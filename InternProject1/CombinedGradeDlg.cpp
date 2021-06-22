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
	, store(gradesPath)
	, tmp(data)
{
}

void CombinedGradeDlg::PrintAllStudents()
{
	std::vector<STUDENT> allStudents;
	//= StudentStore::GetInstance()->GetAllStudents();
	Storage<STUDENT> st(studentsPath);
	st.LoadAll(allStudents);

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

void CombinedGradeDlg::PrintAllSubjects()
{
	std::vector<SUBJECT> allStudents;
	//= StudentStore::GetInstance()->GetAllStudents();
	Storage<SUBJECT> st(subjectsPath);
	st.LoadAll(allStudents);

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

BOOL CombinedGradeDlg::OnInitDialog()
{
	if (!CDialog::OnInitDialog())
		return FALSE;


	gradeIDVal = tmp.nID;

	// Load all students
	PrintAllStudents();

	// Select student
	studentDropdown.SetCurSel(GetIndexByData(tmp.nStudentID, studentDropdown));

	// Load all subjects
	PrintAllSubjects();

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

	case DialogMode::eDialogMode_None:

	default:
		throw std::exception{ "Invalid window state." };
		break;
	}
	return 0;
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

		isOK = store.Add(st);
		break;

	case DialogMode::eDialogMode_Edit:

		isOK = store.Edit(st);
		break;

	case DialogMode::eDialogMode_Remove:

		isOK = store.Delete(st.nID);
		break;

	case DialogMode::eDialogMode_View:
	case DialogMode::eDialogMode_None:
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
