// CombinedStudentDlg.cpp : implementation file
//

#include "pch.h"
#include "InternProject1.h"
#include "CombinedStudentDlg.h"
#include "afxdialogex.h"

#include "CStudent.h"
#include "Storage.h"

// FIXME: Make it work from the Utility file


// CombinedStudentDlg dialog

IMPLEMENT_DYNAMIC(CombinedStudentDlg, CDialog)

CombinedStudentDlg::CombinedStudentDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_STUDENT_COMBINED, pParent)
	, m_eDialogMode(eDialogMode_None)
	, studentNumberVal(0)
	, studentBirthDateVal(COleDateTime::GetCurrentTime())
	, studentStore(studentsPath)

{

}

CombinedStudentDlg::CombinedStudentDlg(DialogMode eDialogMode)
	: CDialog(IDD_STUDENT_COMBINED, nullptr)
	, m_eDialogMode(eDialogMode)
	, studentNumberVal(0)
	, studentBirthDateVal(COleDateTime::GetCurrentTime())
	, studentStore(studentsPath)
{
}

BOOL CombinedStudentDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	switch (m_eDialogMode)
	{
	case DialogMode::eDialogMode_View:
	case DialogMode::eDialogMode_Remove:

		studentBirthDate.EnableWindow(FALSE);
		studentFirstName.EnableWindow(FALSE);
		studentLastName.EnableWindow(FALSE);
		studentNumber.EnableWindow(FALSE);
		break;

	case DialogMode::eDialogMode_Add:
		studentNumberVal = studentStore.LastID();
		UpdateData(FALSE);

	case DialogMode::eDialogMode_Edit:

		studentBirthDate.EnableWindow(TRUE);
		studentFirstName.EnableWindow(TRUE);
		studentLastName.EnableWindow(TRUE);
		studentNumber.EnableWindow(FALSE);
		break;
	
	case DialogMode::eDialogMode_None:

	default:
		throw std::exception{ "Invalid window state." };
		break;
	}
}

CombinedStudentDlg::~CombinedStudentDlg()
{
}

void CombinedStudentDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, studentNumber);
	DDX_Control(pDX, IDC_EDIT2, studentFirstName);
	DDX_Control(pDX, IDC_EDIT3, studentLastName);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, studentBirthDate);
	DDX_Text(pDX, IDC_EDIT1, studentNumberVal);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, studentBirthDateVal);
}


BEGIN_MESSAGE_MAP(CombinedStudentDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CombinedStudentDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CombinedStudentDlg message handlers


void CombinedStudentDlg::OnBnClickedOk()
{
	UpdateData();
	
	BOOL hasError = TRUE;
	STUDENT st;
	CString buff;

	st.nID = studentNumberVal;

	studentFirstName.GetWindowTextW(buff);

	if (buff.GetLength() <= STUDENT::MAX_NAME_SIZE)
	{
		strcpy_s(st.szFirstName, STUDENT::MAX_NAME_SIZE, CT2A(buff));
	}
	else
	{
		strcpy_s(st.szFirstName, STUDENT::MAX_NAME_SIZE, "");
	}

	studentLastName.GetWindowTextW(buff);

	if (buff.GetLength() <= STUDENT::MAX_NAME_SIZE)
	{
		strcpy_s(st.szLastName, STUDENT::MAX_NAME_SIZE, CT2A(buff));
	}
	else
	{
		strcpy_s(st.szLastName, STUDENT::MAX_NAME_SIZE, "");
	}

	studentBirthDateVal.GetAsDBTIMESTAMP(st.dtBirthDate);


	switch (m_eDialogMode)
	{
	case DialogMode::eDialogMode_Add:

		hasError = studentStore.Add(st);
		break;
	case DialogMode::eDialogMode_Edit:

		hasError = studentStore.Edit(st);
		break;
	case DialogMode::eDialogMode_Remove:

		hasError = studentStore.Delete(st.nID);
		break;
	
	case DialogMode::eDialogMode_View:
	case DialogMode::eDialogMode_None:
	default:

		break;
	}
	
	if (!hasError)
	{
		int errorBox = MessageBox((LPCWSTR)L"Error! Check your input.", NULL, MB_OK | MB_ICONWARNING);
	}

	CDialog::OnOK();
}