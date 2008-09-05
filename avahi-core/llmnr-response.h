#ifndef foollmnrresponsehbar
#define foollmnrresponsehbar

/***
  Copyright (C) Sunil Kumar Ghai 2008 <sunilkrghai@gmail.com>

  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2 of the License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
  USA.
***/

typedef struct AvahiLLMNRResponseJob AvahiLLMNRResponseJob;
typedef struct AvahiLLMNRResponseScheduler AvahiLLMNRResponseScheduler;

#include <avahi-common/llist.h>
#include <avahi-common/timeval.h>

#include "iface.h"
#include "dns.h"

struct AvahiLLMNRResponseJob {
    AvahiLLMNRResponseScheduler *s;

    AvahiTimeEvent *time_event;
    AvahiDnsPacket *reply;

    AvahiAddress address;
    uint16_t port;

    AVAHI_LLIST_FIELDS(AvahiLLMNRResponseJob, jobs);
};

struct AvahiLLMNRResponseScheduler {
    AvahiInterface *interface;
    AvahiTimeEventQueue *time_event_queue;

    AVAHI_LLIST_HEAD(AvahiLLMNRResponseJob, jobs);
};

AvahiLLMNRResponseScheduler *avahi_llmnr_response_scheduler_new(AvahiInterface *i);
void avahi_llmnr_response_scheduler_free(AvahiLLMNRResponseScheduler *s);
void avahi_llmnr_response_scheduler_clear(AvahiLLMNRResponseScheduler *s);

int avahi_post_llmnr_response(AvahiLLMNRResponseScheduler *s, AvahiDnsPacket *p, const AvahiAddress *a, uint16_t port);
void avahi_llmnr_response_job_free(AvahiLLMNRResponseScheduler *s, AvahiLLMNRResponseJob *rj);

#endif

