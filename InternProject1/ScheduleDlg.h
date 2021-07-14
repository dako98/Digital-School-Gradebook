#pragma once


// ScheduleDlg dialog

class ScheduleDlg : public CDialog
{
	DECLARE_DYNAMIC(ScheduleDlg)

public:
	ScheduleDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~ScheduleDlg();

	BOOL OnInitDialog() override;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SCHEDULE };
#endif


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl ScheduleListControl;
	CComboBox classSelectDropList;


private:
	BOOL PrintSchedule();
public:
	afx_msg void OnCbnSelchangeCombo1();
};
