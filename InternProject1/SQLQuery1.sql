--DB: (localdb)\MSSQLLocalDB

CREATE DATABASE Test1
USE Test1

/*
CREATE TABLE [Class]
(
[ID]			INT				IDENTITY PRIMARY KEY,
[Name]			NVARCHAR(5)		UNIQUE
)*/

CREATE TABLE [Students]
(
[ID]			INT				IDENTITY PRIMARY KEY NOT NULL,

[NumberInClass]	INT				NOT NULL,
[FirstName]		NVARCHAR(20)	NOT NULL,
[LastName]		NVARCHAR(20)	NOT NULL,
[Birthday]		DATE			NOT NULL,
--[ClassID]		INT				REFERENCES [Class]([ID])
)

CREATE TABLE [Teachers]
(
[ID]			INT				IDENTITY PRIMARY KEY NOT NULL,

[FirstName]		NVARCHAR(20)	NOT NULL,
[LastName]		NVARCHAR(20)	NOT NULL
)

/*
CREATE TABLE [Rooms]
(
[ID]			INT				IDENTITY PRIMARY KEY NOT NULL,

[Name]			NVARCHAR(20)	NOT NULL
)
*/

CREATE TABLE [Subjects]
(
[ID]			INT				IDENTITY PRIMARY KEY NOT NULL,

[Name]			NVARCHAR(20)	NOT NULL,
[TeacherID]		INT				REFERENCES [Teachers]([ID]) ON DELETE CASCADE NOT NULL,
[RoomName]		NVARCHAR(20)	NOT NULL
)

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
[Date]			DATE			NOT NULL,
[Value]			INT				REFERENCES [GradesValues]([Value]) NOT NULL
)


INSERT INTO [Students]([NumberInClass],[FirstName],[LastName],[Birthday])
VALUES
(1, 'S1','SS1', '2021-05-01'),
(2, 'S2','SS2', '2021-05-02'),
(3, 'S3','SS3', '2021-05-03'),
(4, 'S4','SS4', '2021-05-04'),
(5, 'S5','SS5', '2021-05-05'),
(6, 'S6','SS6', '2021-05-06')



INSERT INTO [Teachers]([FirstName],[LastName])
VALUES
('T1','TT1'),
('T2','TT2'),
('T3','TT3'),
('T4','TT4'),
('T5','TT5'),
('T6','TT6')

/*
INSERT INTO [Rooms]([Name])
VALUES
('R1'),
('R2'),
('R3'),
('R4'),
('R5'),
('R6')
*/

INSERT INTO [Subjects]([Name],[RoomName],[TeacherID])
VALUES
('SU1','R1',1),
('SU2','R2',2),
('SU3','R3',3),
('SU4','R4',4),
('SU5','R5',5),
('SU6','R6',6)

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


SELECT S.*, G.[Date], GV.[Name], T.FirstName, T.LastName--, R.[Name]
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

/*
UPDATE [Students]
SET [FirstName] = 'Iv\0an', [LastName] = 'Ivanov'
WHERE [ID] = 1;

UPDATE [Grades]
SET [Value] = 3
WHERE [ID] = 1;
*/

INSERT INTO [Students]([FirstName],[LastName],[Birthday])
VALUES
('S123','SS123', '2021-05-01')


DELETE [Students]



UPDATE [Grades]
SET [Value] = [Value] - 1

--SELECT S.*, R.[Name] AS [RoomName] FROM [Subjects] S LEFT JOIN [Rooms] R ON S.RoomID = R.ID WHERE S.[ID] = 2



SELECT TOP 1 * FROM [Students] ORDER BY [ID] DESC

SELECT * FROM [Students] WHERE [ID] = 3



DROP TABLE [Grades]
DROP TABLE [GradesValues]
DROP TABLE [Subjects]
--DROP TABLE [Rooms]
DROP TABLE [Teachers]
DROP TABLE [Students]
--DROP TABLE [Class]
