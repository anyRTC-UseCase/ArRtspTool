#ifndef __I_AR_LITE_API_H__
#define __I_AR_LITE_API_H__
#include "arts_def.h"

class IArLiteApiEvent
{
public:
	IArLiteApiEvent(void) {};
	virtual ~IArLiteApiEvent(void) {};
	/**
	* Occur when local user joins channel successfully.
	*
	* @param[in] channel    Channel name
	* @param[in] elapsed_ms Time elapsed (ms) since channel is established
	*/
	virtual void on_join_channel_success(const char *channel, int elapsed) {
		(void)channel;
		(void)elapsed;
	};
	/**
	* Occur when channel is disconnected with server.
	*
	* @param[in] channel Channel name
	*/
	virtual void on_connection_lost(const char *channel) {
		(void)channel;
	};
	
	 /** Occurs when the token expires in 30 seconds.

	  The user becomes offline if the token used in the \ref "joinChannel" method expires. The SDK triggers this callback 30 seconds before the token expires to remind the application to get a new token. Upon receiving this callback, generate a new token on the server and call the \ref IRtcEngine::renewToken "renewToken" method to pass the new token to the SDK.

	  @param token Pointer to the token that expires in 30 seconds.
	  */
	virtual void on_rejoin_channel_success(const char *channel, const char*uid, int elapsed) {
		(void)channel;
		(void)uid;
		(void)elapsed;
	};
	/** Occurs when the token expires in 30 seconds.

	The user becomes offline if the token used in the \ref "joinChannel" method expires. The SDK triggers this callback 30 seconds before the token expires to remind the application to get a new token. Upon receiving this callback, generate a new token on the server and call the \ref IRtcEngine::renewToken "renewToken" method to pass the new token to the SDK.

	@param token Pointer to the token that expires in 30 seconds.
	*/
	virtual void on_token_privilege_will_expire(const char* channel) {
		(void)channel;
	};
	/**
	* Report error message during runtime.
	*
	* In most cases, it means SDK can't fix the issue and application should take action.
	*
	* @param[in] channel Channel name
	* @param[in] code    Error code, see #ar_err_code_e
	* @param[in] msg     Error message
	*/
	virtual void on_error(const char *channel, int error, const char *msg) {
		(void)channel;
		(void)error;
		(void)msg;
	};
	/**
	 * When local publish stream to server, check video&audio codec type.
	 *
	 * In most cases, it means SDK can't fix the issue and application should take action.
	 *
	 * @param[in] channel Channel name
	 * @param[in] vid_codec_type    Video codec, see #video_codec_e
	 * @param[in] aud_codec_type    Video codec, see #audio_codec_e
	 */
	virtual void on_user_publish_codec_type(const char*channel, video_codec_e*vid_codec_type, audio_codec_e*aud_codec_type) {
		(void)channel;
		(void)vid_codec_type;
		(void)aud_codec_type;
	}
	/**
	 * Occur when remote user joins channel successfully.
	 *
	 * @param[in] channel    Channel name
	 * @param[in] uid        Remote user ID
	 * @param[in] elapsed_ms Time elapsed (ms) since channel is established
	 */
	virtual void on_user_joined(const char *channel, const char * uid, int elapsed) {
		(void)channel;
		(void)uid;
		(void)elapsed;
	};
	/**
	* Occur when remote user leaves the channel.
	*
	* @param[in] channel Channel name
	* @param[in] uid     Remote user ID
	* @param[in] reason  Reason, see #user_offline_reason_e
	*/
	virtual void on_user_offline(const char *channel, const char * uid, int reason) {
		(void)channel;
		(void)uid;
		(void)reason;
	};
	/**
	* Occur when start recv a remote user stream.
	*
	* @param[in] channel Channel name
	* @param[in] uid     Remote user ID
	* @param[in] elapsed 
	*/
	virtual void on_user_stream_open(const char *channel, const char * uid, int elapsed) {
		(void)channel;
		(void)uid;
		(void)elapsed;
	};
	/**
	* Occur when stop recv a remote user stream.
	*
	* @param[in] channel Channel name
	* @param[in] uid     Remote user ID
	* @param[in] reason  Reason
	*/
	virtual void on_user_stream_closed(const char *channel, const char * uid, int reason) {
		(void)channel;
		(void)uid;
		(void)reason;
	};
	/**
	 * Occur when a remote user sends notification before enable/disable sending audio.
	 *
	 * @param[in] channel Channel name
	 * @param[in] uid     Remote user ID
	 * @param[in] muted   Mute status:
	 *                    - 0:        unmuted
	 *                    - non-ZERO: muted
	 */
	virtual void on_user_mute_audio(const char *channel, const char * uid, int muted) {
		(void)channel;
		(void)uid;
		(void)muted;
	};
	/**
	 * Occur when a remote user sends notification before enable/disable sending video.
	 *
	 * @param[in] channel Channel name.
	 * @param[in] uid     Remote user ID
	 * @param[in] muted   Mute status:
	 *                    - 0:        unmuted
	 *                    - non-ZERO: muted
	 */
	virtual void on_user_mute_video(const char *channel, const char * uid, int muted) {
		(void)channel;
		(void)uid;
		(void)muted;
	};
	/**
	 * Occur when a remote user requests a keyframe.
	 *
	 * This callback notifies the sender to generate a new keyframe.
	 *
	 * @param[in] channel    Channel name
	 * @param[in] uid        Remote user ID
	 * @param[in] stream_id  Stream ID for which a keyframe is requested
	 */
	virtual void on_key_frame_gen_req(const char *channel, const char * requesting_uid, uint8_t stream_id) {
		(void)channel;
		(void)requesting_uid;
		(void)stream_id;
	};
	/**
	 * Occur when receiving the audio frame of a remote user in the channel.
	 *
	 * @param[in] channel    Channel name
	 * @param[in] uid        Remote user ID to which data is sent
	 * @param[in] sent_ts    Timestamp (ms) for sending data
	 * @param[in] codec      Audio codec type
	 * @param[in] seqn       Audio frame seqn
	 * @param[in] data_ptr   Audio frame buffer
	 * @param[in] data_len   Audio frame buffer length (bytes)
	 */
	virtual void on_audio_data(const char *channel, const char * uid, uint32_t sent_ts, uint16_t seqn, uint8_t codec, const void *data, size_t len) {
		(void)channel;
		(void)uid;
		(void)sent_ts;
		(void)seqn;
		(void)codec;
		(void)data;
		(void)len;
	};
	/**
	 * Occur when receiving the video frame of a remote user in the channel.
	 *
	 * @param[in] channel      Channel name
	 * @param[in] uid          Remote user ID to which data is sent
	 * @param[in] sent_ts      Timestamp (ms) for sending data
	 * @param[in] codec        Video codec type
	 * @param[in] stream_id    Video stream ID. Range is [0, 15]
	 * @param[in] is_key_frame Frame type:
	 *                          - 0:        non-keyframe
	 *                          - non-ZERO: keyframe
	 * @param[in] data_ptr     Video frame buffer
	 * @param[in] data_len     Video frame buffer lenth (bytes)
	 */
	virtual void on_video_data(const char *channel, const char * uid, uint32_t sent_ts, uint8_t codec, uint8_t stream_id, int is_key_frame, const void *data, size_t len) {
		(void)channel;
		(void)uid;
		(void)sent_ts;
		(void)codec;
		(void)stream_id;
		(void)is_key_frame;
		(void)data;
		(void)len;
	};
	/**
	 * Occur when RDT(reliable data tunnel) availability changed.
	 *
	 * @note As an E2E tunnel, RDT is available only if there are just 2 users in a channel.
	 *
	 * @param[in] channel          Channel name
	 * @param[in] is_available     Available status:
	 *                             - 0:         unavailable
	 *                             - non-ZERO:  available
	 */
	virtual void on_rdt_availability_changed(const char *channel, int is_available) {
		(void)channel;
		(void)is_available;
	};
	/**
	 * Occur when command comes from reliable data channel.
	 *
	 * @param[in] channel    Channel name
	 * @param[in] uid        Remote user ID
	 * @param[in] cmd        Command value
	 * @param[in] param_ptr  Parameter buffer, set NULL if non-exist
	 * @param[in] param_len  Parameter buffer length in bytes if exist
	 */
	virtual void on_cmd(const char *channel, const char * uid, int cmd, const void *param, size_t param_len) {
		(void)channel;
		(void)uid;
		(void)cmd;
		(void)param;
		(void)param_len;
	};
	/**
	 * Occurs when data comes from reliable data channel.
	 *
	 * @param[in] channel      Channel name
	 * @param[in] uid          Remote user ID
	 * @param[in] data_ptr     Data buffer
	 * @param[in] data_len     Data buffer length
	 */
	virtual void on_data_from_rdt(const char *channel, const char * uid, const void *data, size_t data_len) {
		(void)channel;
		(void)uid;
		(void)data;
		(void)data_len;
	};
	virtual void on_dec_bitrate(const char *channel, uint32_t bps) {
		(void)channel;
		(void)bps;
	};
	virtual void on_inc_bitrate(const char *channel, uint32_t bps) {
		(void)channel;
		(void)bps;
	};
	/**
	 * Advise application to update encoder bitrate.
	 *
	 * @param[in] channel    Channel name
	 * @param[in] target_bps Target value (bps) by which the bitrate should update
	 */
	virtual void on_target_bitrate_changed(const char *channel, uint32_t target_bps) {
		(void)channel;
		(void)target_bps;
	}
};

class IArLiteApi
{
public:
	/**
	 * Initialize the AR ARTS service.
	 *
	 * @note Each process can only be initialized once.
	 *
	 * @param[in] app_id          Application ID
	 * @param[in] event_handler   A set of callback that handles AR SDK events
	 * @param[in] sdk_log_dir     Directory for storing SDK log
	 *                            If `sdk_log_dir` is NULL, the log directory is located in:
	 *                            - iOS:         Application¡¯s documents directory
	 *                            - macOS:       ~/Documents/
	 *                            - Android:     /sdcard/
	 *                            - Ubuntu:      Application¡¯s current directory
	 *                            - Embedded:    Application¡¯s current directory
	 *
	 * @return
	 * - = 0: Success
	 * - < 0: Failure
	 */
	virtual int init(const char *app_id, const char * uid, const IArLiteApiEvent *event_handler, const char *sdk_log_dir) = 0;
	/**
	 * Set the log level.
	 *
	 * Select a level from 0 to 6.
	 *
	 * @param[in] level Log level. Range is [0, 6]
	 * @param[in] console Print on console. 0 no >0 yes
	 *
	 * @return
	 * - = 0: Success
	 * - < 0: Failure
	 */
	virtual int set_log_level(int nLevel, int nPrintConsole) = 0;
	/**
	 * Set the log file configuration.
	 *
	 * @param[in] size_per_file   Each log file size (bytes). Range is [10000, 1000000]
	 * @param[in] max_file_count  Maxium log file count for rollback. Range is [1, 100]
	 *
	 * @return
	 * - = 0: Success
	 * - < 0: Failure
	 */
	virtual int config_log(int per_logfile_size, int logfile_roll_count) = 0;
	/**
	 * Provides technical preview functionalities or special customizations by configuring the SDK with JSON options.
	 *
	 * The JSON options are not public by default. AR is working on making commonly used JSON options public in a standard way.
	 *
	 * @param[in] parameters Sets the parameter as a JSON string in the specified format.
	 *
	 * @return
	 * - = 0: Success
	 * - < 0: Failure
	 */
	virtual int	set_parameters(const char*parameters) = 0;
	/**
	 * Local user joins channel.
	 *
	 * @note Users in the same channel with the same App ID can send data to each other.
	 *       You can join more than one channel at the same time. All channels that
	 *       you join will receive the audio/video data stream that you send unless
	 *       you stop sending the audio/video data stream in a specific channel.
	 *
	 * @param[in] uid             Local user ID
	 *                            If 'uid' is set as NULL, SDK will return error.
	 * @param[in] channel   Channel name
	 *                      Length should be less than 64 bytes
	 *                      Supported character scopes are:
	 *                      - The 26 lowercase English letters: a to z
	 *                      - The 26 uppercase English letters: A to Z
	 *                      - The 10 numbers: 0 to 9
	 *                      - The space
	 *                      - "!", "#", "$", "%", "&", "(", ")", "+", "-", ":", ";", "<",
	 *                        "=", ".", ">", "?", "@", "[", "]", "^", "_", " {", "}", "|",
	 *                        "~", ","
	 *
	 * @param[in] token_ptr Token buffer generated by the server
	 *                      - if token authorization is enabled on developer website, it should be set correctly
	 *                      - else token can be set as `NULL`
	 * @param[in] token_len Token buffer len (bytes), Range is [32, 512]
	 *                      If token is set NULL, token_len should be set 0
	 *
	 * @return
	 * - = 0: Success
	 * - < 0: Failure
	 */
	virtual int join_channel(const char *channel, const void *token, size_t len) = 0;
	/**
	 * Renew token for specific channel OR all channels.
	 *
	 * @note Token should be renewed when valid duration reached expiration.
	 *
	 * @param[in] channel   Channel name. For all channels, set `channel` as NULL
	 * @param[in] token_ptr Token buffer
	 * @param[in] token_len Token buffer length (bytes). Range is [32, 512]
	 *
	 * @return
	 * - = 0: Success
	 * - < 0: Failure
	 */
	virtual int renew_token(const char *channel, const void *token, size_t len) = 0;
	/**
	 * Provides technical preview functionalities or special customizations by configuring the SDK with JSON options.
	 *
	 * The JSON options are not public by default. AR is working on making commonly used JSON options public in a standard way.
	 *
	 * @param[in] channel   Channel name. For all channels, set `channel` as NULL
	 * @param[in] parameters Sets the parameter as a JSON string in the specified format.
	 *
	 * @return
	 * - = 0: Success
	 * - < 0: Failure
	 */
	virtual int	set_chan_parameters(const char *channel, const char*parameters) = 0;
	/**
	 * Decide whether to enable/disable sending local audio data to specific channel OR all channels.
	 *
	 * @param[in] channel   Channel name
	 *                      - if `channel` is set NULL, it means all channels
	 *                      - else it means specific channel
	 * @param[in] mute      Toggle sending local audio
	 *                      - 0:        enable (default)
	 *                      - non-ZERO: disable
	 * @return
	 * - = 0: Success
	 * - < 0: Failure
	 */
	virtual int mute_local_audio(const char *channel, int mute) = 0;
	/**
	 * Decide whether to enable/disable receiving remote audio data from specific channel OR all channels.
	 *
	 * @param[in] channel       Channel name
	 *                          - NULL for all channels
	 *                          - non-NULL for specific channel
	 * @param[in] remote_uid    Remote user ID
	 *                          - if `remote_uid` is set 0, it's for all users
	 *                          - else it's for specific user
	 * @param[in] mute          Toggle receiving remote audio
	 *                          - 0:        enable (default)
	 *                          - non-ZERO: disable
	 *
	 * @return
	 * - = 0: Success
	 * - < 0: Failure
	 */
	virtual int mute_remote_audio(const char *channel, const char * remote_uid, int mute) = 0;
	/**
	 * Decide whether to enable/disable sending local video data to specific channel OR all channels.
	 *
	 * @param[in] channel   Channel name
	 *                      - if `channel` is set NULL, it means all channels
	 *                      - else it means specific channel
	 * @param[in] mute      Toggle sending local video
	 *                      - 0:        enable (default)
	 *                      - non-ZERO: disable
	 *
	 * @return
	 * - = 0: Success
	 * - < 0: Failure
	 */
	virtual int mute_local_video(const char *channel, int mute) = 0;
	/**
	 * Decide whether to enable/disable receiving remote video data from specific channel OR all channels.
	 *
	 * @param[in] channel       Channel name
	 *                          - NULL for all channels
	 *                          - non-NULL for specific channel
	 * @param[in] remote_uid    Remote user ID
	 *                          - if `remote_uid` is set 0, it's for all users
	 *                          - else it's for specific user
	 * @param[in] mute          Toggle receiving remote audio
	 *                          - 0:        enable (default)
	 *                          - non-ZERO: disable
	 *
	 * @return
	 * - = 0: Success
	 * - < 0: Failure
	 */
	virtual int mute_remote_video(const char *channel, const char * remote_uid, int mute) = 0;
	/**
	 * Request remote user to generate a keyframe for all video streams OR specific video stream.
	 *
	 * @param[in] channel      Channel name
	 *                         - NULL for all channels
	 *                         - non-NULL for specific channel
	 * @param[in] remote_uid   Remote user ID
	 *                         - if `remote_uid` is set 0, it's for all users
	 *                         - else it's for specific user
	 * @param[in] stream_id    Stream ID
	 *                         - if `stream_id` is set 0, it's for all video streams
	 *                         - else it's for specific video stream
	 *
	 * @return
	 * - = 0: Success
	 * - < 0: Failure
	 */
	virtual int request_video_key_frame(const char *channel, const char * remote_uid, uint8_t stream_id) = 0;
	/**
	 * Send an audio frame to all channels OR specific channel.
	 *
	 * All remote users in this channel will receive the audio frame.
	 *
	 * @note All channels that you joined will receive the audio frame that you send
	 *       unless you stop sending the local audio to a specific channel.
	 *
	 * @param[in] channel   Channel name
	 *                      - NULL for all channels
	 *                      - non-NULL for specific channel
	 * @param[in] data_ptr  Audio frame buffer
	 * @param[in] data_len  Audio frame buffer length (bytes)
	 * @param[in] info_ptr  Audio frame info, see #audio_frame_info_t
	 *
	 * @return
	 * - = 0: Success
	 * - < 0: Failure
	 */
	virtual int send_audio_data(const char *channel, const void *data, size_t data_len, audio_frame_info_t *info_ptr) = 0;
	/**
	 * Send a video frame to all channels OR specific channel.
	 *
	 * All remote users in the channel will receive the video frame.
	 *
	 * @note All channels that you join will receive the video frame that you send
	 *       unless you stop sending the local video to a specific channel.
	 *
	 * @param[in] channel   Channel name
	 *                      - NULL     for all channels
	 *                      - non-NULL for specific channel
	 * @param[in] stream_id Stream ID
	 * @param[in] data_ptr  Video frame buffer
	 * @param[in] data_len  Video frame buffer length (bytes)
	 * @param[in] info_ptr  Video frame info
	 *
	 * @return
	 * - = 0: Success
	 * - < 0: Failure
	 */
	virtual int send_video_data(const char *channel, uint8_t stream_id, const void *data, size_t data_len, video_frame_info_t *info_ptr) = 0;
	/**
	 * Allow Local user leaves channel.
	 *
	 * @note Local user should leave channel when data transmission is stopped
	 *
	 * @param[in] channel   Channel name
	 *                      - NULL for all channels
	 *                      - non-NULL for specific channel
	 *
	 * @return
	 * - = 0: Success
	 * - < 0: Failure
	 */
	virtual int leave_channel(const char *channel) = 0;
	/**
	 * Release all resource allocated by AR ARTS SDK
	 *
	 * @return
	 * - = 0: Success
	 * - < 0: Failure
	 */
	virtual int fini() = 0;

protected:
	IArLiteApi(void) : arlite_event_(NULL) {};

	virtual ~IArLiteApi(void) {};

	IArLiteApiEvent*	arlite_event_;
};

__ar_api__ IArLiteApi* createArLiteApi();


#endif	// __I_AR_LITE_API_H__
