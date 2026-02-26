# ==============================================================
# Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2025.1 (64-bit)
# Tool Version Limit: 2025.05
# Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
# Copyright 2022-2025 Advanced Micro Devices, Inc. All Rights Reserved.
# 
# ==============================================================
cmake_minimum_required(VERSION 3.15)
project(quad_frame_remapper)
find_package(common)
collector_create (PROJECT_LIB_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}")
collect (PROJECT_LIB_SOURCES xquad_frame_remapper.c)
collect (PROJECT_LIB_SOURCES xquad_frame_remapper_sinit.c)
collect (PROJECT_LIB_SOURCES xquad_frame_remapper_linux.c)
collect (PROJECT_LIB_SOURCES xquad_frame_remapper_g.c)
collector_list (_sources PROJECT_LIB_SOURCES)
collector_create (PROJECT_LIB_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}")
collect (PROJECT_LIB_HEADERS xquad_frame_remapper.h)
collect (PROJECT_LIB_HEADERS xquad_frame_remapper_hw.h)
collector_list (_headers PROJECT_LIB_HEADERS)
file(COPY ${_headers} DESTINATION ${CMAKE_BINARY_DIR}/include)
include_directories(${CMAKE_BINARY_DIR}/include)
add_library(quad_frame_remapper STATIC ${_sources})
set_target_properties(quad_frame_remapper PROPERTIES LINKER_LANGUAGE C)

