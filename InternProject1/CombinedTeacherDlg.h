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
	DialogMode m_eDialogMode;
	ObjectInterface<TEACHER>* store;
	TEACHER tmp;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CEdit teacherNum;
	CEdit teacherFirstName;
	CEdit teacherLastName;
	int teacherNumberVal;
	afx_msg void OnBnClickedOk();
};
