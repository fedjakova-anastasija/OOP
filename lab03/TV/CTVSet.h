#pragma once

using Channels = std::map<int, std::string>;

class CTVSet
{
public:
	CTVSet();
	~CTVSet();

	bool IsTurnedOn() const;
	void TurnOn();
	void TurnOff();
	bool SelectChannel(int channel);
	int GetChannel() const;
	bool SelectPreviousChannel();

	bool SelectChannel(const std::string& channelName);

	int GetSelectedChannel() const;
	bool SetChannelName(int channel, const std::string& channelName);
	bool DeleteChannelName(const std::string& channelName);
	bool GetChannelName(int channel, std::string& channelName) const;
	bool GetChannelByName(const std::string& channelName, int& channel) const;
	Channels GetAllChannels() const;

private:
	bool RemoveChannelByName(const std::string& channelName);
	void RemoveChannelByNumber(int channel);
	bool FoundByName(const std::string& channelName, int& channel) const;

private:
	bool m_isOn = false;
	int m_selectedChannel = 1;
	int m_previousChannel = 1;

	Channels m_channels;
};