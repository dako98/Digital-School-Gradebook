
// InternProject1Dlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "InternProject1.h"
#include "InternProject1Dlg.h"
#include "afxdialogex.h"

#include "ManageStudentsDlg.h"
#include "ManageSubjectsDlg.h"
#include "ManageGradesDlg.h"
#include "ScheduleDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CInternProject1Dlg dialog



CInternProject1Dlg::CInternProject1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_INTERNPROJECT1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CInternProject1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CInternProject1Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_MANAGESTUDENTS, &CInternProject1Dlg::OnBnClickedManagestudents)
	ON_BN_CLICKED(IDC_BUTTON6, &CInternProject1Dlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CInternProject1Dlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON1, &CInternProject1Dlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CInternProject1Dlg message handlers

BOOL CInternProject1Dlg::OnInitDialog()
{
	if (!CDialogEx::OnInitDialog())
	{
		return FALSE;
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CInternProject1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CInternProject1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CInternProject1Dlg::OnBnClickedManagestudents()
{
	// TODO: Add your control notification handler code here
	ManageStudentsDlg dlg;
	dlg.DoModal();
}


void CInternProject1Dlg::OnBnClickedButton6()
{
	// TODO: Add your control notification handler code here
	ManageSubjectsDlg dlg;
	dlg.DoModal();
}


void CInternProject1Dlg::OnBnClickedButton7()
{
	// TODO: Add your control notification handler code here
	ManageGradesDlg dlg;
	dlg.DoModal();
}


void CInternProject1Dlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	ScheduleDlg dlg;
	dlg.DoModal();
}
