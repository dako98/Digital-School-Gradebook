#include "pch.h"
#include "Storage.h"

#include"CStudent.h"
#include"CGrade.h"
#include"CTeacher.h"
#include"CSubject.h"


extern template class Storage<GRADE>;
extern template class Storage<STUDENT>;
extern template class Storage<SUBJECT>;
extern template class Storage<TEACHER>;
