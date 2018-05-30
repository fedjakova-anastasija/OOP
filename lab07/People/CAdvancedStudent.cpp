#include "stdafx.h"
#include "CAdvancedStudent.h"
#include "CPersonImpl.h"

CAdvancedStudent::CAdvancedStudent(const std::string& name, const std::string& surname, const std::string& middleName, const std::string& address, const std::string& universityName, size_t studentTicketNumber, std::string thesisTheme)
	: CStudentImpl<IAdvancedStudent>(name, surname, middleName, address, universityName, studentTicketNumber)
	, m_dissertationTopic(thesisTheme)
{
}

std::string CAdvancedStudent::GetDissertationTopic() const
{
	return m_dissertationTopic;
}
