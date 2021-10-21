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
#ifndef __PULL_TO_RTC_NxN_H__
#define __PULL_TO_RTC_NxN_H__
#include <list>
#include <map>
#include <string>
#include "XRtspClient.h"
#include "RtxNvCap.h"
#include "VidToRtcNxN.h"
#include "IArLiteChan.h"

class PullToRtcNxN : public VidToRtcNxN, public IArLiteChanEvent
{
public:
	PullToRtcNxN(void);
	virtual ~PullToRtcNxN(void);

	//* For MVidToRtc
	virtual int StartTask( const std::string& strAppId);
	virtual int AddTask(const std::string& strUrlOrId, PullMode pmode, const std::string& strChanId);
	virtual void StopTask();
	virtual bool DoProcess();

	//* For IArLiteChanEvent
	virtual void on_join_channel_success(const char* uid, int elapsed);
	virtual void on_connection_lost(const char* uid);
	virtual void on_rejoin_channel_success(const char* uid, int elapsed);
	virtual void on_error(const char* uid, int error, const char* msg);

protected:
	class RtspPull: public XRtspEventCallback 
	{
	public:
		RtspPull(IArLiteChan*rtcClient);
		virtual ~RtspPull(void);

		//* For XRtspEventCallback
		virtual void OnRtspConnecting();
		virtual void OnRtspConnected();
		virtual void OnRtspClosed(int errCode);
		virtual void OnRtspAVData(const char* codecType, bool bKeyframe, unsigned char* pData, int nLen, unsigned int timeStamp);

		void Start(const std::string& strUId, const std::string& strUrl, bool bUseTcp, const std::string& strChanId);
		void Stop();

	private:
		std::string str_uid_;
		IArLiteChan* rtc_client_;
		XRtspClient* rtsp_client_;
	};

	class NvPull : public RtxNvCapEnvent
	{
	public:
		NvPull(IArLiteChan* rtcClient);
		virtual ~NvPull(void);

		//* For RtxNvCapEnvent
		virtual void OnRTXNvH264Data(const char* pData, int nLen);

		void Start(const std::string& strUId, const std::string& strDevId, const std::string& strChanId);
		void Stop();

	private:
		std::string str_uid_;
		IArLiteChan* rtc_client_;
		RtxNvCap* nvcap_client_;
	};

private:
	IArLiteChan* rtc_client_;

	typedef std::map<std::string, RtspPull*>MapRtspPull;
	MapRtspPull map_rtsp_pull_;

	typedef std::map<std::string, NvPull*>MapNvPull;
	MapNvPull map_nv_pull_;

};

#endif	// __RTSP_TO_RTC_NxN_H__