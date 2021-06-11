// EditGradeDlg.cpp : implementation file
//

#include "pch.h"
#include "InternProject1.h"
#include "EditGradeDlg.h"
#include "afxdialogex.h"

#include "Utility.h"

#include "GradeStore.h"
#include "StudentStore.h"
#include "SubjectStore.h"



// EditGradeDlg dialog

IMPLEMENT_DYNAMIC(EditGradeDlg, CDialog)

EditGradeDlg::EditGradeDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_EDIT_GRADE, pParent)
	, currentGradeIndex(0)
	, currentStudentNum(0)
	, currentSubjectID(0)
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
	int index = 0;
	for (const Student& student : allStudents)
	{
		currentRow.Format(_T("%d %s"), student.GetNumber(), student.getName());

		int i = studentsComboBox.AddString(currentRow);
		studentsComboBox.SetItemData(i, index);
		index++;
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
	int index = 0;
	for (const Subject& subject : allSubjects)
	{
		currentRow.Format(_T("%d %s"), subject.GetID(), subject.GetName());

		// FIXME: Add item data to all comboboxes.

		int i = subjectsComboBox.AddString(currentRow);
		subjectsComboBox.SetItemData(i, index);
		index++;
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

	int studentIndexInList = studentsComboBox.GetCurSel();
	int subjectIndexInList = subjectsComboBox.GetCurSel();

	if (studentIndexInList != CB_ERR && subjectIndexInList != CB_ERR)
	{
		int studentNum = allStudents[
			studentsComboBox.GetItemData(
				studentIndexInList)].GetNumber();
		int subjectID = allSubjects[subjectsComboBox.GetItemData(subjectIndexInList)].GetID();
		
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

			int i = allGradesComboBox.AddString(currentRow);
			allGradesComboBox.SetItemData(i, index);
			index++;
		}
		if (studentGrades.size() > 0)
		{
			int selected = 0;
			allGradesComboBox.SetCurSel(selected);
			currentGradeIndex = allGradesComboBox.GetItemData(selected);
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


	UpdateGradeInList();
}


void EditGradeDlg::UpdateGradeInList()
{
	int studentIndexInList = studentsComboBox.GetCurSel();
	int subjectIndexInList = subjectsComboBox.GetCurSel();
	int gradeIndexInList = allGradesComboBox.GetCurSel();
	int updatedGradeValue = studentGrades[allGradesComboBox.GetItemData(gradeIndexInList)].GetValue();

	if (studentIndexInList != CB_ERR && subjectIndexInList != CB_ERR && gradeIndexInList != CB_ERR)
	{
		gradeValue.SetCurSel(GetIndexByData(updatedGradeValue, gradeValue));
	}
}


void EditGradeDlg::OnCbnSelchangeCombo1()
{
	// TODO: Add your control notification handler code here
	PrintGrades();
	currentStudentNum = allStudents[studentsComboBox.GetItemData(studentsComboBox.GetCurSel())].GetNumber();
	UpdateGradeInList();
}


void EditGradeDlg::OnCbnSelchangeCombo2()
{
	// TODO: Add your control notification handler code here
	PrintGrades();
	currentSubjectID = allSubjects[subjectsComboBox.GetItemData(subjectsComboBox.GetCurSel())].GetID();
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

	try
	{
		GradeStore::GetInstance()->RemoveGrade(currentStudentNum,currentSubjectID,studentGrades[currentGradeIndex].GetDate());
	}
	catch (const std::out_of_range& e)
	{
		// TODO: Handle
	}

	CDialog::OnOK();
}
