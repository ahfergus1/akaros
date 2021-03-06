/*
 * Copyright (c) 2014 Google Inc. All rights reserved
 * Contributed by Stephane Eranian <eranian@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
 * OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * This file is part of libpfm, a performance monitoring support library for
 * applications on Linux.
 *
 * PMU: ivbep_unc_pcu (Intel IvyBridge-EP PCU uncore)
 */

static const intel_x86_umask_t ivbep_unc_p_power_state_occupancy[]={
  { .uname = "CORES_C0",
    .udesc  = "Counts number of cores in C0",
    .ucode  = 0x4000,
    .uflags = INTEL_X86_NCOMBO,
  },
  { .uname = "CORES_C3",
    .udesc  = "Counts number of cores in C3",
    .ucode  = 0x8000,
    .uflags = INTEL_X86_NCOMBO,
  },
  { .uname = "CORES_C6",
    .udesc  = "Counts number of cores in C6",
    .ucode  = 0xc000,
    .uflags = INTEL_X86_NCOMBO,
  },
};

static const intel_x86_umask_t ivbep_unc_p_occupancy_counters[]={
  { .uname = "C0",
    .udesc  = "Counts number of cores in C0",
    .ucode  = 0x0100,
    .uflags = INTEL_X86_NCOMBO,
  },
  { .uname = "C3",
    .udesc  = "Counts number of cores in C3",
    .ucode  = 0x0200,
    .uflags = INTEL_X86_NCOMBO,
  },
  { .uname = "C6",
    .udesc  = "Counts number of cores in C6",
    .ucode  = 0x0300,
    .uflags = INTEL_X86_NCOMBO,
  },
};

static const intel_x86_entry_t intel_ivbep_unc_p_pe[]={
  { .name   = "UNC_P_CLOCKTICKS",
    .desc   = "PCU Uncore clockticks",
    .modmsk = IVBEP_UNC_PCU_ATTRS,
    .cntmsk = 0xf,
    .code = 0x00,
  },
  { .name = "UNC_P_CORE0_TRANSITION_CYCLES",
    .desc = "Core 0 C State Transition Cycles",
    .code = 0x70,
    .cntmsk = 0xf,
    .modmsk = IVBEP_UNC_PCU_ATTRS,
  },
  { .name = "UNC_P_CORE1_TRANSITION_CYCLES",
    .desc = "Core 1 C State Transition Cycles",
    .code = 0x71,
    .cntmsk = 0xf,
    .modmsk = IVBEP_UNC_PCU_ATTRS,
  },
  { .name = "UNC_P_CORE2_TRANSITION_CYCLES",
    .desc = "Core 2 C State Transition Cycles",
    .code = 0x72,
    .cntmsk = 0xf,
    .modmsk = IVBEP_UNC_PCU_ATTRS,
  },
  { .name = "UNC_P_CORE3_TRANSITION_CYCLES",
    .desc = "Core 3 C State Transition Cycles",
    .code = 0x73,
    .cntmsk = 0xf,
    .modmsk = IVBEP_UNC_PCU_ATTRS,
  },
  { .name = "UNC_P_CORE4_TRANSITION_CYCLES",
    .desc = "Core 4 C State Transition Cycles",
    .code = 0x74,
    .cntmsk = 0xf,
    .modmsk = IVBEP_UNC_PCU_ATTRS,
  },
  { .name = "UNC_P_CORE5_TRANSITION_CYCLES",
    .desc = "Core 5 C State Transition Cycles",
    .code = 0x75,
    .cntmsk = 0xf,
    .modmsk = IVBEP_UNC_PCU_ATTRS,
  },
  { .name = "UNC_P_CORE6_TRANSITION_CYCLES",
    .desc = "Core 6 C State Transition Cycles",
    .code = 0x76,
    .cntmsk = 0xf,
    .modmsk = IVBEP_UNC_PCU_ATTRS,
  },
  { .name = "UNC_P_CORE7_TRANSITION_CYCLES",
    .desc = "Core 7 C State Transition Cycles",
    .code = 0x77,
    .cntmsk = 0xf,
    .modmsk = IVBEP_UNC_PCU_ATTRS,
  },
  { .name = "UNC_P_CORE8_TRANSITION_CYCLES",
    .desc = "Core 8 C State Transition Cycles",
    .code = 0x78,
    .cntmsk = 0xf,
    .modmsk = IVBEP_UNC_PCU_ATTRS,
  },
  { .name = "UNC_P_CORE9_TRANSITION_CYCLES",
    .desc = "Core 9 C State Transition Cycles",
    .code = 0x79,
    .cntmsk = 0xf,
    .modmsk = IVBEP_UNC_PCU_ATTRS,
  },
  { .name = "UNC_P_CORE10_TRANSITION_CYCLES",
    .desc = "Core 10 C State Transition Cycles",
    .code = 0x7a,
    .cntmsk = 0xf,
    .modmsk = IVBEP_UNC_PCU_ATTRS,
  },
  { .name = "UNC_P_CORE11_TRANSITION_CYCLES",
    .desc = "Core 11 C State Transition Cycles",
    .code = 0x7b,
    .cntmsk = 0xf,
    .modmsk = IVBEP_UNC_PCU_ATTRS,
  },
  { .name = "UNC_P_CORE12_TRANSITION_CYCLES",
    .desc = "Core 12 C State Transition Cycles",
    .code = 0x7c,
    .cntmsk = 0xf,
    .modmsk = IVBEP_UNC_PCU_ATTRS,
  },
  { .name = "UNC_P_CORE13_TRANSITION_CYCLES",
    .desc = "Core 13 C State Transition Cycles",
    .code = 0x7d,
    .cntmsk = 0xf,
    .modmsk = IVBEP_UNC_PCU_ATTRS,
  },
  { .name = "UNC_P_CORE14_TRANSITION_CYCLES",
    .desc = "Core 14 C State Transition Cycles",
    .code = 0x7e,
    .cntmsk = 0xf,
    .modmsk = IVBEP_UNC_PCU_ATTRS,
  },
  { .name = "UNC_P_DELAYED_C_STATE_ABORT_CORE0",
    .desc = "Deep C state rejection Core 0",
    .code = 0x17 | (1ULL << 21), /* sel_ext */
    .cntmsk = 0xf,
    .modmsk = IVBEP_UNC_PCU_ATTRS,
  },
  { .name = "UNC_P_DELAYED_C_STATE_ABORT_CORE1",
    .desc = "Deep C state rejection Core 1",
    .code = 0x18 | (1ULL << 21), /* sel_ext */
    .cntmsk = 0xf,
    .modmsk = IVBEP_UNC_PCU_ATTRS,
  },
  { .name = "UNC_P_DELAYED_C_STATE_ABORT_CORE2",
    .desc = "Deep C state rejection Core 2",
    .code = 0x19 | (1ULL << 21), /* sel_ext */
    .cntmsk = 0xf,
    .modmsk = IVBEP_UNC_PCU_ATTRS,
  },
  { .name = "UNC_P_DELAYED_C_STATE_ABORT_CORE3",
    .desc = "Deep C state rejection Core 3",
    .code = 0x1a | (1ULL << 21), /* sel_ext */
    .cntmsk = 0xf,
    .modmsk = IVBEP_UNC_PCU_ATTRS,
  },
  { .name = "UNC_P_DELAYED_C_STATE_ABORT_CORE4",
    .desc = "Deep C state rejection Core 4",
    .code = 0x1b | (1ULL << 21), /* sel_ext */
    .cntmsk = 0xf,
    .modmsk = IVBEP_UNC_PCU_ATTRS,
  },
  { .name = "UNC_P_DELAYED_C_STATE_ABORT_CORE5",
    .desc = "Deep C state rejection Core 5",
    .code = 0x1c | (1ULL << 21), /* sel_ext */
    .cntmsk = 0xf,
    .modmsk = IVBEP_UNC_PCU_ATTRS,
  },
  { .name = "UNC_P_DELAYED_C_STATE_ABORT_CORE6",
    .desc = "Deep C state rejection Core 6",
    .code = 0x1d | (1ULL << 21), /* sel_ext */
    .cntmsk = 0xf,
    .modmsk = IVBEP_UNC_PCU_ATTRS,
  },
  { .name = "UNC_P_DELAYED_C_STATE_ABORT_CORE7",
    .desc = "Deep C state rejection Core 7",
    .code = 0x1e | (1ULL << 21), /* sel_ext */
    .cntmsk = 0xf,
    .modmsk = IVBEP_UNC_PCU_ATTRS,
  },
  { .name = "UNC_P_DELAYED_C_STATE_ABORT_CORE8",
    .desc = "Deep C state rejection Core 8",
    .code = 0x1f | (1ULL << 21), /* sel_ext */
    .cntmsk = 0xf,
    .modmsk = IVBEP_UNC_PCU_ATTRS,
  },
  { .name = "UNC_P_DELAYED_C_STATE_ABORT_CORE9",
    .desc = "Deep C state rejection Core 9",
    .code = 0x20 | (1ULL << 21), /* sel_ext */
    .cntmsk = 0xf,
    .modmsk = IVBEP_UNC_PCU_ATTRS,
  },
  { .name = "UNC_P_DELAYED_C_STATE_ABORT_CORE10",
    .desc = "Deep C state rejection Core 10",
    .code = 0x21 | (1ULL << 21), /* sel_ext */
    .cntmsk = 0xf,
    .modmsk = IVBEP_UNC_PCU_ATTRS,
  },
  { .name = "UNC_P_DELAYED_C_STATE_ABORT_CORE11",
    .desc = "Deep C state rejection Core 11",
    .code = 0x22 | (1ULL << 21), /* sel_ext */
    .cntmsk = 0xf,
    .modmsk = IVBEP_UNC_PCU_ATTRS,
  },
  { .name = "UNC_P_DELAYED_C_STATE_ABORT_CORE12",
    .desc = "Deep C state rejection Core 12",
    .code = 0x23 | (1ULL << 21), /* sel_ext */
    .cntmsk = 0xf,
    .modmsk = IVBEP_UNC_PCU_ATTRS,
  },
  { .name = "UNC_P_DELAYED_C_STATE_ABORT_CORE13",
    .desc = "Deep C state rejection Core 13",
    .code = 0x24 | (1ULL << 21), /* sel_ext */
    .cntmsk = 0xf,
    .modmsk = IVBEP_UNC_PCU_ATTRS,
  },
  { .name = "UNC_P_DELAYED_C_STATE_ABORT_CORE14",
    .desc = "Deep C state rejection Core 14",
    .code = 0x25 | (1ULL << 21), /* sel_ext */
    .cntmsk = 0xf,
    .modmsk = IVBEP_UNC_PCU_ATTRS,
  },
  { .name = "UNC_P_DEMOTIONS_CORE0",
    .desc = "Core 0 C State Demotions",
    .code = 0x1e,
    .cntmsk = 0xf,
    .modmsk = IVBEP_UNC_PCU_ATTRS,
  },
  { .name = "UNC_P_DEMOTIONS_CORE1",
    .desc = "Core 1 C State Demotions",
    .code = 0x1f,
    .cntmsk = 0xf,
    .modmsk = IVBEP_UNC_PCU_ATTRS,
  },
  { .name = "UNC_P_DEMOTIONS_CORE2",
    .desc = "Core 2 C State Demotions",
    .code = 0x20,
    .cntmsk = 0xf,
    .modmsk = IVBEP_UNC_PCU_ATTRS,
  },
  { .name = "UNC_P_DEMOTIONS_CORE3",
    .desc = "Core 3 C State Demotions",
    .code = 0x21,
    .cntmsk = 0xf,
    .modmsk = IVBEP_UNC_PCU_ATTRS,
  },
  { .name = "UNC_P_DEMOTIONS_CORE4",
    .desc = "Core 4 C State Demotions",
    .code = 0x22,
    .cntmsk = 0xf,
    .modmsk = IVBEP_UNC_PCU_ATTRS,
  },
  { .name = "UNC_P_DEMOTIONS_CORE5",
    .desc = "Core 5 C State Demotions",
    .code = 0x23,
    .cntmsk = 0xf,
    .modmsk = IVBEP_UNC_PCU_ATTRS,
  },
  { .name = "UNC_P_DEMOTIONS_CORE6",
    .desc = "Core 6 C State Demotions",
    .code = 0x24,
    .cntmsk = 0xf,
    .modmsk = IVBEP_UNC_PCU_ATTRS,
  },
  { .name = "UNC_P_DEMOTIONS_CORE7",
    .desc = "Core 7 C State Demotions",
    .code = 0x25,
    .cntmsk = 0xf,
    .modmsk = IVBEP_UNC_PCU_ATTRS,
  },
  { .name = "UNC_P_DEMOTIONS_CORE8",
    .desc = "Core 8 C State Demotions",
    .code = 0x40,
    .cntmsk = 0xf,
    .modmsk = IVBEP_UNC_PCU_ATTRS,
  },
  { .name = "UNC_P_DEMOTIONS_CORE9",
    .desc = "Core 9 C State Demotions",
    .code = 0x41,
    .cntmsk = 0xf,
    .modmsk = IVBEP_UNC_PCU_ATTRS,
  },
  { .name = "UNC_P_DEMOTIONS_CORE10",
    .desc = "Core 10 C State Demotions",
    .code = 0x42,
    .cntmsk = 0xf,
    .modmsk = IVBEP_UNC_PCU_ATTRS,
  },
  { .name = "UNC_P_DEMOTIONS_CORE11",
    .desc = "Core 11 C State Demotions",
    .code = 0x43,
    .cntmsk = 0xf,
    .modmsk = IVBEP_UNC_PCU_ATTRS,
  },
  { .name = "UNC_P_DEMOTIONS_CORE12",
    .desc = "Core 12 C State Demotions",
    .code = 0x44,
    .cntmsk = 0xf,
    .modmsk = IVBEP_UNC_PCU_ATTRS,
  },
  { .name = "UNC_P_DEMOTIONS_CORE13",
    .desc = "Core 13 C State Demotions",
    .code = 0x45,
    .cntmsk = 0xf,
    .modmsk = IVBEP_UNC_PCU_ATTRS,
  },
  { .name = "UNC_P_DEMOTIONS_CORE14",
    .desc = "Core 14 C State Demotions",
    .code = 0x46,
    .cntmsk = 0xf,
    .modmsk = IVBEP_UNC_PCU_ATTRS,
  },
  { .name = "UNC_P_FREQ_BAND0_CYCLES",
    .desc = "Frequency Residency",
    .code = 0xb,
    .cntmsk = 0xf,
    .flags = INTEL_X86_NO_AUTOENCODE,
    .modmsk = IVBEP_UNC_PCU_BAND_ATTRS,
    .modmsk_req = _SNBEP_UNC_ATTR_FF,
  },
  { .name = "UNC_P_FREQ_BAND1_CYCLES",
    .desc = "Frequency Residency",
    .code = 0xc,
    .cntmsk = 0xf,
    .flags = INTEL_X86_NO_AUTOENCODE,
    .modmsk = IVBEP_UNC_PCU_BAND_ATTRS,
    .modmsk_req = _SNBEP_UNC_ATTR_FF,
  },
  { .name = "UNC_P_FREQ_BAND2_CYCLES",
    .desc = "Frequency Residency",
    .code = 0xd,
    .cntmsk = 0xf,
    .flags = INTEL_X86_NO_AUTOENCODE,
    .modmsk = IVBEP_UNC_PCU_BAND_ATTRS,
    .modmsk_req = _SNBEP_UNC_ATTR_FF,
  },
  { .name = "UNC_P_FREQ_BAND3_CYCLES",
    .desc = "Frequency Residency",
    .code = 0xe,
    .cntmsk = 0xf,
    .flags = INTEL_X86_NO_AUTOENCODE,
    .modmsk = IVBEP_UNC_PCU_BAND_ATTRS,
    .modmsk_req = _SNBEP_UNC_ATTR_FF,
  },
  { .name = "UNC_P_FREQ_MAX_CURRENT_CYCLES",
    .desc = "Current Strongest Upper Limit Cycles",
    .code = 0x7,
    .cntmsk = 0xf,
    .modmsk = IVBEP_UNC_PCU_ATTRS,
  },
  { .name = "UNC_P_FREQ_MAX_LIMIT_THERMAL_CYCLES",
    .desc = "Thermal Strongest Upper Limit Cycles",
    .code = 0x4,
    .cntmsk = 0xf,
    .modmsk = IVBEP_UNC_PCU_ATTRS,
  },
  { .name = "UNC_P_FREQ_MAX_OS_CYCLES",
    .desc = "OS Strongest Upper Limit Cycles",
    .code = 0x6,
    .cntmsk = 0xf,
    .modmsk = IVBEP_UNC_PCU_ATTRS,
  },
  { .name = "UNC_P_FREQ_MAX_POWER_CYCLES",
    .desc = "Power Strongest Upper Limit Cycles",
    .code = 0x5,
    .cntmsk = 0xf,
    .modmsk = IVBEP_UNC_PCU_ATTRS,
  },
  { .name = "UNC_P_FREQ_MIN_PERF_P_CYCLES",
    .desc = "Perf P Limit Strongest Lower Limit Cycles",
    .code = 0x02 | (1ULL << 21), /* sel_ext */
    .cntmsk = 0xf,
    .modmsk = IVBEP_UNC_PCU_ATTRS,
  },

  { .name = "UNC_P_FREQ_MIN_IO_P_CYCLES",
    .desc = "IO P Limit Strongest Lower Limit Cycles",
    .code = 0x61,
    .cntmsk = 0xf,
    .modmsk = IVBEP_UNC_PCU_ATTRS,
  },
  { .name = "UNC_P_FREQ_TRANS_CYCLES",
    .desc = "Cycles spent changing Frequency",
    .code = 0x60,
    .cntmsk = 0xf,
    .modmsk = IVBEP_UNC_PCU_ATTRS,
  },
  { .name = "UNC_P_MEMORY_PHASE_SHEDDING_CYCLES",
    .desc = "Memory Phase Shedding Cycles",
    .code = 0x2f,
    .cntmsk = 0xf,
    .modmsk = IVBEP_UNC_PCU_ATTRS,
  },
  { .name = "UNC_P_PKG_C_EXIT_LATENCY",
    .desc = "Package C state exit latency. Counts cycles the package is transitioning from C2 to C3",
    .code = 0x26 | (1ULL << 21), /* sel_ext */
    .cntmsk = 0xf,
    .modmsk = IVBEP_UNC_PCU_ATTRS,
  },
  { .name = "UNC_P_POWER_STATE_OCCUPANCY",
    .desc = "Number of cores in C0",
    .code = 0x80,
    .cntmsk = 0xf,
    .ngrp = 1,
    .modmsk = IVBEP_UNC_PCU_ATTRS,
    .numasks = LIBPFM_ARRAY_SIZE(ivbep_unc_p_power_state_occupancy),
    .umasks  = ivbep_unc_p_power_state_occupancy
  },
  { .name = "UNC_P_PROCHOT_EXTERNAL_CYCLES",
    .desc = "External Prochot",
    .code = 0xa,
    .cntmsk = 0xf,
    .modmsk = IVBEP_UNC_PCU_ATTRS,
  },
  { .name = "UNC_P_PROCHOT_INTERNAL_CYCLES",
    .desc = "Internal Prochot",
    .code = 0x9,
    .cntmsk = 0xf,
    .modmsk = IVBEP_UNC_PCU_ATTRS,
  },
  { .name = "UNC_P_TOTAL_TRANSITION_CYCLES",
    .desc = "Total Core C State Transition Cycles",
    .code = 0x63,
    .cntmsk = 0xf,
    .modmsk = IVBEP_UNC_PCU_ATTRS,
  },
  { .name = "UNC_P_VOLT_TRANS_CYCLES_CHANGE",
    .desc = "Cycles Changing Voltage",
    .code = 0x3,
    .cntmsk = 0xf,
    .modmsk = IVBEP_UNC_PCU_ATTRS,
  },
  { .name = "UNC_P_VOLT_TRANS_CYCLES_DECREASE",
    .desc = "Cycles Decreasing Voltage",
    .code = 0x2,
    .cntmsk = 0xf,
    .modmsk = IVBEP_UNC_PCU_ATTRS,
  },
  { .name = "UNC_P_VOLT_TRANS_CYCLES_INCREASE",
    .desc = "Cycles Increasing Voltage",
    .code = 0x1,
    .cntmsk = 0xf,
    .modmsk = IVBEP_UNC_PCU_ATTRS,
  },
  { .name = "UNC_P_VR_HOT_CYCLES",
    .desc = "VR Hot",
    .code = 0x32,
    .cntmsk = 0xf,
    .modmsk = IVBEP_UNC_PCU_ATTRS,
  },
};
