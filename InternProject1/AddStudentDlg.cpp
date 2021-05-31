// AddStudentDlg.cpp : implementation file
//

#include "pch.h"
#include "InternProject1.h"
#include "AddStudentDlg.h"
#include "afxdialogex.h"

#include "StudentStore.h"


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

void AddStudentDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, studentNameVal);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, studentBirthdayVal);
}


BEGIN_MESSAGE_MAP(AddStudentDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &AddStudentDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// AddStudentDlg message handlers


void AddStudentDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	UpdateData();

	CString name = studentNameVal;
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
	CDialogEx::OnOK();
}
