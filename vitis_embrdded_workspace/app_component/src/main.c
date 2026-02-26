#include <stdio.h>
#include "xil_printf.h"
#include "sleep.h"
#include "xparameters.h"
#include "ddynclk.h"
#include "xvtc.h"
#include "xaxivdma.h"
#include "xil_cache.h"
#include "xquad_frame_remapper.h"

// 定数・設定定義
#define VIDEO_W     1920 //解像度
#define VIDEO_H     1080 //解像度
#define BYTES_PP    3 //1画素のデータ量（3byte）
#define STRIDE      (VIDEO_W * BYTES_PP) //1行分のデータ量
#define TOTAL_BYTES (VIDEO_H * STRIDE) //1フレームのデータ量

// DDRメモリ上のバッファアドレス
#define RX_ADDR_BASE 0x10000000U
#define TX_ADDR_BASE 0x11000000U


static int DynClk_InitAndSetRate(DDynClk *pDyn, u32 baseaddr, u32 freq) {
    DDynClk_Config Cfg = { .DeviceId = 0, .BaseAddress = baseaddr };
    if (DDynClk_CfgInitialize(pDyn, &Cfg, baseaddr) != XST_SUCCESS) return XST_FAILURE;
    DDynClk_SetRate(pDyn, freq);
    while (DDynClk_ReadReg(baseaddr, DDYNCLK_STATUS) == 0) usleep(100000);
    return XST_SUCCESS;
}

static int VtcOut_Start1080p(u32 baseaddr) {
    XVtc Vtc;
    XVtc_Config Config;
    Config.BaseAddress = baseaddr; 
    XVtc_CfgInitialize(&Vtc, &Config, baseaddr);

    XVtc_Timing T = {
        .HActiveVideo = 1920, .HFrontPorch = 88, .HSyncWidth = 44, .HBackPorch = 148, .HSyncPolarity = 1,
        .VActiveVideo = 1080, .V0FrontPorch = 4, .V0SyncWidth = 5, .V0BackPorch = 36, .VSyncPolarity = 1, .Interlaced = 0
    };
    XVtc_SourceSelect S;
    memset(&S, 1, sizeof(S));

    XVtc_Disable(&Vtc);
    XVtc_SetGeneratorTiming(&Vtc, &T);
    XVtc_SetSource(&Vtc, &S);
    XVtc_EnableGenerator(&Vtc);
    XVtc_Enable(&Vtc);
    return XST_SUCCESS;
}

// メイン関数
int main(void)
{
    xil_printf("\r\n=== Image Quad Scale System (4-Screen Video Wall) ===\r\n");

    // DynclkとVTC初期化
    DDynClk DynClk;
    if (DynClk_InitAndSetRate(&DynClk, XPAR_AXI_DYNCLK_0_BASEADDR, 148500000) != XST_SUCCESS) {
        xil_printf("Error: Clock Init failed\r\n");
        return XST_FAILURE;
    }
    
    if (VtcOut_Start1080p(XPAR_V_TC_OUT_BASEADDR) != XST_SUCCESS) {
        xil_printf("Error: VTC Init failed\r\n");
        return XST_FAILURE;
    }

    // Step 2: Image Quad Scale IPの設定
    XQuad_frame_remapper HlsIp;
    XQuad_frame_remapper_Config *IpCfg = NULL;
    XQuad_frame_remapper_Config IpConfigManual;

    UINTPTR IpBaseAddr;
    #ifdef XPAR_XQUAD_FRAME_REMAPPER_0_BASEADDR
        IpBaseAddr = XPAR_XQUAD_FRAME_REMAPPER_0_BASEADDR;
    #elif defined(XPAR_QUAD_FRAME_REMAPPER_0_S_AXI_CONTROL_BASEADDR)
        IpBaseAddr = XPAR_QUAD_FRAME_REMAPPER_0_S_AXI_CONTROL_BASEADDR;
    #else
        IpBaseAddr = 0x40000000; 
        xil_printf("Warning: IP BaseAddr macro not found. Using default: 0x%08x\r\n", IpBaseAddr);
    #endif

    IpConfigManual.Control_BaseAddress = IpBaseAddr;
    IpCfg = &IpConfigManual;

    // 初期化実行
    if (XQuad_frame_remapper_CfgInitialize(&HlsIp, IpCfg) != XST_SUCCESS) {
         xil_printf("Error: Quad Scale IP Init failed\r\n");
         return XST_FAILURE;
    }

    // src: VDMAが書き込んだ場所 (RX_ADDR)
    // dst: 加工後の画像を書き込む場所 (TX_ADDR)
    XQuad_frame_remapper_Set_src(&HlsIp, (u64)RX_ADDR_BASE);
    XQuad_frame_remapper_Set_dst(&HlsIp, (u64)TX_ADDR_BASE);
    
    // サイズ設定: バイト数ではなく「16バイト単位のデータ数」
    // (1920 * 1080 * 3) / 16
    XQuad_frame_remapper_Set_size_in_16bytes(&HlsIp, TOTAL_BYTES / 16);
    XQuad_frame_remapper_EnableAutoRestart(&HlsIp);
    XQuad_frame_remapper_Start(&HlsIp);
    
    xil_printf("Image Quad Scale IP Started.\r\n");

    // VDMAの設定
    XAxiVdma Vdma;
    XAxiVdma_Config *VdmaCfg = XAxiVdma_LookupConfig(XPAR_AXI_VDMA_0_BASEADDR);
    if (!VdmaCfg) {
        xil_printf("Error: VDMA Config not found\r\n");
        return XST_FAILURE;
    }
    XAxiVdma_CfgInitialize(&Vdma, VdmaCfg, VdmaCfg->BaseAddress);
    
    // リセット
    XAxiVdma_Reset(&Vdma, XAXIVDMA_WRITE);
    XAxiVdma_Reset(&Vdma, XAXIVDMA_READ);
    while (XAxiVdma_ResetNotDone(&Vdma, XAXIVDMA_WRITE));
    while (XAxiVdma_ResetNotDone(&Vdma, XAXIVDMA_READ));

    // メモリ初期化
    // 処理が成功しているか分かりやすくするため、初期値をグレー(0x80)にしておく
    // 成功すれば、グレーの背景の上に「田の字」に配置された映像と「黒帯」が表示される
    memset((void*)RX_ADDR_BASE, 0x80, TOTAL_BYTES);
    memset((void*)TX_ADDR_BASE, 0x80, TOTAL_BYTES);
    Xil_DCacheFlushRange(RX_ADDR_BASE, TOTAL_BYTES);
    Xil_DCacheFlushRange(TX_ADDR_BASE, TOTAL_BYTES);

    // VDMA設定
    XAxiVdma_DmaSetup CfgCommon = {
        .VertSizeInput = VIDEO_H,
        .HoriSizeInput = STRIDE,
        .Stride = STRIDE,
        .EnableCircularBuf = 1 
    };
    XAxiVdma_DmaConfig(&Vdma, XAXIVDMA_WRITE, &CfgCommon);
    XAxiVdma_DmaConfig(&Vdma, XAXIVDMA_READ,  &CfgCommon);

    UINTPTR RxAddr[3] = {RX_ADDR_BASE, RX_ADDR_BASE, RX_ADDR_BASE};
    UINTPTR TxAddr[3] = {TX_ADDR_BASE, TX_ADDR_BASE, TX_ADDR_BASE};
    
    XAxiVdma_DmaSetBufferAddr(&Vdma, XAXIVDMA_WRITE, RxAddr);
    XAxiVdma_DmaSetBufferAddr(&Vdma, XAXIVDMA_READ,  TxAddr);

    XAxiVdma_DmaStart(&Vdma, XAXIVDMA_WRITE);
    XAxiVdma_DmaStart(&Vdma, XAXIVDMA_READ);

    xil_printf("VDMA Started. System Running.\r\n");

    while (1) {
        sleep(1); 
    }
}