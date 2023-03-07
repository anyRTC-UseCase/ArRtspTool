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

#include <iostream>
#include "config.h"
#include "PullToRtc1xN.h"
#include "PullToRtcNxN.h"
#include "XUtil.h"

int gVidWidth = 640;
int gVidHeight = 480;
int gVidFps = 30;
int gVidBitrate = 512000;
int main(int argc, char* argv[])
{
	ConfigSet	conf;
	if (argc > 1)
		conf.LoadFromFile(argv[1]);
	else
	{
		std::cout << "Error: Please usage: $0 {conf_path} " << std::endl;
		std::cout << "Please enter any key to exit ..." << std::endl;
		getchar();
		exit(0);
	}
	

	std::string strAppId = conf.GetValue("rtc", "app_id");
	if (strAppId.length() == 0) {
		std::cout << "Rtc appId is null..." << std::endl;
		getchar();
		return -1;
	}
	std::string strMode = conf.GetValue("rtc", "mode");
	if (strMode.compare("1xN") != 0 && strMode.compare("NxN") != 0) {
		std::cout << "Rtc mode must be: 1xN; NxN." << std::endl;
		getchar();
		return -1;
	}
	std::string strChanIds = conf.GetValue("rtc", "chan_id");
	if (strChanIds.length() == 0) {
		std::cout << "Rtc chanId is null..." << std::endl;
		getchar();
		return -1;
	}
	gVidWidth = conf.GetIntVal("vid", "w", 640);
	gVidHeight = conf.GetIntVal("vid", "h", 480);
	gVidFps = conf.GetIntVal("vid", "fps", 30);
	gVidBitrate = conf.GetIntVal("vid", "bitrate", 512)*1000;
	
	//* 支持单路流推多频道
	std::vector<std::string> strArr;
	int nArr = XSplitChar(strChanIds.c_str(), ';', &strArr);
	std::string strChanId = strArr[0];


	VidToRtc1xN* vidToRtc1xN = NULL;
	VidToRtcNxN* vidToRtcNxN = NULL;
	if (strMode.compare("1xN") == 0) {
		// 单路流推到1个或多个频道
		vidToRtc1xN = new PullToRtc1xN();
		std::string strType = conf.GetValue("1xN", "type");
		if (strType.compare("rtsp") == 0) {
			std::string strRtspUrl = conf.GetValue("1xN", "url");
			int nUseTcp = conf.GetIntVal("1xN", "use_tcp");
			if (strRtspUrl.length() == 0) {
				std::cout << "Rtsp url is null..." << std::endl;
				getchar();
				return -1;
			}
			PullMode pmode = nUseTcp == 1 ? PM_RTSP_TCP : PM_RTSP_UDP;
			if (vidToRtc1xN->StartTask(strRtspUrl, pmode, strAppId, strChanId) != 0) {
				std::cout << "Rtsp to rtc start got error!" << std::endl;
				getchar();
				return -1;
			}
		}
		else {
			std::string strDevId = conf.GetValue("1xN", "dev_id");
			if (strDevId.length() == 0) {
				std::cout << "Nv DevId is null..." << std::endl;
				getchar();
				return -1;
			}
			if (vidToRtc1xN->StartTask(strDevId, PM_NV_DEV, strAppId, strChanId) != 0) {
				std::cout << "Nv to rtc start got error!" << std::endl;
				getchar();
				return -1;
			}
		}
		for (int i = 1; i < nArr; i++) {
			std::string& strChanId = strArr[i];
			vidToRtc1xN->AddTask(strChanId);
		}
	}
	else {
		// 多路流推到1个或多个频道
		vidToRtcNxN = new PullToRtcNxN();
		vidToRtcNxN->StartTask(strAppId);
		for (int i = 0; i < nArr; i++) {
			std::string& strChanId = strArr[i];
			std::string strType = conf.GetValue(strChanId.c_str(), "type");
			if (strType.compare("rtsp") == 0) {
				std::string strRtspUrl = conf.GetValue(strChanId.c_str(), "url");
				int nUseTcp = conf.GetIntVal(strChanId.c_str(), "use_tcp");
				if (strRtspUrl.length() != 0) {
					PullMode pmode = nUseTcp == 1 ? PM_RTSP_TCP : PM_RTSP_UDP;
					//* 支持一次性转多路流推到一个频道
					std::vector<std::string> strRtspArr;
					int nRtspArr = XSplitChar(strRtspUrl.c_str(), ';', &strRtspArr);
					for (int j = 0; j < nRtspArr; j++) {
						vidToRtcNxN->AddTask(strRtspArr[j], pmode, strChanId);
					}
				}
			}
			else {
				std::string strDevId = conf.GetValue(strChanId.c_str(), "dev_id");
				//* 支持一次打开多个设备推到一个频道
				std::vector<std::string> strDevArr;
				int nDevArr = XSplitChar(strDevId.c_str(), ';', &strDevArr);
				if (strDevId.length() != 0) {
					for (int j = 0; j < nDevArr; j++) {
						vidToRtcNxN->AddTask(strDevArr[j], PM_NV_DEV, strChanId);
					}
				}
			}
		}
	}
	

	while (1) {
		if (vidToRtc1xN!= NULL && !vidToRtc1xN->DoProcess()) {
			break;
		}
		else if (vidToRtcNxN != NULL && !vidToRtcNxN->DoProcess()) {
			break;
		}

		XSleep(1);
	}

	if (vidToRtc1xN != NULL) {
		vidToRtc1xN->StopTask();
		delete vidToRtc1xN;
		vidToRtc1xN = NULL;
	}

	if (vidToRtcNxN != NULL) {
		vidToRtcNxN->StopTask();
		delete vidToRtcNxN;
		vidToRtcNxN = NULL;
	}

	return 0;
}

