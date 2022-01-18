/*
 *  Copyright (c) 2020 The anyRTC project authors. All Rights Reserved.
 *
 *  Website: https://www.anyrtc.io for more details.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */
#ifndef __PULL_TO_RTC_1xN_H__
#define __PULL_TO_RTC_1xN_H__
#include <list>
#include <string>
#include "XRtspClient.h"
#include "RtxNvCap.h"
#include "VidToRtc1xN.h"
#include "IArLiteApi.h"

class PullToRtc1xN : public VidToRtc1xN, public XRtspEventCallback, public RtxNvCapEnvent, public IArLiteApiEvent
{
public:
	PullToRtc1xN(void);
	virtual ~PullToRtc1xN(void);

	//* VidToRtcM
	virtual int StartTask(const std::string& strUrlOrId, PullMode pmode, const std::string&strAppId, const std::string&strChanId);
	virtual int AddTask(const std::string& strChanId);
	virtual void StopTask();
	virtual bool DoProcess();

	//* For XRtspEventCallback
	virtual void OnRtspConnecting();
	virtual void OnRtspConnected();
	virtual void OnRtspClosed(int errCode);
	virtual void OnRtspAVData(const char*codecType, bool bKeyframe, unsigned char* pData, int nLen, unsigned int timeStamp);

	//* For RtxNvCapEnvent
	virtual void OnRTXNvH264Data(const char* pData, int nLen);

	//* For IArLiteApiEvent
	virtual void on_join_channel_success(const char *channel, int elapsed);
	virtual void on_connection_lost(const char *channel);
	virtual void on_rejoin_channel_success(const char* channel, const char* uid, int elapsed);
	virtual void on_error(const char *channel, int error, const char *msg);

private:
	XRtspClient*	rtsp_client_;
	RtxNvCap*		nvcap_client_;

	IArLiteApi*		rtc_client_;
	std::string		str_chan_id_;
	std::list<std::string> lst_chan_id_;
};

#endif	// __PULL_TO_RTC_1xN_H__