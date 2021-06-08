// EditSubjectDlg.cpp : implementation file
//

#include "pch.h"
#include "InternProject1.h"
#include "EditSubjectDlg.h"
#include "afxdialogex.h"

#include "TeacherStore.h"
#include "SubjectStore.h"


// EditSubjectDlg dialog

IMPLEMENT_DYNAMIC(EditSubjectDlg, CDialog)

EditSubjectDlg::EditSubjectDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_EDIT_SUBJECT_DIALOG, pParent)
	, subjectNameComboBoxVal(_T(""))
	, roomNameVal(_T(""))
{

}

EditSubjectDlg::~EditSubjectDlg()
{
}

void EditSubjectDlg::LoadSubjects()
{

	allSubjects = SubjectStore::GetInstance()->GetAllSubjects();

	CString currentRow;

	// Print all the subjects
	for (const Subject& subject : allSubjects)
	{
		currentRow.Format(_T("%d %s"), subject.GetID(), subject.GetName());

		subjectComboBox.AddString(currentRow);
	}
	if (allSubjects.size() > 0)
	{
		subjectComboBox.SetCurSel(0);
		subjectNameComboBox.SetWindowTextW(allSubjects[subjectComboBox.GetCurSel()].GetName());
		roomName.SetWindowTextW(allSubjects[subjectComboBox.GetCurSel()].GetName());
	}
}



int Search_rec(const int key, const std::vector<Teacher>& arr, int low, int high)
{
	// TODO: verify correctness

	int mid = low + (high - low) / 2;

	if (arr[mid].GetID() == key)
	{
		return mid;
	}
	else if (low >= high)
		return - 1;
	else if (arr[mid].GetID() < key)
		Search_rec(key, arr, low, mid - 1);
	else if (arr[mid].GetID() > key)
		Search_rec(key, arr, mid + 1, high);
}

int Search(const int key, const const std::vector<Teacher>& arr)
{
	return Search_rec(key, arr, 0, arr.size());
}


void EditSubjectDlg::LoadTeachers()
{

	allTeachers = TeacherStore::GetInstance()->GetAllTeachers();

	CString currentRow;

	// Print all the subjects
	for (const Teacher& teacher : allTeachers)
	{
		currentRow.Format(_T("%d %s"), teacher.GetID(), teacher.getName());

		teacherComboBox.AddString(currentRow);
	}
	if (allTeachers.size() > 0)
	{
		Subject currentSubject = allSubjects[subjectComboBox.GetCurSel()];

		int currentTeacherIndex = Search(currentSubject.GetTeacher(), allTeachers);

		teacherComboBox.SetCurSel(currentTeacherIndex);
//		teacherComboBox.SetWindowTextW(allTeachers[teacherComboBox.GetCurSel()].getName());
	}
}

BOOL EditSubjectDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	LoadSubjects();
	LoadTeachers();

	UpdateData();

	return 0;
}

void EditSubjectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, subjectComboBox);
	DDX_Control(pDX, IDC_EDIT1, subjectNameComboBox);
	DDX_Control(pDX, IDC_COMBO2, teacherComboBox);
	DDX_Control(pDX, IDC_EDIT2, roomName);
	DDX_Text(pDX, IDC_EDIT1, subjectNameComboBoxVal);
	DDX_Text(pDX, IDC_EDIT2, roomNameVal);
}


BEGIN_MESSAGE_MAP(EditSubjectDlg, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBO1, &EditSubjectDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDOK, &EditSubjectDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// EditSubjectDlg message handlers


void EditSubjectDlg::OnCbnSelchangeCombo1()
{
	// TODO: Add your control notification handler code here
	subjectNameComboBox.SetWindowTextW(allSubjects[subjectComboBox.GetCurSel()].GetName());
	teacherComboBox.SetCurSel(Search(allSubjects[subjectComboBox.GetCurSel()].GetTeacher(), allTeachers));
	roomName.SetWindowTextW(allSubjects[subjectComboBox.GetCurSel()].GetName());

	UpdateData();
}


void EditSubjectDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	UpdateData();

	if (allSubjects.size() > 0)
	{
		Teacher newTeacher = allTeachers[teacherComboBox.GetCurSel()];

		SubjectStore::GetInstance()->EditSubject(allSubjects[subjectComboBox.GetCurSel()].GetID(), subjectNameComboBoxVal, newTeacher.GetID(), roomNameVal);
	}

	CDialog::OnOK();
}
