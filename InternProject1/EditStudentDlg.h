#pragma once


// EditStudentDlg dialog

class EditStudentDlg : public CDialog
{
	DECLARE_DYNAMIC(EditStudentDlg)

public:
	EditStudentDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~EditStudentDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EDIT_STUDENT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
