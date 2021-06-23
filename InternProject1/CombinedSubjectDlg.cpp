// CombinedSubjectDlg.cpp : implementation file
//

#include "pch.h"
#include "InternProject1.h"
#include "CombinedSubjectDlg.h"
#include "afxdialogex.h"

#include "Utility.h"

#include <unordered_map>

#include "Storage.h"
#include "CTeacher.h"
#include "CSubject.h"

// CombinedSubjectDlg dialog

IMPLEMENT_DYNAMIC(CombinedSubjectDlg, CDialog)

CombinedSubjectDlg::CombinedSubjectDlg(DialogMode eMode, const SUBJECT& data)
	: CDialog(IDD_SUBJECT_COMBINED, nullptr)
	, m_eDialogMode(eMode)
	, subjectIDVal(0)
	, store(subjectsPath)
	, tmp(data)
{
}

BOOL CombinedSubjectDlg::OnInitDialog()
{
	if (!CDialog::OnInitDialog())
		return FALSE;

	std::vector<TEACHER> allTeachers;
	Storage<TEACHER> te(teachersPath);
	te.LoadAll(allTeachers);

	CString currentRow;

	for (const auto& teacher : allTeachers)
	{
		currentRow.Format(_T("%d %s %s"),
			teacher.nID,
			teacher.szFirstName,
			teacher.szLastName);

		int index = teacherDropdown.AddString(currentRow);
		teacherDropdown.SetItemData(index, teacher.nID);
	}

	subjectIDVal = tmp.nID;
	subjectName.SetWindowText(CString(tmp.szName));
	subjectRoom.SetWindowText(CString(tmp.szRoom));
	teacherDropdown.SetCurSel(GetIndexByData(tmp.nTeacherID, teacherDropdown));
	UpdateData(FALSE);

	switch (m_eDialogMode)
	{
		//	case DialogMode::eDialogMode_View:
	case DialogMode::eDialogMode_Remove:

		subjectID.EnableWindow(FALSE);
		subjectName.EnableWindow(FALSE);
		subjectRoom.EnableWindow(FALSE);

		break;

	case DialogMode::eDialogMode_Add:

		UpdateData(FALSE);

	case DialogMode::eDialogMode_Edit:

		subjectID.EnableWindow(FALSE);
		subjectName.EnableWindow(TRUE);
		subjectRoom.EnableWindow(TRUE);
		break;

	case DialogMode::eDialogMode_None:

	default:
		throw std::exception{ "Invalid window state." };
		break;
	}
	return 0;
}

CombinedSubjectDlg::~CombinedSubjectDlg()
{
}

void CombinedSubjectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, teacherDropdown);
	DDX_Text(pDX, IDC_EDIT1, subjectIDVal);
	DDX_Control(pDX, IDC_EDIT2, subjectName);
	DDX_Control(pDX, IDC_EDIT3, subjectRoom);
	DDX_Control(pDX, IDC_EDIT1, subjectID);
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

	su.nID = subjectIDVal;

	subjectName.GetWindowText(buff);

	if (teacherDropdown.GetCurSel() != CB_ERR)
	{
		su.nTeacherID = teacherDropdown.GetItemData(teacherDropdown.GetCurSel());

		if (buff.GetLength() <= SUBJECT::MAX_NAME_SIZE)
		{
			strcpy_s(su.szName, SUBJECT::MAX_NAME_SIZE, CT2A(buff));
		}
		else
		{
			strcpy_s(su.szName, SUBJECT::MAX_NAME_SIZE, "");
		}

		subjectRoom.GetWindowTextW(buff);

		if (buff.GetLength() <= SUBJECT::MAX_NAME_SIZE)
		{
			strcpy_s(su.szRoom, SUBJECT::MAX_NAME_SIZE, CT2A(buff));
		}
		else
		{
			strcpy_s(su.szRoom, SUBJECT::MAX_NAME_SIZE, "");
		}


		switch (m_eDialogMode)
		{
		case DialogMode::eDialogMode_Add:

			isOK = store.Add(su);
			break;
		case DialogMode::eDialogMode_Edit:

			isOK = store.Edit(su);
			break;
		case DialogMode::eDialogMode_Remove:

			isOK = store.Delete(su.nID);


			break;

		case DialogMode::eDialogMode_View:
		case DialogMode::eDialogMode_None:
		default:

			break;
		}
	}
	else
	{
		isOK = FALSE;
	}

	if (!isOK)
	{
		int errorBox = MessageBox((LPCWSTR)L"Error! Check your input.", NULL, MB_OK | MB_ICONWARNING);
		return;
	}

	CDialog::OnOK();
}