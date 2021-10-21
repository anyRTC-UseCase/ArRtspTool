#ifndef __I_AR_LITE_CHAN_H__
#define __I_AR_LITE_CHAN_H__
#include "arts_def.h"

class IArLiteChanEvent
{
public:
	IArLiteChanEvent(void) {};
	virtual ~IArLiteChanEvent(void) {};

	virtual void on_join_channel_success(const char *uid, int elapsed) {
		(void)uid;
		(void)elapsed;
	};
	virtual void on_connection_lost(const char *uid) {
		(void)uid;
	};
	virtual void on_rejoin_channel_success(const char*uid, int elapsed) {
		(void)uid;
		(void)elapsed;
	};
	virtual void on_token_privilege_will_expire(const char* uid) {
		(void)uid;
	};
	virtual void on_error(const char *uid, int error, const char *msg) {
		(void)uid;
		(void)error;
		(void)msg;
	};
	virtual void on_user_publish_codec_type(const char*uid, video_codec_e*vid_codec_type, audio_codec_e*aud_codec_type) {
		(void)uid;
		(void)vid_codec_type;
		(void)aud_codec_type;
	}
	virtual void on_user_joined(const char *uid, const char * peer_uid, int elapsed) {
		(void)uid;
		(void)peer_uid;
		(void)elapsed;
	};
	virtual void on_user_offline(const char *uid, const char * peer_uid, int reason) {
		(void)uid;
		(void)peer_uid;
		(void)reason;
	};
	virtual void on_user_stream_open(const char *uid, const char * peer_uid, int elapsed) {
		(void)uid;
		(void)peer_uid;
		(void)elapsed;
	};
	virtual void on_user_stream_closed(const char *uid, const char * peer_uid, int reason) {
		(void)uid;
		(void)peer_uid;
		(void)reason;
	};
	virtual void on_user_mute_audio(const char *uid, const char * peer_uid, int muted) {
		(void)uid;
		(void)peer_uid;
		(void)muted;
	};
	virtual void on_user_mute_video(const char *uid, const char * peer_uid, int muted) {
		(void)uid;
		(void)peer_uid;
		(void)muted;
	};
	virtual void on_key_frame_gen_req(const char *uid, const char * requesting_uid, uint8_t stream_id) {
		(void)uid;
		(void)requesting_uid;
		(void)stream_id;
	};
	virtual void on_audio_data(const char *uid, const char * peer_uid, uint32_t sent_ts, uint16_t seqn, uint8_t codec, const void *data, size_t len) {
		(void)uid;
		(void)peer_uid;
		(void)sent_ts;
		(void)seqn;
		(void)codec;
		(void)data;
		(void)len;
	};
	virtual void on_video_data(const char *uid, const char * peer_uid, uint32_t sent_ts, uint8_t codec, uint8_t stream_id, int is_key_frame, const void *data, size_t len) {
		(void)uid;
		(void)peer_uid;
		(void)sent_ts;
		(void)codec;
		(void)stream_id;
		(void)is_key_frame;
		(void)data;
		(void)len;
	};
	virtual void on_rdt_availability_changed(const char *uid, int is_available) {
		(void)uid;
		(void)is_available;
	};
	virtual void on_cmd(const char *uid, const char * peer_uid, int cmd, const void *param, size_t param_len) {
		(void)uid;
		(void)peer_uid;
		(void)cmd;
		(void)param;
		(void)param_len;
	};
	virtual void on_data_from_rdt(const char *uid, const char * peer_uid, const void *data, size_t data_len) {
		(void)uid;
		(void)peer_uid;
		(void)data;
		(void)data_len;
	};
	virtual void on_dec_bitrate(const char *uid, uint32_t bps) {
		(void)uid;
		(void)bps;
	};
	virtual void on_inc_bitrate(const char *uid, uint32_t bps) {
		(void)uid;
		(void)bps;
	};
	virtual void on_target_bitrate_changed(const char *uid, uint32_t target_bps) {
		(void)uid;
		(void)target_bps;
	}
};

class IArLiteChan
{
public:
	virtual int init(const char *app_id, const IArLiteChanEvent *event_handler,  const char *sdk_log_dir) = 0;
	virtual int set_log_level(int nLevel, int nPrintConsole) = 0;
	virtual int config_log(int per_logfile_size, int logfile_roll_count) = 0;
	virtual int	set_parameters(const char*parameters) = 0;
	virtual int join_channel(const char * uid, const char *channel, const void *token, size_t len) = 0;
	virtual int renew_token(const char *uid, const void *token, size_t len) = 0;
	virtual int	set_chan_parameters(const char *uid, const char*parameters) = 0;
	virtual int mute_local_audio(const char *uid, int mute) = 0;
	virtual int mute_remote_audio(const char *uid, const char * remote_uid, int mute) = 0;
	virtual int mute_local_video(const char *uid, int mute) = 0;
	virtual int mute_remote_video(const char *uid, const char * remote_uid, int mute) = 0;
	virtual int request_video_key_frame(const char *uid, const char * remote_uid, uint8_t stream_id) = 0;
	virtual int send_audio_data(const char *uid, const void *data, size_t data_len, audio_frame_info_t *info_ptr) = 0;
	virtual int send_video_data(const char *uid, uint8_t stream_id, const void *data, size_t data_len, video_frame_info_t *info_ptr) = 0;
	virtual int leave_channel(const char *uid) = 0;
	virtual int fini() = 0;

protected:
	IArLiteChan(void) : arlite_event_(NULL) {};

	virtual ~IArLiteChan(void) {};

	IArLiteChanEvent*	arlite_event_;
};

__ar_api__ IArLiteChan* createArLiteChan();


#endif	// __I_AR_LITE_CHAN_H__
