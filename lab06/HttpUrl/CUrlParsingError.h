#pragma once
#include "stdafx.h"

class CUrlParsingError : public std::invalid_argument
{
public:
	CUrlParsingError(const std::string& message)
		: invalid_argument(message) {};
};