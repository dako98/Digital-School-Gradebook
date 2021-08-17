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

CombinedTeacherDlg::CombinedTeacherDlg(DialogMode eMode, TEACHER& data)
	: CDialog(IDD_TEACHER_COMBINED, nullptr)
	, m_eDialogMode(eMode)
	, m_teacherNumberVal(0)
	, m_store(&databaseConnection)
	, m_data(data)
{
}

BOOL CombinedTeacherDlg::OnInitDialog()
{
	if (!CDialog::OnInitDialog())
		return FALSE;

	m_teacherNumberVal = m_data.nID;

	if (m_eDialogMode != DialogMode::eDialogMode_Add)
	{
		m_teacherFirstName.SetWindowText(CString{ m_data.szFirstName });
		m_teacherLastName.SetWindowText(CString{ m_data.szLastName });
	}

	UpdateData(FALSE);

	switch (m_eDialogMode)
	{
	case DialogMode::eDialogMode_View:
	case DialogMode::eDialogMode_Remove:

		m_teacherFirstName.EnableWindow(FALSE);
		m_teacherLastName.EnableWindow(FALSE);
		m_teacherNum.EnableWindow(FALSE);

		break;

	case DialogMode::eDialogMode_Add:
	case DialogMode::eDialogMode_Edit:

		m_teacherFirstName.EnableWindow(TRUE);
		m_teacherLastName.EnableWindow(TRUE);
		m_teacherNum.EnableWindow(FALSE);
		break;

	case DialogMode::eDialogMode_None:

	default:
		throw std::invalid_argument{ "Invalid window state." };
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
	DDX_Control(pDX, IDC_EDIT1, m_teacherNum);
	DDX_Control(pDX, IDC_EDIT2, m_teacherFirstName);
	DDX_Control(pDX, IDC_EDIT3, m_teacherLastName);
	DDX_Text(pDX, IDC_EDIT1, m_teacherNumberVal);
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

	st.nID = m_teacherNumberVal;

	if (m_eDialogMode != DialogMode::eDialogMode_Remove)
	{
		m_teacherFirstName.GetWindowText(buff);

		if (buff.GetLength() <= TEACHER::MAX_NAME_SIZE)
		{
			StrCpyW(st.szFirstName, buff);
		}
		else
		{
			StrCpyW(st.szFirstName, _T(""));
		}

		m_teacherLastName.GetWindowTextW(buff);

		if (buff.GetLength() <= TEACHER::MAX_NAME_SIZE)
		{
			StrCpyW(st.szLastName, buff);
		}
		else
		{
			StrCpyW(st.szLastName, _T(""));
		}

		if (st.Validate())
		{
			m_data = st;
			CDialog::OnOK();
		}
		else
		{
			int errorBox = MessageBox((LPCWSTR)L"Error! Check your input.", NULL, MB_OK | MB_ICONWARNING);
		}
	}
	else
	{
		m_data = st;
		CDialog::OnOK();
	}
}
