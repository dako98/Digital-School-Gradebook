// AllStudentsDlg.cpp : implementation file
//

#include "pch.h"
#include "InternProject1.h"
#include "AllStudentsDlg.h"
#include "afxdialogex.h"

#include "StudentStore.h"

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

BOOL AllStudentsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	std::vector<Student> allStudents = StudentStore::GetInstance()->GetAllStudents();

	CString currentRow;

	for (const Student& student : allStudents)
	{
		currentRow.Format(_T("%d %s %s"), student.GetNumber(), student.getName(), student.GetBirthday().Format());

		allStudentsList.AddString(currentRow);
	}
	return 0;
}

void AllStudentsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, allStudentsList);
	DDX_LBString(pDX, IDC_LIST2, allStudentsListVal);
}


BEGIN_MESSAGE_MAP(AllStudentsDlg, CDialog)
END_MESSAGE_MAP()


// AllStudentsDlg message handlers
