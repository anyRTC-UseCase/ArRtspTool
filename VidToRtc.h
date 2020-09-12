#ifndef __VID_TO_RTC_H__
#define __VID_TO_RTC_H__
#include <string>

class VidToRtc
{
public:
	VidToRtc(void) {};
	virtual ~VidToRtc(void) {};

	virtual int StartTask(const std::string&strUrl, const std::string&strAppId, const std::string&strChanId) = 0;
	virtual void StopTask() = 0;

	virtual bool DoProcess() = 0;
};

#endif	// __VID_TO_RTC_H__
