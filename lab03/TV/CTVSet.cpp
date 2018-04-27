#include "stdafx.h"
#include "CTVSet.h"
#include <utility>

CTVSet::CTVSet()
{
}

CTVSet::~CTVSet()
{
}

bool CTVSet::IsTurnedOn() const
{
	return m_isOn;
}

bool CTVSet::SelectChannel(int channel)
{
	if ((m_isOn) && (channel <= 99) && (channel >= 1))
	{
		m_previousChannel = m_selectedChannel;
		m_selectedChannel = channel;
		return true;
	}

	return false;
}

int CTVSet::GetChannel() const
{
	return m_isOn ? m_selectedChannel : 0;
}

void CTVSet::TurnOn()
{
	m_isOn = true;
}

void CTVSet::TurnOff()
{
	m_isOn = false;
}

bool CTVSet::SelectPreviousChannel()
{
	if (m_isOn)
	{
		std::swap(m_selectedChannel, m_previousChannel);
		return true;
	}

	return false;
}

bool CTVSet::SelectChannel(const std::string& channelName)
{
	int channel = 0;
	if (m_isOn && FoundByName(channelName, channel))
	{
		m_previousChannel = m_selectedChannel;
		m_selectedChannel = channel;
		return true;
	}

	return false;
}

int CTVSet::GetSelectedChannel() const
{
	return m_isOn ? m_selectedChannel : 0;
}

bool CTVSet::SetChannelName(int channel, const std::string& channelName)
{
	if (m_isOn && !channelName.empty() && (channel >= 1 && channel <= 99))
	{
		RemoveChannelByName(channelName);

		if (m_channels.find(channel) != m_channels.end())
		{
			m_channels.at(channel) = channelName;
		}
		else
		{
			m_channels.emplace(channel, channelName);
		}
		return true;
	}

	return false;
}

bool CTVSet::DeleteChannelName(const std::string& channelName)
{
	return m_isOn ? RemoveChannelByName(channelName) : false;
}

bool CTVSet::GetChannelName(int channel, std::string& channelName) const
{
	if (m_isOn && (channel >= 1 && channel <= 99) && m_channels.find(channel) != m_channels.end())
	{
		channelName = m_channels.at(channel);
		return true;
	}

	return false;
}

bool CTVSet::GetChannelByName(const std::string& channelName, int& channel) const
{
	return m_isOn ? FoundByName(channelName, channel) : false;
}

Channels CTVSet::GetAllChannels() const
{
	return m_channels;
}

bool CTVSet::RemoveChannelByName(const std::string& channelName)
{
	int channel = 0;
	if (!FoundByName(channelName, channel))
	{
		return false;
	}

	RemoveChannelByNumber(channel);

	return true;
}

void CTVSet::RemoveChannelByNumber(int channel)
{
	m_channels.erase(channel);
}

bool CTVSet::FoundByName(const std::string& channelName, int& channel) const
{
	auto isEqual = [&channelName](const std::pair<int, std::string>& element) {
		return element.second == channelName;
	};

	auto it = std::find_if(m_channels.begin(), m_channels.end(), isEqual);

	if (it != std::end(m_channels))
	{
		channel = it->first;

		return true;
	}

	return false;
}
