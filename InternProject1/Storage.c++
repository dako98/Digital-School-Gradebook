/*
template<class T>
Storage<T>::Storage(const std::string& path)
	:path(path)
{
	std::fstream file{ path, std::ios::in | std::ios::out };

	if (!file.is_open())
	{
		throw std::exception{ std::string{"Can not access file: \"" + path + "\""}.c_str() };
	}

	file.close();
}

template<class T>
Storage<T>::~Storage()
{
}

template<class T>
BOOL Storage<T>::Add(T& recStudent)
{
	BOOL isGood = TRUE;

	if (isGood = recStudent.Validate())
	{
		std::ofstream file{ path, std::ofstream::app };

		file << recStudent << '\n';

		isGood = file.good();
		file.close();
	}
	return isGood;
}

template<class T>
BOOL Storage<T>::Edit(T& recStudent)
{
	BOOL isGood = TRUE;

	isGood = recStudent.Validate();
	
	if (isGood)
	{

		std::vector<T> students;
		std::fstream file{ path, std::ios::in };

		if (file.good())
		{
			if (isGood = _LoadAll(students, file))
			{

				auto elem = std::find_if(students.begin(), students.end(),
					[&recStudent](const T& s) {return s.nID == recStudent.nID; });

				if (elem != students.end())
				{
					*elem = recStudent;
					isGood = TRUE;
				}
				else
				{
					isGood = FALSE;
				}

				file.close();

				if (isGood)
				{
					file.open(path, std::ios::out | std::ios::trunc);

					isGood = _AddBulk(students, file);
				}
			}
		}
		file.close();
	}
	return isGood;
}

template<class T>
BOOL Storage<T>::_AddBulk(const std::vector<T>& allStudents, std::fstream& file)
{
	BOOL isGood = TRUE;

	for (const T& student : allStudents)
	{
		if (isGood = student.Validate())
		{

			file << student << '\n';

			isGood = file.good();
		}
	}

	return isGood;
}

template<class T>
BOOL Storage<T>::Delete(const int nStudentID)
{
	BOOL isGood = TRUE;

	std::vector<T> students;
	std::fstream file{ path, std::ios::in };

	if (isGood = file.is_open())
	{
		if (isGood = _LoadAll(students, file))
		{

			students.erase(std::remove_if(students.begin(), students.end(),
				[&nStudentID](const T& s) {return s.nID == nStudentID; }),
				students.end());

			file.close();
			file.open(path, std::ios::out | std::ios::trunc);

			isGood = _AddBulk(students, file);
		}
	}
	file.close();

	return isGood;
}

template<class T>
BOOL Storage<T>::Load(const int nStudentID, T& recStudent)
{
	BOOL isGood = TRUE;
	T tmp;

	std::ifstream file{ path, std::ios::in };

	if (file.is_open())
	{
		isGood = FALSE;

		while (file.good() && file.peek() != EOF)
		{
			file >> tmp;
			file.ignore(1);

			if (file.good() && tmp.Validate() && tmp.nID == nStudentID)
			{
				isGood = TRUE;
				break;
			}
		}
	}
	else
	{
		isGood = FALSE;
	}

	file.close();

	if (isGood)
	{
		recStudent = tmp;
	}

	return isGood;
}

template<class T>
BOOL Storage<T>::NextID(int& id) const
{
	BOOL isGood = TRUE;

	std::ifstream file{ path, std::ios::in };
	int lastID = 0;
	T tmp;

	while (file.good() && file.peek() != EOF)
	{
		file >> tmp;
		file.ignore(1);

		if (file.good() && tmp.Validate())
		{
			lastID = max(lastID, tmp.nID);
		}
		else
		{
			isGood = FALSE;
		}
	}

	if (isGood)
	{
		id = lastID + 1;
	}

	return isGood;
}

template<class T>
BOOL Storage<T>::LoadAll(std::vector<T>& out)
{
	BOOL isOK = FALSE;

	std::fstream file{ path, std::ios::in };

	if (file.is_open())
	{
		isOK = _LoadAll(out, file);
	}

	file.close();

	return isOK;
}

template<class T>
BOOL Storage<T>::_LoadAll(std::vector<T>& allStudents, std::fstream& file)
{
	BOOL isGood = TRUE;
	T tmp;

	allStudents.clear();

	if (file.good())
	{

		while (file.good() && file.peek() != EOF)
		{
			file >> tmp;
			file.ignore(1);

			if (file.good() && tmp.Validate())
			{
				allStudents.push_back(tmp);
			}
			else
			{
				isGood = FALSE;
				break;
			}
		}
	}
	else
	{
		isGood = FALSE;
	}

	return isGood;
}

*/