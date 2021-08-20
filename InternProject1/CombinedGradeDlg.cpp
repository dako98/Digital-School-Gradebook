// CombinedGradeDlg.cpp : implementation file
//

#include "pch.h"
#include "InternProject1.h"
#include "CombinedGradeDlg.h"
#include "afxdialogex.h"

#include "CStudent.h"
#include "CSubject.h"
#include "Utility.h"


// CombinedGradeDlg dialog

IMPLEMENT_DYNAMIC(CombinedGradeDlg, CDialog)

CombinedGradeDlg::CombinedGradeDlg(DialogMode eMode, GRADE& data)
	: CDialog(IDD_GRADES_COMBINED, nullptr)
	, m_eDialogMode(eMode)
	, m_gradeIDVal(0)
	, m_data(data)
	, m_studentStore(&databaseConnection)
	, m_subjectStore(&databaseConnection)
{
}

BOOL CombinedGradeDlg::PrintAllStudents()
{
	BOOL isOK;

	std::vector<STUDENT> allStudents;
	isOK = m_studentStore.LoadAll(allStudents);

	if (isOK)
	{
		CString currentRow;

		for (const auto& student : allStudents)
		{
			currentRow.Format(_T("%d %s %s"),
				student.nID,
				CString{ student.szFirstName },
				CString{ student.szLastName });

			int index = m_studentDropdown.AddString(currentRow);
			m_studentDropdown.SetItemData(index, student.nID);
		}
	}
	return isOK;
}

BOOL CombinedGradeDlg::PrintAllSubjects()
{
	BOOL isOK;

	std::vector<SUBJECT> allStudents;
	isOK = m_subjectStore.LoadAll(allStudents);

	if (isOK)
	{
		CString currentRow;

		for (const auto& student : allStudents)
		{
			currentRow.Format(_T("%d %s"),
				student.nID,
				CString{ student.szName });

			int index = m_subjectDropdown.AddString(currentRow);
			m_subjectDropdown.SetItemData(index, student.nID);
		}
	}
	return isOK;
}

BOOL CombinedGradeDlg::OnInitDialog()
{
	if (!CDialog::OnInitDialog())
		return FALSE;

	BOOL isOK;


	if (m_eDialogMode != DialogMode::eDialogMode_Add)
	{
		m_gradeIDVal = m_data.nID;
	}

	// Load all students
	isOK = PrintAllStudents();

	if (isOK)
	{
		// Select student
		m_studentDropdown.SetCurSel(GetIndexByData(m_data.nStudentID, m_studentDropdown));

		// Load all subjects
		isOK = PrintAllSubjects();
	}

	if (isOK)
	{
		// Select subject
		m_subjectDropdown.SetCurSel(GetIndexByData(m_data.nSubjectID, m_subjectDropdown));


		// Load all grade values
		for (size_t i = GRADE::GRADES::INVALID + 1; i < GRADE::GRADES::COUNT; i++)
		{
			int index = m_gradeDropdown.AddString(MapGradeName(i));
			m_gradeDropdown.SetItemData(index, i);
		}

		// Select grade value
		m_gradeDropdown.SetCurSel(GetIndexByData(m_data.value, m_gradeDropdown));

		// Select date
		m_gradeDateVal.SetDateTime(m_data.dtDate.year
			, m_data.dtDate.month
			, m_data.dtDate.day
			, m_data.dtDate.hour
			, m_data.dtDate.minute
			, m_data.dtDate.second);
	}

	UpdateData(FALSE);

	switch (m_eDialogMode)
	{
	case DialogMode::eDialogMode_View:
	case DialogMode::eDialogMode_Remove:

		m_studentDropdown.EnableWindow(FALSE);
		m_subjectDropdown.EnableWindow(FALSE);
		m_gradeDropdown.EnableWindow(FALSE);
		m_gradeDate.EnableWindow(FALSE);

		break;

	case DialogMode::eDialogMode_Add:

		m_studentDropdown.EnableWindow(TRUE);
		m_subjectDropdown.EnableWindow(TRUE);
		m_gradeDropdown.EnableWindow(TRUE);
		m_gradeDate.EnableWindow(TRUE);

		UpdateData(FALSE);

		break;

	case DialogMode::eDialogMode_Edit:

		m_studentDropdown.EnableWindow(FALSE);
		m_subjectDropdown.EnableWindow(TRUE);
		m_gradeDropdown.EnableWindow(TRUE);
		m_gradeDate.EnableWindow(TRUE);
		break;

	default:
		throw std::invalid_argument{ "Invalid window state." };
		break;
	}
	return isOK;
}

CombinedGradeDlg::~CombinedGradeDlg()
{
}

void CombinedGradeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_GRADES_GRADE_ID, m_gradeIDVal);
	DDX_Control(pDX, IDC_GRADES_STUDENT_COMBO, m_studentDropdown);
	DDX_Control(pDX, IDC_GRADES_SUBJECT_COMBO, m_subjectDropdown);
	DDX_Control(pDX, IDC_GRADES_GRADE_COMBO, m_gradeDropdown);
	DDX_Control(pDX, IDC_GRADE_DATETIMEPICKER, m_gradeDate);
	DDX_DateTimeCtrl(pDX, IDC_GRADE_DATETIMEPICKER, m_gradeDateVal);
}


BEGIN_MESSAGE_MAP(CombinedGradeDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CombinedGradeDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CombinedGradeDlg message handlers


void CombinedGradeDlg::OnBnClickedOk()
{
	UpdateData();

	BOOL isOK = TRUE;
	GRADE st;

	st.nID = m_gradeIDVal;

	if (m_eDialogMode != DialogMode::eDialogMode_Remove)
	{
		st.nStudentID = m_studentDropdown.GetItemData(m_studentDropdown.GetCurSel());
		st.nSubjectID = m_subjectDropdown.GetItemData(m_subjectDropdown.GetCurSel());
		st.value = m_gradeDropdown.GetItemData(m_gradeDropdown.GetCurSel());

		DBTIMESTAMP date;
		m_gradeDateVal.GetAsDBTIMESTAMP(date);
		st.dtDate.year		= date.year;
		st.dtDate.month		= date.month;
		st.dtDate.day		= date.day;
		st.dtDate.hour		= date.hour;
		st.dtDate.minute	= date.minute;
		st.dtDate.second	= date.second;
		
		if (st.Validate())
		{
			m_data = st;
			CDialog::OnOK();
		}
		else
		{
			int errorBox = MessageBox((LPCWSTR)L"Error! Check your input.", NULL, MB_OK | MB_ICONWARNING);
		}
	}
	else
	{
		m_data = st;
		CDialog::OnOK();
	}
}
