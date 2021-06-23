#pragma once


// BirthdayersDlg dialog

class BirthdayersDlg : public CDialog
{
	DECLARE_DYNAMIC(BirthdayersDlg)

public:
	BirthdayersDlg(const DBTIMESTAMP& date);

	BOOL OnInitDialog() override;

	virtual ~BirthdayersDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BIRTHDAYERS };
#endif

private:
	DBTIMESTAMP date;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CListBox birthdayersList;
};
