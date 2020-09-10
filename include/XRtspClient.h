#ifndef __X_RTSP_CLIENT_H__
#define __X_RTSP_CLIENT_H__
#include "ArBase.h"

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

AR_API XRtspClient* AR_CALL CreateRtspClient(XRtspEventCallback &rCallback, char const* rtspURL, bool bUseTcp);


#endif	// __X_RTSP_CLIENT_H__