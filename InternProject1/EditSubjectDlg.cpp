// EditSubjectDlg.cpp : implementation file
//

#include "pch.h"
#include "InternProject1.h"
#include "EditSubjectDlg.h"
#include "afxdialogex.h"

#include "Utility.h"

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
	int index = 0;
	for (const Subject& subject : allSubjects)
	{
		currentRow.Format(_T("%d %s"), subject.GetID(), subject.GetName());

		int i = subjectComboBox.AddString(currentRow);
		subjectComboBox.SetItemData(i, index);
		index++;
	}
	if (allSubjects.size() > 0)
	{
		int selected = 0;
		subjectComboBox.SetCurSel(0);
		subjectNameComboBox.SetWindowTextW(allSubjects[selected].GetName());
		roomName.SetWindowTextW(allSubjects[selected].GetName());
	}
}


// TODO: Why am I doing this?
int Search_rec(const int key, const std::vector<Teacher>& arr, int low, int high)
{
	// TODO: verify correctness

	int mid = low + (high - low) / 2;

	if (low > high)
		return - 1;
	else if (arr[mid].GetID() == key)
		return mid;
	else if (arr[mid].GetID() < key)
		Search_rec(key, arr, low, mid - 1);
	else if (arr[mid].GetID() > key)
		Search_rec(key, arr, mid + 1, high);
}

int Search(const int key, const const std::vector<Teacher>& arr)
{
	return Search_rec(key, arr, 0, arr.size() - 1);
}


void EditSubjectDlg::LoadTeachers()
{

	allTeachers = TeacherStore::GetInstance()->GetAllTeachers();

	CString currentRow;

	// Print all the subjects
	int index = 0;
	for (const Teacher& teacher : allTeachers)
	{
		currentRow.Format(_T("%d %s"), teacher.GetID(), teacher.getName());

		int i = teacherComboBox.AddString(currentRow);
		teacherComboBox.SetItemData(i, index);
		index++;
	}
	if (allTeachers.size() > 0)
	{
		Subject currentSubject = allSubjects[subjectComboBox.GetItemData(subjectComboBox.GetCurSel())];

//		int currentTeacherIndex = Search(currentSubject.GetTeacher(), allTeachers);

		int indexInList = Search(currentSubject.GetTeacher(), allTeachers);

		teacherComboBox.SetCurSel(indexInList);

//		teacherComboBox.SetCurSel(GetIndexByData(currentSubject.GetTeacher(),teacherComboBox));
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
	subjectNameComboBox.SetWindowTextW(allSubjects[subjectComboBox.GetItemData(subjectComboBox.GetCurSel())].GetName());

	Subject currentSubject = allSubjects[subjectComboBox.GetItemData(subjectComboBox.GetCurSel())];

	int index = Search(currentSubject.GetTeacher(), allTeachers);
	teacherComboBox.SetCurSel(GetIndexByData(index, teacherComboBox));

//	teacherComboBox.SetCurSel(Search(allSubjects[subjectComboBox.GetCurSel()].GetTeacher(), allTeachers));
	roomName.SetWindowTextW(allSubjects[subjectComboBox.GetItemData(subjectComboBox.GetCurSel())].GetRoom());

	UpdateData();
}


void EditSubjectDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	UpdateData();

	if (allSubjects.size() > 0)
	{
		int newTeacherID = allTeachers[teacherComboBox.GetItemData(teacherComboBox.GetCurSel())].GetID();
		int subjectID = allSubjects[subjectComboBox.GetItemData(subjectComboBox.GetCurSel())].GetID();

		try
		{
			SubjectStore::GetInstance()->EditSubject(subjectID, subjectNameComboBoxVal, newTeacherID, roomNameVal);
		}
		catch (const std::invalid_argument& e)
		{
			// TODO: Handle
		}
		catch (const std::out_of_range& e)
		{
			// TODO: Handle
		}
	}

	CDialog::OnOK();
}
