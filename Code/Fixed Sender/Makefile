CONTIKI_PROJECT = sender
all: $(CONTIKI_PROJECT)

CONTIKI = /home/saptarshi/Ericsson-SICS-SDR/docker/contiki-ng

PLATFORMS_EXCLUDE = nrf52dk

#use this to enable TSCH: MAKE_MAC = MAKE_MAC_TSCH
MAKE_MAC ?= MAKE_MAC_CSMA
MAKE_NET ?= MAKE_NET_IPV6
include $(CONTIKI)/Makefile.include
