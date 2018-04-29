#include "stdafx.h"
#include "RemoteControl.h"
#include "CTVSet.h"

CRemoteControl::CRemoteControl(CTVSet& tv, std::istream& input, std::ostream& output)
	: m_tv(tv)
	, m_input(input)
	, m_output(output)
	, m_actionMap({ { "Info", std::bind(&CRemoteControl::Info, this, std::placeholders::_1) },
		  { "TurnOn", std::bind(&CRemoteControl::TurnOn, this, std::placeholders::_1) },
		  { "TurnOff", std::bind(&CRemoteControl::TurnOff, this, std::placeholders::_1) },
		  { "SelectChannel", std::bind(&CRemoteControl::SelectChannel, this, std::placeholders::_1) },
		  { "SelectPreviousChannel", std::bind(&CRemoteControl::SelectPreviousChannel, this, std::placeholders::_1) },
		  { "GetChannelByName", std::bind(&CRemoteControl::GetChannelByName, this, std::placeholders::_1) },
		  { "GetChannelName", std::bind(&CRemoteControl::GetChannelName, this, std::placeholders::_1) },
		  { "SetChannelName", std::bind(&CRemoteControl::SetChannelName, this, std::placeholders::_1) },
		  { "DeleteChannelName", std::bind(&CRemoteControl::DeleteChannelName, this, std::placeholders::_1) } })
{
}

bool CRemoteControl::HandleCommand()
{
	std::string commandLine;
	getline(m_input, commandLine);
	std::istringstream strm(commandLine);

	std::string action;
	strm >> action;

	auto it = m_actionMap.find(action);
	if (it != m_actionMap.end())
	{
		it->second(strm);
		return true;
	}

	return false;
}

bool CRemoteControl::CheckChannelNumber(const std::string& stringNumber, int& number)
{
	try
	{
		number = stoi(stringNumber);
	}
	catch (const std::exception& isError)
	{
		std::cout << isError.what() << std::endl;
		return false;
	}

	return true;
}

bool CRemoteControl::TurnOn(std::istream&)
{
	m_tv.TurnOn();
	m_output << "TV is turned on" << std::endl;

	return true;
}

bool CRemoteControl::TurnOff(std::istream&)
{
	m_tv.TurnOff();
	m_output << "TV is turned off" << std::endl;

	return true;
}

bool CRemoteControl::SelectChannel(std::istream& args)
{
	std::string stringChannelNumber;
	args >> stringChannelNumber;
	int channel;
	if (!CheckChannelNumber(stringChannelNumber, channel))
	{
		return false;
	}

	if ((m_tv.IsTurnedOn()) && ((channel < 1) || (channel > 99)))
	{
		m_output << "Invalid channel" << std::endl;
	}
	else if (!m_tv.IsTurnedOn())
	{
		m_output << "Can't select channel because TV is turned off" << std::endl;
	}
	else
	{
		m_tv.SelectChannel(channel);
		m_output << "Channel selected" << std::endl;
	}

	return true;
}

bool CRemoteControl::SelectPreviousChannel(std::istream&)
{
	if (m_tv.IsTurnedOn())
	{
		m_tv.SelectPreviousChannel();
		m_output << "Previous channel selected" << std::endl;
	}
	else
	{
		m_output << "TV is turned off" << std::endl;
	}

	return true;
}

bool CRemoteControl::Info(std::istream&)
{
	int channel = m_tv.GetSelectedChannel();
	std::string channelName;

	m_output << " Selected channel: " << channel << (m_tv.GetChannelName(channel, channelName) ? " - " + channelName : "") << std::endl;

	Channels channels = m_tv.GetAllChannels();

	if (!channels.empty())
	{
		for (const auto& channel : channels)
		{
			m_output << channel.first << " - " << channel.second << std::endl;
		}
	}

	return true;
}

void CRemoteControl::GetChannelByName(std::istream& args)
{
	std::string channelName;
	args >> channelName;

	Channels channels = m_tv.GetAllChannels();

	if (channelName.empty())
	{
		m_output << "Channel name can not be empty" << std::endl;
	}
	else if (!channels.empty())
	{
		for (const auto& channel : channels)
		{
			if (channelName == channel.second)
			{
				m_output << channel.first << " - " << channel.second << std::endl;
			}
		}
	}
}

void CRemoteControl::GetChannelName(std::istream& args)
{
	int channelNumber;
	args >> channelNumber;	
	
	Channels channels = m_tv.GetAllChannels();

	if (!m_tv.SelectChannel(channelNumber))
	{
		m_output << "Failed to select channel" << std::endl;
	}
	else if (!channels.empty())
	{
		for (const auto& channel : channels)
		{
			if (channelNumber == channel.first)
			{
				m_output << channel.first << " - " << channel.second << std::endl;
			}
		}
	}
}

void CRemoteControl::SetChannelName(std::istream& args)
{
	int channel;
	args >> channel;
	std::string channelName;
	args >> channelName;
	if (channelName.empty())
	{
		m_output << "Name of channel can not be empty" << std::endl;
	}
	else
	{
		m_output << "Name of channel '" << channelName << "' set to '" << channel << " '" << (m_tv.SetChannelName(channel, channelName) ? "successfully" : " not successfully") << std::endl;
	}
}

void CRemoteControl::DeleteChannelName(std::istream& args)
{
	std::string channelName;
	args >> channelName;

	if (channelName.empty())
	{
		m_output << "Name of channel can not be empty" << std::endl;
	}
	else if (!m_tv.DeleteChannelName(channelName))
	{
		m_output << "Failed to delete channel" << std::endl;
	}
	else
	{
		m_output << "Succeded to delete channel" << std::endl;
	}
}
