#include "stdafx.h"
#include "ParserURL.h"
#include <exception>
#include <map>
#include <regex>
#include <sstream>

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

void PrintURLInfo(std::ostream& output, const std::string& url, Protocol& protocol, int& port, std::string& host, std::string& document)
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
	if (protocol == "http")
	{
		return Protocol::HTTP;
	}
	if (protocol == "https")
	{
		return Protocol::HTTPS;
	}
	if (protocol == "ftp")
	{
		return Protocol::FTP;
	}
	throw std::exception("Unknown protocol");
}

const std::map<Protocol, int> DEFAULT_PORT = {
	{ Protocol::HTTP, 80 },
	{ Protocol::HTTPS, 443 },
	{ Protocol::FTP, 21 },
};

const int MIN_BOUND = 1;
const int MAX_BOUND = 65535;

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
	port = urlMatch[3].matched ? std::stoi(urlMatch[3]) : static_cast<int>(protocol);

	const std::string str = urlMatch[3];
	if (str.empty())
	{
		port = DEFAULT_PORT.at(protocol);
	}

	if (port < MIN_BOUND || port > MAX_BOUND)
	{
		throw std::exception("Port is out of range 1, 65535");
	}

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
	catch (...)
	{
		std::cerr << "Unknown exception" << std::endl;
		return false;
	}
}
