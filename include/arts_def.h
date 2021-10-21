#ifndef __ARTS_DEF_H__
#define __ARTS_DEF_H__

#include <stddef.h>
#include <stdint.h>

#if defined(_MSC_VER)
#if defined(__BUILDING_AR_SDK__)
#define __ar_api__ __declspec(dllexport)
#else
#define __ar_api__ __declspec(dllimport)
#endif
#elif defined(__ANDROID__) || defined(__linux__)
#define __ar_api__ __attribute__((visibility("default")))
#else
#define __ar_api__
#endif

#define AR_TOKEN_MAX_LEN             512
#define AR_CMD_PARAM_MAX_LEN         256
#define AR_CREDENTIAL_MAX_LEN        256
#define AR_CERTIFICATE_MAX_LEN       1024

/** Error code. */
typedef enum {
	/** No error. */
	eERR_OK = 0,

	/** General error */
	eERR_FAILED = 1,

	/**
	 * Network is unavailable
	 */
	eERR_NET_DOWN = 14,

	/**
	 * Request to join channel is rejected.
	 * It occurs when local user is already in channel and try to join the same channel again.
	 */
	eERR_JOIN_CHANNEL_REJECTED = 17,

	/** App ID is invalid. */
	eERR_INVALID_APP_ID = 101,

	/** Channel is invalid. */
	eERR_INVALID_CHANNEL_NAME = 102,

	/**
	 * Server rejected request to look up channel.
	 */
	eERR_LOOKUP_CHANNEL_REJECTED = 105,

	/**
	 * Server rejected request to open channel.
	 */
	eERR_OPEN_CHANNEL_REJECTED = 107,

	/**
	 * Token expired due to reasons belows:
	 * - Authorized Timestamp expired:      The timestamp is represented by the number of
	 *                                      seconds elapsed since 1/1/1970. The user can use
	 *                                      the Token to access the AR service within five
	 *                                      minutes after the Token is generated. If the user
	 *                                      does not access the AR service after five minutes,
	 *                                      this Token will no longer be valid.
	 * - Call Expiration Timestamp expired: The timestamp indicates the exact time when a
	 *                                      user can no longer use the AR service (for example,
	 *                                      when a user is forced to leave an ongoing call).
	 *                                      When the value is set for the Call Expiration Timestamp,
	 *                                      it does not mean that the Token will be expired,
	 *                                      but that the user will be kicked out of the channel.
	 */
	eERR_TOKEN_EXPIRED = 109,

	/**
	 * Token is invalid due to reasons belows:
	 * - If application certificate is enabled on the Dashboard,
	 *   valid token SHOULD be set when invoke.
	 *
	 * - If uid field is mandatory, and users must set the same uid when setting the
	 *   uid parameter when calling `ar_rtc_join_channel`.
	 */
	eERR_INVALID_TOKEN = 110,

	/** Switching roles failed.
	 *  Please try to rejoin the channel.
	 */
	eERR_SET_CLIENT_ROLE_NOT_AUTHORIZED = 119,

	/** Ticket to open channel is invalid */
	eERR_OPEN_CHANNEL_INVALID_TICKET = 121,

	/** Try another server. */
	eERR_OPEN_CHANNEL_TRY_NEXT_VOS = 122,

	/** Client is banned by the server */
	eERR_CLIENT_IS_BANNED_BY_SERVER = 123,
} ar_err_code_e;

/**
 * The definition of the user_offline_reason_e enum.
 */
typedef enum {
	/**
	 * 0: Remote user leaves channel actively
	 */
	eUSER_OFFLINE_QUIT = 0,
	/**
	 * 1: Remote user is dropped due to timeout
	 */
	eUSER_OFFLINE_DROPPED = 1,
} user_offline_reason_e;

/**
 * The definition of the video_codec_e enum.
 */
typedef enum {
	/**
	 * 2: h264
	 */
	eVIDEO_CODEC_H264 = 2,
	/**
	 * 5: mjpg
	 */
	eVIDEO_CODEC_MJPG = 5,
	/**
	 * 6: generic
	 */
	eVIDEO_CODEC_GENERIC = 6,
} video_codec_e;

/**
 * The definition of the video_frame_type_e enum.
 */
typedef enum {
	/**
	 * 1: key frame
	 */
	eVIDEO_FRAME_KEY = 1,
	/*
	 * 4: delta frame, e.g: P-Frame
	 */
	eVIDEO_FRAME_DELTA = 4,
} video_frame_type_e;

/**
 * The definition of the video_frame_rate_e enum.
 */
typedef enum {
	/**
	 * 1: 1 fps.
	 */
	eVIDEO_FRAME_RATE_FPS_1 = 1,
	/**
	 * 7: 7 fps.
	 */
	eVIDEO_FRAME_RATE_FPS_7 = 7,
	/**
	 * 10: 10 fps.
	 */
	eVIDEO_FRAME_RATE_FPS_10 = 10,
	/**
	 * 15: 15 fps.
	 */
	eVIDEO_FRAME_RATE_FPS_15 = 15,
	/**
	 * 24: 24 fps.
	 */
	eVIDEO_FRAME_RATE_FPS_24 = 24,
	/**
	 * 30: 30 fps.
	 */
	eVIDEO_FRAME_RATE_FPS_30 = 30,
	/**
	 * 60: 60 fps. Applies to Windows and macOS only.
	 */
	eVIDEO_FRAME_RATE_FPS_60 = 60,
} video_frame_rate_e;

/**
 * The definition of the video_frame_info_t struct.
 */
typedef struct {
	/**
	 * The video codec: #video_codec_e.
	 */
	video_codec_e  codec;
	/**
	 * The frame type of the encoded video frame: #video_frame_type_e.
	 */
	video_frame_type_e  type;
	/**
	 * The number of video frames per second.
	 * -This value will be used for calculating timestamps of the encoded image.
	 * - If frame_per_sec equals zero, then real timestamp will be used.
	 * - Otherwise, timestamp will be adjusted to the value of frame_per_sec set.
	 */
	video_frame_rate_e frames_per_sec;
} video_frame_info_t;

/**
 * Audio codec type list.
 */
typedef enum {
	/**
	 * 1: OPUS
	 */
	eAUDIO_CODEC_OPUS = 1,
	/**
	 * 3-4: G711
	 */
	eAUDIO_CODEC_G711A = 3,
	eAUDIO_CODEC_G711U = 4,
	/**
	 * 5: G722
	 */
	eAUDIO_CODEC_G722 = 5,
	/**
	 * 8: AACLC
	 */
	eAUDIO_CODEC_AACLC = 8,
	/**
	 * 9: HEAAC
	 */
	eAUDIO_CODEC_HEAAC = 9,
	/**
	 * 253: GENERIC
	 */
	eAUDIO_CODEC_GENERIC = 253,
} audio_codec_e;

/**
 * The definition of the audio_frame_info_t struct.
 */
typedef struct {
	/**
	 * Audio codec type, reference #audio_codec_e.
	 */
	audio_codec_e  codec;
} audio_frame_info_t;

typedef enum {
	eLOG_LEVEL_VERBOSE = 0,
	eLOG_LEVEL_DEBUG = 1,
	eLOG_LEVEL_INFO = 2,
	eLOG_LEVEL_WARN = 3,
	eLOG_LEVEL_ERROR = 4,
	eLOG_LEVEL_FATAL = 5,
	eLOG_LEVEL_NONE = 6
} log_level_e;

#endif	// __ARTS_DEF_H__