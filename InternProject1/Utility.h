#pragma once

static const char* const databaseConnectionString =	"Driver={ODBC Driver 17 for SQL Server}; Server=(localdb)\\MSSQLLocalDB; Database=Test1;";

//static const char* const studentsPath	=	"Students.txt";
//static const char* const teachersPath	=	"Teachers.txt";
//static const char* const subjectsPath	=	"Subjects.txt";
//static const char* const gradesPath	=	"Grades.txt";

static const char* const studentsPath			=	databaseConnectionString;
static const char* const teachersPath			=	databaseConnectionString;
static const char* const subjectsPath			=	databaseConnectionString;
static const char* const gradesPath				=	databaseConnectionString;
static const char* const classesPath			=	databaseConnectionString;




enum DialogMode
{
	eDialogMode_None = 0,
	eDialogMode_Add,
	eDialogMode_Edit,
	eDialogMode_Remove,
	eDialogMode_View
};

extern int		GetIndexByData(const int target, const CComboBox& comboBox);
extern CString	MapGradeName(const int value);