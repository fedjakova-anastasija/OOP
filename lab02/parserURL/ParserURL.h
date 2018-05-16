#pragma once

#include <string>
#include <iostream>

enum class Protocol
{
	HTTP = 80,
	HTTPS = 443,
	FTP = 21
};

void ParseURLs(std::istream& input, std::ostream& output);
void PrintURLInfo(std::ostream& output, const std::string& url, Protocol& protocol, int port, const std::string& host, const std::string& document);
bool ParseURL(const std::string& url, Protocol& protocol, int& port, std::string& host, std::string& document);