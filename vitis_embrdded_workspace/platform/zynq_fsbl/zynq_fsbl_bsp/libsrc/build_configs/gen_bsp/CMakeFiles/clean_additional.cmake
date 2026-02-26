# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "")
  file(REMOVE_RECURSE
  "C:\\quad_frame_remapper\\vitis_embrdded_workspace\\platform\\zynq_fsbl\\zynq_fsbl_bsp\\include\\diskio.h"
  "C:\\quad_frame_remapper\\vitis_embrdded_workspace\\platform\\zynq_fsbl\\zynq_fsbl_bsp\\include\\ff.h"
  "C:\\quad_frame_remapper\\vitis_embrdded_workspace\\platform\\zynq_fsbl\\zynq_fsbl_bsp\\include\\ffconf.h"
  "C:\\quad_frame_remapper\\vitis_embrdded_workspace\\platform\\zynq_fsbl\\zynq_fsbl_bsp\\include\\sleep.h"
  "C:\\quad_frame_remapper\\vitis_embrdded_workspace\\platform\\zynq_fsbl\\zynq_fsbl_bsp\\include\\xilffs.h"
  "C:\\quad_frame_remapper\\vitis_embrdded_workspace\\platform\\zynq_fsbl\\zynq_fsbl_bsp\\include\\xilffs_config.h"
  "C:\\quad_frame_remapper\\vitis_embrdded_workspace\\platform\\zynq_fsbl\\zynq_fsbl_bsp\\include\\xilrsa.h"
  "C:\\quad_frame_remapper\\vitis_embrdded_workspace\\platform\\zynq_fsbl\\zynq_fsbl_bsp\\include\\xiltimer.h"
  "C:\\quad_frame_remapper\\vitis_embrdded_workspace\\platform\\zynq_fsbl\\zynq_fsbl_bsp\\include\\xtimer_config.h"
  "C:\\quad_frame_remapper\\vitis_embrdded_workspace\\platform\\zynq_fsbl\\zynq_fsbl_bsp\\lib\\libxilffs.a"
  "C:\\quad_frame_remapper\\vitis_embrdded_workspace\\platform\\zynq_fsbl\\zynq_fsbl_bsp\\lib\\libxilrsa.a"
  "C:\\quad_frame_remapper\\vitis_embrdded_workspace\\platform\\zynq_fsbl\\zynq_fsbl_bsp\\lib\\libxiltimer.a"
  )
endif()
