// AllStudentsDlg.cpp : implementation file
//

#include "pch.h"
#include "InternProject1.h"
#include "AllStudentsDlg.h"
#include "afxdialogex.h"

#include "StudentStore.h"
#include "Teacher.h"
#include "TeacherStore.h"

// AllStudentsDlg dialog

IMPLEMENT_DYNAMIC(AllStudentsDlg, CDialog)

AllStudentsDlg::AllStudentsDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_ALL_STUDENTS, pParent)
	, allStudentsListVal(_T(""))
{
}

AllStudentsDlg::~AllStudentsDlg()
{
}

void AllStudentsDlg::PrintAllStudents()
{
	std::vector<Student> allStudents = StudentStore::GetInstance()->GetAllStudents();

	CString currentRow;

	for (const Student& student : allStudents)
	{
		currentRow.Format(_T("%d %s %s"), student.GetNumber(), student.getName(), student.GetBirthday().Format());

		allStudentsList.AddString(currentRow);
	}
}

BOOL AllStudentsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	PrintAllStudents();
	studentsRadioBtn.SetCheck(true);

	return 0;
}

void AllStudentsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, allStudentsList);
	DDX_LBString(pDX, IDC_LIST2, allStudentsListVal);
	DDX_Control(pDX, IDC_RADIO4, studentsRadioBtn);
}


BEGIN_MESSAGE_MAP(AllStudentsDlg, CDialog)
	ON_BN_CLICKED(IDC_RADIO4, &AllStudentsDlg::OnBnClickedRadio4)
	ON_BN_CLICKED(IDC_RADIO5, &AllStudentsDlg::OnBnClickedRadio5)
END_MESSAGE_MAP()


// AllStudentsDlg message handlers


void AllStudentsDlg::OnBnClickedRadio4()
{
	// TODO: Add your control notification handler code here
	allStudentsList.ResetContent();
	PrintAllStudents();
}

void AllStudentsDlg::PrintAllTeachers()
{
	std::vector<Teacher> allTeachers = TeacherStore::GetInstance()->GetAllTeachers();

	CString currentRow;

	for (const Teacher& teacher : allTeachers)
	{
		currentRow.Format(_T("%d %s"), teacher.GetID(), teacher.getName());

		allStudentsList.AddString(currentRow);
	}
}

void AllStudentsDlg::OnBnClickedRadio5()
{
	// TODO: Add your control notification handler code here
	allStudentsList.ResetContent();
	PrintAllTeachers();
}
