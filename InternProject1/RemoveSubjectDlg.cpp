// RemoveSubjectDlg.cpp : implementation file
//

#include "pch.h"
#include "InternProject1.h"
#include "RemoveSubjectDlg.h"
#include "afxdialogex.h"

#include "SubjectStore.h"
#include "GradeStore.h"
#include "StudentStore.h"

// RemoveSubjectDlg dialog

IMPLEMENT_DYNAMIC(RemoveSubjectDlg, CDialog)

RemoveSubjectDlg::RemoveSubjectDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_REMOVE_SUBJECT_DIALOG, pParent)
{

}

RemoveSubjectDlg::~RemoveSubjectDlg()
{
}

void RemoveSubjectDlg::LoadSubjects()
{

	allSubjects = SubjectStore::GetInstance()->GetAllSubjects();

	CString currentRow;

	// Print all the subjects
	for (const Subject& subject : allSubjects)
	{
		currentRow.Format(_T("%d %s"), subject.GetID(), subject.GetName());

		subjectsComboBox.AddString(currentRow);
	}
	if (allSubjects.size() > 0)
	{
		subjectsComboBox.SetCurSel(0);
	}
}

BOOL RemoveSubjectDlg::OnInitDialog()
{


	return 0;
}

void RemoveSubjectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, subjectsComboBox);
}


BEGIN_MESSAGE_MAP(RemoveSubjectDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &RemoveSubjectDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// RemoveSubjectDlg message handlers


void RemoveSubjectDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here

	UpdateData();
	allStudents = StudentStore::GetInstance()->GetAllStudents();

	// TODO: Add your control notification handler code here
	if (allStudents.size() > 0)
	{
		int subjectID = allSubjects[subjectsComboBox.GetCurSel()].GetID();

		try
		{
			GradeStore::GetInstance()->ClearSubject(subjectID);
		}
		catch (const std::out_of_range& e)
		{
			// TODO: Handle
		}
		catch (const std::invalid_argument& e)
		{
			// TODO: Handle
		}

		try
		{
			SubjectStore::GetInstance()->RemoveSubject(subjectID);
		}
		catch (const std::out_of_range& e)
		{
			// TODO: Handle
		}
		catch (const std::invalid_argument& e)
		{
			// TODO: Handle
		}
		// FIXME: Clearing list does not work.
//		studentList.DeleteString(studentList.GetCurSel());
	}
	LoadSubjects();
	UpdateData();
}
