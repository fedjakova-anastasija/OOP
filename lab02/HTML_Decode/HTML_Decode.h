#pragma once

#include "stdafx.h"

std::string DecodeHtmlEntitiesInString(const std::string& subject, const std::string& searchString, const std::string& replacementString);
std::string HtmlDecode(const std::string& html);
bool DecodeHtmlEntities(std::istream& input, std::ostream& output);
