#include "PullToRtcNxN.h"
#include "XUtil.h"

extern int gVidWidth;
extern int gVidHeight;
extern int gVidFps;
extern int gVidBitrate;

PullToRtcNxN::NvPull::NvPull(IArLiteChan* rtcClient)
	: rtc_client_(rtcClient)
	, nvcap_client_(NULL)
{

}
PullToRtcNxN::NvPull::~NvPull(void)
{

}

//* For RtxNvCapEnvent
void PullToRtcNxN::NvPull::OnRTXNvH264Data(const char* pData, int nLen)
{
	int nType = pData[4] & 0x1f;
	bool bKeyframe = false;
	if (nType == 7) {
		bKeyframe = true;
	}
	if (rtc_client_ != NULL) {
		video_frame_info_t vFrameInfo;
		vFrameInfo.codec = video_codec_e::eVIDEO_CODEC_H264;
		vFrameInfo.type = bKeyframe ? video_frame_type_e::eVIDEO_FRAME_KEY : video_frame_type_e::eVIDEO_FRAME_DELTA;
		vFrameInfo.frames_per_sec = video_frame_rate_e::eVIDEO_FRAME_RATE_FPS_30;
		rtc_client_->send_video_data(str_uid_.c_str(), 0, pData, nLen, &vFrameInfo);
	}
}

void PullToRtcNxN::NvPull::Start(const std::string& strUId, const std::string& strDevId, const std::string& strChanId)
{
#ifdef RTX_NV_CAP
	if (nvcap_client_ == NULL) {
		str_uid_ = strUId;
		nvcap_client_ = createRtxNvCap();
		nvcap_client_->SetVideoParam(gVidWidth, gVidHeight, gVidFps, gVidBitrate);
		nvcap_client_->SetRtxNvCapEnvent(this);

		nvcap_client_->StartCap(strDevId.c_str(), 7081);

		rtc_client_->join_channel(str_uid_.c_str(), strChanId.c_str(), "", 0);
	}
#endif
}
void PullToRtcNxN::NvPull::Stop()
{
#ifdef RTX_NV_CAP
	if (nvcap_client_ != NULL) {
		nvcap_client_->Close();
		nvcap_client_ = NULL;

		rtc_client_->leave_channel(str_uid_.c_str());
	}
#endif
}

PullToRtcNxN::RtspPull::RtspPull(IArLiteChan* rtcClient)
	: rtc_client_(rtcClient)
	, rtsp_client_(NULL)
{

}
PullToRtcNxN::RtspPull::~RtspPull(void)
{

}

//* For XRtspEventCallback
void PullToRtcNxN::RtspPull::OnRtspConnecting()
{
	printf("PullToRtcNxN::RtspPull::OnRtspConnecting \r\n");
}
void PullToRtcNxN::RtspPull::OnRtspConnected()
{
	printf("PullToRtcNxN::RtspPull::OnRtspConnected \r\n");
}
void PullToRtcNxN::RtspPull::OnRtspClosed(int errCode)
{
	printf("PullToRtcNxN::RtspPull::OnRtspClosed \r\n");
}
void PullToRtcNxN::RtspPull::OnRtspAVData(const char* codecType, bool bKeyframe, unsigned char* pData, int nLen, unsigned int timeStamp)
{
	if (strcmp("H264", codecType) == 0) {
		if (bKeyframe) {
			printf("UId: %s Key: %d len: %d\r\n", str_uid_.c_str(), bKeyframe, nLen);
		}
		if (rtc_client_ != NULL) {
			video_frame_info_t vFrameInfo;
			vFrameInfo.codec = video_codec_e::eVIDEO_CODEC_H264;
			vFrameInfo.type = bKeyframe ? video_frame_type_e::eVIDEO_FRAME_KEY : video_frame_type_e::eVIDEO_FRAME_DELTA;
			vFrameInfo.frames_per_sec = video_frame_rate_e::eVIDEO_FRAME_RATE_FPS_30;
			rtc_client_->send_video_data(str_uid_.c_str(), 0, pData, nLen, &vFrameInfo);
		}
	}
}

void PullToRtcNxN::RtspPull::Start(const std::string& strUId, const std::string& strUrl, bool bUseTcp, const std::string& strChanId)
{
	if (rtsp_client_ == NULL) {
		str_uid_ = strUId;
		rtsp_client_ = CreateRtspClient(*this, strUrl.c_str(), bUseTcp);

		rtc_client_->join_channel(str_uid_.c_str(), strChanId.c_str(), "", 0);
	}
}
void PullToRtcNxN::RtspPull::Stop()
{
	if (rtsp_client_ != NULL) {
		rtsp_client_->ShutDown();
		rtsp_client_ = NULL;

		rtc_client_->leave_channel(str_uid_.c_str());
	}
}

PullToRtcNxN::PullToRtcNxN(void)
	: rtc_client_(NULL)
{

}
PullToRtcNxN::~PullToRtcNxN(void)
{

}

//* For MVidToRtc
int PullToRtcNxN::StartTask(const std::string& strAppId)
{
	if (rtc_client_ == NULL) {
		rtc_client_ = createArLiteChan();
		rtc_client_->init(strAppId.c_str(), this, NULL);
		rtc_client_->set_parameters("{\"Cmd\":\"SetHost\", \"Host\": true}");
		rtc_client_->set_parameters("{\"Cmd\":\"SetStreamCast\", \"HostUId\": \"NoBody\"}");
	}

	return 0;
}
int PullToRtcNxN::AddTask(const std::string& strUrlOrId, PullMode pmode, const std::string& strChanId)
{
	if (rtc_client_ == NULL)
		return -1;
	std::string strUId;
	XGetRandomStr(strUId, 16);
	printf("PullToRtcNxN::AddTask uId: %s mode: %d chanId: %s urlOrId: %s\r\n", strUId.c_str(), pmode, strChanId.c_str(), strUrlOrId.c_str());
	if (pmode == PM_RTSP_UDP || pmode == PM_RTSP_TCP) {
		while (1) {
			if (map_rtsp_pull_.find(strUId) == map_rtsp_pull_.end()) {
				RtspPull* rtspPull = new RtspPull(rtc_client_);
				rtspPull->Start(strUId, strUrlOrId, pmode == PM_RTSP_TCP, strChanId);

				map_rtsp_pull_[strUId] = rtspPull;

				break;
			}
			else {
				XSleep(1);
				XGetRandomStr(strUId, 16);
			}
		}
		
	}
	else if (pmode == PM_NV_DEV) {
		while (1) {
			if (map_nv_pull_.find(strUId) == map_nv_pull_.end()) {
				NvPull* nvPull = new NvPull(rtc_client_);
				nvPull->Start(strUId, strUrlOrId, strChanId);

				map_nv_pull_[strUId] = nvPull;
			}
			else {
				XSleep(1);
				XGetRandomStr(strUId, 16);
			}
		}
	}
	

	return 0;
}
void PullToRtcNxN::StopTask()
{
	MapRtspPull::iterator itrr = map_rtsp_pull_.begin();
	while (itrr != map_rtsp_pull_.end()) {
		RtspPull* rtspPull = itrr->second;
		rtspPull->Stop();
		delete rtspPull;
		rtspPull = NULL;
		itrr = map_rtsp_pull_.erase(itrr);
	}

	MapNvPull::iterator itnr = map_nv_pull_.begin();
	while (itnr != map_nv_pull_.end()) {
		NvPull* nvPull = itnr->second;
		nvPull->Stop();
		delete nvPull;
		nvPull = NULL;
		itnr = map_nv_pull_.erase(itnr);
	}

	if (rtc_client_ != NULL) {
		rtc_client_->fini();
		rtc_client_ = NULL;
	}
}
bool PullToRtcNxN::DoProcess()
{
	//* 主线程 - 处理业务逻辑
	return true;
}

//* For IArLiteChanEvent
void PullToRtcNxN::on_join_channel_success(const char* uid, int elapsed)
{

}
void PullToRtcNxN::on_connection_lost(const char* uid)
{

}
void PullToRtcNxN::on_rejoin_channel_success(const char* uid, int elapsed)
{

}
void PullToRtcNxN::on_error(const char* uid, int error, const char* msg)
{

}
