// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2025.1 (64-bit)
// Tool Version Limit: 2025.05
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// Copyright 2022-2025 Advanced Micro Devices, Inc. All Rights Reserved.
// 
// ==============================================================
#ifndef __linux__

#include "xstatus.h"
#ifdef SDT
#include "xparameters.h"
#endif
#include "xquad_frame_remapper.h"

extern XQuad_frame_remapper_Config XQuad_frame_remapper_ConfigTable[];

#ifdef SDT
XQuad_frame_remapper_Config *XQuad_frame_remapper_LookupConfig(UINTPTR BaseAddress) {
	XQuad_frame_remapper_Config *ConfigPtr = NULL;

	int Index;

	for (Index = (u32)0x0; XQuad_frame_remapper_ConfigTable[Index].Name != NULL; Index++) {
		if (!BaseAddress || XQuad_frame_remapper_ConfigTable[Index].Control_BaseAddress == BaseAddress) {
			ConfigPtr = &XQuad_frame_remapper_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XQuad_frame_remapper_Initialize(XQuad_frame_remapper *InstancePtr, UINTPTR BaseAddress) {
	XQuad_frame_remapper_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XQuad_frame_remapper_LookupConfig(BaseAddress);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XQuad_frame_remapper_CfgInitialize(InstancePtr, ConfigPtr);
}
#else
XQuad_frame_remapper_Config *XQuad_frame_remapper_LookupConfig(u16 DeviceId) {
	XQuad_frame_remapper_Config *ConfigPtr = NULL;

	int Index;

	for (Index = 0; Index < XPAR_XQUAD_FRAME_REMAPPER_NUM_INSTANCES; Index++) {
		if (XQuad_frame_remapper_ConfigTable[Index].DeviceId == DeviceId) {
			ConfigPtr = &XQuad_frame_remapper_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XQuad_frame_remapper_Initialize(XQuad_frame_remapper *InstancePtr, u16 DeviceId) {
	XQuad_frame_remapper_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XQuad_frame_remapper_LookupConfig(DeviceId);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XQuad_frame_remapper_CfgInitialize(InstancePtr, ConfigPtr);
}
#endif

#endif

