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
	, m_subjectStore(_T("Subjects"), &databaseConnection)
//	, m_gradeStore(_T("Grades"), &databaseConnection)
	, m_teacherStore(_T("Teachers"), &databaseConnection)
	, m_data(data)
{
}

BOOL CombinedSubjectDlg::OnInitDialog()
{
	if (!CDialog::OnInitDialog())
		return FALSE;

	m_subjectIDVal = m_data.nID;

	if (m_eDialogMode != DialogMode::eDialogMode_Add)
	{
		m_subjectName.SetWindowText(CString{ m_data.szName });
		m_subjectRoom.SetWindowText(CString{ m_data.szRoom });
	}
	else
	{
//		m_subjectStore.NextID(m_subjectIDVal);
	}

	BOOL isOK = TRUE;

	std::vector<TEACHER> allTeachers;
//	Storage<TEACHER> te{ teachersPath };
	isOK = m_teacherStore.LoadAll(allTeachers);

	if (isOK)
	{
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
	}
	UpdateData(FALSE);

	switch (m_eDialogMode)
	{
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
		throw std::exception{ "Invalid window state." };
		break;
	}

	return isOK;
}

CombinedSubjectDlg::~CombinedSubjectDlg()
{
}

void CombinedSubjectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_teacherDropdown);
	DDX_Text(pDX, IDC_EDIT1, m_subjectIDVal);
	DDX_Control(pDX, IDC_EDIT2, m_subjectName);
	DDX_Control(pDX, IDC_EDIT3, m_subjectRoom);
	DDX_Control(pDX, IDC_EDIT1, m_subjectID);
}


BEGIN_MESSAGE_MAP(CombinedSubjectDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CombinedSubjectDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CombinedSubjectDlg message handlers


void CombinedSubjectDlg::OnBnClickedOk()
{

	UpdateData();

	BOOL isOK = TRUE;
	SUBJECT su;
	CString buff;

	su.nID = m_subjectIDVal;

	if (m_eDialogMode != DialogMode::eDialogMode_Remove)
	{
		// Read data from window.
		m_subjectName.GetWindowText(buff);

		if (m_teacherDropdown.GetCurSel() != CB_ERR)
		{
			su.nTeacherID = m_teacherDropdown.GetItemData(m_teacherDropdown.GetCurSel());

			if (buff.GetLength() <= SUBJECT::MAX_NAME_SIZE)
			{
				//				strcpy_s(su.szName, SUBJECT::MAX_NAME_SIZE, CT2A(buff));
				su.szName = buff;
			}
			else
			{
				//				strcpy_s(su.szName, SUBJECT::MAX_NAME_SIZE, "");
				su.szName = "";
			}

			m_subjectRoom.GetWindowTextW(buff);

			if (buff.GetLength() <= SUBJECT::MAX_NAME_SIZE)
			{
				//				strcpy_s(su.szRoom, SUBJECT::MAX_NAME_SIZE, CT2A(buff));
				su.szRoom = buff;

			}
			else
			{
				//				strcpy_s(su.szRoom, SUBJECT::MAX_NAME_SIZE, "");
				su.szRoom = "";

			}
		}
		else
		{
			isOK = FALSE;
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

/*
	switch (m_eDialogMode)
	{
	case DialogMode::eDialogMode_Add:

		isOK = m_subjectStore.Add(su);
		break;
	case DialogMode::eDialogMode_Edit:

		isOK = m_subjectStore.Edit(su);
		break;
	case DialogMode::eDialogMode_Remove:
	{
		isOK = m_subjectStore.Delete(su.nID);


		Storage<GRADE> gradeStore{ gradesPath };
		std::vector<GRADE> allGrades;
		isOK = gradeStore->LoadAll(allGrades);

		if (isOK)
		{
			for (const auto& grade : allGrades)
			{
				if (grade.nSubjectID == su.nID)
				{
					isOK = gradeStore->Delete(grade.nID);

					if (!isOK)
					{
						break;
					}
				}
			}
		}
		
	}
	break;

	default:
		throw std::exception{ "Invalid window state." };
		break;
	}
	*/


}