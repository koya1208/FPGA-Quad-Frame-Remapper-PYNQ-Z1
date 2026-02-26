; ModuleID = 'C:/quad_frame_remapper/vitis_hls_workspace/hls_component/hls_component/hls/.autopilot/db/a.g.ld.5.gdce.bc'
source_filename = "llvm-link"
target datalayout = "e-m:e-i64:64-i128:128-i256:256-i512:512-i1024:1024-i2048:2048-i4096:4096-n8:16:32:64-S128-v16:16-v24:32-v32:32-v48:64-v96:128-v192:256-v256:256-v512:512-v1024:1024"
target triple = "fpga64-xilinx-none"

%"struct.ap_uint<128>" = type { %"struct.ap_int_base<128, false>" }
%"struct.ap_int_base<128, false>" = type { %"struct.ssdm_int<128, false>" }
%"struct.ssdm_int<128, false>" = type { i128 }

; Function Attrs: noinline
define void @apatb_quad_frame_remapper_ir(%"struct.ap_uint<128>"* noalias nocapture nonnull readonly "maxi" %src, %"struct.ap_uint<128>"* noalias nocapture nonnull "maxi" %dst, i32 %size_in_16bytes) local_unnamed_addr #0 {
entry:
  %0 = bitcast %"struct.ap_uint<128>"* %src to [388800 x %"struct.ap_uint<128>"]*
  %1 = call i8* @malloc(i64 6220800)
  %src_copy = bitcast i8* %1 to [388800 x i128]*
  %2 = bitcast %"struct.ap_uint<128>"* %dst to [388800 x %"struct.ap_uint<128>"]*
  %3 = call i8* @malloc(i64 6220800)
  %dst_copy = bitcast i8* %3 to [388800 x i128]*
  call fastcc void @copy_in([388800 x %"struct.ap_uint<128>"]* nonnull %0, [388800 x i128]* %src_copy, [388800 x %"struct.ap_uint<128>"]* nonnull %2, [388800 x i128]* %dst_copy)
  call void @apatb_quad_frame_remapper_hw([388800 x i128]* %src_copy, [388800 x i128]* %dst_copy, i32 %size_in_16bytes)
  call void @copy_back([388800 x %"struct.ap_uint<128>"]* %0, [388800 x i128]* %src_copy, [388800 x %"struct.ap_uint<128>"]* %2, [388800 x i128]* %dst_copy)
  call void @free(i8* %1)
  call void @free(i8* %3)
  ret void
}

; Function Attrs: argmemonly noinline norecurse willreturn
define internal fastcc void @copy_in([388800 x %"struct.ap_uint<128>"]* readonly "unpacked"="0", [388800 x i128]* nocapture "unpacked"="1.0", [388800 x %"struct.ap_uint<128>"]* readonly "unpacked"="2", [388800 x i128]* nocapture "unpacked"="3.0") unnamed_addr #1 {
entry:
  call fastcc void @"onebyonecpy_hls.p0a388800struct.ap_uint<128>.12"([388800 x i128]* %1, [388800 x %"struct.ap_uint<128>"]* %0)
  call fastcc void @"onebyonecpy_hls.p0a388800struct.ap_uint<128>.12"([388800 x i128]* %3, [388800 x %"struct.ap_uint<128>"]* %2)
  ret void
}

; Function Attrs: argmemonly noinline norecurse willreturn
define void @"arraycpy_hls.p0a388800struct.ap_uint<128>"([388800 x %"struct.ap_uint<128>"]* %dst, [388800 x %"struct.ap_uint<128>"]* readonly %src, i64 %num) local_unnamed_addr #2 {
entry:
  %0 = icmp eq [388800 x %"struct.ap_uint<128>"]* %src, null
  %1 = icmp eq [388800 x %"struct.ap_uint<128>"]* %dst, null
  %2 = or i1 %1, %0
  br i1 %2, label %ret, label %copy

copy:                                             ; preds = %entry
  %for.loop.cond7 = icmp sgt i64 %num, 0
  br i1 %for.loop.cond7, label %for.loop.lr.ph, label %copy.split

for.loop.lr.ph:                                   ; preds = %copy
  br label %for.loop

for.loop:                                         ; preds = %for.loop, %for.loop.lr.ph
  %for.loop.idx8 = phi i64 [ 0, %for.loop.lr.ph ], [ %for.loop.idx.next, %for.loop ]
  %src.addr.0.0.05 = getelementptr [388800 x %"struct.ap_uint<128>"], [388800 x %"struct.ap_uint<128>"]* %src, i64 0, i64 %for.loop.idx8, i32 0, i32 0, i32 0
  %dst.addr.0.0.06 = getelementptr [388800 x %"struct.ap_uint<128>"], [388800 x %"struct.ap_uint<128>"]* %dst, i64 0, i64 %for.loop.idx8, i32 0, i32 0, i32 0
  %3 = load i128, i128* %src.addr.0.0.05, align 16
  store i128 %3, i128* %dst.addr.0.0.06, align 16
  %for.loop.idx.next = add nuw nsw i64 %for.loop.idx8, 1
  %exitcond = icmp ne i64 %for.loop.idx.next, %num
  br i1 %exitcond, label %for.loop, label %copy.split

copy.split:                                       ; preds = %for.loop, %copy
  br label %ret

ret:                                              ; preds = %copy.split, %entry
  ret void
}

; Function Attrs: argmemonly noinline norecurse willreturn
define internal fastcc void @copy_out([388800 x %"struct.ap_uint<128>"]* "unpacked"="0", [388800 x i128]* nocapture readonly "unpacked"="1.0", [388800 x %"struct.ap_uint<128>"]* "unpacked"="2", [388800 x i128]* nocapture readonly "unpacked"="3.0") unnamed_addr #3 {
entry:
  call fastcc void @"onebyonecpy_hls.p0a388800struct.ap_uint<128>"([388800 x %"struct.ap_uint<128>"]* %0, [388800 x i128]* %1)
  call fastcc void @"onebyonecpy_hls.p0a388800struct.ap_uint<128>"([388800 x %"struct.ap_uint<128>"]* %2, [388800 x i128]* %3)
  ret void
}

declare i8* @malloc(i64) local_unnamed_addr

declare void @free(i8*) local_unnamed_addr

; Function Attrs: argmemonly noinline norecurse willreturn
define internal fastcc void @"onebyonecpy_hls.p0a388800struct.ap_uint<128>"([388800 x %"struct.ap_uint<128>"]* "unpacked"="0" %dst, [388800 x i128]* nocapture readonly "unpacked"="1.0" %src) unnamed_addr #4 {
entry:
  %0 = icmp eq [388800 x %"struct.ap_uint<128>"]* %dst, null
  br i1 %0, label %ret, label %copy

copy:                                             ; preds = %entry
  call void @"arraycpy_hls.p0a388800struct.ap_uint<128>.8"([388800 x %"struct.ap_uint<128>"]* nonnull %dst, [388800 x i128]* %src, i64 388800)
  br label %ret

ret:                                              ; preds = %copy, %entry
  ret void
}

; Function Attrs: argmemonly noinline norecurse willreturn
define void @"arraycpy_hls.p0a388800struct.ap_uint<128>.8"([388800 x %"struct.ap_uint<128>"]* "unpacked"="0" %dst, [388800 x i128]* nocapture readonly "unpacked"="1.0" %src, i64 "unpacked"="2" %num) local_unnamed_addr #2 {
entry:
  %0 = icmp eq [388800 x %"struct.ap_uint<128>"]* %dst, null
  br i1 %0, label %ret, label %copy

copy:                                             ; preds = %entry
  %for.loop.cond1 = icmp sgt i64 %num, 0
  br i1 %for.loop.cond1, label %for.loop.lr.ph, label %copy.split

for.loop.lr.ph:                                   ; preds = %copy
  br label %for.loop

for.loop:                                         ; preds = %for.loop, %for.loop.lr.ph
  %for.loop.idx2 = phi i64 [ 0, %for.loop.lr.ph ], [ %for.loop.idx.next, %for.loop ]
  %src.addr.0.0.05 = getelementptr [388800 x i128], [388800 x i128]* %src, i64 0, i64 %for.loop.idx2
  %dst.addr.0.0.06 = getelementptr [388800 x %"struct.ap_uint<128>"], [388800 x %"struct.ap_uint<128>"]* %dst, i64 0, i64 %for.loop.idx2, i32 0, i32 0, i32 0
  %1 = load i128, i128* %src.addr.0.0.05, align 16
  store i128 %1, i128* %dst.addr.0.0.06, align 16
  %for.loop.idx.next = add nuw nsw i64 %for.loop.idx2, 1
  %exitcond = icmp ne i64 %for.loop.idx.next, %num
  br i1 %exitcond, label %for.loop, label %copy.split

copy.split:                                       ; preds = %for.loop, %copy
  br label %ret

ret:                                              ; preds = %copy.split, %entry
  ret void
}

; Function Attrs: argmemonly noinline norecurse willreturn
define internal fastcc void @"onebyonecpy_hls.p0a388800struct.ap_uint<128>.12"([388800 x i128]* nocapture "unpacked"="0.0" %dst, [388800 x %"struct.ap_uint<128>"]* readonly "unpacked"="1" %src) unnamed_addr #4 {
entry:
  %0 = icmp eq [388800 x %"struct.ap_uint<128>"]* %src, null
  br i1 %0, label %ret, label %copy

copy:                                             ; preds = %entry
  call void @"arraycpy_hls.p0a388800struct.ap_uint<128>.15"([388800 x i128]* %dst, [388800 x %"struct.ap_uint<128>"]* nonnull %src, i64 388800)
  br label %ret

ret:                                              ; preds = %copy, %entry
  ret void
}

; Function Attrs: argmemonly noinline norecurse willreturn
define void @"arraycpy_hls.p0a388800struct.ap_uint<128>.15"([388800 x i128]* nocapture "unpacked"="0.0" %dst, [388800 x %"struct.ap_uint<128>"]* readonly "unpacked"="1" %src, i64 "unpacked"="2" %num) local_unnamed_addr #2 {
entry:
  %0 = icmp eq [388800 x %"struct.ap_uint<128>"]* %src, null
  br i1 %0, label %ret, label %copy

copy:                                             ; preds = %entry
  %for.loop.cond1 = icmp sgt i64 %num, 0
  br i1 %for.loop.cond1, label %for.loop.lr.ph, label %copy.split

for.loop.lr.ph:                                   ; preds = %copy
  br label %for.loop

for.loop:                                         ; preds = %for.loop, %for.loop.lr.ph
  %for.loop.idx2 = phi i64 [ 0, %for.loop.lr.ph ], [ %for.loop.idx.next, %for.loop ]
  %src.addr.0.0.05 = getelementptr [388800 x %"struct.ap_uint<128>"], [388800 x %"struct.ap_uint<128>"]* %src, i64 0, i64 %for.loop.idx2, i32 0, i32 0, i32 0
  %dst.addr.0.0.06 = getelementptr [388800 x i128], [388800 x i128]* %dst, i64 0, i64 %for.loop.idx2
  %1 = load i128, i128* %src.addr.0.0.05, align 16
  store i128 %1, i128* %dst.addr.0.0.06, align 16
  %for.loop.idx.next = add nuw nsw i64 %for.loop.idx2, 1
  %exitcond = icmp ne i64 %for.loop.idx.next, %num
  br i1 %exitcond, label %for.loop, label %copy.split

copy.split:                                       ; preds = %for.loop, %copy
  br label %ret

ret:                                              ; preds = %copy.split, %entry
  ret void
}

declare void @apatb_quad_frame_remapper_hw([388800 x i128]*, [388800 x i128]*, i32)

; Function Attrs: argmemonly noinline norecurse willreturn
define internal fastcc void @copy_back([388800 x %"struct.ap_uint<128>"]* "unpacked"="0", [388800 x i128]* nocapture readonly "unpacked"="1.0", [388800 x %"struct.ap_uint<128>"]* "unpacked"="2", [388800 x i128]* nocapture readonly "unpacked"="3.0") unnamed_addr #3 {
entry:
  call fastcc void @"onebyonecpy_hls.p0a388800struct.ap_uint<128>"([388800 x %"struct.ap_uint<128>"]* %2, [388800 x i128]* %3)
  ret void
}

declare void @quad_frame_remapper_hw_stub(%"struct.ap_uint<128>"* noalias nocapture nonnull readonly, %"struct.ap_uint<128>"* noalias nocapture nonnull, i32)

define void @quad_frame_remapper_hw_stub_wrapper([388800 x i128]*, [388800 x i128]*, i32) #5 {
entry:
  %3 = call i8* @malloc(i64 6220800)
  %4 = bitcast i8* %3 to [388800 x %"struct.ap_uint<128>"]*
  %5 = call i8* @malloc(i64 6220800)
  %6 = bitcast i8* %5 to [388800 x %"struct.ap_uint<128>"]*
  call void @copy_out([388800 x %"struct.ap_uint<128>"]* %4, [388800 x i128]* %0, [388800 x %"struct.ap_uint<128>"]* %6, [388800 x i128]* %1)
  %7 = bitcast [388800 x %"struct.ap_uint<128>"]* %4 to %"struct.ap_uint<128>"*
  %8 = bitcast [388800 x %"struct.ap_uint<128>"]* %6 to %"struct.ap_uint<128>"*
  call void @quad_frame_remapper_hw_stub(%"struct.ap_uint<128>"* %7, %"struct.ap_uint<128>"* %8, i32 %2)
  call void @copy_in([388800 x %"struct.ap_uint<128>"]* %4, [388800 x i128]* %0, [388800 x %"struct.ap_uint<128>"]* %6, [388800 x i128]* %1)
  call void @free(i8* %3)
  call void @free(i8* %5)
  ret void
}

attributes #0 = { noinline "fpga.wrapper.func"="wrapper" }
attributes #1 = { argmemonly noinline norecurse willreturn "fpga.wrapper.func"="copyin" }
attributes #2 = { argmemonly noinline norecurse willreturn "fpga.wrapper.func"="arraycpy_hls" }
attributes #3 = { argmemonly noinline norecurse willreturn "fpga.wrapper.func"="copyout" }
attributes #4 = { argmemonly noinline norecurse willreturn "fpga.wrapper.func"="onebyonecpy_hls" }
attributes #5 = { "fpga.wrapper.func"="stub" }

!llvm.dbg.cu = !{}
!llvm.ident = !{!0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0}
!llvm.module.flags = !{!1, !2, !3}
!blackbox_cfg = !{!4}

!0 = !{!"clang version 7.0.0 "}
!1 = !{i32 2, !"Dwarf Version", i32 4}
!2 = !{i32 2, !"Debug Info Version", i32 3}
!3 = !{i32 1, !"wchar_size", i32 4}
!4 = !{}
