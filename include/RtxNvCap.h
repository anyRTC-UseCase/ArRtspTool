#ifndef __RTX_NV_CAP_H__
#define __RTX_NV_CAP_H__

#if defined(__ANDROID__) || defined(__linux__)
#define NV_API extern "C" __attribute__((visibility("default")))
#define NV_CALL
#else
#define NV_API extern "C"
#define NV_CALL
#endif

class RtxNvCapEnvent
{
public:
	RtxNvCapEnvent(void) {};
	virtual ~RtxNvCapEnvent(void) {};

	virtual void OnRTXNvH264Data(const char*pData, int nLen) = 0;
};

class RtxNvCap
{
protected:
	RtxNvCap(void){};
	
public:
	virtual ~RtxNvCap(void){};

	virtual void SetVideoParam(int nWidth, int nHeight, int nFps, int nBitrate) = 0;
	virtual void SetRtxNvCapEnvent(RtxNvCapEnvent*pEvent) = 0;
	
	virtual int StartCap(const char* pDevName, int nPort) = 0;
	virtual void Close() = 0;
};


NV_API RtxNvCap* NV_CALL createRtxNvCap();
	

#endif // __RTX_NV_CAP_H__