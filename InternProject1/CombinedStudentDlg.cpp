// CombinedStudentDlg.cpp : implementation file
//

#include "pch.h"
#include "InternProject1.h"
#include "CombinedStudentDlg.h"
#include "afxdialogex.h"

#include "CStudent.h"
#include "CGrade.h"
#include "Storage.h"


// CombinedStudentDlg dialog

IMPLEMENT_DYNAMIC(CombinedStudentDlg, CDialog)

CombinedStudentDlg::CombinedStudentDlg(DialogMode eDialogMode, STUDENT& m_student)
	: CDialog(IDD_STUDENT_COMBINED, nullptr)
	, m_eDialogMode(eDialogMode)
	, m_studentNumberVal(0)
	, m_studentBirthDateVal(COleDateTime::GetCurrentTime())
	, m_data(m_student)
	, m_classesStore(&databaseConnection)
	, m_tmp(m_data)
{
}

BOOL CombinedStudentDlg::OnInitDialog()
{
	if (!CDialog::OnInitDialog())
	{
		return FALSE;
	}


	//TODO: Fill list with classes.
	if (!LoadAllClasses())
	{
		return FALSE;
	}

	m_studentNumberVal = m_data.nID;

	if (m_eDialogMode != DialogMode::eDialogMode_Add)
	{
		m_studentBirthDateVal.SetDateTime(m_data.dtBirthDate.year
			, m_data.dtBirthDate.month
			, m_data.dtBirthDate.day
			, m_data.dtBirthDate.hour
			, m_data.dtBirthDate.minute
			, m_data.dtBirthDate.second);
		m_studentFirstName.SetWindowText(CString{ m_data.szFirstName });
		m_studentLastName.SetWindowText(CString{ m_data.szLastName });

		CString tmp;
		tmp.Format(_T("%d"), m_data.numberInClass);
		m_numberInClassEditBox.SetWindowText(tmp);

	}

	UpdateData(FALSE);

	switch (m_eDialogMode)
	{
	case DialogMode::eDialogMode_View:
	case DialogMode::eDialogMode_Remove:

		m_studentBirthDate.EnableWindow(FALSE);
		m_studentFirstName.EnableWindow(FALSE);
		m_studentLastName.EnableWindow(FALSE);
		m_studentNumber.EnableWindow(FALSE);
		m_classList.EnableWindow(FALSE);
		m_numberInClassEditBox.EnableWindow(FALSE);

		break;

	case DialogMode::eDialogMode_Add:
	case DialogMode::eDialogMode_Edit:

		m_studentBirthDate.EnableWindow(TRUE);
		m_studentFirstName.EnableWindow(TRUE);
		m_studentLastName.EnableWindow(TRUE);
		m_studentNumber.EnableWindow(FALSE);
		m_classList.EnableWindow(TRUE);
		m_numberInClassEditBox.EnableWindow(TRUE);


		break;

	default:
		throw std::invalid_argument{ "Invalid window state." };
		break;
	}

	return TRUE;
}

CombinedStudentDlg::~CombinedStudentDlg()
{
}

void CombinedStudentDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STUDENT_ID, m_studentNumber);
	DDX_Control(pDX, IDC_STUDENT_FIRST_NAME_EDIT, m_studentFirstName);
	DDX_Control(pDX, IDC_STUDENT_LAST_NAME_EDIT, m_studentLastName);
	DDX_Control(pDX, IDC_DATETIMEPICKER, m_studentBirthDate);
	DDX_Text(pDX, IDC_STUDENT_ID, m_studentNumberVal);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER, m_studentBirthDateVal);
	DDX_Control(pDX, IDC_COMBO_CLASSES, m_classList);
	DDX_Control(pDX, IDC_STUDENT_NUMBER_IN_CLASS_EDIT, m_numberInClassEditBox);
}

BOOL CombinedStudentDlg::LoadAllClasses()
{
	std::vector<STUDENT_CLASS> classes;

	if (!m_classesStore.LoadAll(classes))
	{
		return FALSE;
	}

	CString currentRow;

	for (const auto& cClass : classes)
	{
		currentRow.Format(_T("%d %s"),
			cClass.nID,
			cClass.szName);

		int index = m_classList.AddString(currentRow);
		m_classList.SetItemData(index, cClass.nID);
	}

	m_classList.SetCurSel(GetIndexByData(m_data.classID, m_classList));

	UpdateData(FALSE);

	return TRUE;
}


BEGIN_MESSAGE_MAP(CombinedStudentDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CombinedStudentDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CombinedStudentDlg message handlers


void CombinedStudentDlg::OnBnClickedOk()
{
	UpdateData();

	CString buff;

	m_tmp.nID = m_studentNumberVal;
	m_tmp.classID = m_classList.GetItemData(m_classList.GetCurSel());

	if (m_eDialogMode != DialogMode::eDialogMode_Remove)
	{
		m_studentFirstName.GetWindowTextW(buff);

		if (buff.GetLength() <= STUDENT::MAX_NAME_SIZE)
		{
			StrCpyW(m_tmp.szFirstName, buff);
		}
		else
		{
			StrCpyW(m_tmp.szFirstName, _T(""));
		}

		m_studentLastName.GetWindowTextW(buff);

		if (buff.GetLength() <= STUDENT::MAX_NAME_SIZE)
		{
			StrCpyW(m_tmp.szLastName, buff);
		}
		else
		{
			StrCpyW(m_tmp.szLastName, _T(""));
		}

		DBTIMESTAMP date;
		m_studentBirthDateVal.GetAsDBTIMESTAMP(date);

		m_tmp.dtBirthDate.year		= date.year;
		m_tmp.dtBirthDate.month		= date.month;
		m_tmp.dtBirthDate.day		= date.day;
		m_tmp.dtBirthDate.hour		= date.hour;
		m_tmp.dtBirthDate.minute	= date.minute;
		m_tmp.dtBirthDate.second	= date.second;

		m_tmp.classID = m_classList.GetItemData(m_classList.GetCurSel());

		m_numberInClassEditBox.GetWindowText(buff);
		m_tmp.numberInClass = _wtoi(buff);

		if (m_tmp.Validate())
		{
			m_data = m_tmp;
			CDialog::OnOK();
		}
		else
		{
			int errorBox = MessageBox((LPCWSTR)L"Error! Check your input.", NULL, MB_OK | MB_ICONWARNING);
		}
	}
	else
	{
		m_data = m_tmp;
		CDialog::OnOK();
	}
}
