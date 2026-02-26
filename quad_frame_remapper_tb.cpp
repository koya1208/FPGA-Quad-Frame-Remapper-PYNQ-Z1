#include <iostream>
#include <vector>
#include <ap_int.h>

extern "C" void quad_frame_remapper(
    ap_uint<128>* src, 
    ap_uint<128>* dst, 
    int size_in_16bytes
);

const int WIDTH = 1920;
const int HEIGHT = 1080;
const int STRIDE = WIDTH * 3;
const int TOTAL_BYTES = HEIGHT * STRIDE;
const int TOTAL_WORDS = TOTAL_BYTES / 16;

int main() {
    std::cout << "--- Starting C Simulation for image_quad_scale ---" << std::endl;

    std::vector<ap_uint<128>> src(TOTAL_WORDS);
    std::vector<ap_uint<128>> dst(TOTAL_WORDS);

    // 1. 入力データ作成: 全面真っ白(0xFF)にする
    // どこを切り取っても「白」になるように
    memset(src.data(), 0xFF, TOTAL_BYTES);
    
    // 出力バッファは0x55(グレー)で埋めておく(書き込み確認用)
    memset(dst.data(), 0x55, TOTAL_BYTES);

    // 2. IP実行
    quad_frame_remapper(src.data(), dst.data(), TOTAL_WORDS);

    // 3. 検証
    unsigned char* p_dst = (unsigned char*)dst.data();

    // Check 1: 左上のカド (黒帯のはず)
    // 座標(10, 10)
    int idx_black = (10 * WIDTH + 10) * 3;
    if (p_dst[idx_black] != 0x00) {
        std::cout << "Error: Top-Left margin is not Black!" << std::endl;
        return 1;
    }

    // Check 2: 左上の映像エリア中心 (白のはず)
    // 座標(960/2, 540/2) = (480, 270)
    int idx_white = (270 * WIDTH + 480) * 3;
    if (p_dst[idx_white] != 0xFF) {
        std::cout << "Error: Top-Left video area is not White!" << std::endl;
        return 1;
    }

    std::cout << "--- C Simulation PASSED! ---" << std::endl;
    return 0;
}