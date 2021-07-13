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
{

}

ScheduleDlg::~ScheduleDlg()
{
}

BOOL ScheduleDlg::OnInitDialog()
{
	if (!CDialog::OnInitDialog())
		return FALSE;

	BOOL isOK = TRUE;

	Storage<CSchedule> scheduleStore(databaseConnectionString);
	CSchedule schedule;
	isOK = scheduleStore.Load(1, schedule);

	ListView_SetExtendedListViewStyle(ScheduleListControl, LVS_EX_GRIDLINES);

/*	ScheduleListControl.InsertColumn(
		0,              // Rank/order of item 
		_T("Day 1"),          // Caption for this header 
		LVCFMT_LEFT,    // Relative position of items under header 
		100);           // Width of items under header

	ScheduleListControl.InsertColumn(1, _T("Day 2"), LVCFMT_CENTER, 80);
	ScheduleListControl.InsertColumn(2, _T("Day 3"), LVCFMT_CENTER, 80);
	ScheduleListControl.InsertColumn(3, _T("Day 4"), LVCFMT_CENTER, 80);
	ScheduleListControl.InsertColumn(4, _T("Day 5"), LVCFMT_CENTER, 80);
	ScheduleListControl.InsertColumn(5, _T("Day 6"), LVCFMT_CENTER, 80);
	ScheduleListControl.InsertColumn(6, _T("Day 7"), LVCFMT_CENTER, 80);*/
//	ScheduleListControl.InsertColumn(2, _T("Duration"), LVCFMT_LEFT, 100);
//	ScheduleListControl.InsertColumn(3, _T("Name"), LVCFMT_LEFT, 80);
	
	ScheduleListControl.SetColumnWidth(0, 120);
	ScheduleListControl.SetColumnWidth(1, 200);
	ScheduleListControl.SetColumnWidth(2, 200);
	ScheduleListControl.SetColumnWidth(3, 200);
	ScheduleListControl.SetColumnWidth(4, 200);
	ScheduleListControl.SetColumnWidth(5, 200);
	ScheduleListControl.SetColumnWidth(6, 200);

//	int nItem;
	CString text;

	unsigned int maxRows = 0;
	unsigned int days = schedule.days.size();
	unsigned int currentDay = 0;
	for (const auto& day : schedule.days)
	{
		maxRows = ( (maxRows < day.classes.size()) ? day.classes.size() : maxRows);
		text.Format(_T("Day %d"), currentDay + 1);

		ScheduleListControl.InsertColumn(currentDay+1,text, LVCFMT_CENTER, 80);
		currentDay++;
	}

	for (size_t i = 0; i < maxRows; i++)
	{
		text.Format(_T("%d"), i + 1);
		ScheduleListControl.InsertItem(0, text);
	}

	for (size_t col = 0; col < days; col++)
	{
		int row = 0;
		for (const auto& _class : schedule.days[col].classes)
		{
			text.Format(_T("%d"), _class.nSubjectID);
			ScheduleListControl.SetItemText(row, col, text);
			row++;
		}
	}

	return isOK;
}

void ScheduleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, ScheduleListControl);
}


BEGIN_MESSAGE_MAP(ScheduleDlg, CDialog)
END_MESSAGE_MAP()


// ScheduleDlg message handlers
