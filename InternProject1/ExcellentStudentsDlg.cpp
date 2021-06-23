// ExcellentStudentsDlg.cpp : implementation file
//

#include "pch.h"
#include "InternProject1.h"
#include "ExcellentStudentsDlg.h"
#include "afxdialogex.h"

#include <unordered_set>

#include "Utility.h"

#include "Storage.h"
#include "CGrade.h"
#include "CStudent.h"


// ExcellentStudentsDlg dialog

IMPLEMENT_DYNAMIC(ExcellentStudentsDlg, CDialog)

ExcellentStudentsDlg::ExcellentStudentsDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_EXCELLENT_STUDENTS, pParent)
{

}

BOOL ExcellentStudentsDlg::OnInitDialog()
{
	if (!CDialog::OnInitDialog())
		return FALSE;

	BOOL isOK;

	// Get all grades
	Storage<GRADE> gradeStore(gradesPath);
	std::vector<GRADE> allGrades;
	isOK = gradeStore.LoadAll(allGrades);

	if (isOK)
	{
		// Filter grades
		std::unordered_set<int> excellentStudentIDs;
		for (const auto& grade : allGrades)
		{
			if (grade.value == GRADE::GRADES::A)
			{
				excellentStudentIDs.insert(grade.nStudentID);
			}
			else
			{
				excellentStudentIDs.erase(grade.nStudentID);
			}
		}

		// Print student names
		CString currentRow;
		Storage<STUDENT> studentStore(studentsPath);
		STUDENT tmp;

		for (const auto& studentID : excellentStudentIDs)
		{
			isOK = studentStore.Load(studentID, tmp);

			if (!isOK)
			{
				break;
			}

			currentRow.Format(_T("%d %s %s"),
				tmp.nID,
				CString{ tmp.szFirstName },
				CString{ tmp.szLastName });

			excellentStudentsList.AddString(currentRow);
		}
	}
	return isOK;
}

ExcellentStudentsDlg::~ExcellentStudentsDlg()
{
}

void ExcellentStudentsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, excellentStudentsList);
}


BEGIN_MESSAGE_MAP(ExcellentStudentsDlg, CDialog)
END_MESSAGE_MAP()


// ExcellentStudentsDlg message handlers
