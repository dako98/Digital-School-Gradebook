--DB: (localdb)\MSSQLLocalDB

CREATE DATABASE Test1
USE Test1

CREATE TABLE [Teachers]
(
[ID]			INT				IDENTITY PRIMARY KEY NOT NULL,

[FirstName]		NVARCHAR(20)	NOT NULL,
[LastName]		NVARCHAR(20)	NOT NULL
)

CREATE TABLE [Classes]
(
[ID]			INT				IDENTITY PRIMARY KEY NOT NULL,

[Name]			NVARCHAR(5)		UNIQUE NOT NULL,
[ClassTeacherID]INT				REFERENCES [Teachers]([ID]) NOT NULL	
)

CREATE TABLE [Students]
(
[ID]			INT				IDENTITY PRIMARY KEY NOT NULL,

[NumberInClass]	INT				NOT NULL,
[FirstName]		NVARCHAR(20)	NOT NULL,
[LastName]		NVARCHAR(20)	NOT NULL,
[Birthday]		DATETIME		NOT NULL,
[ClassID]		INT				REFERENCES [Classes]([ID]) NOT NULL
)

CREATE UNIQUE INDEX UniqueNumberInClass   
   ON Students([ClassID], [NumberInClass]); 

CREATE TABLE [Subjects]
(
[ID]			INT				IDENTITY PRIMARY KEY NOT NULL,

[Name]			NVARCHAR(20)	NOT NULL,
[TeacherID]		INT				REFERENCES [Teachers]([ID]) ON DELETE CASCADE NOT NULL,
[RoomName]		NVARCHAR(20)	NOT NULL
)

CREATE TABLE [Schedule]
(
[ID]			INT				IDENTITY PRIMARY KEY NOT NULL,

[Number]		INT				NOT NULL,
[SubjectID]		INT				REFERENCES [Subjects]([ID]) NOT NULL,
[DayOfWeek]		INT				CHECK([DayOfWeek] < 7) NOT NULL,
[ClassID]		INT				REFERENCES [Classes]([ID]) NOT NULL
)

/*
CREATE UNIQUE INDEX UniqueNumberInScheduleClass
   ON Schedule([Number], [DayOfWeek], [ClassID]);
*/

CREATE TABLE [GradesValues]
(
[Value]			INT				PRIMARY KEY NOT NULL,

[Name]			VARCHAR(20)		UNIQUE NOT NULL
)

CREATE TABLE [Grades]
(
[ID]			INT				IDENTITY PRIMARY KEY NOT NULL,

[StudentID]		INT				REFERENCES [Students]([ID]) ON DELETE CASCADE NOT NULL,
[SubjectID]		INT				REFERENCES [SUBJECTS]([ID]) ON DELETE CASCADE NOT NULL,
[Date]			DATETIME		NOT NULL,
[Value]			INT				REFERENCES [GradesValues]([Value]) NOT NULL
)

/*----------------------------------------*/





INSERT INTO [Teachers]([FirstName],[LastName])
VALUES
('T1','TT1'),
('T2','TT2'),
('T3','TT3'),
('T4','TT4'),
('T5','TT5'),
('T6','TT6')

INSERT INTO [Classes]([Name],[ClassTeacherID])
VALUES
('C1',1),
('C2',2),
('C3',3)

INSERT INTO [Students]([NumberInClass],[FirstName],[LastName],[Birthday],[ClassID])
VALUES
(1, 'S1','SS1', '2021-05-01',1),
(2, 'S2','SS2', '2021-05-02',1),
(3, 'S3','SS3', '2021-05-03',2),
(4, 'S4','SS4', '2021-05-04',2),
(5, 'S5','SS5', '2021-05-05',3),
(6, 'S6','SS6', '2021-05-06',3)

INSERT INTO [Subjects]([Name],[RoomName],[TeacherID])
VALUES
('SU1','R1',1),
('SU2','R2',2),
('SU3','R3',3),
('SU4','R4',4),
('SU5','R5',5),
('SU6','R6',6)

INSERT INTO [Schedule]([Number],[SubjectID],[DayOfWeek],[ClassID])
VALUES
(1,1,0,1),
(2,2,0,1),
(3,3,0,1),
(4,4,0,1),
(5,5,0,1),
(6,6,0,1),
(7,1,0,1),
						   
(1,1,1,1),
(2,6,1,1),
(3,5,1,1),
(4,4,1,1),
(5,3,1,1),
(6,2,1,1),
(7,1,1,1),
						   
(1,2,2,1),
(2,4,2,1),
(3,6,2,1),
(4,1,2,1),
(5,1,2,1),
(6,3,2,1),
(7,5,2,1),
						   
(1,1,3,1),
(2,6,3,1),
(3,2,3,1),
(4,5,3,1),
(5,3,3,1),
(6,1,3,1),
(7,4,3,1),
						   
(1,1,4,1),
(2,3,4,1),
(3,5,4,1),
(4,1,4,1),
(5,6,4,1),
(6,2,4,1),
(7,4,4,1)

INSERT INTO [GradesValues]([Name],[Value])
VALUES
('A',5),
('B',4),
('C',3),
('D',2),
('F',1)

INSERT INTO [Grades]([StudentID],[SubjectID],[Value],[Date])
VALUES
(1,1,1,'2021-05-05'),
(2,2,2,'2021-05-06'),
(3,3,3,'2021-05-07'),
(4,4,4,'2021-05-08'),
(5,5,5,'2021-05-09'),
(6,6,5,'2021-05-10')

/*----------------------------------------*/






SELECT S.*, G.[Date], GV.[Name] AS [Grade], T.FirstName, T.LastName
--, R.[Name]
FROM [Students] S
LEFT JOIN [Grades] G
ON S.ID = G.StudentID
LEFT JOIN GradesValues GV
ON GV.[Value] = G.[Value]
LEFT JOIN [Subjects] SU
ON G.SubjectID = SU.ID
LEFT JOIN [Teachers] T
ON T.ID = SU.TeacherID
--LEFT JOIN [Rooms] R
--ON R.ID = SU.RoomID
ORDER BY S.FirstName



SELECT * 
FROM [Students]

SELECT * 
FROM [Grades]

SELECT * 
FROM [Subjects]

SELECT *
FROM [Schedule]

SELECT *
FROM [Classes]


/*
UPDATE [Students]
SET [FirstName] = 'Iv\0an', [LastName] = 'Ivanov'
WHERE [ID] = 1;

UPDATE [Grades]
SET [Value] = 3
WHERE [ID] = 1;
*/


INSERT INTO [Students]([NumberInClass],[FirstName],[LastName],[Birthday],[ClassID])
VALUES
(5, 'S1','SS1', '2021-05-01',1)

DELETE [Students]

UPDATE [Students]
SET [FirstName] = 'abc', [NumberInClass] = 2
WHERE [ID] = 2



UPDATE [Grades]
SET [Value] = [Value] - 1

--SELECT S.*, R.[Name] AS [RoomName] FROM [Subjects] S LEFT JOIN [Rooms] R ON S.RoomID = R.ID WHERE S.[ID] = 2



SELECT TOP 1 * FROM [Students] ORDER BY [ID] DESC

SELECT * FROM [Students] WHERE [ID] = 3



SELECT *
FROM [Schedule] sc
JOIN [Subjects] su
ON su.ID = sc.SubjectID
WHERE sc.[DayOfWeek] = 0
ORDER BY
sc.[DayOfWeek], sc.[Number]




select scope_identity() as last_id










INSERT INTO [Students]([NumberInClass],[FirstName],[LastName],[Birthday],[ClassID])
VALUES
(1, 'S1','SS1', '2021-05-01',2)







/*----------------------------------------*/

DROP TABLE [Grades]
DROP TABLE [GradesValues]
DROP TABLE [Schedule]
DROP TABLE [Subjects]
DROP TABLE [Students]
DROP TABLE [Classes]
DROP TABLE [Teachers]



/*----------------------------------------*/
sp_who

SELECT SCOPE_IDENTITY()

select scope_identity() as last_id
SELECT scope_identity() AS last_id