#include "stdafx.h"
#include "CHttpUrl.h"

std::string GetProtocol(Protocol protocol)
{
	return (protocol == Protocol::HTTP) ? "http" : "https";
}

void PrintURLInfo(std::ostream& output, const std::string& newUrl, const std::string& domain, Protocol& protocol, int port, const std::string& document)
{
	output << "PROTOCOL: " << GetProtocol(protocol) << std::endl;
	output << "DOMAIN: " << domain << std::endl;
	output << "PORT: " <<port << std::endl;
	output << "DOCUMENT: " << document << std::endl;
}

int main()
{
	std::string newUrl;
	std::cout << "URL: ";

	while (std::getline(std::cin, newUrl))
	{
		if (newUrl.empty())
		{
			break;
		}

		std::string domain;
		Protocol protocol;
		int port;
		std::string document;
		try
		{
			CHttpUrl url(newUrl);
			protocol = url.GetProtocol();
			port = url.GetPort();
			document = url.GetDocument();
			domain = url.GetDomain();
			PrintURLInfo(std::cout, newUrl, domain, protocol, port, document);
		}
		catch (const std::exception& e)
		{
			std::cerr << e.what() << std::endl;
		}

		std::cout << std::endl;
		std::cout << "URL: ";

	}

	return 0;
}