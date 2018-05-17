#include "stdafx.h"
#include "ParserURL.h"
#include <exception>
#include <map>
#include <regex>
#include <sstream>

namespace
{
const std::map<Protocol, std::string> MATCH_PROTOCOL = {
	{ Protocol::HTTP, "http" },
	{ Protocol::HTTPS, "https" },
	{ Protocol::FTP, "ftp" },
};

const int MIN_BOUND = 1;
const int MAX_BOUND = 65535;
} // namespace

void ParseURLs(std::istream& input, std::ostream& output)
{
	std::string url;
	while (std::getline(std::cin, url))
	{
		if (url.empty())
		{
			break;
		}

		int port;
		std::string host;
		std::string document;
		Protocol protocol;
		if (!ParseURL(url, protocol, port, host, document))
		{
			std::cout << "URL parsing failed" << std::endl;
			continue;
		}

		PrintURLInfo(std::cout, url, protocol, port, host, document);
	}
}

void PrintURLInfo(std::ostream& output, const std::string& url, Protocol& protocol, int port, const std::string& host, const std::string& document)
{
	output << url << std::endl
		   << "HOST: " << host << std::endl
		   << "PORT: " << port << std::endl
		   << "DOC: " << document << std::endl;
}

Protocol ParseProtocol(const std::string& protocolStr)
{
	std::string protocol;
	transform(protocolStr.begin(), protocolStr.end(), back_inserter(protocol), tolower);
	for (const auto& item : MATCH_PROTOCOL)
	{
		if (protocol == item.second)
		{
			return item.first;
		}
	}

	throw std::invalid_argument("Unknown protocol");
}

int ParsePort(const std::string& strPort, Protocol protocol)
{
	if (strPort.empty())
	{
		return static_cast<int>(protocol);
	}

	int port = std::stoi(strPort);
	if (port < MIN_BOUND || port > MAX_BOUND)
	{
		throw std::invalid_argument("Port is out of range 1, 65535");
	}

	return port;
}

void TryParseURL(const std::string& url, Protocol& protocol, int& port, std::string& host, std::string& document)
{
	std::regex urlRegex(R"(^(\w+):\/\/([^\s:\/]+)(?::(\d+))?(?:\/(\S*))?$)", std::regex::icase);
	std::smatch urlMatch;
	bool mapped = regex_search(url, urlMatch, urlRegex);
	if (!mapped)
	{
		throw std::runtime_error("Match failed");
	}

	protocol = ParseProtocol(urlMatch[1]);
	host = urlMatch[2];
	port = ParsePort(urlMatch[3], protocol);
	document = urlMatch[4];
}

bool ParseURL(const std::string& url, Protocol& protocol, int& port, std::string& host, std::string& document)
{
	try
	{
		TryParseURL(url, protocol, port, host, document);
		return true;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return false;
	}
}
