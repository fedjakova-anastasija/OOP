#pragma once
#include <iostream>
#include <string>

template <class Base>
class CPersonImpl : public Base
{
public:
	CPersonImpl(const std::string& name, const std::string& surname, const std::string middleName, const std::string& address)
		: m_name(name)
		, m_surname(surname)
		, m_middleName(middleName)
		, m_address(address)
	{
	}

	virtual std::string GetName() const
	{
		return m_name;
	}

	virtual std::string GetSurname() const
	{
		return m_surname;
	}

	virtual std::string GetMiddleName() const
	{
		return m_middleName;
	}

	virtual std::string GetAddress() const
	{
		return m_address;
	}

private:
	std::string m_name;
	std::string m_surname;
	std::string m_middleName;
	std::string m_address;
};
