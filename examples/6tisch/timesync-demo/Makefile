CONTIKI_PROJECT = node
all: $(CONTIKI_PROJECT)

CONTIKI=../../..

PLATFORMS_EXCLUDE = sky nrf52dk native

# Our target is LAUNCHPAD CC1352P1 with simplelink environment
TARGET ?= cc26x0-cc13x0
BOARD  ?= launchpad/cc1352


MAKE_ORCHESTRA_SENDER_BASED ?= 1

# Turn on the shell (command line on serial port) 
MODULES += os/services/shell
MODULES += os/net/app-layer/ota
MODULES += os/services/orchestra

MAKE_MAC = MAKE_MAC_TSCH

# Activate RPL classic Storing mode when using a sender based schedule
ifeq ($(MAKE_ORCHESTRA_SENDER_BASED), 1)
CFLAGS += -DWS4_TSCH_SENDER_BASED=1
MAKE_ROUTING = MAKE_ROUTING_RPL_CLASSIC
MODULES += os/net/routing/rpl-classic
endif

include $(CONTIKI)/Makefile.dir-variables


include $(CONTIKI)/Makefile.include
