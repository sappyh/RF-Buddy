/*
 * Copyright (c) 2017, RISE SICS.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * This file is part of the Contiki operating system.
 *
 */

/**
 * \file
 *         Sender Process for RF-Buddy
 * \author
*         Saptarshi Hazra <saptarshi.hazra@ri.se>
 *
 */

#include "contiki.h"
#include "net/netstack.h"
// #include "net/ip"

#define LINKADDR_CONF_SIZE 2
#include "net/linkaddr.h"
#include <string.h>
#include <stdio.h> /* For printf() */

/* Log configuration */
#include "sys/log.h"
#define LOG_MODULE "App"
#define LOG_LEVEL LOG_LEVEL_DBG


/* Configuration */
// #define SEND_INTERVAL (10 * CLOCK_SECOND)

#if MAC_CONF_WITH_TSCH
#include "net/mac/tsch/tsch.h"
static linkaddr_t coordinator_addr =  {{ 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }};
#endif /* MAC_CONF_WITH_TSCH */

int MoteID=1;

static void
set_lladdr(void)
{
  linkaddr_t addr;

  memset(&addr, 0, sizeof(linkaddr_t));
  addr.u8[0] = MoteID & 0xff;
  addr.u8[1] = MoteID >> 8;
  linkaddr_set_node_addr(&addr);
}


/*---------------------------------------------------------------------------*/
PROCESS(sender_process, "Sender for RF process");
AUTOSTART_PROCESSES(&sender_process);


/*---------------------------------------------------------------------------*/
PROCESS_THREAD(sender_process, ev, data)
{
  // static struct etimer periodic_timer;
  set_lladdr();

  PROCESS_BEGIN();

  // etimer_set(&periodic_timer, SEND_INTERVAL);
  // while(1) {
  //   PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&periodic_timer));
  //   etimer_reset(&periodic_timer);
  // }

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
