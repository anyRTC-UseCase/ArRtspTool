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
#ifndef __PULL_MODE_H__
#define __PULL_MODE_H__
#include <stdio.h>
#include <string.h>

typedef enum
{
	PM_RTSP_UDP = 0,		// Rtsp Udp ģʽ
	PM_RTSP_TCP,			// Rtsp Tcp ģʽ
	PM_NV_DEV,				// Nv Jetsonϵ�� �豸
}PullMode;


#endif	// __PULL_MODE_H__
