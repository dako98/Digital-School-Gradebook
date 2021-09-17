// CombinedSubjectDlg.cpp : implementation file
//

#include "pch.h"
#include "InternProject1.h"
#include "CombinedSubjectDlg.h"
#include "afxdialogex.h"

#include "Utility.h"

#include "Storage.h"
#include "CTeacher.h"
#include "CSubject.h"
#include "CGrade.h"

// CombinedSubjectDlg dialog

IMPLEMENT_DYNAMIC(CombinedSubjectDlg, CDialog)

CombinedSubjectDlg::CombinedSubjectDlg(DialogMode eMode, SUBJECT& data)
	: CDialog(IDD_SUBJECT_COMBINED, nullptr)
	, m_eDialogMode(eMode)
	, m_subjectIDVal(0)
	, m_subjectStore(&databaseConnection)
	, m_teacherStore(&databaseConnection)
	, m_data(data)
{
}

BOOL CombinedSubjectDlg::OnInitDialog()
{
	if (!CDialog::OnInitDialog())
	{
		return FALSE;
	}

	m_subjectIDVal = m_data.nID;

	if (m_eDialogMode != DialogMode::eDialogMode_Add)
	{
		m_subjectName.SetWindowText(CString{ m_data.szName });
		m_subjectRoom.SetWindowText(CString{ m_data.szRoom });
	}

	std::vector<TEACHER> allTeachers;
	if (!m_teacherStore.LoadAll(allTeachers))
	{
		return FALSE;
	}


	CString currentRow;

	for (const auto& teacher : allTeachers)
	{
		currentRow.Format(_T("%d %s %s"),
			teacher.nID,
			CString{ teacher.szFirstName },
			CString{ teacher.szLastName });

		int index = m_teacherDropdown.AddString(currentRow);
		m_teacherDropdown.SetItemData(index, teacher.nID);
	}

	m_teacherDropdown.SetCurSel(GetIndexByData(m_data.nTeacherID, m_teacherDropdown));

	UpdateData(FALSE);

	switch (m_eDialogMode)
	{
	case DialogMode::eDialogMode_View:
	case DialogMode::eDialogMode_Remove:

		m_subjectID.EnableWindow(FALSE);
		m_subjectName.EnableWindow(FALSE);
		m_subjectRoom.EnableWindow(FALSE);
		m_teacherDropdown.EnableWindow(FALSE);

		break;

	case DialogMode::eDialogMode_Add:
	case DialogMode::eDialogMode_Edit:

		m_subjectID.EnableWindow(FALSE);
		m_subjectName.EnableWindow(TRUE);
		m_subjectRoom.EnableWindow(TRUE);
		m_teacherDropdown.EnableWindow(TRUE);

		break;

	default:
		throw std::invalid_argument{ "Invalid window state." };
		break;
	}

	return TRUE;
}

CombinedSubjectDlg::~CombinedSubjectDlg()
{
}

void CombinedSubjectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SUBJECT_TEACHER_COMBO, m_teacherDropdown);
	DDX_Text(pDX, IDC_SUBJECT_ID_EDIT, m_subjectIDVal);
	DDX_Control(pDX, IDC_SUBJECT_NAME_EDIT, m_subjectName);
	DDX_Control(pDX, IDC_SUBJECT_ROOM_EDIT, m_subjectRoom);
	DDX_Control(pDX, IDC_SUBJECT_ID_EDIT, m_subjectID);
}


BEGIN_MESSAGE_MAP(CombinedSubjectDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CombinedSubjectDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CombinedSubjectDlg message handlers


void CombinedSubjectDlg::OnBnClickedOk()
{

	UpdateData();

	SUBJECT su;
	CString buff;

	su.nID = m_subjectIDVal;

	if (m_eDialogMode != DialogMode::eDialogMode_Remove)
	{
		if (m_teacherDropdown.GetCurSel() == CB_ERR)
		{
			return;
		}

		// Read data from window.
		m_subjectName.GetWindowText(buff);

			su.nTeacherID = m_teacherDropdown.GetItemData(m_teacherDropdown.GetCurSel());

			if (buff.GetLength() <= SUBJECT::MAX_NAME_SIZE)
			{
				StrCpyW(su.szName, buff);
			}
			else
			{
				StrCpyW(su.szName, _T(""));
			}

			m_subjectRoom.GetWindowTextW(buff);

			if (buff.GetLength() <= SUBJECT::MAX_NAME_SIZE)
			{
				StrCpyW(su.szRoom, buff);
			}
			else
			{
				StrCpyW(su.szRoom, _T(""));
			}

		if (su.Validate())
		{
			m_data = su;
			CDialog::OnOK();
		}
		else
		{
			int errorBox = MessageBox((LPCWSTR)L"Error! Check your input.", NULL, MB_OK | MB_ICONWARNING);
		}
	}// !!eDialogMode_Remove
	else
	{
		m_data = su;
		CDialog::OnOK();
	}
}