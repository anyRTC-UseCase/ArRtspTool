#ifndef __RTSP_TO_RTC_H__
#define __RTSP_TO_RTC_H__
#include <string>
#include "XRtspClient.h"
#include "ARtS.h"
#include "VidToRtc.h"

class RtspToRtc : public VidToRtc, public XRtspEventCallback, public ARtSEvent
{
public:
	RtspToRtc(void);
	virtual ~RtspToRtc(void);

	void SetUseTcp(int nUseTcp);

	virtual int StartTask(const std::string&strRtspUrl, const std::string&strAppId, const std::string&strChanId);
	virtual void StopTask();

	virtual bool DoProcess();

	//* For XRtspEventCallback
	virtual void OnRtspConnecting();
	virtual void OnRtspConnected();
	virtual void OnRtspClosed(int errCode);
	virtual void OnRtspAVData(const char*codecType, bool bKeyframe, unsigned char* pData, int nLen, unsigned int timeStamp);

	//* For ARtSEvent
	virtual void on_join_channel_success(const char *channel, int elapsed);
	virtual void on_connection_lost(const char *channel);
	virtual void on_rejoin_channel_success(const char *channel, int elapsed);
	virtual void on_warning(const char *channel, int warning, const char *msg);
	virtual void on_error(const char *channel, int error, const char *msg);
	virtual void on_rtc_stats(const AR::RtcStats& stats);


private:
	XRtspClient*	rtsp_client_;

	ARtS*			rtc_client_;
	bool			b_use_tcp_;
};

#endif	// __RTSP_TO_RTC_H__