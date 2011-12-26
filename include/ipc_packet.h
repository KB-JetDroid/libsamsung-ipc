/**
 * This file is part of libsamsung-ipc.
 *
 * Copyright (C) 2011 KB <kbjetdroid@gmail.com>
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

#ifndef __DEVICE_JET_IPC_H__
#define __DEVICE_JET_IPC_H__

#define MAX_SIGNLE_FRAME_DATA 	0xFF4

struct ipcPacketHeader {
	unsigned char reserved; //probably dummy
	unsigned char ipcPacketType;
} __attribute__((__packed__));

struct ipcNvPacket {
	struct ipcPacketHeader header;
	unsigned int size;
} __attribute__((__packed__));

struct ipcRequest {
	struct ipcPacketHeader header;
	unsigned char *respBuf;
} __attribute__((__packed__));


#endif
