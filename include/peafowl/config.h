/*
 *  config.h
 *
 *  Created on: 23/09/2012
 *
 * =========================================================================
 *  Copyright (C) 2012-2013, Daniele De Sensi (d.desensi.software@gmail.com)
 *
 *  This file is part of Peafowl.
 *
 *  Peafowl is free software: you can redistribute it and/or
 *  modify it under the terms of the Lesser GNU General Public
 *  License as published by the Free Software Foundation, either
 *  version 3 of the License, or (at your option) any later version.

 *  Peafowl is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  Lesser GNU General Public License for more details.
 *
 *  You should have received a copy of the Lesser GNU General Public
 *  License along with Peafowl.
 *  If not, see <http://www.gnu.org/licenses/>.
 *
 * =========================================================================
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#define PFWL_CACHE_LINE_SIZE 64

/*******************************************************************/
/*                  Performance related macros.                    */
/*******************************************************************/
#ifndef PFWL_NUMA_AWARE
#define PFWL_NUMA_AWARE 0
#define PFWL_NUMA_AWARE_FLOW_TABLE_NODE 1
#endif

#ifndef PFWL_USE_MTF
#define PFWL_USE_MTF 1
#endif

#ifndef PFWL_FLOW_TABLE_ALIGN_FLOWS
#define PFWL_FLOW_TABLE_ALIGN_FLOWS 0
#endif

#ifndef PFWL_USE_LIKELY
#define PFWL_USE_LIKELY 1
#endif

#if !defined(likely)
#if defined(__GNUC__) && (PFWL_USE_LIKELY == 1)
#define likely(x) __builtin_expect(!!(x), 1)
#else
#define likely(x) (x)
#endif
#endif

#if !defined(unlikely)
#if defined(__GNUC__) && (PFWL_USE_LIKELY == 1)
#define unlikely(x) __builtin_expect(!!(x), 0)
#else
#define unlikely(x) (x)
#endif
#endif

#if (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L) || defined(__cplusplus)
#define PFWL_USE_INLINING 1
#else
#error "A compiler which supports at least C99 is needed"
#endif

/*******************************************************************/
/*                       Functional macros.                        */
/*******************************************************************/
#define PFWL_DEFAULT_MAX_TRIALS_PER_FLOW 0

#define PFWL_MAX_CPU_SOCKETS 8

#define PFWL_ENABLE_L3_TRUNCATION_PROTECTION
#define PFWL_ENABLE_L4_TRUNCATION_PROTECTION

#ifndef PFWL_FLOW_TABLE_USE_MEMORY_POOL
#define PFWL_FLOW_TABLE_USE_MEMORY_POOL 0
#endif

#if PFWL_FLOW_TABLE_USE_MEMORY_POOL
#define PFWL_FLOW_TABLE_MEMORY_POOL_DEFAULT_SIZE_v4 500000
#define PFWL_FLOW_TABLE_MEMORY_POOL_DEFAULT_SIZE_v6 100
#endif

#define PFWL_IPv4_FRAGMENTATION_DEFAULT_TABLE_SIZE 512
#define PFWL_IPv4_FRAGMENTATION_DEFAULT_PER_HOST_MEMORY_LIMIT 102400 /* 100K */
#define PFWL_IPv4_FRAGMENTATION_DEFAULT_TOTAL_MEMORY_LIMIT                    \
  10240000 /* 10M. If each host fills its memory limit, we can support up to \
              1000 hosts. */
#define PFWL_IPv4_FRAGMENTATION_DEFAULT_REASSEMBLY_TIMEOUT 30

#define PFWL_IPv6_FRAGMENTATION_DEFAULT_TABLE_SIZE 512
#define PFWL_IPv6_FRAGMENTATION_DEFAULT_PER_HOST_MEMORY_LIMIT 102400 /* 100K */
#define PFWL_IPv6_FRAGMENTATION_DEFAULT_TOTAL_MEMORY_LIMIT                    \
  10240000 /* 10M. If each host fills its memory limit, we can support up to \
              1000 hosts. */
#define PFWL_IPv6_FRAGMENTATION_DEFAULT_REASSEMBLY_TIMEOUT 60

/** Hash functions choice. **/
enum hashes {
  PFWL_SIMPLE_HASH = 0,
  PFWL_FNV_HASH,
  PFWL_MURMUR3_HASH,
  PFWL_BKDR_HASH,
};

#define PFWL_FLOW_TABLE_HASH_VERSION PFWL_SIMPLE_HASH

#define PFWL_ACTIVATE_ALL_HASH_FUNCTIONS_CODE 1

#ifndef PFWL_THREAD_SAFETY_ENABLED
#define PFWL_THREAD_SAFETY_ENABLED 0
#endif

#define __STDC_FORMAT_MACROS  // To enable inttypes.h macros also for g++

/******************************************************************/
/* Configuration macros for multicore version.                    */
/* Change their value ONLY IF you really know what you are doing. */
/******************************************************************/

#if PFWL_NUMA_AWARE
#define PFWL_NUMA_AWARE_TASKS_NODE 0
#define PFWL_NUMA_AWARE_PACKETS_NODE 0
#endif

#define PFWL_MULTICORE_DEFAULT_GRAIN_SIZE 1  // 256

#ifndef PFWL_MULTICORE_USE_TASKS_POOL
#define PFWL_MULTICORE_USE_TASKS_POOL 1
#endif
#define PFWL_MULTICORE_TASKS_POOL_SIZE 16384

#ifndef PFWL_MULTICORE_PREFETCH
#define PFWL_MULTICORE_PREFETCH 0
#endif

#ifndef PFWL_MULTICORE_ALIGN_TASKS
#define PFWL_MULTICORE_ALIGN_TASKS 1
#endif

#define PFWL_MULTICORE_L3_L4_ORDERED_FARM 0
#define PFWL_MULTICORE_L3_L4_NOT_ORDERED_FARM 1
#define PFWL_MULTICORE_L3_L4_ON_DEMAND 2

#ifndef PFWL_MULTICORE_L3_L4_FARM_TYPE
#define PFWL_MULTICORE_L3_L4_FARM_TYPE PFWL_MULTICORE_L3_L4_ORDERED_FARM
#endif

#ifndef PFWL_MULTICORE_DEFAULT_BUFFER_SIZE
#define PFWL_MULTICORE_DEFAULT_BUFFER_SIZE 32768
#endif

#ifndef PFWL_MULTICORE_L3_L4_FARM_INPUT_BUFFER_SIZE
#define PFWL_MULTICORE_L3_L4_FARM_INPUT_BUFFER_SIZE \
  PFWL_MULTICORE_DEFAULT_BUFFER_SIZE
#endif

#ifndef PFWL_MULTICORE_L3_L4_FARM_OUTPUT_BUFFER_SIZE
#define PFWL_MULTICORE_L3_L4_FARM_OUTPUT_BUFFER_SIZE \
  PFWL_MULTICORE_DEFAULT_BUFFER_SIZE
#endif

#ifndef PFWL_MULTICORE_L7_FARM_INPUT_BUFFER_SIZE
#define PFWL_MULTICORE_L7_FARM_INPUT_BUFFER_SIZE \
  PFWL_MULTICORE_DEFAULT_BUFFER_SIZE
#endif

#ifndef PFWL_MULTICORE_L7_FARM_OUTPUT_BUFFER_SIZE
#define PFWL_MULTICORE_L7_FARM_OUTPUT_BUFFER_SIZE \
  PFWL_MULTICORE_DEFAULT_BUFFER_SIZE
#endif

#ifndef PFWL_MULTICORE_PIPELINE_INPUT_BUFFER_SIZE
#define PFWL_MULTICORE_PIPELINE_INPUT_BUFFER_SIZE \
  PFWL_MULTICORE_DEFAULT_BUFFER_SIZE
#endif

#ifndef PFWL_MULTICORE_PIPELINE_OUTPUT_BUFFER_SIZE
#define PFWL_MULTICORE_PIPELINE_OUTPUT_BUFFER_SIZE \
  PFWL_MULTICORE_DEFAULT_BUFFER_SIZE
#endif

#ifndef MC_PFWL_TICKS_WAIT
#define MC_PFWL_TICKS_WAIT 0
#endif

#ifndef MC_PFWL_AVG_RHO
#define MC_PFWL_AVG_RHO 0
#endif

#ifndef MC_PFWL_POWER_USE_MODEL
#define MC_PFWL_POWER_USE_MODEL 1
#endif

#ifndef SPINTICKS
#define SPINTICKS 1000
#endif

#endif /* CONFIG_H_ */
