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
#include "RtspToRtc.h"
#include "XUtil.h"

int main(int argc, char*argv[])
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

	initARtSEngine();

	RtspToRtc* rtspToRtc = new RtspToRtc();
	std::string strRtspUrl = conf.GetValue("rtsp", "url");
	if (strRtspUrl.length() == 0) {
		std::cout << "Rtsp url is null..." << std::endl;
		getchar();
		return -1;
	}
	std::string strAppId = conf.GetValue("rtc", "app_id");
	if (strAppId.length() == 0) {
		std::cout << "Rtc appId is null..." << std::endl;
		getchar();
		return -1;
	}
	std::string strChanId = conf.GetValue("rtc", "chan_id");
	if (strChanId.length() == 0) {
		std::cout << "Rtc chanId is null..." << std::endl;
		getchar();
		return -1;
	}

	if (rtspToRtc->StartTask(strRtspUrl, strAppId, strChanId) != 0) {
		std::cout << "Rtsp to rtc start got error!" << std::endl;
		getchar();
		return -1;
	}

	while (1) {
		if (!rtspToRtc->DoProcess()) {
			break;
		}

		XSleep(1);
	}

	rtspToRtc->StopTask();
	delete rtspToRtc;
	rtspToRtc = NULL;
	deinitARtSEngine();

	return 0;
}

