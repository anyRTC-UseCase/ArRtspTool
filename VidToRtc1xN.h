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
#ifndef __VID_TO_RTC_1xN_H__
#define __VID_TO_RTC_1xN_H__
/**
 * 模式： 1xN
 * 说明：
 * 源只有1个，可以转到1个或多个频道中去
 */
#include <string>
#include "PullMode.h"


class VidToRtc1xN
{
public:
	VidToRtc1xN(void) {};
	virtual ~VidToRtc1xN(void) {};

	virtual int StartTask(const std::string&strUrlOrId, PullMode pmode, const std::string&strAppId, const std::string&strChanId) = 0;
	virtual int AddTask(const std::string& strChanId) = 0;
	virtual void StopTask() = 0;

	virtual bool DoProcess() = 0;
};

#endif	// __VID_TO_RTC_1xN_H__
