// AddSubjectDlg.cpp : implementation file
//

#include "pch.h"
#include "InternProject1.h"
#include "AddSubjectDlg.h"
#include "afxdialogex.h"

#include <vector>

#include "Utility.h"

#include "Teacher.h"
#include "TeacherStore.h"
#include "SubjectStore.h"

// AddSubjectDlg dialog



IMPLEMENT_DYNAMIC(AddSubjectDlg, CDialog)

AddSubjectDlg::AddSubjectDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_ADD_SUBJECT_DIALOG, pParent)
	, subjectNameVal(_T(""))
	, subjectRoomVal(_T(""))
{

}

AddSubjectDlg::~AddSubjectDlg()
{
}

BOOL AddSubjectDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	allTeachers = TeacherStore::GetInstance()->GetAllTeachers();

	populateList(teacherList, allTeachers);
	UpdateData();


	return 0;
}

void AddSubjectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, teacherList);
	DDX_Text(pDX, IDC_EDIT1, subjectNameVal);
	DDX_Text(pDX, IDC_EDIT2, subjectRoomVal);
}


BEGIN_MESSAGE_MAP(AddSubjectDlg, CDialog)
	ON_BN_CLICKED(IDOK, &AddSubjectDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// AddSubjectDlg message handlers


void AddSubjectDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here

	UpdateData();
	if (allTeachers.size() > 0)
	{
		int teacherID = allTeachers[teacherList.GetItemData(teacherList.GetCurSel())].GetID();

		try
		{
			SubjectStore::GetInstance()->AddSubject(subjectNameVal, teacherID, subjectRoomVal);
		}
		catch (std::invalid_argument& e)
		{
			// TODO: Handle
		}
	}

	CDialog::OnOK();
}
