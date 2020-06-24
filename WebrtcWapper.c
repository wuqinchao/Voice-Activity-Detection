#include "WebrtcWapper.h"
#include "webrtc/common_audio/vad/include/webrtc_vad.h"

void logdata(byte* samples, int frameLength)
{
	printf("C+ ");
	for (int i = 0; i < frameLength * 2; i++)
	{
		printf("%02X", samples[i]);
	}
	printf("\r\n");
}

VadInst* inst = NULL;

int WebrtcOpen(int mode)
{
	if (!inst) {
		if (WebRtcVad_Create(&inst) == -1)
		{
			return -1;
		}
		if (WebRtcVad_Init(inst) == -1)
		{
			return -2;
		}
		if (WebRtcVad_set_mode(inst, mode) == -1)
		{
			return -3;
		}
		//printf("webrtc opened\r\n");
	}
	return 0;
}

//WEBRTCWAPPER_API int WebrtcDetection(int sampleRate, char* samples, int frameLength)
int WebrtcDetection(int sampleRate, byte* samples, int frameLength, int mode)
{
	//printf("mode %d samplerate %d\r\n", mode, sampleRate);
	//logdata(samples, frameLength);
	int ret = -999;

	WebrtcOpen(mode);

	ret = WebRtcVad_Process(inst, sampleRate, (int16_t*)samples, frameLength);
	if (ret == -1)
	{
		return -4;
	}
	
	//printf("004 mode %d samplerate %d frame_len:%d  return %d\r\n", mode, sampleRate, frameLength, ret);
	return ret;
}

void WebrtcClose()
{
	if (inst)
	{
		WebRtcVad_Free(inst);
		inst = NULL;
		//printf("webrtc closed\r\n");
	}
}