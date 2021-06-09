// AddStudentDlg.cpp : implementation file
//

#include "pch.h"
#include "InternProject1.h"
#include "AddStudentDlg.h"
#include "afxdialogex.h"

#include "StudentStore.h"
#include "TeacherStore.h"


// AddStudentDlg dialog

IMPLEMENT_DYNAMIC(AddStudentDlg, CDialogEx)

AddStudentDlg::AddStudentDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ADDSTUDENT, pParent)
	, studentNameVal(_T(""))
	, studentBirthdayVal(COleDateTime::GetCurrentTime())
{

}

AddStudentDlg::~AddStudentDlg()
{
}

BOOL AddStudentDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	studentRadioBtn.SetCheck(true);

	return 0;
}

void AddStudentDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, studentNameVal);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, studentBirthdayVal);
	DDX_Control(pDX, IDC_RADIO1, studentRadioBtn);
	DDX_Control(pDX, IDC_RADIO2, teacherRadioBtn);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, studentBirthday);
}


BEGIN_MESSAGE_MAP(AddStudentDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &AddStudentDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_RADIO1, &AddStudentDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &AddStudentDlg::OnBnClickedRadio2)
END_MESSAGE_MAP()


// AddStudentDlg message handlers


void AddStudentDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	UpdateData();

	CString name = studentNameVal;

	if (studentRadioBtn.GetState() == BST_CHECKED)
	{

		COleDateTime birthday = studentBirthdayVal;

		try
		{
			StudentStore::GetInstance()->AddStudent(name, birthday);
		}
		catch (std::invalid_argument& e)
		{
			// TODO: Error message
			return;
		}
	}
	else
	{
		try
		{
			TeacherStore::GetInstance()->AddTeacher(name);
		}
		catch (std::invalid_argument& e)
		{
			// TODO: Error message
			return;
		}
	}
	CDialogEx::OnOK();
}


void AddStudentDlg::OnBnClickedRadio1()
{
	// TODO: Add your control notification handler code here
	studentBirthday.EnableWindow(true);
}


void AddStudentDlg::OnBnClickedRadio2()
{
	// TODO: Add your control notification handler code here
	studentBirthday.EnableWindow(false);
}
