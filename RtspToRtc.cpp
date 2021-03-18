#include "RtspToRtc.h"

RtspToRtc::RtspToRtc(void)
	: rtsp_client_(NULL)
	, rtc_client_(NULL)
	, b_use_tcp_(false)
{

}
RtspToRtc::~RtspToRtc(void)
{

}

void RtspToRtc::SetUseTcp(int nUseTcp)
{
	if (nUseTcp == 0) {
		b_use_tcp_ = false;
	}
	else
	{
		b_use_tcp_ = true;
	}
}

int RtspToRtc::StartTask(const std::string&strRtspUrl, const std::string&strAppId, const std::string&strChanId)
{
	if (rtc_client_ == NULL) {
		rtc_client_ = createARtSEngine();
		rtc_client_->init(strAppId.c_str(), "", this, NULL);
		rtc_client_->set_parameters("{\"Cmd\":\"SetHost\", \"Host\": true}");
		rtc_client_->set_parameters("{\"Cmd\":\"SetStreamCast\", \"HostUId\": \"NoBody\"}");
		rtc_client_->join_channel(strChanId.c_str(), "", 0);
	}
	if (rtsp_client_ == NULL) {
		rtsp_client_ = CreateRtspClient(*this, strRtspUrl.c_str(), b_use_tcp_);
	}
	return 0;
}
void RtspToRtc::StopTask()
{
	if (rtsp_client_ != NULL) {
		rtsp_client_->ShutDown();
		rtsp_client_ = NULL;
	}

	if (rtc_client_ != NULL) {
		rtc_client_->fini();
		rtc_client_ = NULL;
	}
}

bool RtspToRtc::DoProcess()
{
	return true;
}

//* For XRtspEventCallback
void RtspToRtc::OnRtspConnecting()
{

}
void RtspToRtc::OnRtspConnected()
{

}
void RtspToRtc::OnRtspClosed(int errCode)
{

}
void RtspToRtc::OnRtspAVData(const char*codecType, bool bKeyframe, unsigned char* pData, int nLen, unsigned int timeStamp)
{
	if (strcmp("H264", codecType) == 0) {
		if (rtc_client_ != NULL) {
			rtc_client_->send_video_data(0, bKeyframe, pData, nLen);
		}
	}
	
}

//* For ARtSEvent
void RtspToRtc::on_join_channel_success(const char *channel, int elapsed) 
{}
void RtspToRtc::on_connection_lost(const char *channel) 
{}
void RtspToRtc::on_rejoin_channel_success(const char *channel, int elapsed) 
{}
void RtspToRtc::on_warning(const char *channel, int warning, const char *msg) 
{}
void RtspToRtc::on_error(const char *channel, int error, const char *msg) 
{}
void RtspToRtc::on_rtc_stats(const AR::RtcStats& stats) 
{}
