// RemoveStudentDlg.cpp : implementation file
//

#include "pch.h"
#include "InternProject1.h"
#include "RemoveStudentDlg.h"
#include "afxdialogex.h"

#include <vector>

#include "StudentStore.h"
#include "GradeStore.h"


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

	allStudents = StudentStore::GetInstance()->GetAllStudents();


	studentList.ResetContent();

	// Print all the students
	populateList(studentList, allStudents);
	UpdateData();


	return 0;
}

void RemoveStudentDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, studentList);
}


BEGIN_MESSAGE_MAP(RemoveStudentDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &RemoveStudentDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// RemoveStudentDlg message handlers


void RemoveStudentDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here

	UpdateData();
	allStudents = StudentStore::GetInstance()->GetAllStudents();

	// TODO: Add your control notification handler code here
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
	}
	populateList(studentList, allStudents);
	UpdateData();
}
