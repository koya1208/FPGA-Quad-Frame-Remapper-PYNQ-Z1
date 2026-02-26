set SynModuleInfo {
  {SRCNAME quad_frame_remapper_Pipeline_3 MODELNAME quad_frame_remapper_Pipeline_3 RTLNAME quad_frame_remapper_quad_frame_remapper_Pipeline_3
    SUBMODULES {
      {MODELNAME quad_frame_remapper_flow_control_loop_pipe_sequential_init RTLNAME quad_frame_remapper_flow_control_loop_pipe_sequential_init BINDTYPE interface TYPE internal_upc_flow_control INSTNAME quad_frame_remapper_flow_control_loop_pipe_sequential_init_U}
    }
  }
  {SRCNAME quad_frame_remapper_Pipeline_4 MODELNAME quad_frame_remapper_Pipeline_4 RTLNAME quad_frame_remapper_quad_frame_remapper_Pipeline_4}
  {SRCNAME quad_frame_remapper_Pipeline_VITIS_LOOP_132_2 MODELNAME quad_frame_remapper_Pipeline_VITIS_LOOP_132_2 RTLNAME quad_frame_remapper_quad_frame_remapper_Pipeline_VITIS_LOOP_132_2}
  {SRCNAME quad_frame_remapper_Pipeline_VITIS_LOOP_146_3 MODELNAME quad_frame_remapper_Pipeline_VITIS_LOOP_146_3 RTLNAME quad_frame_remapper_quad_frame_remapper_Pipeline_VITIS_LOOP_146_3}
  {SRCNAME quad_frame_remapper_Pipeline_7 MODELNAME quad_frame_remapper_Pipeline_7 RTLNAME quad_frame_remapper_quad_frame_remapper_Pipeline_7}
  {SRCNAME quad_frame_remapper_Pipeline_1 MODELNAME quad_frame_remapper_Pipeline_1 RTLNAME quad_frame_remapper_quad_frame_remapper_Pipeline_1}
  {SRCNAME quad_frame_remapper_Pipeline_2 MODELNAME quad_frame_remapper_Pipeline_2 RTLNAME quad_frame_remapper_quad_frame_remapper_Pipeline_2}
  {SRCNAME quad_frame_remapper MODELNAME quad_frame_remapper RTLNAME quad_frame_remapper IS_TOP 1
    SUBMODULES {
      {MODELNAME quad_frame_remapper_mul_11ns_10ns_19_1_1 RTLNAME quad_frame_remapper_mul_11ns_10ns_19_1_1 BINDTYPE op TYPE mul IMPL auto LATENCY 0 ALLOW_PRAGMA 1}
      {MODELNAME quad_frame_remapper_line_buf_in_RAM_1WNR_AUTO_1R1W RTLNAME quad_frame_remapper_line_buf_in_RAM_1WNR_AUTO_1R1W BINDTYPE storage TYPE ram_1wnr IMPL auto LATENCY 2 ALLOW_PRAGMA 1}
      {MODELNAME quad_frame_remapper_line_buf_out_RAM_AUTO_1R1W RTLNAME quad_frame_remapper_line_buf_out_RAM_AUTO_1R1W BINDTYPE storage TYPE ram IMPL auto LATENCY 2 ALLOW_PRAGMA 1}
      {MODELNAME quad_frame_remapper_gmem0_m_axi RTLNAME quad_frame_remapper_gmem0_m_axi BINDTYPE interface TYPE adapter IMPL m_axi}
      {MODELNAME quad_frame_remapper_gmem1_m_axi RTLNAME quad_frame_remapper_gmem1_m_axi BINDTYPE interface TYPE adapter IMPL m_axi}
      {MODELNAME quad_frame_remapper_control_s_axi RTLNAME quad_frame_remapper_control_s_axi BINDTYPE interface TYPE interface_s_axilite}
    }
  }
}
