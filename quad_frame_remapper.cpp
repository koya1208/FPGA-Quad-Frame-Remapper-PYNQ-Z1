/**
 * プロジェクト名 : Quad Frame Remapper (HLS版)
 * ファイル名     : image_quad_scale.cpp
 *
 * 概要：
 *   1920x1080 RGB画像を4分割し、
 *   各象限を0.8倍に縮小して中央配置するIP。
 *   余白部分は黒(0x00)で埋める。
 * 
 * 出力イメージ：
 *   下記の図は外部ディスプレイへ映像を出力した際のイメージ図を表す。
 *  ---------------------------------------- 
 * ¦  ----------------    ----------------  ¦
 * ¦ ¦                ¦  ¦                ¦ ¦
 * ¦ ¦                ¦  ¦                ¦ ¦
 * ¦ ¦                ¦  ¦                ¦ ¦
 * ¦  ----------------    ----------------  ¦
 * ¦  ----------------    ----------------  ¦
 * ¦ ¦                ¦  ¦                ¦ ¦
 * ¦ ¦                ¦  ¦                ¦ ¦
 * ¦ ¦                ¦  ¦                ¦ ¦
 * ¦  ----------------    ----------------  ¦
 *  ----------------------------------------
 * 
 * 動作概要：
 *   ・DDRメモリから1ラインずつ読み出す
 *   ・Nearest Neighbor法で縮小
 *   ・中央に配置
 *   ・DDRへ書き戻す
 *
 * インターフェース：
 *   ・AXI4 Master (m_axi) : DDRアクセス用
 *   ・AXI4-Lite           : 制御用
 */

#include <ap_int.h>
#include <string.h>

extern "C" {

/**
 * HLSトップ関数
 *
 * @param src  入力フレームバッファ（DDR）
 * @param dst  出力フレームバッファ（DDR）
 * @param size_in_16bytes フレーム全体サイズ（16byte単位）
 */
void quad_frame_remapper(
    ap_uint<128>* src, 
    ap_uint<128>* dst, 
    int size_in_16bytes
) {
// 1:AXIインターフェース設定
#pragma HLS INTERFACE m_axi port=src offset=slave bundle=gmem0 depth=388800 max_read_burst_length=256 num_read_outstanding=4
#pragma HLS INTERFACE m_axi port=dst offset=slave bundle=gmem1 depth=388800 max_write_burst_length=32 num_write_outstanding=2

#pragma HLS INTERFACE s_axilite port=src    bundle=control
#pragma HLS INTERFACE s_axilite port=dst    bundle=control
#pragma HLS INTERFACE s_axilite port=size_in_16bytes   bundle=control
#pragma HLS INTERFACE s_axilite port=return bundle=control

    // 2:パラメータ設定
    const int WIDTH = 1920;
    const int HEIGHT = 1080;
    const int BYTES_PP = 3; // RGB 24bit
    const int STRIDE = WIDTH * BYTES_PP; // 1行のバイト数 (5760 bytes)
    const int WIDTH_WORDS = STRIDE / 16; // 360 words

    // 象限の設定 (画面の1/4)
    const int Q_W = 960; // 象限の幅
    const int Q_H = 540; // 象限の高さ

    // 縮小設定 (Scale = 0.8)
    // 960 * 0.8 = 768 px
    // 540 * 0.8 = 432 px
    const int SCALED_W = 768;
    const int SCALED_H = 432;

    // 余白（マージン）の計算: (象限サイズ - 縮小サイズ) / 2
    const int MARGIN_X = (Q_W - SCALED_W) / 2; // 96 px
    const int MARGIN_Y = (Q_H - SCALED_H) / 2; // 54 px

    // ラインバッファ (入力用と出力用)
    ap_uint<128> line_buf_in[360];
    ap_uint<128> line_buf_out[360];

    unsigned char* p_in  = (unsigned char*)line_buf_in;
    unsigned char* p_out = (unsigned char*)line_buf_out;

    // 3:処理内容
    for (int y = 0; y < HEIGHT; y++) {
        
        // A:座標判定
        // 今のY座標は「上半分」か「下半分」か？
        bool is_bottom = (y >= Q_H);
        
        // 象限内でのローカルY座標 (0 ~ 539)
        int local_y = is_bottom ? (y - Q_H) : y;

        // B:黒帯判定 (Y方向)
        // 映像エリア外なら、真っ黒にして書き込んで終了
        if (local_y < MARGIN_Y || local_y >= (MARGIN_Y + SCALED_H)) {
            // バッファを0(黒)で埋める
            memset(p_out, 0, STRIDE);
            
            // DDRへ書き込み
            memcpy((ap_uint<128>*)(dst + y * WIDTH_WORDS), 
                   line_buf_out, 
                   WIDTH_WORDS * sizeof(ap_uint<128>));
            continue; // 次の行へ
        }

        // C:縮小配置
        
        // 1. 入力画像の「どの行」を読むべきか計算 (Nearest Neighbor法)
        int img_y = local_y - MARGIN_Y;
        int src_local_y = (img_y * 10) / 8; // 0.8で割る = 1.25倍する
        
        // 上下象限に応じた入力Y座標
        int src_y = is_bottom ? (src_local_y + Q_H) : src_local_y;

        // 2. DDRから1行読み込み
        memcpy(line_buf_in, 
               (const ap_uint<128>*)(src + src_y * WIDTH_WORDS), 
               WIDTH_WORDS * sizeof(ap_uint<128>));

        // 3. 出力バッファの構築 (X方向の処理)
        // まず全体を黒でリセット
        memset(p_out, 0, STRIDE);

        // 左象限の縮小配置
        for (int i = 0; i < SCALED_W; i++) {
            // 縮小元のX座標を計算
            int src_x = (i * 10) / 8; // 0~959
            
            // 出力先のX座標: マージン(96) + i
            int dst_x = MARGIN_X + i;

            // 画素コピー (RGB 3バイト)
            p_out[dst_x * 3 + 0] = p_in[src_x * 3 + 0];
            p_out[dst_x * 3 + 1] = p_in[src_x * 3 + 1];
            p_out[dst_x * 3 + 2] = p_in[src_x * 3 + 2];
        }

        // 右象限の縮小配置
        for (int i = 0; i < SCALED_W; i++) {
            // 縮小元のX座標: 右半分オフセット(960) + 計算値
            int src_x = Q_W + ((i * 10) / 8); // 960 ~ 1919

            // 出力先のX座標: 右半分オフセット(960) + マージン(96) + i
            int dst_x = Q_W + MARGIN_X + i;

            // 画素コピー
            p_out[dst_x * 3 + 0] = p_in[src_x * 3 + 0];
            p_out[dst_x * 3 + 1] = p_in[src_x * 3 + 1];
            p_out[dst_x * 3 + 2] = p_in[src_x * 3 + 2];
        }

        // 4. DDRへ書き込み
        memcpy((ap_uint<128>*)(dst + y * WIDTH_WORDS), 
               line_buf_out, 
               WIDTH_WORDS * sizeof(ap_uint<128>));
    }
}

}