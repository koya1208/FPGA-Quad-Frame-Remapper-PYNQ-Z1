// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2025.1 (64-bit)
// Tool Version Limit: 2025.05
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// Copyright 2022-2025 Advanced Micro Devices, Inc. All Rights Reserved.
// 
// ==============================================================
/***************************** Include Files *********************************/
#include "xquad_frame_remapper.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XQuad_frame_remapper_CfgInitialize(XQuad_frame_remapper *InstancePtr, XQuad_frame_remapper_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Control_BaseAddress = ConfigPtr->Control_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XQuad_frame_remapper_Start(XQuad_frame_remapper *InstancePtr) {
    u32 Data;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XQuad_frame_remapper_ReadReg(InstancePtr->Control_BaseAddress, XQUAD_FRAME_REMAPPER_CONTROL_ADDR_AP_CTRL) & 0x80;
    XQuad_frame_remapper_WriteReg(InstancePtr->Control_BaseAddress, XQUAD_FRAME_REMAPPER_CONTROL_ADDR_AP_CTRL, Data | 0x01);
}

u32 XQuad_frame_remapper_IsDone(XQuad_frame_remapper *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XQuad_frame_remapper_ReadReg(InstancePtr->Control_BaseAddress, XQUAD_FRAME_REMAPPER_CONTROL_ADDR_AP_CTRL);
    return (Data >> 1) & 0x1;
}

u32 XQuad_frame_remapper_IsIdle(XQuad_frame_remapper *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XQuad_frame_remapper_ReadReg(InstancePtr->Control_BaseAddress, XQUAD_FRAME_REMAPPER_CONTROL_ADDR_AP_CTRL);
    return (Data >> 2) & 0x1;
}

u32 XQuad_frame_remapper_IsReady(XQuad_frame_remapper *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XQuad_frame_remapper_ReadReg(InstancePtr->Control_BaseAddress, XQUAD_FRAME_REMAPPER_CONTROL_ADDR_AP_CTRL);
    // check ap_start to see if the pcore is ready for next input
    return !(Data & 0x1);
}

void XQuad_frame_remapper_EnableAutoRestart(XQuad_frame_remapper *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XQuad_frame_remapper_WriteReg(InstancePtr->Control_BaseAddress, XQUAD_FRAME_REMAPPER_CONTROL_ADDR_AP_CTRL, 0x80);
}

void XQuad_frame_remapper_DisableAutoRestart(XQuad_frame_remapper *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XQuad_frame_remapper_WriteReg(InstancePtr->Control_BaseAddress, XQUAD_FRAME_REMAPPER_CONTROL_ADDR_AP_CTRL, 0);
}

void XQuad_frame_remapper_Set_src(XQuad_frame_remapper *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XQuad_frame_remapper_WriteReg(InstancePtr->Control_BaseAddress, XQUAD_FRAME_REMAPPER_CONTROL_ADDR_SRC_DATA, (u32)(Data));
    XQuad_frame_remapper_WriteReg(InstancePtr->Control_BaseAddress, XQUAD_FRAME_REMAPPER_CONTROL_ADDR_SRC_DATA + 4, (u32)(Data >> 32));
}

u64 XQuad_frame_remapper_Get_src(XQuad_frame_remapper *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XQuad_frame_remapper_ReadReg(InstancePtr->Control_BaseAddress, XQUAD_FRAME_REMAPPER_CONTROL_ADDR_SRC_DATA);
    Data += (u64)XQuad_frame_remapper_ReadReg(InstancePtr->Control_BaseAddress, XQUAD_FRAME_REMAPPER_CONTROL_ADDR_SRC_DATA + 4) << 32;
    return Data;
}

void XQuad_frame_remapper_Set_dst(XQuad_frame_remapper *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XQuad_frame_remapper_WriteReg(InstancePtr->Control_BaseAddress, XQUAD_FRAME_REMAPPER_CONTROL_ADDR_DST_DATA, (u32)(Data));
    XQuad_frame_remapper_WriteReg(InstancePtr->Control_BaseAddress, XQUAD_FRAME_REMAPPER_CONTROL_ADDR_DST_DATA + 4, (u32)(Data >> 32));
}

u64 XQuad_frame_remapper_Get_dst(XQuad_frame_remapper *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XQuad_frame_remapper_ReadReg(InstancePtr->Control_BaseAddress, XQUAD_FRAME_REMAPPER_CONTROL_ADDR_DST_DATA);
    Data += (u64)XQuad_frame_remapper_ReadReg(InstancePtr->Control_BaseAddress, XQUAD_FRAME_REMAPPER_CONTROL_ADDR_DST_DATA + 4) << 32;
    return Data;
}

void XQuad_frame_remapper_Set_size_in_16bytes(XQuad_frame_remapper *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XQuad_frame_remapper_WriteReg(InstancePtr->Control_BaseAddress, XQUAD_FRAME_REMAPPER_CONTROL_ADDR_SIZE_IN_16BYTES_DATA, Data);
}

u32 XQuad_frame_remapper_Get_size_in_16bytes(XQuad_frame_remapper *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XQuad_frame_remapper_ReadReg(InstancePtr->Control_BaseAddress, XQUAD_FRAME_REMAPPER_CONTROL_ADDR_SIZE_IN_16BYTES_DATA);
    return Data;
}

void XQuad_frame_remapper_InterruptGlobalEnable(XQuad_frame_remapper *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XQuad_frame_remapper_WriteReg(InstancePtr->Control_BaseAddress, XQUAD_FRAME_REMAPPER_CONTROL_ADDR_GIE, 1);
}

void XQuad_frame_remapper_InterruptGlobalDisable(XQuad_frame_remapper *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XQuad_frame_remapper_WriteReg(InstancePtr->Control_BaseAddress, XQUAD_FRAME_REMAPPER_CONTROL_ADDR_GIE, 0);
}

void XQuad_frame_remapper_InterruptEnable(XQuad_frame_remapper *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XQuad_frame_remapper_ReadReg(InstancePtr->Control_BaseAddress, XQUAD_FRAME_REMAPPER_CONTROL_ADDR_IER);
    XQuad_frame_remapper_WriteReg(InstancePtr->Control_BaseAddress, XQUAD_FRAME_REMAPPER_CONTROL_ADDR_IER, Register | Mask);
}

void XQuad_frame_remapper_InterruptDisable(XQuad_frame_remapper *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XQuad_frame_remapper_ReadReg(InstancePtr->Control_BaseAddress, XQUAD_FRAME_REMAPPER_CONTROL_ADDR_IER);
    XQuad_frame_remapper_WriteReg(InstancePtr->Control_BaseAddress, XQUAD_FRAME_REMAPPER_CONTROL_ADDR_IER, Register & (~Mask));
}

void XQuad_frame_remapper_InterruptClear(XQuad_frame_remapper *InstancePtr, u32 Mask) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XQuad_frame_remapper_WriteReg(InstancePtr->Control_BaseAddress, XQUAD_FRAME_REMAPPER_CONTROL_ADDR_ISR, Mask);
}

u32 XQuad_frame_remapper_InterruptGetEnabled(XQuad_frame_remapper *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XQuad_frame_remapper_ReadReg(InstancePtr->Control_BaseAddress, XQUAD_FRAME_REMAPPER_CONTROL_ADDR_IER);
}

u32 XQuad_frame_remapper_InterruptGetStatus(XQuad_frame_remapper *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XQuad_frame_remapper_ReadReg(InstancePtr->Control_BaseAddress, XQUAD_FRAME_REMAPPER_CONTROL_ADDR_ISR);
}

