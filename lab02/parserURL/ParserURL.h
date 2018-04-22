#pragma once

#include <string>
#include <iostream>

enum class Protocol
{
	HTTP,
	HTTPS,
	FTP
};

void ParseURLs(std::istream& input, std::ostream& output);
void PrintURLInfo(std::ostream& output, const std::string& url, Protocol& protocol, int& port, std::string& host, std::string& document);
bool ParseURL(const std::string& url, Protocol& protocol, int& port, std::string& host, std::string& document);