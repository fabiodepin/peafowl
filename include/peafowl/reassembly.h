/*
 * reassembly.h
 *
 * Created on: 05/10/2012
 *
 * Contains data structures used for both IPv4 and IPv6
 * fragmentation and for TCP stream reassembly. Here for
 * 'fragments' we mean both the IP fragments
 * and the TCP segments.
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

#ifndef REASSEMBLY_H_
#define REASSEMBLY_H_

#include <peafowl/utils.h>

#include <sys/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct pfwl_reassembly_timer pfwl_reassembly_timer_t;
typedef struct pfwl_reassembly_fragment pfwl_reassembly_fragment_t;

/**If tail insertion, then the head will be the first to expire. **/
struct pfwl_reassembly_timer {
  pfwl_reassembly_timer_t* prev;
  pfwl_reassembly_timer_t* next;
  void* data;
  uint32_t expiration_time;
};

/* Describe an IP fragment (or TCP segment). */
struct pfwl_reassembly_fragment {
  /* Offset of fragment. */
  uint32_t offset;
  /* Last byte of data in fragment. */
  uint32_t end;
  /**
   * This is needed because when a segment contains a FIN,
   * then the expected sequence number in the other direction
   * will be incremented by one.
   */
  uint8_t tcp_fin : 1;
  /* Pointer into real fragment data. */
  unsigned char* ptr;
  /* Linked list pointers to the other fragments. */
  pfwl_reassembly_fragment_t* next;
  pfwl_reassembly_fragment_t* prev;
};

/**
 * Returns 1 if the sequence number x is before y, 0 otherwise.
 * @param x First sequence number.
 * @param y Second sequence number.
 * @return 1 if x is before y, 0 otherwise.
 */
uint8_t pfwl_reassembly_before(uint32_t x, uint32_t y);

/**
 * Returns 1 if the sequence number x is before or equal y, 0 otherwise.
 * @param x First sequence number.
 * @param y Second sequence number.
 * @return 1 if x is before or equal y, 0 otherwise.
 */
uint8_t pfwl_reassembly_before_or_equal(uint32_t x, uint32_t y);

/**
 * Returns 1 if the sequence number x is after y, 0 otherwise.
 * @param x First sequence number.
 * @param y Second sequence number.
 * @return 1 if x is after y, 0 otherwise.
 */
uint8_t pfwl_reassembly_after(uint32_t x, uint32_t y);

/**
 * Returns 1 if the sequence number x is after or equal y, 0 otherwise.
 * @param x First sequence number.
 * @param y Second sequence number.
 * @return 1 if x is after or equal y, 0 otherwise.
 */
uint8_t pfwl_reassembly_after_or_equal(uint32_t x, uint32_t y);

/**
 * Returns the length of a TCP segment (or IP fragment).
 * @param offset The offset where the segment starts.
 * @param end The last byte of the segment.
 * @return The length of the TCP segment (or IP fragment).
 */
uint32_t pfwl_reassembly_fragment_length(uint32_t offset, uint32_t end);

/**
 * Add a new timer to the list of IP reassembly timers.
 * @param head A pointer to the head of the timers list.
 * @param tail A pointer to the tail of the timers list.
 * @param timer The timer to insert.
 */
void pfwl_reassembly_add_timer(pfwl_reassembly_timer_t** head,
                              pfwl_reassembly_timer_t** tail,
                              pfwl_reassembly_timer_t* timer);

/**
 * Remove a timer to the list of IP reassembly timers.
 * @param head A pointer to the head of the timers list.
 * @param tail A pointer to the tail of the timers list.
 * @param timer The timer to remove.
 */
void pfwl_reassembly_delete_timer(pfwl_reassembly_timer_t** head,
                                 pfwl_reassembly_timer_t** tail,
                                 pfwl_reassembly_timer_t* timer);

/**
 * Insert a fragment in the correct position in the list of fragments,
 * considering overlaps, etc..
 * @param head The head of the list of fragments.
 * @param data The data contained in the fragment (without IP header).
 * @param offset The offset of this fragment.
 * @param end The end of this fragment.
 * @param bytes_removed The total number of bytes removed
 *                      (in the fragments) by this call.
 * @param bytes_inserted The total number of byte inserted
 *                       (in the fragments) by this call.
 *
 * @return The created fragment.
 */
pfwl_reassembly_fragment_t* pfwl_reassembly_insert_fragment(
    pfwl_reassembly_fragment_t** head, const unsigned char* data,
    uint32_t offset, uint32_t end, uint32_t* bytes_removed,
    uint32_t* bytes_inserted);

/**
 * See there is a train of contiguous fragments.
 * @param head The pointer to the head of the list of fragments.
 * @return 0 if there are missing fragments, 1 otherwise.
 */
uint8_t pfwl_reassembly_ip_check_train_of_contiguous_fragments(
    pfwl_reassembly_fragment_t* head);

/**
 * Compacts a train of contiguous fragments and returns it.
 * @param head A pointer to the head of the train.
 * @param where A pointer to a buffer where to put the data.
 * @param len The data_length of the buffer where to put the data.
 * @return The data_length of the recompacted data. If an error
 * occurred (e.g. misbehaving packet), -1 is returned.
 */
int32_t pfwl_reassembly_ip_compact_fragments(pfwl_reassembly_fragment_t* head,
                                            unsigned char** where,
                                            uint32_t len);

#ifdef __cplusplus
}
#endif

#endif /* REASSEMBLY_H_ */
