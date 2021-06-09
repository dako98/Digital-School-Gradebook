// AddGradeDlg.cpp : implementation file
//

#include "pch.h"
#include "InternProject1.h"
#include "AddGradeDlg.h"
#include "afxdialogex.h"

#include "StudentStore.h"
#include "SubjectStore.h"
#include "GradeStore.h"

// AddGradeDlg dialog

IMPLEMENT_DYNAMIC(AddGradeDlg, CDialog)

AddGradeDlg::AddGradeDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_ADD_GRADE, pParent)
	, gradeSliderVal(0)
	, gradeDateVal(COleDateTime::GetCurrentTime())
{

}

AddGradeDlg::~AddGradeDlg()
{
}

BOOL AddGradeDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	PrintStudents();
	PrintSubjects();

	gradeSlider.SetRange(GRADES::INVALID + 1, GRADES::COUNT - 1, TRUE);
	gradeSlider.SetPos(GRADES::INVALID + 1);



	return 0;
}

void AddGradeDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	UpdateData();

	if (gradeSliderVal > 0)
	{
		gradeText.Format(_T("%d"), gradeSliderVal);

		UpdateData(FALSE);
	
	}
}

void AddGradeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, studentComboBox);
	DDX_Control(pDX, IDC_COMBO2, subjectComboBox);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, gradeDate);
	DDX_Control(pDX, IDC_SLIDER2, gradeSlider);
	DDX_Text(pDX,/* IDCANCEL*/ IDC_ADD_GRADE_TXT_GRADE_TEXT, gradeText);
	DDX_Slider(pDX, IDC_SLIDER2, gradeSliderVal);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, gradeDateVal);
}


void AddGradeDlg::PrintStudents()
{
	allStudents = StudentStore::GetInstance()->GetAllStudents();

	CString currentRow;

	// Print all the students
	for (const Student& student : allStudents)
	{
		currentRow.Format(_T("%d %s"), student.GetNumber(), student.getName());

		studentComboBox.AddString(currentRow);
	}
	if (allStudents.size() > 0)
	{
		studentComboBox.SetCurSel(0);

	}

}

void AddGradeDlg::PrintSubjects()
{
	allSubjects = SubjectStore::GetInstance()->GetAllSubjects();

	CString currentRow;

	// Print all the students
	for (const Subject& subject : allSubjects)
	{
		currentRow.Format(_T("%d %s"), subject.GetID(), subject.GetName());

		subjectComboBox.AddString(currentRow);
	}
	if (allStudents.size() > 0)
	{
		subjectComboBox.SetCurSel(0);
	}

}

BEGIN_MESSAGE_MAP(AddGradeDlg, CDialog)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDOK, &AddGradeDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// AddGradeDlg message handlers


void AddGradeDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here

	UpdateData();

	if (allStudents.size() > 0 && allSubjects.size() > 0)
	{
		int studentID = allStudents[studentComboBox.GetCurSel()].GetNumber();
		int subjectID = allSubjects[subjectComboBox.GetCurSel()].GetID();

		try
		{
			GradeStore::GetInstance()->AddGrade(studentID, subjectID, gradeDateVal , gradeSliderVal);
		}
		catch (const std::out_of_range& e)
		{
			// TODO: Handle
		}
		catch (const std::invalid_argument& e)
		{
			// TODO: Handle
		}
	}

	CDialog::OnOK();
}
