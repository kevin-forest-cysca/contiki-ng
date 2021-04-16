/*
 * Copyright (c) 2015, SICS Swedish ICT.
 * Copyright (c) 2018, University of Bristol - http://www.bristol.ac.uk
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
 */


#ifndef __PROJECT_CONF_H__
#define __PROJECT_CONF_H__

/*
 * Signal to the rest of the code that we are building with OTA extensions
 * The platform will be responsible to generate an offset firmware and to
 * reserve space for metadata.
 */
//#define OTA 1

#define SERIAL_LINE_CONF_BUFSIZE  128
#define CC26XX_UART_CONF_BAUD_RATE  460800

/*******************************************************/
/******************* 32 KHz crystal configuration ******/
/*******************************************************/
#define SET_CCFG_MODE_CONF_SCLK_LF_OPTION            0x2        // LF XOSC : EXTERNAL CRYSTAL
//#define SET_CCFG_MODE_CONF_SCLK_LF_OPTION            0x3        // LF RCOSC : INTERNAL RC CRYSTAL

/*******************************************************/
/******************* Software configuration ************/
/*******************************************************/

// Make sure WATCHDOG is disabled else will reset
#define WATCHDOG_CONF_DISABLE 1
#define WATCHDOG_CONF_TIMEOUT_MS  30000

// Disable bootloader
#define CCFG_CONF_ROM_BOOTLOADER_ENABLE 0

//Setup heap mem size (for dynamic memory allocation)
#define HEAPMEM_CONF_ARENA_SIZE 0x2000 //4096 bytes

/*******************************************************/
/******************* Packet configuration **************/
/*******************************************************/
//Enable packet fragmentation
#define SICSLOWPAN_CONF_FRAG 1

//Max packet length.
//Minimum 116 for TSCH.
//Tests showed that messages are dropped if not at least 50+max payload
#define UIP_CONF_BUFFER_SIZE 1280  //default is 1280
//#define RF_CONF_RX_BUF_SIZE               250
//#define PACKETBUF_CONF_SIZE               250

// We use this parameter to turn on retries
#define UIP_CONF_TAG_TC_WITH_VARIABLE_RETRANSMISSIONS 1

// Increase queue lenght from 8 to 32
#define QUEUEBUF_CONF_NUM 32

/******************************************************/
/******************* Radio configuration **************/
/******************************************************/
// Enable High power for TX (+20 DBM)
// DEFAULT : 1 (ENABLED)
#define RF_CONF_TXPOWER_BOOST_MODE 0

// ACCEPTABLE RSSI TRESHOLD FOR PROP MODE DRIVER
// DEFAULT : 0X97 (-105 DBM)
#define PROP_MODE_CONF_CCA_RSSI_THRESHOLD 0x97

//Use 915Mhz
#define DOT_15_4G_CONF_FREQ_BAND_ID DOT_15_4G_FREQ_BAND_915 //DOT_15_4G_FREQ_BAND_915 //7

//use only 1 channel (so no channel hopping)
/* 1 channel, sequence length 1 */
#define TSCH_CONF_DEFAULT_HOPPING_SEQUENCE      TSCH_HOPPING_SEQUENCE_1_1
#define TSCH_CONF_JOIN_HOPPING_SEQUENCE         TSCH_HOPPING_SEQUENCE_1_1

/*******************************************************/
/******************* Configure TSCH ********************/
/*******************************************************/
// Set to enable TSCH security
// DEFAULT : 0 (NOT ENABLED)
#ifndef WITH_SECURITY
#define WITH_SECURITY 0
#endif

/* IEEE802.15.4 PANID */
#define IEEE802154_CONF_PANID 0x81a6

/* Do not start TSCH at init, wait for NETSTACK_MAC.on() */
#define TSCH_CONF_AUTOSTART 0
//#define TSCH_CONF_CCA_ENABLED 1     //Activate Collision Avoidance

/* 6TiSCH minimal schedule length.
 * Larger values result in less frequent active slots: reduces capacity and saves energy. */
#define TSCH_SCHEDULE_CONF_DEFAULT_LENGTH 3 //11

// Turn this ON to enable tsch debugging messages for each slot
//#define TSCH_LOG_CONF_PER_SLOT                     0

#if WITH_SECURITY
/* Enable security */
#define LLSEC802154_CONF_ENABLED 1
#endif /* WITH_SECURITY */

// TSCH BEACON time interval
//#define TSCH_CONF_EB_PERIOD (4 * CLOCK_SECOND)
//#define TSCH_CONF_MAX_EB_PERIOD (4 * CLOCK_SECOND)

// Turn ON MAC retries to 3
#define TSCH_CONF_MAC_MAX_FRAME_RETRIES       16


//Number of other nodes each node can speak to, including parent
#define NBR_TABLE_CONF_MAX_NEIGHBORS    9

//Max number of nodes in the system
#define NETSTACK_MAX_ROUTE_ENTRIES      128

#if WS4_TSCH_SENDER_BASED
#undef NETSTACK_CONF_ROUTING
#define NETSTACK_CONF_ROUTING                       rpl_classic_driver

#undef ROUNTING_CONF_RPL_LITE
#define ROUTING_CONF_RPL_LITE                       0
#define ROUNTING_CONF_RPL_CLASSIC                   1

#define RPL_CONF_WITH_NON_STORING                   0
#define RPL_CONF_MOP                                RPL_MOP_STORING_NO_MULTICAST    //We could use multicast later on

#define RPL_CONF_MAX_INSTANCES                      1

#define ORCHESTRA_CONF_RULES    { &eb_per_time_source, \
                                  &unicast_per_neighbor_rpl_storing, \
                                  &default_common }

#define ORCHESTRA_CONF_UNICAST_SENDER_BASED 1

/******************************************************/
/******************* Configure RPL Classic********************/
/******************************************************/
//#define RPL_CONF_DIO_INTERVAL_MIN                       GetScenarioValue(SCENARIO_VAR_RPL_DIO_INTERVAL_MIN)
//#define RPL_CONF_DIO_INTERVAL_DOUBLINGS                 GetScenarioValue(SCENARIO_VAR_RPL_DIO_INTERVAL_DOUBLINGS)
//#define RPL_CONF_DIS_INTERVAL                           GetScenarioValue(SCENARIO_VAR_RPL_DIS_INTERVAL)
//#define RPL_CONF_PROBING_INTERVAL                       GetScenarioValue(SCENARIO_VAR_RPL_PROBING_INTERVAL)
//#define RPL_CONF_DEFAULT_LIFETIME_UNIT                  GetScenarioValue(SCENARIO_VAR_RPL_DEFAULT_LIFETIME_UNIT)
//#define RPL_CONF_DEFAULT_LIFETIME                       GetScenarioValue(SCENARIO_VAR_RPL_DEFAULT_LIFETIME)
//#define RPL_CONF_DIO_INTERVAL_MIN                       12 // 2^(12) = 4.096 s
//#define RPL_CONF_DIO_INTERVAL_DOUBLINGS                 1  // 2^(12+2) = 16.384 s
//#define RPL_CONF_DIS_INTERVAL                           5 // 5.0 s
#define RPL_CONF_DIS_INTERVAL                             30 // 30.0 s
//#define RPL_CONF_PROBING_INTERVAL                       15 * CLOCK_SECOND// 15.0 s
//#define RPL_CONF_DEFAULT_LIFETIME                       RPL_INFINITE_LIFETIME // Infinite duration
#define RPL_CONF_DAO_RETRANSMISSION_TIMEOUT               25 * CLOCK_SECOND //10
#define RPL_CONF_WITH_DAO_ACK                             1

#else

/******************************************************/
/******************* Configure RPL LITE********************/
/******************************************************/
//#define RPL_CONF_DIO_INTERVAL_MIN                       GetScenarioValue(SCENARIO_VAR_RPL_DIO_INTERVAL_MIN)
//#define RPL_CONF_DIO_INTERVAL_DOUBLINGS                 GetScenarioValue(SCENARIO_VAR_RPL_DIO_INTERVAL_DOUBLINGS)
//#define RPL_CONF_DIS_INTERVAL                           GetScenarioValue(SCENARIO_VAR_RPL_DIS_INTERVAL)
//#define RPL_CONF_PROBING_INTERVAL                       GetScenarioValue(SCENARIO_VAR_RPL_PROBING_INTERVAL)
//#define RPL_CONF_DEFAULT_LIFETIME_UNIT                  GetScenarioValue(SCENARIO_VAR_RPL_DEFAULT_LIFETIME_UNIT)
//#define RPL_CONF_DEFAULT_LIFETIME                       GetScenarioValue(SCENARIO_VAR_RPL_DEFAULT_LIFETIME)
//#define RPL_CONF_DIO_INTERVAL_MIN                       12 // 2^(12) = 4.096 s
//#define RPL_CONF_DIO_INTERVAL_DOUBLINGS                 1  // 2^(12+2) = 16.384 s
//#define RPL_CONF_DIS_INTERVAL                           5 * CLOCK_SECOND // 5.0 s
#define RPL_CONF_DIS_INTERVAL                             30 * CLOCK_SECOND // 30.0 s
//#define RPL_CONF_PROBING_INTERVAL                       15 * CLOCK_SECOND// 15.0 s
//#define RPL_CONF_DEFAULT_LIFETIME                       RPL_INFINITE_LIFETIME // Infinite duration
#define RPL_CONF_DAO_RETRANSMISSION_TIMEOUT               25 * CLOCK_SECOND //10
#define RPL_CONF_WITH_DAO_ACK                             1

#endif



/*******************************************************/
/******************* Configure Logging *****************/
/*******************************************************/
#define LOG_CONF_LEVEL_MAIN                        LOG_LEVEL_INFO
#define LOG_CONF_LEVEL_RPL                         LOG_LEVEL_WARN
#define LOG_CONF_LEVEL_TCPIP                       LOG_LEVEL_WARN
#define LOG_CONF_LEVEL_IPV6                        LOG_LEVEL_ERR
#define LOG_CONF_LEVEL_6LOWPAN                     LOG_LEVEL_WARN
#define LOG_CONF_LEVEL_MAC                         LOG_LEVEL_WARN
//#define LOG_CONF_LEVEL_FRAMER                      LOG_LEVEL_NONE


//#define TI_UART_CONF_BAUD_RATE 38400

#endif /* __PROJECT_CONF_H__ */
