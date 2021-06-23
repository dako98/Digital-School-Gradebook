// CombinedTeacherDlg.cpp : implementation file
//

#include "pch.h"
#include "InternProject1.h"
#include "CombinedTeacherDlg.h"
#include "afxdialogex.h"

#include "Utility.h"
#include "CTeacher.h"
#include "Storage.h"


// CombinedTeacherDlg dialog

IMPLEMENT_DYNAMIC(CombinedTeacherDlg, CDialog)

CombinedTeacherDlg::CombinedTeacherDlg(DialogMode eMode, const TEACHER& data)
	: CDialog(IDD_TEACHER_COMBINED, nullptr)
	, m_eDialogMode(eMode)
	, teacherNumberVal(0)
	, store(teachersPath)
	, tmp(data)
{
}

BOOL CombinedTeacherDlg::OnInitDialog()
{
	if (!CDialog::OnInitDialog())
		return FALSE;

	teacherNumberVal = tmp.nID;

	if (m_eDialogMode != DialogMode::eDialogMode_Add)
	{
		teacherFirstName.SetWindowText(CString{ tmp.szFirstName });
		teacherLastName.SetWindowText(CString{ tmp.szLastName });
	}
	UpdateData(FALSE);

	switch (m_eDialogMode)
	{
	case DialogMode::eDialogMode_Remove:

		teacherFirstName.EnableWindow(FALSE);
		teacherLastName.EnableWindow(FALSE);
		teacherNum.EnableWindow(FALSE);

		break;

	case DialogMode::eDialogMode_Add:
	case DialogMode::eDialogMode_Edit:

		teacherFirstName.EnableWindow(TRUE);
		teacherLastName.EnableWindow(TRUE);
		teacherNum.EnableWindow(FALSE);
		break;

	case DialogMode::eDialogMode_None:

	default:
		throw std::exception{ "Invalid window state." };
		break;
	}
	return 0;
}

CombinedTeacherDlg::~CombinedTeacherDlg()
{
}

void CombinedTeacherDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, teacherNum);
	DDX_Control(pDX, IDC_EDIT2, teacherFirstName);
	DDX_Control(pDX, IDC_EDIT3, teacherLastName);
	DDX_Text(pDX, IDC_EDIT1, teacherNumberVal);
}


BEGIN_MESSAGE_MAP(CombinedTeacherDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CombinedTeacherDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CombinedTeacherDlg message handlers


void CombinedTeacherDlg::OnBnClickedOk()
{
	UpdateData();

	BOOL isOK = TRUE;
	TEACHER st;
	CString buff;

	st.nID = teacherNumberVal;

	if (m_eDialogMode != DialogMode::eDialogMode_Remove)
	{
		teacherFirstName.GetWindowText(buff);

		if (buff.GetLength() <= TEACHER::MAX_NAME_SIZE)
		{
			strcpy_s(st.szFirstName, TEACHER::MAX_NAME_SIZE, CT2A(buff));
		}
		else
		{
			strcpy_s(st.szFirstName, TEACHER::MAX_NAME_SIZE, "");
		}

		teacherLastName.GetWindowTextW(buff);

		if (buff.GetLength() <= TEACHER::MAX_NAME_SIZE)
		{
			strcpy_s(st.szLastName, TEACHER::MAX_NAME_SIZE, CT2A(buff));
		}
		else
		{
			strcpy_s(st.szLastName, TEACHER::MAX_NAME_SIZE, "");
		}
	}

	switch (m_eDialogMode)
	{
	case DialogMode::eDialogMode_Add:

		isOK = store.Add(st);
		break;
	case DialogMode::eDialogMode_Edit:

		isOK = store.Edit(st);
		break;
	case DialogMode::eDialogMode_Remove:
	
		isOK = store.Delete(st.nID);


		break;

	default:
		throw std::exception{ "Invalid window state." };
		break;
	}

	if (!isOK)
	{
		int errorBox = MessageBox((LPCWSTR)L"Error! Check your input.", NULL, MB_OK | MB_ICONWARNING);
		return;
	}

	CDialog::OnOK();
}
