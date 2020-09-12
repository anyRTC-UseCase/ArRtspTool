#include "NvToRtc.h"

NvToRtc::NvToRtc(void)
	: nvcap_client_(NULL)
	, rtc_client_(NULL)
{

}
NvToRtc::~NvToRtc(void)
{

}

int NvToRtc::StartTask(const std::string&strDevId, const std::string&strAppId, const std::string&strChanId)
{
	if (rtc_client_ == NULL) {
		rtc_client_ = createARtSEngine();
		rtc_client_->init(strAppId.c_str(), "", this, NULL);
		rtc_client_->set_parameters("{\"Cmd\":\"SetHost\", \"Host\": true}");
		rtc_client_->set_parameters("{\"Cmd\":\"SetStreamCast\", \"HostUId\": \"NoBody\"}");
		rtc_client_->join_channel(strChanId.c_str(), "", 0);
	}
	if (nvcap_client_ == NULL) {
		nvcap_client_ = createRtxNvCap();
		nvcap_client_->SetVideoParam(640, 480, 30, 512000);
		nvcap_client_->SetRtxNvCapEnvent(this);

		nvcap_client_->StartCap(strDevId.c_str(), 7081);
	}
	return 0;
}
void NvToRtc::StopTask()
{
	if (nvcap_client_ != NULL) {
		nvcap_client_->Close();
		delete nvcap_client_;
		nvcap_client_ = NULL;
	}

	if (rtc_client_ != NULL) {
		rtc_client_->fini();
		rtc_client_ = NULL;
	}
}

bool NvToRtc::DoProcess()
{
	return true;
}

//* For XRtspEventCallback
void NvToRtc::OnRTXNvH264Data(const char*pData, int nLen)
{
	int nType = pData[4] & 0x1f;
	bool bKeyframe = false;
	if (nType == 7) {
		bKeyframe = true;
	}
	if (rtc_client_ != NULL) {
		rtc_client_->send_video_data(0, bKeyframe, pData, nLen);
	}

}

//* For ARtSEvent
void NvToRtc::on_join_channel_success(const char *channel, int elapsed)
{}
void NvToRtc::on_connection_lost(const char *channel)
{}
void NvToRtc::on_rejoin_channel_success(const char *channel, int elapsed)
{}
void NvToRtc::on_warning(const char *channel, int warning, const char *msg)
{}
void NvToRtc::on_error(const char *channel, int error, const char *msg)
{}
void NvToRtc::on_rtc_stats(const AR::RtcStats& stats)
{}
