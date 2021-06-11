// EditGradeDlg.cpp : implementation file
//

#include "pch.h"
#include "InternProject1.h"
#include "EditGradeDlg.h"
#include "afxdialogex.h"

#include "GradeStore.h"
#include "StudentStore.h"
#include "SubjectStore.h"


int GetIndexByData(const int target, const CComboBox& comboBox);

// EditGradeDlg dialog

IMPLEMENT_DYNAMIC(EditGradeDlg, CDialog)

EditGradeDlg::EditGradeDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_EDIT_GRADE, pParent)
{

}

EditGradeDlg::~EditGradeDlg()
{
}

BOOL EditGradeDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	PrintStudents();
	PrintSubjects();
	PrintGrades();
	PrintValue();

	return 0;
}

void EditGradeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, studentsComboBox);
	DDX_Control(pDX, IDC_COMBO2, subjectsComboBox);
	DDX_Control(pDX, IDC_COMBO3, allGradesComboBox);
	DDX_Control(pDX, IDC_COMBO4, gradeValue);
}


BEGIN_MESSAGE_MAP(EditGradeDlg, CDialog)
	ON_BN_CLICKED(IDOK, &EditGradeDlg::OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_COMBO1, &EditGradeDlg::OnCbnSelchangeCombo1)
	ON_CBN_SELCHANGE(IDC_COMBO2, &EditGradeDlg::OnCbnSelchangeCombo2)
	ON_CBN_SELCHANGE(IDC_COMBO3, &EditGradeDlg::OnCbnSelchangeCombo3)
	ON_BN_CLICKED(IDC_BUTTON1, &EditGradeDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// EditGradeDlg message handlers


void EditGradeDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	int studentInList = studentsComboBox.GetCurSel();
	int subjectInList = subjectsComboBox.GetCurSel();
	int gradeInList = allGradesComboBox.GetCurSel();
	int valueInList = gradeValue.GetCurSel();
	int updatedGradeInList = gradeValue.GetCurSel();

	if (studentInList != CB_ERR && subjectInList != CB_ERR && gradeInList != CB_ERR && valueInList != CB_ERR)
	{
		int studentNum = studentsComboBox.GetItemData(studentInList);
		int subjectID = subjectsComboBox.GetItemData(subjectInList);
		int updatedGradeValue = gradeValue.GetItemData(updatedGradeInList);
		ATL::COleDateTime gradeDate = studentGrades[gradeInList].GetDate();

		GradeStore::GetInstance()->EditGrade(studentNum, subjectID, gradeDate, updatedGradeInList);
	}

	CDialog::OnOK();
}

void EditGradeDlg::PrintStudents()
{
	studentsComboBox.ResetContent();

	allStudents = StudentStore::GetInstance()->GetAllStudents();

	CString currentRow;

	// Print all the students
	for (const Student& student : allStudents)
	{
		currentRow.Format(_T("%d %s"), student.GetNumber(), student.getName());

		int id = studentsComboBox.AddString(currentRow);
		studentsComboBox.SetItemData(id, student.GetNumber());
	}
	if (allStudents.size() > 0)
	{
		int selected = 0;
		studentsComboBox.SetCurSel(selected);
		currentStudentNum = studentsComboBox.GetItemData(selected);
	}
}

void EditGradeDlg::PrintSubjects()
{
	subjectsComboBox.ResetContent();

	allSubjects = SubjectStore::GetInstance()->GetAllSubjects();

	CString currentRow;

	// Print all the subjects
	for (const Subject& subject : allSubjects)
	{
		currentRow.Format(_T("%d %s"), subject.GetID(), subject.GetName());

		// FIXME: Add item data to all comboboxes.

		int id = subjectsComboBox.AddString(currentRow);
		subjectsComboBox.SetItemData(id, subject.GetID());
	}
	if (allSubjects.size() > 0)
	{
		int selected = 0;
		subjectsComboBox.SetCurSel(selected);
		currentSubjectID = studentsComboBox.GetItemData(selected);

	}
}

void EditGradeDlg::PrintGrades()
{
	allGradesComboBox.ResetContent();

	int studentNum = studentsComboBox.GetCurSel();
	int subjectID = subjectsComboBox.GetCurSel();

	if (studentNum != CB_ERR && subjectID != CB_ERR)
	{
		studentNum = allStudents[studentNum].GetNumber();
		subjectID = allSubjects[subjectID].GetID();

		try
		{
			studentGrades = GradeStore::GetInstance()->GetGrades(studentNum, subjectID);
		}
		catch (const std::invalid_argument& e)
		{
			// TODO: Handle
		}

		CString currentRow;

		// Print all the grades
		int index = 0;
		for (const Grade& grade : studentGrades)
		{
			currentRow.Format(_T("%d %s"), grade.GetValue(), grade.GetDate().Format(_T("%d.%B")));

			int indexInList = allGradesComboBox.AddString(currentRow);
			allGradesComboBox.SetItemData(indexInList, index);
			++index;
		}
		if (studentGrades.size() > 0)
		{
			allGradesComboBox.SetCurSel(0);
		}
	}
}

void EditGradeDlg::PrintValue()
{
	CString currentRow;

	// Print all the subjects
	for (int i = GRADES::INVALID + 1; i < GRADES::COUNT; ++i)
	{
		currentRow.Format(_T("%s"), Grade::MapName(i));

		int index = gradeValue.AddString(currentRow);
		gradeValue.SetItemData(index, i);
	}


	int studentNum = studentsComboBox.GetCurSel();
	int subjectID = subjectsComboBox.GetCurSel();
	int gradeInList = allGradesComboBox.GetCurSel();

	if (studentNum != CB_ERR && subjectID != CB_ERR && gradeInList != CB_ERR)
	{
		gradeValue.SetCurSel(0);
	}
}

int GetIndexByData(const int target, const CComboBox& comboBox)
{
	int result = CB_ERR;
	int length = comboBox.GetCount();

	for (size_t i = 0; i < length; i++)
	{
		if (comboBox.GetItemData(i) == target)
		{
			result = i;
			break;
		}
	}

	return result;
}

void EditGradeDlg::UpdateGradeInList()
{
	int studentNum = studentsComboBox.GetCurSel();
	int subjectID = subjectsComboBox.GetCurSel();
	int gradeInList = allGradesComboBox.GetCurSel();
	int updatedGradeValue = studentGrades[gradeInList].GetValue();

	if (studentNum != CB_ERR && subjectID != CB_ERR && gradeInList != CB_ERR)
	{
		gradeValue.SetCurSel(GetIndexByData(updatedGradeValue, gradeValue));
	}
}


void EditGradeDlg::OnCbnSelchangeCombo1()
{
	// TODO: Add your control notification handler code here
	PrintGrades();
	currentStudentNum = studentsComboBox.GetItemData(studentsComboBox.GetCurSel());
	UpdateGradeInList();
}


void EditGradeDlg::OnCbnSelchangeCombo2()
{
	// TODO: Add your control notification handler code here
	PrintGrades();
	currentSubjectID = subjectsComboBox.GetItemData(subjectsComboBox.GetCurSel());
	UpdateGradeInList();
}


void EditGradeDlg::OnCbnSelchangeCombo3()
{
	// TODO: Add your control notification handler code here
	currentGradeIndex = allGradesComboBox.GetItemData(allGradesComboBox.GetCurSel());
	UpdateGradeInList();
}


void EditGradeDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here

	GradeStore::GetInstance()->RemoveGrade(currentStudentNum,currentSubjectID,studentGrades[currentGradeIndex].GetDate());

	CDialog::OnOK();
}
