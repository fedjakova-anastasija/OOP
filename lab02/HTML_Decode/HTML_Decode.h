#pragma once

#include "stdafx.h"

std::string DecodeHtmlCharactersInString(const std::string& subject, const std::string& searchString, const std::string& replacementString);
std::string HtmlDecode(const std::string& html);
bool DecodeHtmlCharacters(std::istream& input, std::ostream& output);
