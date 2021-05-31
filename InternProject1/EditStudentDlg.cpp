// EditStudentDlg.cpp : implementation file
//

#include "pch.h"
#include "InternProject1.h"
#include "EditStudentDlg.h"
#include "afxdialogex.h"

#include "StudentStore.h"


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
}


BEGIN_MESSAGE_MAP(EditStudentDlg, CDialog)
	ON_BN_CLICKED(IDOK, &EditStudentDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// EditStudentDlg message handlers


void EditStudentDlg::OnBnClickedOk()
{
	UpdateData();
	allStudents = StudentStore::GetInstance()->GetAllStudents();

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
	CDialog::OnOK();
}
