#ifndef __NV_TO_RTC_H__
#define __NV_TO_RTC_H__
#include <string>
#include "RtxNvCap.h"
#include "ARtS.h"
#include "VidToRtc.h"

class NvToRtc : public VidToRtc, public RtxNvCapEnvent, public ARtSEvent
{
public:
	NvToRtc(void);
	virtual ~NvToRtc(void);

	virtual int StartTask(const std::string&strDevId, const std::string&strAppId, const std::string&strChanId);
	virtual void StopTask();

	virtual bool DoProcess();

	//* For RtxNvCapEnvent
	virtual void OnRTXNvH264Data(const char*pData, int nLen);

	//* For ARtSEvent
	virtual void on_join_channel_success(const char *channel, int elapsed);
	virtual void on_connection_lost(const char *channel);
	virtual void on_rejoin_channel_success(const char *channel, int elapsed);
	virtual void on_warning(const char *channel, int warning, const char *msg);
	virtual void on_error(const char *channel, int error, const char *msg);
	virtual void on_rtc_stats(const AR::RtcStats& stats);

private:
	RtxNvCap*	nvcap_client_;

	ARtS*			rtc_client_;

};


#endif	// __NV_TO_RTC_H__
