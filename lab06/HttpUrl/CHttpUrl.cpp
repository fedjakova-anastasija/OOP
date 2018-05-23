#include "stdafx.h"
#include "CHttpUrl.h"
#include "CUrlParsingError.h"

namespace
{
const std::map<Protocol, std::string> MATCH_PROTOCOL = {
	{ Protocol::HTTP, "http" },
	{ Protocol::HTTPS, "https" }
};

const int MIN_BOUND = 1;
const int MAX_BOUND = 65535;

std::string GetProtocol(Protocol protocol)
{
	return (protocol == Protocol::HTTP) ? "http" : "https";
}
}

CHttpUrl::CHttpUrl(const std::string& url)
	: m_url(url)
{
	std::regex urlRegex(R"(^(\w+):\/\/([^\s:\/]+)(?::(\d+))?(?:\/(\S*))?$)", std::regex::icase);
	std::smatch urlMatch;
	bool mapped = regex_search(url, urlMatch, urlRegex);
	if (!mapped)
	{
		throw CUrlParsingError("Wrong URL");
	}

	m_protocol = ParseProtocol(urlMatch[1]);
	m_domain = ParseDomain(urlMatch[2]);
	m_port = ParsePort(urlMatch[3]);
	m_document = ParseDocument(urlMatch[4]);
}

CHttpUrl::CHttpUrl(std::string const& domain, std::string const& document, Protocol protocol)
	: m_domain(domain)
	, m_document(ParseDocument(document))
	, m_protocol(protocol)
{
	std::regex domainRegex(R"(^([^\s:\/]+)$)");
	std::smatch urlMatch;
	bool mapped = regex_search(domain, urlMatch, domainRegex);
	if (!mapped)
	{
		throw CUrlParsingError("Wrong domain");
	}

	std::string portString;
	if (static_cast<unsigned short>(m_protocol) == m_port)
	{
		portString = "";
	}
	else
	{
		portString = ":" + std::to_string(m_port);
	}

	std::string protocolStr;
	
	for (const auto& item : MATCH_PROTOCOL)
	{
		if (protocolStr == item.second)
		{
			m_protocol = item.first;
		}
	}
	m_url = m_protocol + "://" + m_domain + portString + m_document;
}

CHttpUrl::CHttpUrl(std::string const& domain, std::string const& document, Protocol protocol, unsigned short port)
	: m_domain(domain)
	, m_document(ParseDocument(document))
	, m_protocol(protocol)
	, m_port(port)
{
	if (port < MIN_BOUND || MAX_BOUND < port)
	{
		throw CUrlParsingError("Wrong port");
	}

	std::string portString;
	if (static_cast<unsigned short>(m_protocol) == m_port)
	{
		portString = "";
	}
	else
	{
		portString = ":" + std::to_string(m_port);
	}

	std::string protocolStr;
	
	for (const auto& item : MATCH_PROTOCOL)
	{
		if (protocolStr == item.second)
		{
			m_protocol = item.first;
		}
	}
	m_url = m_protocol + "://" + m_domain + portString + m_document;
}

std::string CHttpUrl::ParseDomain(std::string const& domain)
{
	if (domain.empty())
	{
		throw CUrlParsingError("Wrong domain");
	}

	return domain;
}

std::string CHttpUrl::ParseDocument(const std::string& document)
{
	return (document[0] != '/') || (document.empty()) ? '/' + document : document;
}

Protocol CHttpUrl::ParseProtocol(const std::string& protocol)
{
	std::string protocolStr;
	transform(protocol.begin(), protocol.end(), back_inserter(protocolStr), tolower);
	for (const auto& item : MATCH_PROTOCOL)
	{
		if (protocolStr == item.second)
		{
			return item.first;
		}
	}

	throw CUrlParsingError("Wrong protocol");
}

unsigned short CHttpUrl::ParsePort(const std::string& strPort)
{
	if (strPort.empty())
	{
		return static_cast<unsigned short>(m_protocol);
	}

	int port = std::stoi(strPort);
	if (port < MIN_BOUND || port > MAX_BOUND)
	{
		throw CUrlParsingError("Port is out of range 1, 65535");
	}

	return port;
}

std::string CHttpUrl::GetUrl() const
{
	return m_url;
}

std::string CHttpUrl::GetDomain() const
{
	return m_domain;
}

std::string CHttpUrl::GetDocument() const
{
	return m_document;
}

Protocol CHttpUrl::GetProtocol() const
{
	return m_protocol;
}

unsigned short CHttpUrl::GetPort() const
{
	return m_port;
}
