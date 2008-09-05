#ifndef fooverifyhbar
#define fooverifyhbar

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

typedef struct AvahiLLMNREntryVerify AvahiLLMNREntryVerify;
typedef struct AvahiVerifierData AvahiVerifierData;

#include <avahi-common/address.h>

#include "internal.h"
#include "publish.h"

/* State of the verifier */
typedef enum {
    AVAHI_VERIFYING,
    AVAHI_CONFLICT,
    AVAHI_VERIFIED
} AvahiLLMNREntryVerifyState;

/* AvahiLLMNREntryVerify */
struct AvahiLLMNREntryVerify {
    AvahiServer *s;
    AvahiInterface *interface;
    AvahiEntry *e;

    AvahiLLMNRQuery *lq;
    AvahiLLMNREntryVerifyState state;

    AVAHI_LLIST_FIELDS(AvahiLLMNREntryVerify, by_interface);
    AVAHI_LLIST_FIELDS(AvahiLLMNREntryVerify, by_entry);
};

/* This structure is passed as userdata in AvahiLLMNRQuery */
struct AvahiVerifierData{

    AvahiLLMNREntryVerify *ev;
    const AvahiAddress *address;
    int t_bit;
};

void avahi_verify_interface(AvahiServer *s, AvahiInterface *i);
void avahi_verify_entry(AvahiServer *s, AvahiEntry *e);
void avahi_verify_group(AvahiServer *s, AvahiSEntryGroup *g);

void avahi_llmnr_entry_return_to_initial_state(AvahiServer *s, AvahiEntry *e, AvahiInterface *i);

/* returns -1 if there is no verifier or state is AVAHI_CONFLICT for this entry */
/* returns 1 if state is AVAHI_VERFYING */
/* return 0 if state is AVHAI_VERIFIED */
int avahi_llmnr_entry_is_verifying(AvahiServer *s, AvahiEntry *e, AvahiInterface *i);
/* AvahiLLMNREntryVerify* get_verifier(AvahiSLLMNR *sl, AvahiInterface *i, AvahiEntry *e)*/

void avahi_reverify_entry(AvahiServer *s, AvahiEntry *e);
AvahiLLMNREntryVerifyState avahi_llmnr_entry_verify_state(AvahiLLMNREntryVerify *ev);
void avahi_remove_verifiers(AvahiServer *s, AvahiEntry *e);
void avahi_remove_interface_verifiers(AvahiServer *s, AvahiInterface *i);

#endif /* fooverifyhbar */
