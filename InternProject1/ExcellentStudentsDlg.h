#pragma once
#include "DBConnector.h"


// ExcellentStudentsDlg dialog

class ExcellentStudentsDlg : public CDialog
{
	DECLARE_DYNAMIC(ExcellentStudentsDlg)

public:
	ExcellentStudentsDlg(CWnd* pParent = nullptr);   // standard constructor

	BOOL OnInitDialog() override;

	virtual ~ExcellentStudentsDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EXCELLENT_STUDENTS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CListBox excellentStudentsList;
private:
	std::unique_ptr<ObjectInterface<STUDENT>>	studentStore;
	std::unique_ptr<ObjectInterface<GRADE>>		gradeStore;
};
