// ScheduleDlg.cpp : implementation file
//

#include "pch.h"
#include "InternProject1.h"
#include "ScheduleDlg.h"
#include "afxdialogex.h"

#include "Utility.h"

#include "CSchedule.h"
#include "Storage.h"


// ScheduleDlg dialog

IMPLEMENT_DYNAMIC(ScheduleDlg, CDialog)

ScheduleDlg::ScheduleDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_SCHEDULE, pParent)
	, scheduleStore(new ScheduleDatabaseInterface(_T("Schedule"), &databaseConnection))
	, classStore(new ClassesDatabaseInterface(_T("Classes"), &databaseConnection))
{

}

ScheduleDlg::~ScheduleDlg()
{
}

BOOL ScheduleDlg::PrintSchedule()
{
	BOOL isOK = TRUE;

//	Storage<CSchedule> scheduleStore(databaseConnectionString);
	CSchedule schedule;
	isOK = scheduleStore->Load(classSelectDropList.GetItemData(classSelectDropList.GetCurSel()), schedule);

	ListView_SetExtendedListViewStyle(ScheduleListControl, LVS_EX_GRIDLINES);

	/*	ScheduleListControl.InsertColumn(
			0,              // Rank/order of item
			_T("Day 1"),          // Caption for this header
			LVCFMT_LEFT,    // Relative position of items under header
			100);           // Width of items under header
*/

/*	
	ScheduleListControl.SetColumnWidth(0, 200);
	ScheduleListControl.SetColumnWidth(1, 200);
	ScheduleListControl.SetColumnWidth(2, 200);
	ScheduleListControl.SetColumnWidth(3, 200);
	ScheduleListControl.SetColumnWidth(4, 200);
	ScheduleListControl.SetColumnWidth(5, 200);
	ScheduleListControl.SetColumnWidth(6, 200);
*/

	CString text;

	unsigned int maxRows = 0;
	unsigned int days = schedule.days.size();
	unsigned int currentDay = 0;
	for (const auto& day : schedule.days)
	{
		maxRows = ((maxRows < day.classes.size()) ? day.classes.size() : maxRows);
		text.Format(_T("Day %d"), currentDay + 1);

		ScheduleListControl.InsertColumn(currentDay + 1, text, LVCFMT_CENTER, 80);
		currentDay++;
	}

	for (size_t i = 0; i < maxRows; i++)
	{
		text.Format(_T("%d"), i + 1);
		ScheduleListControl.InsertItem(0, text);
	}

	std::set<int> uniqueIDs;

	for (const auto& day : schedule.days)
	{
		for (const auto& _class : day.classes)
		{
			uniqueIDs.insert(_class.nSubjectID);
		}
	}

	std::vector<int> ids(uniqueIDs.begin(), uniqueIDs.end());
	std::unordered_map<int, CString> subjectNames;

	isOK = IDtoNameMapper(&databaseConnection, CString{ "Subjects" }, CString{ "ID" }, CString{ "Name" }, ids, subjectNames);

	if (isOK)
	{
		for (size_t col = 0; col < days; col++)
		{
			int row = 0;
			for (const auto& _class : schedule.days[col].classes)
			{
				text.Format(_T("%s"), subjectNames[_class.nSubjectID]);
				ScheduleListControl.SetItemText(row, col, text);
				row++;
			}
		}
	}
	return isOK;
}

BOOL ScheduleDlg::OnInitDialog()
{
	if (!CDialog::OnInitDialog())
		return FALSE;

	BOOL isOK = TRUE;

//	Storage<CClass> classStorage(databaseConnectionString);
	std::vector<CClass> allClasses;

	isOK = classStore->LoadAll(allClasses);

	if (isOK)
	{
		CString currentRow;

		for (const auto& cClass : allClasses)
		{
			currentRow.Format(_T("%d %s"),
				cClass.ID,
				cClass.name);

			int index = classSelectDropList.AddString(currentRow);
			classSelectDropList.SetItemData(index, cClass.ID);
		}

		classSelectDropList.SetCurSel(CB_ERR);

		if (classSelectDropList.GetCurSel() != CB_ERR)
		{
			isOK = PrintSchedule();
		}

	}
	return isOK;
}

void ScheduleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, ScheduleListControl);
	DDX_Control(pDX, IDC_COMBO1, classSelectDropList);
}


BEGIN_MESSAGE_MAP(ScheduleDlg, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBO1, &ScheduleDlg::OnCbnSelchangeCombo1)
END_MESSAGE_MAP()


// ScheduleDlg message handlers


void ScheduleDlg::OnCbnSelchangeCombo1()
{
	// TODO: Add your control notification handler code here
	int nCount = ScheduleListControl.GetItemCount();

	// Delete all of the items from the list view control.
	for (int i = 0; i < nCount; i++)
	{
		ScheduleListControl.DeleteItem(0);
	}

	int nColumnCount = ScheduleListControl.GetHeaderCtrl()->GetItemCount();

	// Delete all of the columns.
	for (int i = 0; i < nColumnCount; i++)
	{
		ScheduleListControl.DeleteColumn(0);
	}

	PrintSchedule();
}
