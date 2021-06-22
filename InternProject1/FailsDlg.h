#pragma once


// FailsDlg dialog

class FailsDlg : public CDialog
{
	DECLARE_DYNAMIC(FailsDlg)

public:
	FailsDlg(CWnd* pParent = nullptr);   // standard constructor

	BOOL OnInitDialog() override;

	virtual ~FailsDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FAILS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CListBox failsList;
	CListBox badGradesList;
};
