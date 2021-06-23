// AllSubjectsDlg.cpp : implementation file
//

#include "pch.h"
#include "InternProject1.h"
#include "AllSubjectsDlg.h"
#include "afxdialogex.h"

#include <vector>

#include "Storage.h"
#include "CSubject.h"
#include "CombinedSubjectDlg.h"


// AllSubjectsDlg dialog

IMPLEMENT_DYNAMIC(AllSubjectsDlg, CDialog)

AllSubjectsDlg::AllSubjectsDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_ALL_SUBJECTS, pParent)
{

}

AllSubjectsDlg::~AllSubjectsDlg()
{
}

void AllSubjectsDlg::PrintAll()
{
	subjectsList.ResetContent();

	std::vector<SUBJECT> all;
	Storage<SUBJECT> su(subjectsPath);
	su.LoadAll(all);

	CString currentRow;

	for (const auto& subject : all)
	{
		currentRow.Format(_T("%d %s %s"),
			subject.nID,
			CString{ subject.szName },
			CString{ subject.szRoom });

		int index = subjectsList.AddString(currentRow);
		subjectsList.SetItemData(index, subject.nID);
	}
}

BOOL AllSubjectsDlg::OnInitDialog()
{
	if(!CDialog::OnInitDialog())
		return FALSE;

	PrintAll();

	return 0;
}

void AllSubjectsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, subjectsList);
}


BEGIN_MESSAGE_MAP(AllSubjectsDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &AllSubjectsDlg::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON2, &AllSubjectsDlg::OnBnClickedButtonEdit)
	ON_BN_CLICKED(IDC_BUTTON3, &AllSubjectsDlg::OnBnClickedButtonRemove)
END_MESSAGE_MAP()


// AllSubjectsDlg message handlers


void AllSubjectsDlg::OnBnClickedButtonAdd()
{
	SUBJECT tmp;
	Storage<SUBJECT> store(subjectsPath);
	
	tmp.nID = store.LastID() + 1;

	CombinedSubjectDlg dlg(eDialogMode_Add, tmp);
	dlg.DoModal();

	PrintAll();
}


void AllSubjectsDlg::OnBnClickedButtonEdit()
{
	if (subjectsList.GetCurSel() != LB_ERR)
	{
		SUBJECT tmp;
		Storage<SUBJECT> store(subjectsPath);

		store.Load(subjectsList.GetItemData(subjectsList.GetCurSel()), tmp);

		CombinedSubjectDlg dlg(eDialogMode_Edit, tmp);
		dlg.DoModal();

		PrintAll();
	}
}


void AllSubjectsDlg::OnBnClickedButtonRemove()
{
	if (subjectsList.GetCurSel() != LB_ERR)
	{
		SUBJECT tmp;
		Storage<SUBJECT> store(studentsPath);

		store.Load(subjectsList.GetItemData(subjectsList.GetCurSel()), tmp);

		CombinedSubjectDlg dlg(eDialogMode_Remove, tmp);
		dlg.DoModal();

		PrintAll();
	}
}
