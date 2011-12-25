/**
 * This file is part of libsamsung-ipc.
 *
 * Copyright (C) 2010-2011 Joerie de Gram <j.de.gram@gmail.com>
 *               2011 Simon Busch <morphis@gravedo.de>
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
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <stdbool.h>
#include <termios.h>
#include <fcntl.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pthread.h>
#include <getopt.h>

#include <radio.h>
#include <ipc_packet.h>


int get_nvm_data(void *data, unsigned int size)
{
	int fd, retval;
	char *nvmFile = "/efs/bml4";
	fd = open(nvmFile, O_RDONLY);

	printf("KB: file %s open status = %d\n", nvmFile, fd);
	retval = read(fd, data, size);
	printf("KB: file %s read status = %d\n", nvmFile, retval);

	if (fd > 0)
		close(fd);
	return 0;
}

void modem_response_ipc(struct ipc_client *client, struct modem_io *resp)
{
	printf("KB: Inside modem_response_ipc\n");
	int retval;
	struct ipcPacketHeader *rx_header;
	struct ipcRequest tx_packet;

	struct modem_io request;
    unsigned char *frame;
    unsigned char *payload;
    int frame_length;

	printf("Frame header = 0x%x\n Frame type = 0x%x\n Frame length = 0x%x\n", resp->magic, resp->cmd, resp->datasize);

	hexdump(resp->data, resp->datasize);

    rx_header = (struct ipcPacketHeader *)(resp->data);

	printf("KB: Packet type = 0x%x\n", rx_header->ipcPacketType);

    switch (rx_header->ipcPacketType)
    {
    	case 0x01:
    		printf("KB: ReadNvBackup IPC packet received\n");

    		struct ipcNvPacket *rx_packet;

    		rx_packet = (struct ipcNvPacket *)(resp->data);

    		printf("KB: size = 0x%x\n", rx_packet->size);

    		tx_packet.header.ipcPacketType = 0x03;
    		tx_packet.header.reserved = 0;
    		tx_packet.respBuf = NULL;

    		payload = malloc((rx_packet->size) + sizeof(struct ipcPacketHeader));

    		memcpy(payload, &tx_packet, sizeof(struct ipcPacketHeader));

    		retval = get_nvm_data(payload + sizeof(struct ipcPacketHeader), rx_packet->size);

    		request.magic = 0xCAFECAFE;
    		request.cmd = IPC_GROUP_IPC;
    		request.datasize = rx_packet->size +  sizeof(struct ipcPacketHeader);

    		request.data = payload;

    		_ipc_client_send(client, &request);

    		break;

    	default :
    		printf("KB: Packet type 0x%x is not yet handled\n", rx_header->ipcPacketType);

    		break;
    }

    printf("KB: Inside modem_response_fm leaving\n");

}
