#include "PullToRtc1xN.h"

PullToRtc1xN::PullToRtc1xN(void)
	: rtsp_client_(NULL)
	, nvcap_client_(NULL)
	, rtc_client_(NULL)
{

}
PullToRtc1xN::~PullToRtc1xN(void)
{

}

int PullToRtc1xN::StartTask(const std::string& strUrlOrId, PullMode pmode, const std::string&strAppId, const std::string&strChanId)
{
	if (rtc_client_ == NULL) {
		rtc_client_ = createArLiteApi();
		rtc_client_->init(strAppId.c_str(), "", this, NULL);
		rtc_client_->set_parameters("{\"Cmd\":\"SetHost\", \"Host\": true}");
		rtc_client_->set_parameters("{\"Cmd\":\"SetStreamCast\", \"HostUId\": \"NoBody\"}");
		rtc_client_->join_channel(strChanId.c_str(), "", 0);
		lst_chan_id_.push_back(strChanId);
		str_chan_id_ = strChanId;
	}
	if (pmode == PM_RTSP_UDP || pmode == PM_RTSP_TCP) {
		if (rtsp_client_ == NULL) {
			rtsp_client_ = CreateRtspClient(*this, strUrlOrId.c_str(), pmode == PM_RTSP_TCP);
		}
	}
	else if (pmode == PM_NV_DEV) {
#ifdef RTX_NV_CAP
		if (nvcap_client_ == NULL) {
			nvcap_client_ = createRtxNvCap();
			nvcap_client_->SetVideoParam(640, 480, 30, 512000);
			nvcap_client_->SetRtxNvCapEnvent(this);

			nvcap_client_->StartCap(strUrlOrId.c_str(), 7081);
		}
#endif
	}
	return 0;
}
int PullToRtc1xN::AddTask(const std::string& strChanId)
{
	if (rtc_client_ == NULL) {
		return -1;
	}
	std::list<std::string>::iterator itlr = lst_chan_id_.begin();
	while (itlr != lst_chan_id_.end()) {
		if ((*itlr).compare(strChanId) == 0) {
			return -1;
		}
		itlr++;
	}
	rtc_client_->join_channel(strChanId.c_str(), "", 0);
	lst_chan_id_.push_back(strChanId);
	return 0;
}
void PullToRtc1xN::StopTask()
{
	if (rtsp_client_ != NULL) {
		rtsp_client_->ShutDown();
		rtsp_client_ = NULL;
	}
#ifdef RTX_NV_CAP
	if (nvcap_client_ != NULL) {
		nvcap_client_->Close();
		delete nvcap_client_;
		nvcap_client_ = NULL;
	}
#endif

	if (rtc_client_ != NULL) {
		rtc_client_->leave_channel(str_chan_id_.c_str());
		std::list<std::string>::iterator itlr = lst_chan_id_.begin();
		while (itlr != lst_chan_id_.end()) {
			rtc_client_->leave_channel((*itlr).c_str());
			itlr++;
		}
		rtc_client_->fini();
		rtc_client_ = NULL;
	}

	lst_chan_id_.clear();
}

bool PullToRtc1xN::DoProcess()
{
	//* 主线程 - 处理业务逻辑
	return true;
}

//* For XRtspEventCallback
void PullToRtc1xN::OnRtspConnecting()
{
	printf("PullToRtc1xN::OnRtspConnecting \r\n");
}
void PullToRtc1xN::OnRtspConnected()
{
	printf("PullToRtc1xN::OnRtspConnected \r\n");
}
void PullToRtc1xN::OnRtspClosed(int errCode)
{
	printf("PullToRtc1xN::OnRtspClosed code: %d \r\n", errCode);
}
void PullToRtc1xN::OnRtspAVData(const char*codecType, bool bKeyframe, unsigned char* pData, int nLen, unsigned int timeStamp)
{
	if (strcmp("H264", codecType) == 0) {
		if (bKeyframe) {
			printf("Key: %d len: %d\r\n", bKeyframe, nLen);
		}
		if (rtc_client_ != NULL) {
			video_frame_info_t vFrameInfo;
			vFrameInfo.codec = video_codec_e::eVIDEO_CODEC_H264;
			vFrameInfo.type = bKeyframe?video_frame_type_e::eVIDEO_FRAME_KEY : video_frame_type_e::eVIDEO_FRAME_DELTA;
			vFrameInfo.frames_per_sec = video_frame_rate_e::eVIDEO_FRAME_RATE_FPS_30;
			std::list<std::string>::iterator itlr = lst_chan_id_.begin();
			while (itlr != lst_chan_id_.end()) {
				rtc_client_->send_video_data((*itlr).c_str(), 0, pData, nLen, &vFrameInfo);
				itlr++;
			}
		}
	}
}

//* For RtxNvCapEnvent
void PullToRtc1xN::OnRTXNvH264Data(const char* pData, int nLen)
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
		std::list<std::string>::iterator itlr = lst_chan_id_.begin();
		while (itlr != lst_chan_id_.end()) {
			rtc_client_->send_video_data((*itlr).c_str(), 0, pData, nLen, &vFrameInfo);
			itlr++;
		}
	}
}

//* For ARtSEvent
void PullToRtc1xN::on_join_channel_success(const char *channel, int elapsed) 
{
	printf("PullToRtc1xN::on_join_channel_success : %s\r\n", channel);
}
void PullToRtc1xN::on_connection_lost(const char *channel) 
{
	printf("PullToRtc1xN::on_connection_lost : %s\r\n", channel);
}
void PullToRtc1xN::on_rejoin_channel_success(const char *channel, const char* uid, int elapsed)
{
	printf("PullToRtc1xN::on_rejoin_channel_success : %s\r\n", channel);
}
void PullToRtc1xN::on_error(const char *channel, int error, const char *msg) 
{
	printf("PullToRtc1xN::on_error : %s err: %d\r\n", channel, error);
}

