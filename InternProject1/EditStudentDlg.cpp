// EditStudentDlg.cpp : implementation file
//

#include "pch.h"
#include "InternProject1.h"
#include "EditStudentDlg.h"
#include "afxdialogex.h"

#include "StudentStore.h"
#include "Teacher.h"
#include "TeacherStore.h"


// EditStudentDlg dialog

IMPLEMENT_DYNAMIC(EditStudentDlg, CDialog)

EditStudentDlg::EditStudentDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_EDIT_STUDENT, pParent)
	, studentNameVal(_T(""))
	, studentBirthdayVal(COleDateTime::GetCurrentTime())
{

}

EditStudentDlg::~EditStudentDlg()
{
}

BOOL EditStudentDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	studentsRadioBtn.SetCheck(true);
	PrintStudents();

	UpdateData();
//	studentsComboBox.GetLBText(studentsComboBox.GetCurSel(), currentRow);

	return 0;
}

void EditStudentDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, studentsComboBox);
	DDX_Text(pDX, IDC_EDIT1, studentNameVal);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, studentBirthdayVal);
	DDX_Control(pDX, IDC_EDIT1, studentName);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, studentBirthday);
	DDX_Control(pDX, IDC_RADIO1, studentsRadioBtn);
	DDX_Control(pDX, IDC_RADIO2, teachersRadioBtn);
}


BEGIN_MESSAGE_MAP(EditStudentDlg, CDialog)
	ON_BN_CLICKED(IDOK, &EditStudentDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_RADIO2, &EditStudentDlg::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO1, &EditStudentDlg::OnBnClickedRadio1)
END_MESSAGE_MAP()


// EditStudentDlg message handlers


void EditStudentDlg::OnBnClickedOk()
{
	UpdateData();

	if (studentsRadioBtn.GetCheck() == BST_CHECKED)
	{
//		allStudents = StudentStore::GetInstance()->GetAllStudents();

		// TODO: Add your control notification handler code here
		if (allStudents.size() > 0)
		{
			int studentID = allStudents[studentsComboBox.GetCurSel()].GetNumber();

			try
			{
				StudentStore::GetInstance()->EditStudent(studentID, studentNameVal, studentBirthdayVal);
			}
			catch (const std::out_of_range& e)
			{
				// TODO: Handle
			}
			catch (const std::invalid_argument& e)
			{
				// TODO: Handle
			}
		}
	}
	else
	{
//		std::vector<Teacher> allTeachers = TeacherStore::GetInstance()->GetAllTeachers();

		// TODO: Add your control notification handler code here
		if (allTeachers.size() > 0)
		{
			int teacherID = allTeachers[studentsComboBox.GetCurSel()].GetID();

			try
			{
				TeacherStore::GetInstance()->EditTeacher(teacherID, studentNameVal);
			}
			catch (const std::out_of_range& e)
			{
				// TODO: Handle
			}
			catch (const std::invalid_argument& e)
			{
				// TODO: Handle
			}
		}
	}

	CDialog::OnOK();
}

void EditStudentDlg::PrintStudents()
{
	allStudents = StudentStore::GetInstance()->GetAllStudents();

	CString currentRow;

	// Print all the students
	for (const Student& student : allStudents)
	{
		currentRow.Format(_T("%d %s"), student.GetNumber(), student.getName());

		studentsComboBox.AddString(currentRow);
	}
	if (allStudents.size() > 0)
	{
		studentsComboBox.SetCurSel(0);
		studentName.SetWindowTextW(allStudents[studentsComboBox.GetCurSel()].getName());
		studentBirthday.SetTime(allStudents[studentsComboBox.GetCurSel()].GetBirthday());

		//		studentNameVal = allStudents[studentsComboBox.GetCurSel()].getName();
		//		studentBirthdayVal = allStudents[studentsComboBox.GetCurSel()].GetBirthday();
	}

}

void EditStudentDlg::PrintTeachers()
{
	allTeachers = TeacherStore::GetInstance()->GetAllTeachers();

	CString currentRow;

	// Print all the teachers
	for (const Teacher& teacher : allTeachers)
	{
		currentRow.Format(_T("%d %s"), teacher.GetID(), teacher.getName());

		studentsComboBox.AddString(currentRow);
	}
	if (allTeachers.size() > 0)
	{
		studentsComboBox.SetCurSel(0);
		studentName.SetWindowTextW(allTeachers[studentsComboBox.GetCurSel()].getName());
	}
}

void EditStudentDlg::OnBnClickedRadio2()
{
	// TODO: Add your control notification handler code here
	studentBirthday.EnableWindow(false);
	studentsComboBox.ResetContent();
	studentName.SetWindowTextW(_T(""));

	PrintTeachers();
	UpdateData();
}


void EditStudentDlg::OnBnClickedRadio1()
{
	// TODO: Add your control notification handler code here
	studentBirthday.EnableWindow(true);
	studentsComboBox.ResetContent();
	studentName.SetWindowTextW(_T(""));

	PrintStudents();
	UpdateData();
}
