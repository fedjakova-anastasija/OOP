#pragma once
#include <functional>
#include <iostream>
#include <map>
#include <sstream>

class CTVSet;

class CRemoteControl
{
public:
	CRemoteControl(CTVSet& tv, std::istream& input, std::ostream& output);
	bool HandleCommand();

private:
	bool TurnOn(std::istream& args);
	bool TurnOff(std::istream& args);
	bool Info(std::istream& args);
	bool SelectChannel(std::istream& args);
	bool SelectPreviousChannel(std::istream& args);
	bool CheckChannelNumber(const std::string& inputString, int& number);

	void SetChannelName(std::istream& args);
	void GetChannelByName(std::istream& args);
	void GetChannelName(std::istream& args);
	void DeleteChannelName(std::istream& args);

private:
	using ActionMap = std::map<std::string, std::function<void(std::istream& args)>>;
	CTVSet& m_tv;
	std::istream& m_input;
	std::ostream& m_output;

	const ActionMap m_actionMap;
};