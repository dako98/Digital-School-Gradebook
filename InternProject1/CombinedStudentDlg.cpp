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

CombinedStudentDlg::CombinedStudentDlg(DialogMode eDialogMode,const STUDENT& student)
	: CDialog(IDD_STUDENT_COMBINED, nullptr)
	, m_eDialogMode(eDialogMode)
	, studentNumberVal(0)
	, studentBirthDateVal(COleDateTime::GetCurrentTime())
	, studentStore(studentsPath)
	, student(student)
{
}

BOOL CombinedStudentDlg::OnInitDialog()
{
	if(!CDialog::OnInitDialog())
		return FALSE;

	BOOL isOK = TRUE;

	//TODO: Fill list with classes.
	isOK = LoadAllClasses();

	studentNumberVal = student.nID;

	if (m_eDialogMode != DialogMode::eDialogMode_Add)
	{
		studentBirthDateVal = student.dtBirthDate;
		studentFirstName.SetWindowText(CString{ student.szFirstName });
		studentLastName.SetWindowText(CString{ student.szLastName });

		CString tmp;
		tmp.Format(_T("%d"), student.numberInClass);
		numberInClassEditBox.SetWindowText(tmp);

	}
	UpdateData(FALSE);

	switch (m_eDialogMode)
	{
	case DialogMode::eDialogMode_Remove:

		studentBirthDate.EnableWindow(FALSE);
		studentFirstName.EnableWindow(FALSE);
		studentLastName.EnableWindow(FALSE);
		studentNumber.EnableWindow(FALSE);
		classList.EnableWindow(FALSE);
		numberInClassEditBox.EnableWindow(FALSE);

		break;

	case DialogMode::eDialogMode_Add:
	case DialogMode::eDialogMode_Edit:

		studentBirthDate.EnableWindow(TRUE);
		studentFirstName.EnableWindow(TRUE);
		studentLastName.EnableWindow(TRUE);
		studentNumber.EnableWindow(FALSE);
		classList.EnableWindow(TRUE);
		numberInClassEditBox.EnableWindow(TRUE);


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
	DDX_Control(pDX, IDC_EDIT1, studentNumber);
	DDX_Control(pDX, IDC_EDIT2, studentFirstName);
	DDX_Control(pDX, IDC_EDIT3, studentLastName);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, studentBirthDate);
	DDX_Text(pDX, IDC_EDIT1, studentNumberVal);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, studentBirthDateVal);
	DDX_Control(pDX, IDC_COMBO_CLASSES, classList);
	DDX_Control(pDX, IDC_EDIT4, numberInClassEditBox);
}

BOOL CombinedStudentDlg::LoadAllClasses()
{
	std::vector<CClass> classes;
	BOOL isOK = TRUE;

	CDatabase db;
	db.OpenEx(CString{ classesPath }, CDatabase::openReadOnly | CDatabase::noOdbcDialog);
	ClassesSet sSet(&db);

	ClassesSetWrapper st(&sSet);

	isOK = st.LoadAll(classes);


	if (isOK)
	{
		CString currentRow;

		for (const auto& cClass : classes)
		{
			currentRow.Format(_T("%d %s"),
				cClass.ID,
				cClass.name);

			int index = classList.AddString(currentRow);
			classList.SetItemData(index, cClass.ID);
		}

		classList.SetCurSel(GetIndexByData(student.classID, classList));
	}
	UpdateData(FALSE);

	db.Close();

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

	st.nID = studentNumberVal;
	st.classID = classList.GetItemData(classList.GetCurSel());

	if (m_eDialogMode != DialogMode::eDialogMode_Remove)
	{
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

		st.classID = classList.GetItemData(classList.GetCurSel());

		numberInClassEditBox.GetWindowText(buff);
		st.numberInClass = _wtoi(buff);
	}

	switch (m_eDialogMode)
	{
	case DialogMode::eDialogMode_Add:

		isOK = studentStore.Add(st);
		break;

	case DialogMode::eDialogMode_Edit:

		isOK = studentStore.Edit(st);
		break;

	case DialogMode::eDialogMode_Remove:
	
		isOK = studentStore.Delete(st.nID);
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
