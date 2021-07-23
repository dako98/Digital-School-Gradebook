// ScheduledClassEditDlg.cpp : implementation file
//

#include "pch.h"
#include "InternProject1.h"
#include "ScheduledClassEditDlg.h"
#include "afxdialogex.h"

#include "Utility.h"
#include "CombinedScheduleClassDlg.h"
#include <vector>


// ScheduledClassEditDlg dialog

IMPLEMENT_DYNAMIC(ScheduledClassEditDlg, CDialog)

ScheduledClassEditDlg::ScheduledClassEditDlg(const CSchedule& schedule)
	: CDialog(IDD_EDIT_SCHEDULE, nullptr)
	, subjectStore(new SubjectDatabaseInterface(_T("Subjects"), &databaseConnection))
	, scheduledClassStore(new ScheduledClassDatabaseInterface(_T("Schedule"), &databaseConnection))
	, scheduleStore( new ScheduleDatabaseInterface(_T("Schedule"), &databaseConnection))
	, schedule(schedule)
{
}

ScheduledClassEditDlg::~ScheduledClassEditDlg()
{
}

void ScheduledClassEditDlg::PrintClassesOfDay(int day)
{
	classesInDayList.ResetContent();
	for (const auto& scheduledClass : schedule.days[day].classes)
	{
		int index = classesInDayList.AddString(subjectNames[scheduledClass.nSubjectID]);
		classesInDayList.SetItemData(index, scheduledClass.nID);
	}
}

void ScheduledClassEditDlg::MoveScheduledClass(int id, int up, int tomorrow)
{
	unsigned int daysInWeek = schedule.days.size();
	unsigned int dayLength = 0;
	unsigned int day, indexInDay;

	bool found = false;

	for (day = 0; day < daysInWeek; day++)
	{
		dayLength = schedule.days[day].classes.size();

		for (indexInDay = 0; indexInDay < dayLength; indexInDay++)
		{
			if (schedule.days[day].classes[indexInDay].nID == id)
			{
				found = true;
				break;
			}
		}
		if (found)
		{
			break;
		}
	}
	if (up > 0)
	{
		ASSERT(indexInDay > 0);

		std::swap(schedule.days[day].classes[indexInDay].nID, schedule.days[day].classes[indexInDay - 1].nID);
		std::swap(schedule.days[day].classes[indexInDay].nSubjectID, schedule.days[day].classes[indexInDay - 1].nSubjectID);
	}
	else if (up < 0)
	{
		ASSERT(indexInDay < dayLength - 1);

		std::swap(schedule.days[day].classes[indexInDay].nID, schedule.days[day].classes[indexInDay + 1].nID);
		std::swap(schedule.days[day].classes[indexInDay].nSubjectID, schedule.days[day].classes[indexInDay + 1].nSubjectID);
	}

	if (tomorrow > 0)
	{
		ASSERT(day > 0);

		std::swap(schedule.days[day].classes[indexInDay].nID, schedule.days[day - 1].classes[indexInDay].nID);
		std::swap(schedule.days[day].classes[indexInDay].nSubjectID, schedule.days[day - 1].classes[indexInDay].nSubjectID);
	}
	else if (tomorrow < 0)
	{
		ASSERT(day < daysInWeek - 1);

		std::swap(schedule.days[day].classes[indexInDay].nID, schedule.days[day + 1].classes[indexInDay].nID);
		std::swap(schedule.days[day].classes[indexInDay].nSubjectID, schedule.days[day + 1].classes[indexInDay].nSubjectID);
	}
}

BOOL ScheduledClassEditDlg::OnInitDialog()
{
	if(!CDialog::OnInitDialog())
		return FALSE;

	BOOL isOK = TRUE;

	CString className;
	isOK = IDtoNameMapper(&databaseConnection, CString{ "Classes" }, CString{ "ID" }, CString{ "Name" },  schedule.classID , className);

	currentClassEdit.SetWindowText(className);


	std::set<int> uniqueIDs;

	// Print days of week
	unsigned int daysInWeek = schedule.days.size();
	CString text;
	for (size_t i = 0; i < daysInWeek; i++)
	{
		text.Format(_T("Day %d"), i + 1);
		int index = daysOfWeekList.AddString(text);
		daysOfWeekList.SetItemData(index, i);

		for (const auto& _class : schedule.days[i].classes)
		{
			uniqueIDs.insert(_class.nSubjectID);
		}
	}

	// Map subject names
	std::vector<int> ids(uniqueIDs.begin(), uniqueIDs.end());
	isOK = IDtoNameMapper(&databaseConnection, CString{ "Subjects" }, CString{ "ID" }, CString{ "Name" }, ids, subjectNames);

	// Select first day
	daysOfWeekList.SetCurSel(daysInWeek > 0 ? 0 : CB_ERR);

	// Print classes for the day
	if (daysOfWeekList.GetCurSel() != CB_ERR)
	{
		PrintClassesOfDay(daysOfWeekList.GetItemData(daysOfWeekList.GetCurSel()));
	}

	return isOK;
}

void ScheduledClassEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, daysOfWeekList);
	DDX_Control(pDX, IDC_LIST1, classesInDayList);
	DDX_Control(pDX, IDC_EDIT1, currentClassEdit);
	DDX_Control(pDX, IDC_BUTTON2, buttonUp);
	DDX_Control(pDX, IDC_BUTTON3, buttonDown);
}


BEGIN_MESSAGE_MAP(ScheduledClassEditDlg, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBO1, &ScheduledClassEditDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON2, &ScheduledClassEditDlg::OnBnClickedButtonUp)
	ON_BN_CLICKED(IDC_BUTTON3, &ScheduledClassEditDlg::OnBnClickedButtonDown)
	ON_LBN_SELCHANGE(IDC_LIST1, &ScheduledClassEditDlg::OnLbnSelchangeList1)
	ON_BN_CLICKED(IDC_BUTTON1, &ScheduledClassEditDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON4, &ScheduledClassEditDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDOK, &ScheduledClassEditDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// ScheduledClassEditDlg message handlers


void ScheduledClassEditDlg::OnCbnSelchangeCombo1()
{
	// TODO: Add your control notification handler code here
	PrintClassesOfDay(daysOfWeekList.GetItemData(daysOfWeekList.GetCurSel()));
}


void ScheduledClassEditDlg::OnBnClickedButtonUp()
{
	// TODO: Add your control notification handler code here
	int id = classesInDayList.GetItemData(classesInDayList.GetCurSel());
	MoveScheduledClass(id, 1, 0);
	PrintClassesOfDay(daysOfWeekList.GetItemData(daysOfWeekList.GetCurSel()));
	classesInDayList.SetCurSel(GetIndexByData(id,classesInDayList));
	OnLbnSelchangeList1();
}


void ScheduledClassEditDlg::OnBnClickedButtonDown()
{
	// TODO: Add your control notification handler code here
	int id = classesInDayList.GetItemData(classesInDayList.GetCurSel());
	MoveScheduledClass(id, -1, 0);
	PrintClassesOfDay(daysOfWeekList.GetItemData(daysOfWeekList.GetCurSel()));
	classesInDayList.SetCurSel(GetIndexByData(id, classesInDayList));
	OnLbnSelchangeList1();
}


void ScheduledClassEditDlg::OnLbnSelchangeList1()
{
	// TODO: Add your control notification handler code here
	if (classesInDayList.GetCurSel() <= 0)
	{
		buttonUp.EnableWindow(FALSE);
	}
	else
	{
		buttonUp.EnableWindow(TRUE);
	}

	if (classesInDayList.GetCurSel() >= classesInDayList.GetCount() - 1)
	{
		buttonDown.EnableWindow(FALSE);
	}
	else
	{
		buttonDown.EnableWindow(TRUE);
	}

}


void ScheduledClassEditDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	int day = daysOfWeekList.GetItemData(daysOfWeekList.GetCurSel());
	int classesinDayCount = schedule.days[day].classes.size();
	ScheduleClass tmp;
	if (classesinDayCount > 0)
	{
		tmp.duration = schedule.days[day].classes[classesinDayCount - 1].duration;
		tmp.begin.hour += (schedule.days[day].classes[classesinDayCount - 1].begin.minute + 40 + 10) / 60;
		tmp.begin.minute += (schedule.days[day].classes[classesinDayCount - 1].begin.minute + 40 + 10) % 60;
	}

	CombinedScheduleClassDlg subjectPicker(eDialogMode_Add, tmp);
	subjectPicker.DoModal();

	if (tmp.nSubjectID != -1)
	{
		schedule.days[day].classes.push_sorted(tmp);
		tmp.classID = schedule.classID;
		tmp.dayOfWeek = day;
		toAdd.push_back(tmp);
		PrintClassesOfDay(day);
	}

}


void ScheduledClassEditDlg::OnBnClickedButton4()
{
	// TODO: Add your control notification handler code here
	SUBJECT subject;
	int id = classesInDayList.GetItemData(classesInDayList.GetCurSel());
	
	unsigned int daysInWeek = schedule.days.size();
	unsigned int dayLength = 0;
	unsigned int day, indexInDay;
	bool found = false;;

	for (day = 0; day < daysInWeek; day++)
	{
		dayLength = schedule.days[day].classes.size();

		for (indexInDay = 0; indexInDay < dayLength; indexInDay++)
		{
			if (schedule.days[day].classes[indexInDay].nID == id)
			{
				found = true;
				break;
			}
		}
		if (found)
		{
			break;
		}
	}
	ScheduleClass tmp;
	scheduledClassStore->Load(schedule.days[day].classes[indexInDay].nID,tmp);

	CombinedScheduleClassDlg subjectPicker(eDialogMode_Remove, tmp);
	subjectPicker.DoModal();

	if (tmp.nSubjectID != -1)
	{
		toDelete.push_back(schedule.days[day].classes[indexInDay]);

		schedule.days[day].classes.erase(schedule.days[day].classes.begin() + indexInDay);
		PrintClassesOfDay(day);
	}
}


void ScheduledClassEditDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here

	for (auto& scheduledClass : toAdd)
	{
		ASSERT(scheduledClass.nSubjectID != -1);

		scheduledClassStore->Add(scheduledClass);
	}
	scheduleStore->Edit(schedule);
	for (const auto& scheduledClass : toDelete)
	{
		if (scheduledClass.nID != -1)
		{
			scheduledClassStore->Delete(scheduledClass.nID);
		}
	}
	CDialog::OnOK();
}
