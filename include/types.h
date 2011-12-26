/**
 * This file is part of libsamsung-ipc.
 *
 * Copyright (C) 2010-2011 Joerie de Gram <j.de.gram@gmail.com>
 *
 * Modified for Jet - KB <kbjetdroid@gmail.com>
 *
 * libsamsung-ipc is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * libsamsung-ipc is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libsamsung-ipc.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef __TYPES_H__
#define __TYPES_H__

#include "call.h"
#include "disp.h"
#include "gen.h"
#include "misc.h"
#include "net.h"
#include "sec.h"
#include "sms.h"
#include "pwr.h"
#include "gprs.h"
#include "fm_packet.h"
#include "ipc_packet.h"

/* AP -> Baseband */
#define IPC_TYPE_EXEC                               0x01
#define IPC_TYPE_GET                                0x02
#define IPC_TYPE_SET                                0x03
#define IPC_TYPE_CFRM                               0x04
#define IPC_TYPE_EVENT                              0x05

/* Baseband -> AP */
#define IPC_TYPE_INDI                               0x01
#define IPC_TYPE_RESP                               0x02
#define IPC_TYPE_NOTI                               0x03

/* Message groups for Jet*/
#if defined(DEVICE_JET)
#define IPC_GROUP_SIM                               0x02
#define IPC_GROUP_PROTO                             0x03
#define IPC_GROUP_TAPI                              0x04
#define IPC_GROUP_FM                                0x06
#define IPC_GROUP_SND                               0x09
#define IPC_GROUP_VID                               0x0B
#define IPC_GROUP_VIDCAP                            0x0A
#define IPC_GROUP_BOOT                              0x0F
#define IPC_GROUP_MULTI_DBG                         0x19
#define IPC_GROUP_DIAG                              0x1A
#define IPC_GROUP_MULTI_FIFO                        0x1E
#define IPC_GROUP_RSD                               0x2E
#define IPC_GROUP_NV                                0x31
#define IPC_GROUP_LBS                               0x32
#define IPC_GROUP_QMS                               0x33
#define IPC_GROUP_DSM                               0x34
#define IPC_GROUP_BT                                0x91
#define IPC_GROUP_TM                                0x92
#define IPC_GROUP_IPC                               0x93
#define IPC_GROUP_RBM                               0x94
#define IPC_GROUP_DM                                0x95
#define IPC_GROUP_SSB                               0x96
#else
/* Message groups */
#define IPC_GROUP_PWR                               0x01
#define IPC_GROUP_CALL                              0x02
#define IPC_GROUP_SMS                               0x04
#define IPC_GROUP_SEC                               0x05
#define IPC_GROUP_PB                                0x06
#define IPC_GROUP_DISP                              0x07
#define IPC_GROUP_NET                               0x08
#define IPC_GROUP_SND                               0x09
#define IPC_GROUP_MISC                              0x0A
#define IPC_GROUP_SVC                               0x0B
#define IPC_GROUP_SS                                0x0C
#define IPC_GROUP_GPRS                              0x0D
#define IPC_GROUP_SAT                               0x0E
#define IPC_GROUP_CFG                               0x0F
#define IPC_GROUP_IMEI                              0x10
#define IPC_GROUP_GPS                               0x11
#define IPC_GROUP_SAP                               0x12
#define IPC_GROUP_GEN                               0x80
#endif

/* Pb */
#define IPC_PB_ACCESS                               0x0601
#define IPC_PB_STORAGE                              0x0602
#define IPC_PB_STORAGE_LIST                         0x0603
#define IPC_PB_ENTRY_INFO                           0x0604
#define IPC_PB_CAPABILITY_INFO                      0x0605

/* SND */

#define IPC_SND_SPKR_VOLUME_CTRL                    0x9001
#define IPC_SND_MIC_MUTE_CTRL                       0x0902
#define IPC_SND_AUDIO_PATH_CTRL                     0x0903
#define IPC_SND_RINGBACK_TONE_CTRL                  0x0908
#define IPC_SND_CLOCK_CTRL                          0x0909

/* SS */
#define IPC_SS_WAITING                              0x0C01
#define IPC_SS_CLI                                  0x0C02
#define IPC_SS_BARRING                              0x0C03
#define IPC_SS_BARRING_PW                           0x0C04
#define IPC_SS_FORWARDING                           0x0C05
#define IPC_SS_INFO                                 0x0C06
#define IPC_SS_MANAGE_CALL                          0x0C07
#define IPC_SS_USSD                                 0x0C08
#define IPC_SS_AOC                                  0x0C09
#define IPC_SS_RELEASE_COMPLETE                     0x0C0A

/* Sat */
#define IPC_SAT_PROFILE_DOWNLOAD                    0x0E01
#define IPC_SAT_ENVELOPE_CMD                        0x0E02
#define IPC_SAT_PROACTIVE_CMD                       0x0E03
#define IPC_SAT_TERMINATE_USAT_SESSION              0x0E04
#define IPC_SAT_EVENT_DOWNLOAD                      0x0E05
#define IPC_SAT_PROVIDE_LOCAL_INFO                  0x0E06
#define IPC_SAT_POLLING                             0x0E07
#define IPC_SAT_REFRESH                             0x0E08
#define IPC_SAT_SETUP_EVENT_LIST                    0x0E09
#define IPC_SAT_CALL_CONTROL_RESULT                 0x0E0A
#define IPC_SAT_IMAGE_CLUT                          0x0E0B
#define IPC_SAT_CALL_PROCESSING                     0x0E0C

/* IMEI */
#define IPC_IMEI_START                              0x1001
#define IPC_IMEI_CHECK_DEVICE_INFO                  0x1002

#endif

// vim:ts=4:sw=4:expandtab
