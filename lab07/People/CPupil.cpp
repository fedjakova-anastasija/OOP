#include "stdafx.h"
#include "CPersonImpl.h"
#include "CPupil.h"

CPupil::CPupil(const std::string& name, const std::string& surname, const std::string& middleName, const std::string& address, const std::string& schoolName, const std::string& schoolClass)
	: CPersonImpl<IPupil>(name, surname, middleName, address)
	, m_schoolName(schoolName)
	, m_schoolClass(schoolClass)
{
}

std::string CPupil::GetSchoolName() const
{
	return m_schoolName;
}

std::string CPupil::GetSchoolClass() const
{
	return m_schoolClass;
}