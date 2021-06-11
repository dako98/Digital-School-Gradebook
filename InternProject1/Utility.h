#pragma once

#include <vector>

#include "Teacher.h"
#include "Student.h"

int GetIndexByData(const int target, const CComboBox& comboBox);
void populateList(CComboBox& list, const std::vector<Teacher>& src);
void populateList(CComboBox& list, const std::vector<Student>& src);
