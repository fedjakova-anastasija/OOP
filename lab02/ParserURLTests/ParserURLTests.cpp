#include "stdafx.h"
#include "../ParserURL/ParserURL.h"
#include <map>

bool CheckParseURL(const std::string &url, Protocol protocolExpected,
	const std::string& hostExpected, const std::string& documentExpected)
{
	const int portExpected = static_cast<int>(protocolExpected);

	int port;
	std::string host;
	std::string document;
	Protocol protocol;
	if (!ParseURL(url, protocol, port, host, document))
	{
		return false;
	}

	return (protocol == protocolExpected && port == portExpected
		&& host == hostExpected && document == documentExpected);
}

TEST_CASE("Parses sample URL", "[parseURL]")
{
	std::string url("http://www.mysite.com/docs/document1.html?page=30&lang=en#title");
	CHECK(CheckParseURL(url, Protocol::HTTP, "www.mysite.com", "docs/document1.html?page=30&lang=en#title"));
}

TEST_CASE("Parses URLs with all possible protocols", "[parseURL]")
{
	CHECK(CheckParseURL("http://example.com", Protocol::HTTP, "example.com", ""));
	CHECK(CheckParseURL("https://example.com", Protocol::HTTPS, "example.com", ""));
	CHECK(CheckParseURL("ftp://example.com", Protocol::FTP, "example.com", ""));
}

TEST_CASE("Parses protocols in any letter cases", "[parseURL]")
{
	CHECK(CheckParseURL("HTTP://example.com", Protocol::HTTP, "example.com", ""));
}

TEST_CASE("Fails to parse url without required parts", "[parseURL]")
{
	int port;
	std::string host;
	std::string document;
	Protocol protocol;
	CHECK_FALSE(ParseURL("example.com", protocol, port, host, document));
	CHECK_FALSE(ParseURL("http://:8080/index.html", protocol, port, host, document));
	CHECK_FALSE(ParseURL("http:///index.html", protocol, port, host, document));
	CHECK_FALSE(ParseURL("http://", protocol, port, host, document));
}

TEST_CASE("Fails to parse port out of bounds", "[parseURL]")
{
	int port;
	std::string host;
	std::string document;
	Protocol protocol;
	CHECK_FALSE(ParseURL("https://example.com:0", protocol, port, host, document));
	CHECK(ParseURL("http://example.com:100", protocol, port, host, document));
	CHECK_FALSE(ParseURL("http://example.com:65536", protocol, port, host, document));
}

TEST_CASE("Fails to parse correct port", "[parseURL]")
{
	int port;
	std::string host;
	std::string document;
	Protocol protocol;
	CHECK(ParseURL("https://example.com:100", protocol, port, host, document));
}
