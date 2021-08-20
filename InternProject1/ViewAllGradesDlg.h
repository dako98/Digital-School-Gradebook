#pragma once

#include "DBConnector.h"
// ViewAllGradesDlg dialog

class ViewAllGradesDlg : public CDialog
{
	DECLARE_DYNAMIC(ViewAllGradesDlg)

public:
	ViewAllGradesDlg(CWnd* pParent = nullptr);   // standard constructor

	BOOL OnInitDialog() override;

	virtual ~ViewAllGradesDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ALL_GRADES_DLG };
#endif
private:
	BOOL PrintAllGrades();


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CListBox					m_lsGrades;

	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonEdit();
	afx_msg void OnBnClickedButtonRemove();
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
};
