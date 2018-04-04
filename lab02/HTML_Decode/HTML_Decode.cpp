#include "stdafx.h"
#include "HTML_Decode.h"

const std::array<std::pair<std::string, std::string>, 5> HTML_CHARACTERS = { {
	{ "\"", "&quot;" },
	{ "'", "&apos;" },
	{ "<", "&lt;" },
	{ ">", "&gt;" },
	{ "&", "&amp;" },
} };


bool DecodeHtmlCharacters(std::istream& input, std::ostream& output)
{
	std::string html;
	while (std::getline(input, html))
	{
		output << HtmlDecode(html) << std::endl;
	}

	return static_cast<bool>(output);
}

std::string HtmlDecode(const std::string& html)
{
	std::string result = html;
	for (auto& htmlCharacters : HTML_CHARACTERS)
	{
		result = DecodeHtmlCharactersInString(result, htmlCharacters.second, htmlCharacters.first);
	}
	return result;
}

std::string DecodeHtmlCharactersInString(const std::string& subject, const std::string& searchString, const std::string& replacementString)
{
	if (searchString.empty())
	{
		return subject;
	}

	size_t startPos = 0;
	std::string resultString;

	while (startPos != std::string::npos)
	{
		size_t foundPos = subject.find(searchString, startPos);
		resultString.append(subject, startPos, foundPos - startPos);

		if (foundPos != std::string::npos)
		{
			resultString.append(replacementString);
			foundPos += searchString.length();
		}

		startPos = foundPos;
	}

	return resultString;
}


