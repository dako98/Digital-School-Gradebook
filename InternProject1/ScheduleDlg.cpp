// ScheduleDlg.cpp : implementation file
//

#include "pch.h"
#include "InternProject1.h"
#include "ScheduleDlg.h"
#include "afxdialogex.h"

#include "Utility.h"
#include "ScheduledClassEditDlg.h"

#include "CSchedule.h"
#include "Storage.h"


// ScheduleDlg dialog

IMPLEMENT_DYNAMIC(ScheduleDlg, CDialog)

ScheduleDlg::ScheduleDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_SCHEDULE, pParent)
	, m_scheduleStore(&databaseConnection)
	, m_classStore(&databaseConnection)
	, m_schedule()
{

}

ScheduleDlg::~ScheduleDlg()
{
}

BOOL ScheduleDlg::PrintSchedule()
{
	int nCount = m_ScheduleListControl.GetItemCount();

	// Delete all of the items from the list view control.
	for (int i = 0; i < nCount; i++)
	{
		m_ScheduleListControl.DeleteItem(0);
	}

	int nColumnCount = m_ScheduleListControl.GetHeaderCtrl()->GetItemCount();

	// Delete all of the columns.
	for (int i = 0; i < nColumnCount; i++)
	{
		m_ScheduleListControl.DeleteColumn(0);
	}


	if (!m_scheduleStore.Load(m_classSelectDropList.GetItemData(m_classSelectDropList.GetCurSel()), m_schedule))
	{
		return FALSE;
	}

	ListView_SetExtendedListViewStyle(m_ScheduleListControl, LVS_EX_GRIDLINES);

	CString text;

	unsigned int maxRows = 0;
	unsigned int days = m_schedule.days.size();
	unsigned int currentDay = 0;
	for (const auto& day : m_schedule.days)
	{
		maxRows = ((maxRows < day.classes.size()) ? day.classes.size() : maxRows);
		text.Format(_T("Day %d"), currentDay + 1);

		m_ScheduleListControl.InsertColumn(currentDay + 1, text, LVCFMT_CENTER, 80);
		currentDay++;
	}

	for (size_t i = 0; i < maxRows; i++)
	{
		text.Format(_T("%d"), i + 1);
		m_ScheduleListControl.InsertItem(0, text);
	}

	std::set<int> uniqueIDs;

	for (const auto& day : m_schedule.days)
	{
		for (const auto& _class : day.classes)
		{
			uniqueIDs.insert(_class.nSubjectID);
		}
	}

	std::vector<int> ids(uniqueIDs.begin(), uniqueIDs.end());
	std::unordered_map<int, CString> m_subjectNames;

	if(!IDtoNameMapper(&databaseConnection, _T("Subjects"), _T("ID"), _T("Name"), ids, m_subjectNames))
	{
		// Failing to map the names is a non-critical error.
		int errorBox = MessageBox((LPCWSTR)L"Could not load storage.", NULL, MB_OK | MB_ICONWARNING);
	}

	for (size_t col = 0; col < days; col++)
	{
		int row = 0;
		for (const auto& _class : m_schedule.days[col].classes)
		{
			text.Format(_T("%s"), m_subjectNames[_class.nSubjectID]);
			m_ScheduleListControl.SetItemText(row, col, text);
			++row;
		}
	}

	return TRUE;
}

BOOL ScheduleDlg::OnInitDialog()
{
	if (!CDialog::OnInitDialog())
	{
		return FALSE;
	}

	std::vector<STUDENT_CLASS> allClasses;

	if (!m_classStore.LoadAll(allClasses))
	{
		return FALSE;
	}

	CString currentRow;

	for (const auto& cClass : allClasses)
	{
		currentRow.Format(_T("%d %s"),
			cClass.nID,
			cClass.szName);

		int index = m_classSelectDropList.AddString(currentRow);
		m_classSelectDropList.SetItemData(index, cClass.nID);
	}

	m_classSelectDropList.SetCurSel(allClasses.size() > 0 ? 0 : CB_ERR);

	if (m_classSelectDropList.GetCurSel() != CB_ERR)
	{
		if (!PrintSchedule())
		{
			return FALSE;
		}
	}

	return TRUE;
}

void ScheduleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SCHEDULE_LIST, m_ScheduleListControl);
	DDX_Control(pDX, IDC_SCHEDULE_CLASS_COMBO, m_classSelectDropList);
}


BEGIN_MESSAGE_MAP(ScheduleDlg, CDialog)
	ON_CBN_SELCHANGE(IDC_SCHEDULE_CLASS_COMBO, &ScheduleDlg::OnCbnSelchangeClassCombo)
	ON_BN_CLICKED(IDC_BTN_SCHEDULE_EDIT, &ScheduleDlg::OnBnClickedButtonEdit)
	ON_WM_CONTEXTMENU()
END_MESSAGE_MAP()


// ScheduleDlg message handlers


void ScheduleDlg::OnCbnSelchangeClassCombo()
{
	// TODO: Add your control notification handler code here
	PrintSchedule();
}


void ScheduleDlg::OnBnClickedButtonEdit()
{
	// TODO: Add your control notification handler code here
	ScheduledClassEditDlg dlg(m_schedule.classID, CSchedule::DAYS_IN_WEEK);
	dlg.DoModal();
	PrintSchedule();
}


void ScheduleDlg::OnContextMenu(CWnd* pWnd, CPoint point)
{
	POSITION pos = m_ScheduleListControl.GetFirstSelectedItemPosition();
	bool bIsItemSelected = pos != NULL;

	CMenu submenu;
	submenu.CreatePopupMenu();

	submenu.AppendMenu(MF_STRING, ID_POPUP_ADD,		_T("Add student"));
	submenu.AppendMenu(MF_STRING, ID_POPUP_EDIT,	_T("Edit student"));
	submenu.AppendMenu(MF_STRING, ID_POPUP_DELETE,	_T("Delete student"));
	submenu.AppendMenu(MF_STRING, ID_POPUP_VIEW,	_T("View student"));

	//disable edit/delete/view from submenu
	submenu.EnableMenuItem(ID_POPUP_EDIT,		!bIsItemSelected);
	submenu.EnableMenuItem(ID_POPUP_DELETE,		!bIsItemSelected);
	submenu.EnableMenuItem(ID_POPUP_VIEW,		!bIsItemSelected);

	submenu.TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this);
}