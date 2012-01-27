/**
 * This file is part of libsamsung-ipc.
 *
 * Copyright (C) 2011-2012 KB <kbjetdroid@gmail.com>
 *
 * Implemented as per the Mocha AP-CP protocol analysis done by Dominik Marszk
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

#ifndef __IPC_H__
#define __IPC_H__

struct ipcPacketHeader {
	uint8_t reserved; //probably dummy
	uint8_t ipcPacketType;
} __attribute__((__packed__));

struct ipcNvPacket {
	struct ipcPacketHeader header;
	uint32_t size;
} __attribute__((__packed__));

struct ipcPMICPacket {
	struct ipcPacketHeader header;
	uint32_t unk1;
	uint32_t unk2;
	uint32_t value;
} __attribute__((__packed__));

struct ipcRequest {
	struct ipcPacketHeader header;
	uint8_t *respBuf;
} __attribute__((__packed__));

void modem_response_ipc(struct ipc_client *client, struct modem_io *resp);

#endif
