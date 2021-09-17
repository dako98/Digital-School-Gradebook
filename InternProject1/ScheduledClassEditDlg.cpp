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

ScheduledClassEditDlg::ScheduledClassEditDlg(const int classID, const int daysInWeek)
	:CDialog(IDD_EDIT_SCHEDULE, nullptr)
	, m_classID(classID)
	, m_daysInWeek(daysInWeek)
{
}

ScheduledClassEditDlg::~ScheduledClassEditDlg()
{
}

BOOL ScheduledClassEditDlg::PrintClassesOfDay(int day)
{
	m_classesInDayList.ResetContent();
	if (day == CB_ERR)
	{
		return TRUE;
	}

	ScheduledClassDatabaseInterface scheduleStore(&databaseConnection);
	CString filter;
	filter.Format(_T("[ClassID] = %d AND [DayOfWeek] = %d"), m_classID, day);
	std::vector<ScheduleClass> dayClasses;
	if (!scheduleStore.LoadWhere(filter, dayClasses))
	{
		return FALSE;
	}
	sorted_vector<ScheduleClass> sorted;
	sorted.SetSorted(true);

	for (const auto& i : dayClasses)
	{
		sorted.push_unsorted(i);
	}
	sorted.sort();

	CString subjectName;
	for (const auto& scheduledClass : sorted)
	{
		if (!IDtoNameMapper(&databaseConnection, _T("Subjects"), _T("ID"), _T("Name"), scheduledClass.nSubjectID, subjectName))
		{
			return FALSE;
		}
		int index = m_classesInDayList.AddString(subjectName);
		m_classesInDayList.SetItemData(index, scheduledClass.nID);
	}

	return TRUE;
}

BOOL ScheduledClassEditDlg::MoveScheduledClass(int currentItemId, Direction direction /*int up/*, int tomorrow*/)
{
	int currentItemInList = m_classesInDayList.GetCurSel();
	ScheduleClass currentItem, otherItem;
	int otherItemInList;
	int otherItemID;
	ScheduledClassDatabaseInterface scheduleStore(&databaseConnection);
	if (!scheduleStore.Load(currentItemId, currentItem))
	{
		return FALSE;
	}

	switch (direction)
	{
	case Up:
	{
		otherItemInList = currentItemInList - 1;

		ASSERT(otherItemInList > LB_ERR && currentItemInList > LB_ERR &&
			otherItemInList < m_classesInDayList.GetCount() && currentItemInList < m_classesInDayList.GetCount());

	}
	break;
	case Down:

	{
		otherItemInList = currentItemInList + 1;

		ASSERT(otherItemInList > LB_ERR && currentItemInList > LB_ERR &&
			otherItemInList < m_classesInDayList.GetCount() && currentItemInList < m_classesInDayList.GetCount());
		
	}
	break;


	default:
	{
		return TRUE;
	}
	break;
	}

	otherItemID = m_classesInDayList.GetItemData(otherItemInList);

	if (!scheduleStore.Load(otherItemID, otherItem))
	{
		return FALSE;
	}

	std::swap(currentItem.nNumberInDay, otherItem.nNumberInDay);

	databaseConnection.BeginTrans();

	if (!scheduleStore.Edit(currentItem) || 
		!scheduleStore.Edit(otherItem))
	{
		databaseConnection.Rollback();
		return FALSE;
	}
	else
	{
		databaseConnection.CommitTrans();

		return TRUE;
	}
}

BOOL ScheduledClassEditDlg::OnInitDialog()
{
	if (!CDialog::OnInitDialog())
	{
		return FALSE;
	}


	// Print days of week
	CString text;
	for (int i = 0; i < m_daysInWeek; i++)
	{
		text.Format(_T("Day %d"), i + 1);
		int index = m_daysOfWeekList.AddString(text);
		m_daysOfWeekList.SetItemData(index, i);
	}

	if (!PrintClassesOfDay(m_daysOfWeekList.GetCurSel()))
	{
		return FALSE;
	}
	OnLbnSelchangeClass();

	return TRUE;
}

void ScheduledClassEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_SCHEDULE_COMBO, m_daysOfWeekList);
	DDX_Control(pDX, IDC_EDIT_SCHEDULE_LIST, m_classesInDayList);
	DDX_Control(pDX, IDC_EDIT_SCHEDULE_EDIT, m_currentClassEdit);
	DDX_Control(pDX, IDC_BTN_EDIT_SCHEDULE_UP, m_buttonUp);
	DDX_Control(pDX, IDC_BTN_EDIT_SCHEDULE_DOWN, m_buttonDown);
}


BEGIN_MESSAGE_MAP(ScheduledClassEditDlg, CDialog)
	ON_CBN_SELCHANGE(IDC_EDIT_SCHEDULE_COMBO, &ScheduledClassEditDlg::OnCbnSelchangeDay)
	ON_BN_CLICKED(IDC_BTN_EDIT_SCHEDULE_UP, &ScheduledClassEditDlg::OnBnClickedButtonUp)
	ON_BN_CLICKED(IDC_BTN_EDIT_SCHEDULE_DOWN, &ScheduledClassEditDlg::OnBnClickedButtonDown)
	ON_LBN_SELCHANGE(IDC_EDIT_SCHEDULE_LIST, &ScheduledClassEditDlg::OnLbnSelchangeClass)
	ON_BN_CLICKED(IDC_BTN_EDIT_SCHEDULE_ADD, &ScheduledClassEditDlg::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BTN_EDIT_SCHEDULE_REMOVE, &ScheduledClassEditDlg::OnBnClickedButtonRemove)
	ON_BN_CLICKED(IDOK, &ScheduledClassEditDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// ScheduledClassEditDlg message handlers


void ScheduledClassEditDlg::OnCbnSelchangeDay()
{
	// TODO: Add your control notification handler code here
	if (m_daysOfWeekList.GetCurSel() == CB_ERR)
	{
		return;
	}
	PrintClassesOfDay(m_daysOfWeekList.GetItemData(m_daysOfWeekList.GetCurSel()));
}


void ScheduledClassEditDlg::OnBnClickedButtonUp()
{
	// TODO: Add your control notification handler code here
	int id = m_classesInDayList.GetItemData(m_classesInDayList.GetCurSel());
	MoveScheduledClass(id, Direction::Up);
	PrintClassesOfDay(m_daysOfWeekList.GetItemData(m_daysOfWeekList.GetCurSel()));
	m_classesInDayList.SetCurSel(GetIndexByData(id, m_classesInDayList));
	OnLbnSelchangeClass();
}


void ScheduledClassEditDlg::OnBnClickedButtonDown()
{
	// TODO: Add your control notification handler code here
	int id = m_classesInDayList.GetItemData(m_classesInDayList.GetCurSel());
	MoveScheduledClass(id, Direction::Down);
	PrintClassesOfDay(m_daysOfWeekList.GetItemData(m_daysOfWeekList.GetCurSel()));
	m_classesInDayList.SetCurSel(GetIndexByData(id, m_classesInDayList));
	OnLbnSelchangeClass();
}


void ScheduledClassEditDlg::OnLbnSelchangeClass()
{
	// TODO: Add your control notification handler code here
	if (m_classesInDayList.GetCurSel() <= 0)
	{
		m_buttonUp.EnableWindow(FALSE);
	}
	else
	{
		m_buttonUp.EnableWindow(TRUE);
	}

	if (m_classesInDayList.GetCurSel() >= m_classesInDayList.GetCount() - 1)
	{
		m_buttonDown.EnableWindow(FALSE);
	}
	else
	{
		m_buttonDown.EnableWindow(TRUE);
	}
}


void ScheduledClassEditDlg::OnBnClickedButtonAdd()
{

	if (m_daysOfWeekList.GetCurSel() == CB_ERR)
	{
		return;
	}

	ScheduledClassDatabaseInterface scheduleStore(&databaseConnection);

	ScheduleClass tmp;
	tmp.nNumberInDay = 1;

	if (m_classesInDayList.GetCount() > 0)
	{
		int debug = m_classesInDayList.GetCount();
		int id = m_classesInDayList.GetItemData(m_classesInDayList.GetCount() - 1);
		ScheduleClass lastClass;
		scheduleStore.Load(id, lastClass);
		tmp.nNumberInDay = lastClass.nNumberInDay + 1;
	}
	
	tmp.classID = m_classID;
	tmp.dayOfWeek = m_daysOfWeekList.GetItemData(m_daysOfWeekList.GetCurSel());

	CombinedScheduleClassDlg dlg{ DialogMode::eDialogMode_Add, tmp };

	if (dlg.DoModal() == IDOK)
	{
		if (!scheduleStore.Add(tmp))
		{
			int errorBox = MessageBox((LPCWSTR)L"Could not load storage.", NULL, MB_OK | MB_ICONWARNING);
			return;
		}
		PrintClassesOfDay(m_daysOfWeekList.GetCurSel());
	}
}


void ScheduledClassEditDlg::OnBnClickedButtonRemove()
{

	if (m_classesInDayList.GetCurSel() == LB_ERR)
	{
		return;
	}

	int id = m_classesInDayList.GetItemData(m_classesInDayList.GetCurSel());


	ScheduledClassDatabaseInterface scheduleStore{ &databaseConnection };
	ScheduleClass tmp;
	if (!scheduleStore.Load(id, tmp))
	{
		int errorBox = MessageBox((LPCWSTR)L"Could not load storage.", NULL, MB_OK | MB_ICONWARNING);
		return;
	}

	CombinedScheduleClassDlg dlg{ DialogMode::eDialogMode_Remove, tmp };
	if (dlg.DoModal() == IDOK)
	{
		if (!scheduleStore.Delete(id))
		{
			int errorBox = MessageBox((LPCWSTR)L"Could not load storage.", NULL, MB_OK | MB_ICONWARNING);
			return;
		}
	}
	PrintClassesOfDay(m_daysOfWeekList.GetCurSel());
}

void ScheduledClassEditDlg::OnBnClickedOk()
{
	CDialog::OnOK();
}
