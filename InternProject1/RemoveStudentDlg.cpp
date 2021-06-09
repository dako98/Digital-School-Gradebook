// RemoveStudentDlg.cpp : implementation file
//

#include "pch.h"
#include "InternProject1.h"
#include "RemoveStudentDlg.h"
#include "afxdialogex.h"

#include <vector>

#include "StudentStore.h"
#include "GradeStore.h"
#include "TeacherStore.h"


// RemoveStudentDlg dialog


void populateList(CComboBox& list, const std::vector<Student>& src)
{
	list.ResetContent();
	CString currentRow;

	for (const Student& student : src)
	{
		currentRow.Format(_T("%d %s"), student.GetNumber(), student.getName());

		list.AddString(currentRow);
	}
	if (src.size() > 0)
	{
		list.SetCurSel(0);
	}
}


IMPLEMENT_DYNAMIC(RemoveStudentDlg, CDialog)

RemoveStudentDlg::RemoveStudentDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_REMOVE_STUDENT_DIALOG, pParent)
{

}

RemoveStudentDlg::~RemoveStudentDlg()
{
}

BOOL RemoveStudentDlg::OnInitDialog()
{
	CDialog::OnInitDialog();


	studentRadioBtn.SetCheck(true);
	PrintStudents();

	UpdateData();

	//	studentsComboBox.GetLBText(studentsComboBox.GetCurSel(), currentRow);


	//allStudents = StudentStore::GetInstance()->GetAllStudents();


	//studentList.ResetContent();

	//// Print all the students
	//populateList(studentList, allStudents);
	//UpdateData();


	return 0;
}

void RemoveStudentDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, studentList);
	DDX_Control(pDX, IDC_RADIO1, studentRadioBtn);
	DDX_Control(pDX, IDC_RADIO2, teacherRadioBtn);
}


BEGIN_MESSAGE_MAP(RemoveStudentDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &RemoveStudentDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_RADIO1, &RemoveStudentDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &RemoveStudentDlg::OnBnClickedRadio2)
END_MESSAGE_MAP()


// RemoveStudentDlg message handlers


void RemoveStudentDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here

	UpdateData();
//	allStudents = StudentStore::GetInstance()->GetAllStudents();

	if (studentRadioBtn.GetState() == BST_CHECKED)
	{

		if (allStudents.size() > 0)
		{
			int studentID = allStudents[studentList.GetCurSel()].GetNumber();

			try
			{
				GradeStore::GetInstance()->ClearStudent(studentID);
			}
			catch (const std::out_of_range& e)
			{
				// TODO: Handle
			}
			catch (const std::invalid_argument& e)
			{
				// TODO: Handle
			}

			try
			{
				StudentStore::GetInstance()->RemoveStudent(studentID);
			}
			catch (const std::out_of_range& e)
			{
				// TODO: Handle
			}
			catch (const std::invalid_argument& e)
			{
				// TODO: Handle
			}
			// FIXME: Clearing list does not work.
	//		studentList.DeleteString(studentList.GetCurSel());
//		populateList(studentList, allStudents);
		PrintStudents();
		}
	}
	else
	{
		if (allTeachers.size() > 0)
		{
			int teacherID = allTeachers[studentList.GetCurSel()].GetID();

			try
			{
				TeacherStore::GetInstance()->RemoveTeacher(teacherID);
			}
			catch (const std::out_of_range& e)
			{
				// TODO: Handle
			}
			catch (const std::invalid_argument& e)
			{
				// TODO: Handle
			}
			PrintTeachers();
		}
	}
	UpdateData();
}


void RemoveStudentDlg::OnBnClickedRadio1()
{
	// TODO: Add your control notification handler code here
	studentList.ResetContent();
	PrintStudents();
}


void RemoveStudentDlg::OnBnClickedRadio2()
{
	// TODO: Add your control notification handler code here
	studentList.ResetContent();
	PrintTeachers();
}


void RemoveStudentDlg::PrintStudents()
{
	allStudents = StudentStore::GetInstance()->GetAllStudents();

	CString currentRow;

	// Print all the students
	for (const Student& student : allStudents)
	{
		currentRow.Format(_T("%d %s"), student.GetNumber(), student.getName());

		studentList.AddString(currentRow);
	}
	if (allStudents.size() > 0)
	{
		studentList.SetCurSel(0);

	}

}

void RemoveStudentDlg::PrintTeachers()
{
	allTeachers = TeacherStore::GetInstance()->GetAllTeachers();

	CString currentRow;

	// Print all the teachers
	for (const Teacher& teacher : allTeachers)
	{
		currentRow.Format(_T("%d %s"), teacher.GetID(), teacher.getName());

		studentList.AddString(currentRow);
	}
	if (allTeachers.size() > 0)
	{
		studentList.SetCurSel(0);
	}
}