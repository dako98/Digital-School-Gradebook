#pragma once

#include <unordered_map>

#include "DBConnector.h"

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

private:
	
	// Struct[map - studentID] { subject[map - subjectID]{ gradesSum, gradesCount } }
	struct studentStr
	{
		struct subject
		{
			int gradeSum = 0;
			int gradesCount = 0;
		};
		std::unordered_map<int, subject> subject;
	};
	std::unique_ptr <ObjectInterface<STUDENT>>	studentStore;
	std::unique_ptr <ObjectInterface<SUBJECT>>	subjectStore;
	std::unique_ptr <ObjectInterface<GRADE>>	gradeStore;

};
