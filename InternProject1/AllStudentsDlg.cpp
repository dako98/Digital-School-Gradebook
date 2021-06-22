// AllStudentsDlg.cpp : implementation file
//

#include "pch.h"
#include "InternProject1.h"
#include "AllStudentsDlg.h"
#include "afxdialogex.h"

#include "StudentStore.h"
#include "Teacher.h"
#include "TeacherStore.h"
#include "CombinedStudentDlg.h"
#include "CombinedTeacherDlg.h"
#include "Storage.h"
#include "CStudent.h"

#include "CStudent.h"
#include "CTeacher.h"
#include "Storage.h"
#include "Utility.h"


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

void AllStudentsDlg::PrintAll()
{
	allStudentsList.ResetContent();

	if (studentsRadioBtn.GetCheck() == BST_CHECKED)
	{
		PrintAllStudents();
	}
	else
	{
		PrintAllTeachers();
	}
}

void AllStudentsDlg::PrintAllStudents()
{
	std::vector<STUDENT> allStudents;
	Storage<STUDENT> st(studentsPath);
	st.LoadAll(allStudents);

	CString currentRow;

	for (const auto& student : allStudents)
	{
		currentRow.Format(_T("%d %s %s %s"), 
			student.nID, 
			CString{ student.szFirstName },
			CString{ student.szLastName },
			COleDateTime(student.dtBirthDate).Format());

		int index = allStudentsList.AddString(currentRow);
		allStudentsList.SetItemData(index, student.nID);
	}
}

BOOL AllStudentsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	studentsRadioBtn.SetCheck(true);

	PrintAll();

	return 0;
}

void AllStudentsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, allStudentsList);
	DDX_LBString(pDX, IDC_LIST2, allStudentsListVal);
	DDX_Control(pDX, IDC_RADIO4, studentsRadioBtn);
}


BEGIN_MESSAGE_MAP(AllStudentsDlg, CDialog)
	ON_BN_CLICKED(IDC_RADIO4, &AllStudentsDlg::OnBnClickedRadio4)
	ON_BN_CLICKED(IDC_RADIO5, &AllStudentsDlg::OnBnClickedRadio5)
	ON_BN_CLICKED(IDC_BUTTON1, &AllStudentsDlg::OnBnClickedButtonEdit)
	ON_BN_CLICKED(IDC_BUTTON3, &AllStudentsDlg::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON2, &AllStudentsDlg::OnBnClickedButtonRemove)
END_MESSAGE_MAP()


// AllStudentsDlg message handlers


void AllStudentsDlg::OnBnClickedRadio4()
{
	// TODO: Add your control notification handler code here
	allStudentsList.ResetContent();
	PrintAll();
}

void AllStudentsDlg::PrintAllTeachers()
{
	std::vector<TEACHER> all;
	//= StudentStore::GetInstance()->GetAllStudents();
	Storage<TEACHER> st(teachersPath);
	st.LoadAll(all);

	CString currentRow;

	for (const auto& student : all)
	{
		currentRow.Format(_T("%d %s %s"), 
			student.nID, 
			CString{ student.szFirstName },
			CString{ student.szLastName });

		int index = allStudentsList.AddString(currentRow);
		allStudentsList.SetItemData(index, student.nID);
	}
}

void AllStudentsDlg::OnBnClickedRadio5()
{
	// TODO: Add your control notification handler code here
	allStudentsList.ResetContent();
	PrintAll();
}


void AllStudentsDlg::OnBnClickedButtonEdit()
{
	if (studentsRadioBtn.GetCheck() == BST_CHECKED)
	{
		STUDENT tmp;
		Storage<STUDENT> studentStore(studentsPath);

		studentStore.Load(allStudentsList.GetItemData(allStudentsList.GetCurSel()), tmp);

		CombinedStudentDlg dlg(eDialogMode_Edit, tmp);
		dlg.DoModal();
	}
	else
	{
		TEACHER tmp;
		Storage<TEACHER> store(teachersPath);

		store.Load(allStudentsList.GetItemData(allStudentsList.GetCurSel()), tmp);

		CombinedTeacherDlg dlg(eDialogMode_Edit, tmp);
		dlg.DoModal();
	}

	PrintAll();
	// TODO: Add your control notification handler code here
}


void AllStudentsDlg::OnBnClickedButtonAdd()
{
	if (studentsRadioBtn.GetCheck() == BST_CHECKED)
	{
		STUDENT tmp;
		Storage<STUDENT> store(studentsPath);

		tmp.nID = store.LastID() + 1;

		CombinedStudentDlg dlg(eDialogMode_Add, tmp);
		dlg.DoModal();
	}
	else
	{
		TEACHER tmp;
		Storage<TEACHER> store(teachersPath);

		tmp.nID = store.LastID() + 1;

		CombinedTeacherDlg dlg(eDialogMode_Add, tmp);
		dlg.DoModal();
	}

	PrintAll();

	// TODO: Add your control notification handler code here
}


void AllStudentsDlg::OnBnClickedButtonRemove()
{
	if (studentsRadioBtn.GetCheck() == BST_CHECKED)
	{
		STUDENT tmp;
		Storage<STUDENT> studentStore(studentsPath);

		studentStore.Load(allStudentsList.GetItemData(allStudentsList.GetCurSel()), tmp);

		CombinedStudentDlg dlg(eDialogMode_Remove, tmp);
		dlg.DoModal();
	}
	else
	{
		TEACHER tmp;
		Storage<TEACHER> store(teachersPath);

		store.Load(allStudentsList.GetItemData(allStudentsList.GetCurSel()), tmp);

		CombinedTeacherDlg dlg(eDialogMode_Remove, tmp);
		dlg.DoModal();
	}
	PrintAll();
	// TODO: Add your control notification handler code here
}
