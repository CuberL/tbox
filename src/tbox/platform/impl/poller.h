/*!The Treasure Box Library
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * 
 * Copyright (C) 2009-2020, TBOOX Open Source Group.
 *
 * @author      ruki
 * @file        poller.h
 * @ingroup     platform
 *
 */
#ifndef TB_PLATFORM_IMPL_POLLER_H
#define TB_PLATFORM_IMPL_POLLER_H

/* //////////////////////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"

/* //////////////////////////////////////////////////////////////////////////////////////
 * types
 */

// the poller type
typedef struct __tb_poller_t
{
    // the user private data
    tb_cpointer_t       priv;

    // the poller type
    tb_uint16_t         type;

    // the supported events
    tb_uint16_t         supported_events;

    /* exit poller
     *
     * @param poller    the poller
     */
    tb_void_t           (*exit)(struct __tb_poller_t* poller);

    /* kill all waited events, tb_poller_wait() will return -1
     *
     * @param poller    the poller
     */
    tb_void_t           (*kill)(struct __tb_poller_t* poller);

    /* spak the poller, break the tb_poller_wait() and return all events
     *
     * @param poller    the poller
     */
    tb_void_t           (*spak)(struct __tb_poller_t* poller);

    /* wait events for all objects
     *
     * @param poller    the poller
     * @param func      the events function
     * @param timeout   the timeout, infinity: -1
     *
     * @return          > 0: the events number, 0: timeout, -1: failed
     */
    tb_long_t           (*wait)(struct __tb_poller_t* poller, tb_poller_event_func_t func, tb_long_t timeout);
    
    /* insert socket to poller
     *
     * @param poller    the poller
     * @param sock      the socket
     * @param events    the poller events
     * @param priv      the private data
     *
     * @return          tb_true or tb_false
     */
    tb_bool_t           (*insert)(struct __tb_poller_t* poller, tb_socket_ref_t sock, tb_size_t events, tb_cpointer_t priv);

    /* remove socket from poller
     *
     * @param poller    the poller
     * @param sock      the sock
     *
     * @return          tb_true or tb_false
     */
    tb_bool_t           (*remove)(struct __tb_poller_t* poller, tb_socket_ref_t sock);

    /* modify events for the given socket
     *
     * @param poller    the poller
     * @param sock      the socket
     * @param events    the poller events
     * @param priv      the private data
     *
     * @return          tb_true or tb_false
     */
    tb_bool_t           (*modify)(struct __tb_poller_t* poller, tb_socket_ref_t sock, tb_size_t events, tb_cpointer_t priv);

    /* attach the poller to the current thread (only for windows/iocp now)
     *
     * @param poller    the poller
     */
    tb_void_t           (*attach)(struct __tb_poller_t* poller);

}tb_poller_t;

#endif