#pragma once

#include "Utility.h"
#include "CTeacher.h"
#include "Storage.h"

// CombinedTeacherDlg dialog

class CombinedTeacherDlg : public CDialog
{
	DECLARE_DYNAMIC(CombinedTeacherDlg)

public:
	CombinedTeacherDlg(DialogMode eMode, const TEACHER& data);

	BOOL OnInitDialog() override;

	virtual ~CombinedTeacherDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TEACHER_COMBINED };
#endif

private:
	DialogMode					m_eDialogMode;
	TeacherDatabaseInterface	m_store;
	TEACHER						m_tmp;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CEdit						m_teacherNum;
	CEdit						m_teacherFirstName;
	CEdit						m_teacherLastName;
	int							m_teacherNumberVal;

	afx_msg void OnBnClickedOk();
};
