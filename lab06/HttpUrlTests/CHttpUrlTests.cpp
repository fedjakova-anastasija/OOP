#include "stdafx.h"
#include "../HttpUrl/CHttpUrl.h"
#include "../HttpUrl/CUrlParsingError.h"

const std::map<Protocol, int> DEFAULT_PORTS = {
	{ Protocol::HTTP, 80 },
	{ Protocol::HTTPS, 443 },
};

void CheckHttpUrlParsing(const std::string& url, Protocol protocolExpected, int portExpected, const std::string& domainExpected, const std::string& documentExpected)
{
	CHttpUrl httpUrl(url);

	CHECK(httpUrl.GetProtocol() == protocolExpected);
	CHECK(httpUrl.GetDomain() == domainExpected);
	CHECK(httpUrl.GetPort() == portExpected);
	CHECK(httpUrl.GetDocument() == documentExpected);
}

void CheckHttpUrlParsing(const std::string& url, Protocol protocolExpected, const std::string& domainExpected, const std::string& documentExpected)
{
	const int portExpected = DEFAULT_PORTS.at(protocolExpected);
	return CheckHttpUrlParsing(url, protocolExpected, portExpected, domainExpected, documentExpected);
}

void CheckHttpUrlParsingFail(const std::string& url)
{
	CHECK_THROWS_AS(CHttpUrl(url), CUrlParsingError);
}

TEST_CASE("Parses URL")
{
	std::string url("http://mail.ru/photos");
	CheckHttpUrlParsing(url, Protocol::HTTP, "mail.ru", "/photos");
}

TEST_CASE("Parses URLs with HTTP and HTTPS")
{
	CheckHttpUrlParsing("http://example.com", Protocol::HTTP, "example.com", "/");
	CheckHttpUrlParsing("https://example.com", Protocol::HTTPS, "example.com", "/");
}

TEST_CASE("Parses protocols in any letter cases")
{
	CheckHttpUrlParsing("httP://example.com", Protocol::HTTP, "example.com", "/");
	CheckHttpUrlParsing("htTps://example.com", Protocol::HTTPS, "example.com", "/");
}

TEST_CASE("Fails to parse only domain")
{
	CheckHttpUrlParsingFail("example.com");
}

TEST_CASE("Fails to parse only protocol")
{
	CheckHttpUrlParsingFail("http://");
}

TEST_CASE("Fails to parse url without domain")
{
	CheckHttpUrlParsingFail("http://:20/example.com");
}

TEST_CASE("Fails to parse url with syntax error")
{
	CheckHttpUrlParsingFail("http:/example.com");
}

TEST_CASE("Parses URL without port")
{
	CheckHttpUrlParsing("http://example.com", Protocol::HTTP, "example.com", "/");
	CheckHttpUrlParsing("https://example.com/ex", Protocol::HTTPS, "example.com", "/ex");
}

TEST_CASE("Fails to parse port out of bounds")
{
	CheckHttpUrlParsingFail("https://example.com:0");
	CheckHttpUrlParsingFail("http://example.com:65536");
}

TEST_CASE("Parses URL with empty document or without document")
{
	CheckHttpUrlParsing("http://example.com", Protocol::HTTP, "example.com", "/");
	CheckHttpUrlParsing("https://example.com/", Protocol::HTTPS, "example.com", "/");
}

TEST_CASE("Parses URL with default port and hides it")
{
	CheckHttpUrlParsing("http://example.com:80", Protocol::HTTP, "example.com", "/");
	CheckHttpUrlParsing("https://example.com:443", Protocol::HTTPS, "example.com", "/");
}

TEST_CASE("Parses URL with custom port and shows it")
{
	CheckHttpUrlParsing("http://example.com:8", Protocol::HTTP, 8, "example.com", "/");
	CheckHttpUrlParsing("https://example.com:4",  Protocol::HTTPS, 4, "example.com", "/");
}
