#include "stdafx.h"
#include "CPersonImpl.h"
#include "CStudent.h"

CStudent::CStudent(const std::string& name, const std::string& surname, const std::string& middleName, const std::string& address, const std::string& universityName, size_t studentTicketNumber)
	: CStudentImpl<IStudent>(name, surname, middleName, address, universityName, studentTicketNumber)
{
}
