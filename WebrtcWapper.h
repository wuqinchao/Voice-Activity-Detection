#pragma once
#include <Windows.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

int WebrtcDetection(int sampleRate, byte* samples, int frameLength, int mode);

#ifdef __cplusplus
}
#endif