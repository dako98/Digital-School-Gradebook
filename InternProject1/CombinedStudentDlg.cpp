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

CombinedStudentDlg::CombinedStudentDlg(DialogMode eDialogMode,const STUDENT& m_student)
	: CDialog(IDD_STUDENT_COMBINED, nullptr)
	, m_eDialogMode(eDialogMode)
	, m_studentNumberVal(0)
	, m_studentBirthDateVal(COleDateTime::GetCurrentTime())
	, m_student(m_student)
	, m_studentStore(_T("Students"), &databaseConnection)
	, m_classesStore(_T("Classes"), &databaseConnection)
{
}

BOOL CombinedStudentDlg::OnInitDialog()
{
	if(!CDialog::OnInitDialog())
		return FALSE;

	BOOL isOK = TRUE;

	//TODO: Fill list with classes.
	isOK = LoadAllClasses();

	m_studentNumberVal = m_student.nID;

	if (m_eDialogMode != DialogMode::eDialogMode_Add)
	{
		m_studentBirthDateVal = m_student.dtBirthDate;
		m_studentFirstName.SetWindowText(CString{ m_student.szFirstName });
		m_studentLastName.SetWindowText(CString{ m_student.szLastName });

		CString tmp;
		tmp.Format(_T("%d"), m_student.numberInClass);
		m_numberInClassEditBox.SetWindowText(tmp);

	}
	else
	{
//		m_studentStore.NextID(m_studentNumberVal);
	}
	UpdateData(FALSE);

	switch (m_eDialogMode)
	{
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
		throw std::exception{ "Invalid window state." };
		break;
	}

	return isOK;
}

CombinedStudentDlg::~CombinedStudentDlg()
{
}

void CombinedStudentDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_studentNumber);
	DDX_Control(pDX, IDC_EDIT2, m_studentFirstName);
	DDX_Control(pDX, IDC_EDIT3, m_studentLastName);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_studentBirthDate);
	DDX_Text(pDX, IDC_EDIT1, m_studentNumberVal);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_studentBirthDateVal);
	DDX_Control(pDX, IDC_COMBO_CLASSES, m_classList);
	DDX_Control(pDX, IDC_EDIT4, m_numberInClassEditBox);
}

BOOL CombinedStudentDlg::LoadAllClasses()
{
	std::vector<CClass> classes;
	BOOL isOK = TRUE;


//	ClassesSet sSet(&databaseConnection);

//	ClassesSetWrapper st(&sSet);

	isOK = m_classesStore.LoadAll(classes);


	if (isOK)
	{
		CString currentRow;

		for (const auto& cClass : classes)
		{
			currentRow.Format(_T("%d %s"),
				cClass.ID,
				cClass.name);

			int index = m_classList.AddString(currentRow);
			m_classList.SetItemData(index, cClass.ID);
		}

		m_classList.SetCurSel(GetIndexByData(m_student.classID, m_classList));
	}
	UpdateData(FALSE);

	return isOK;
}


BEGIN_MESSAGE_MAP(CombinedStudentDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CombinedStudentDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CombinedStudentDlg message handlers


void CombinedStudentDlg::OnBnClickedOk()
{
	UpdateData();
	
	BOOL isOK = TRUE;
	STUDENT st;
	CString buff;

	st.nID = m_studentNumberVal;
	st.classID = m_classList.GetItemData(m_classList.GetCurSel());

	if (m_eDialogMode != DialogMode::eDialogMode_Remove)
	{
		m_studentFirstName.GetWindowTextW(buff);

		if (buff.GetLength() <= STUDENT::MAX_NAME_SIZE)
		{
			st.szFirstName = buff;
		}
		else
		{
			st.szFirstName = "";
		}

		m_studentLastName.GetWindowTextW(buff);

		if (buff.GetLength() <= STUDENT::MAX_NAME_SIZE)
		{
			st.szLastName = buff;
		}
		else
		{
			st.szLastName = "";
		}

		m_studentBirthDateVal.GetAsDBTIMESTAMP(st.dtBirthDate);

		st.classID = m_classList.GetItemData(m_classList.GetCurSel());

		m_numberInClassEditBox.GetWindowText(buff);
		st.numberInClass = _wtoi(buff);
	}

	switch (m_eDialogMode)
	{
	case DialogMode::eDialogMode_Add:

		isOK = m_studentStore.Add(st);
		break;

	case DialogMode::eDialogMode_Edit:

		isOK = m_studentStore.Edit(st);
		break;

	case DialogMode::eDialogMode_Remove:
	
		isOK = m_studentStore.Delete(st.nID);
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
