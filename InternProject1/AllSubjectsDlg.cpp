// AllSubjectsDlg.cpp : implementation file
//

#include "pch.h"
#include "InternProject1.h"
#include "AllSubjectsDlg.h"
#include "afxdialogex.h"

#include <vector>

#include "SubjectStore.h"


// AllSubjectsDlg dialog


void populateList(CListBox& list, const std::vector<Subject>& src)
{
	list.ResetContent();
	CString currentRow;

	for (const Subject& subject : src)
	{
		currentRow.Format(_T("%d %s %s"), subject.GetID(), subject.GetName(), subject.GetRoom());

		list.AddString(currentRow);
	}
	if (src.size() > 0)
	{
		list.SetCurSel(0);
	}
}

IMPLEMENT_DYNAMIC(AllSubjectsDlg, CDialog)

AllSubjectsDlg::AllSubjectsDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_ALL_SUBJECTS, pParent)
{

}

AllSubjectsDlg::~AllSubjectsDlg()
{
}

BOOL AllSubjectsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	std::vector<Subject> allSubjects = SubjectStore::GetInstance()->GetAllSubjects();

	populateList(subjectsList, allSubjects);
	UpdateData();

	return 0;
}

void AllSubjectsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, subjectsList);
}


BEGIN_MESSAGE_MAP(AllSubjectsDlg, CDialog)
END_MESSAGE_MAP()


// AllSubjectsDlg message handlers
