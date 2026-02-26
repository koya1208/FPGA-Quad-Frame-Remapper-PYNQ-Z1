// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2025.1 (64-bit)
// Tool Version Limit: 2025.05
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// Copyright 2022-2025 Advanced Micro Devices, Inc. All Rights Reserved.
// 
// ==============================================================
#ifndef XQUAD_FRAME_REMAPPER_H
#define XQUAD_FRAME_REMAPPER_H

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/
#ifndef __linux__
#include "xil_types.h"
#include "xil_assert.h"
#include "xstatus.h"
#include "xil_io.h"
#else
#include <stdint.h>
#include <assert.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stddef.h>
#endif
#include "xquad_frame_remapper_hw.h"

/**************************** Type Definitions ******************************/
#ifdef __linux__
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
#else
typedef struct {
#ifdef SDT
    char *Name;
#else
    u16 DeviceId;
#endif
    u64 Control_BaseAddress;
} XQuad_frame_remapper_Config;
#endif

typedef struct {
    u64 Control_BaseAddress;
    u32 IsReady;
} XQuad_frame_remapper;

typedef u32 word_type;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XQuad_frame_remapper_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XQuad_frame_remapper_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XQuad_frame_remapper_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XQuad_frame_remapper_ReadReg(BaseAddress, RegOffset) \
    *(volatile u32*)((BaseAddress) + (RegOffset))

#define Xil_AssertVoid(expr)    assert(expr)
#define Xil_AssertNonvoid(expr) assert(expr)

#define XST_SUCCESS             0
#define XST_DEVICE_NOT_FOUND    2
#define XST_OPEN_DEVICE_FAILED  3
#define XIL_COMPONENT_IS_READY  1
#endif

/************************** Function Prototypes *****************************/
#ifndef __linux__
#ifdef SDT
int XQuad_frame_remapper_Initialize(XQuad_frame_remapper *InstancePtr, UINTPTR BaseAddress);
XQuad_frame_remapper_Config* XQuad_frame_remapper_LookupConfig(UINTPTR BaseAddress);
#else
int XQuad_frame_remapper_Initialize(XQuad_frame_remapper *InstancePtr, u16 DeviceId);
XQuad_frame_remapper_Config* XQuad_frame_remapper_LookupConfig(u16 DeviceId);
#endif
int XQuad_frame_remapper_CfgInitialize(XQuad_frame_remapper *InstancePtr, XQuad_frame_remapper_Config *ConfigPtr);
#else
int XQuad_frame_remapper_Initialize(XQuad_frame_remapper *InstancePtr, const char* InstanceName);
int XQuad_frame_remapper_Release(XQuad_frame_remapper *InstancePtr);
#endif

void XQuad_frame_remapper_Start(XQuad_frame_remapper *InstancePtr);
u32 XQuad_frame_remapper_IsDone(XQuad_frame_remapper *InstancePtr);
u32 XQuad_frame_remapper_IsIdle(XQuad_frame_remapper *InstancePtr);
u32 XQuad_frame_remapper_IsReady(XQuad_frame_remapper *InstancePtr);
void XQuad_frame_remapper_EnableAutoRestart(XQuad_frame_remapper *InstancePtr);
void XQuad_frame_remapper_DisableAutoRestart(XQuad_frame_remapper *InstancePtr);

void XQuad_frame_remapper_Set_src(XQuad_frame_remapper *InstancePtr, u64 Data);
u64 XQuad_frame_remapper_Get_src(XQuad_frame_remapper *InstancePtr);
void XQuad_frame_remapper_Set_dst(XQuad_frame_remapper *InstancePtr, u64 Data);
u64 XQuad_frame_remapper_Get_dst(XQuad_frame_remapper *InstancePtr);
void XQuad_frame_remapper_Set_size_in_16bytes(XQuad_frame_remapper *InstancePtr, u32 Data);
u32 XQuad_frame_remapper_Get_size_in_16bytes(XQuad_frame_remapper *InstancePtr);

void XQuad_frame_remapper_InterruptGlobalEnable(XQuad_frame_remapper *InstancePtr);
void XQuad_frame_remapper_InterruptGlobalDisable(XQuad_frame_remapper *InstancePtr);
void XQuad_frame_remapper_InterruptEnable(XQuad_frame_remapper *InstancePtr, u32 Mask);
void XQuad_frame_remapper_InterruptDisable(XQuad_frame_remapper *InstancePtr, u32 Mask);
void XQuad_frame_remapper_InterruptClear(XQuad_frame_remapper *InstancePtr, u32 Mask);
u32 XQuad_frame_remapper_InterruptGetEnabled(XQuad_frame_remapper *InstancePtr);
u32 XQuad_frame_remapper_InterruptGetStatus(XQuad_frame_remapper *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif
