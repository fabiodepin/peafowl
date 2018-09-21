/*
 * hash_functions.h
 *
 * Created on: 06/10/2012
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

#ifndef HASH_FUNCTIONS_H_
#define HASH_FUNCTIONS_H_

#include <peafowl/peafowl.h>

#include <sys/types.h>

#ifdef __cplusplus
extern "C" {
#endif

#if PFWL_FLOW_TABLE_HASH_VERSION == PFWL_FNV_HASH || \
    PFWL_ACTIVATE_ALL_HASH_FUNCTIONS_CODE == 1
uint32_t v4_fnv_hash_function(const pfwl_pkt_infos_t* const in);

uint32_t v6_fnv_hash_function(const pfwl_pkt_infos_t* const in);
#endif

#if PFWL_FLOW_TABLE_HASH_VERSION == PFWL_MURMUR3_HASH || \
    PFWL_ACTIVATE_ALL_HASH_FUNCTIONS_CODE == 1
uint32_t v4_hash_murmur3(const pfwl_pkt_infos_t* const in, uint32_t seed);

uint32_t v6_hash_murmur3(const pfwl_pkt_infos_t* const in, uint32_t seed);
#endif

#if PFWL_FLOW_TABLE_HASH_VERSION == PFWL_SIMPLE_HASH || \
    PFWL_ACTIVATE_ALL_HASH_FUNCTIONS_CODE == 1
uint32_t v4_hash_function_simple(const pfwl_pkt_infos_t* const in);

uint32_t v6_hash_function_simple(const pfwl_pkt_infos_t* const in);
#endif

#if PFWL_FLOW_TABLE_HASH_VERSION == PFWL_BKDR_HASH || \
    PFWL_ACTIVATE_ALL_HASH_FUNCTIONS_CODE == 1
uint32_t v4_hash_function_bkdr(const pfwl_pkt_infos_t* const in);

uint32_t v6_hash_function_bkdr(const pfwl_pkt_infos_t* const in);
#endif

#ifdef __cplusplus
}
#endif

#endif /* HASH_FUNCTIONS_H_ */
