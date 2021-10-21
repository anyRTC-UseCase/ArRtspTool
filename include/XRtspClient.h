#ifndef __X_RTSP_CLIENT_H__
#define __X_RTSP_CLIENT_H__
#include "arts_def.h"

class XRtspEventCallback
{
public:
	virtual void OnRtspConnecting() = 0;

	virtual void OnRtspConnected() = 0;

	virtual void OnRtspClosed(int errCode) = 0;

	virtual void OnRtspAVData(const char*codecType, bool bKeyframe, unsigned char* pData, int nLen, unsigned int timeStamp) = 0;
};

class XRtspClient
{
public:
	virtual void ShutDown() = 0;	// Will delete client
protected:
	XRtspClient(void){};
	virtual ~XRtspClient(void) {};
	
};

__ar_api__ XRtspClient* CreateRtspClient(XRtspEventCallback &rCallback, char const* rtspURL, bool bUseTcp);


#endif	// __X_RTSP_CLIENT_H__