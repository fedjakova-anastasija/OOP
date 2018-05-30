#pragma once
#include "stdafx.h"
#include "IStudent.h"

class IAdvancedStudent : public IStudent
{
public:
	virtual std::string GetDissertationTopic() const = 0;
};