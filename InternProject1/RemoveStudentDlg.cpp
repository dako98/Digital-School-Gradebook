// RemoveStudentDlg.cpp : implementation file
//

#include "pch.h"
#include "InternProject1.h"
#include "RemoveStudentDlg.h"
#include "afxdialogex.h"

#include <vector>

#include "Utility.h"

#include "StudentStore.h"
#include "GradeStore.h"
#include "TeacherStore.h"


// RemoveStudentDlg dialog



/*
void populateList(CComboBox& list, const std::vector<Teacher>& src)
{
	list.ResetContent();
	CString currentRow;

	int index = 0;
	for (const Teacher& teacher : src)
	{
		currentRow.Format(_T("%d %s"), teacher.GetID(), teacher.getName());

		int i = list.AddString(currentRow);
		list.SetItemData(i, index);
		index++;
	}
	if (src.size() > 0)
	{
		list.SetCurSel(0);
	}
}
*/


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
			int studentID = allStudents[studentList.GetItemData(studentList.GetCurSel())].GetNumber();

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
			int teacherID = allTeachers[studentList.GetItemData(studentList.GetCurSel())].GetID();

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

	populateList(studentList, allStudents);
}

void RemoveStudentDlg::PrintTeachers()
{
	allTeachers = TeacherStore::GetInstance()->GetAllTeachers();

	populateList(studentList, allTeachers);
}

