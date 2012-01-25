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

/*
 * TODO: Implement handling of all the IPC packets
 *
 */

char *nvmFile = "/efs/bml4";

char *jetFWVersion = "S800MPOJB1";

/*
 * TODO: Read sound config data from file
 */
//	File									Field	Default	Hex
int RCV_MSM_Data[] =	{	-1900	,	//	<RX_CALL_VOL>	-900	-0x384
							-1900	,	//		-900	-0x384
							-1500	,	//		-600	-0x258
							-1500	,	//		-600	-0x258
							-1000	,	//		-300	-0x12C
							-1000	,	//		-300	-0x12C
							-700	,	//		0	0x0
							-700	,	//		0	0x0
							-400	,	//		300	0x12C
							-400	,	//		300	0x12C
							-100	,	//		600	0x258
							-100	,	//		600	0x258
							500	,	//		900	0x384
							500	,	//		900	0x384
							-3200	,	//	<RX_DTMF_VOL>	-4200	-0x1068
							-3200	,	//		-4000	-0xFA0
							-2900	,	//		-3800	-0xED8
							-2900	,	//		-3600	-0xE10
							-2600	,	//		-3400	-0xD48
							-2600	,	//		-3200	-0xC80
							-2300	,	//		-3000	-0xBB8
							-2300	,	//		-2800	-0xAF0
							-2000	,	//		-2600	-0xA28
							-2000	,	//		-2400	-0x960
							-1800	,	//		-2200	-0x898
							-1800	,	//		-2000	-0x7D0
							-1600	,	//		-1800	-0x708
							-1600	,	//		-1600	-0x640
							5	,	//	<CODEC_GAIN>	4	0x4
							-12	,	//		-12	-0xC
							5	,	//		4	0x4
							3	,	//		5	0x5
							-84	,	//		-12	-0xC
							10	,	//		10	0xA
							1	,	//	<ECHO_CANCELLER>	1	0x1
							1	,	//	<TX_AGC>	1	0x1
							8192	,	//		0	0x0
							0	,	//		65535	0xFFFF
							3200	,	//		1920	0x780
							65408	,	//		65434	0xFF9A
							7040	,	//		6924	0x1B0C
							32768	,	//		62259	0xF333
							1	,	//	<RX_AGC>	1	0x1
							8192	,	//		32613	0x7F65
							0	,	//		0	0x0
							3840	,	//		1920	0x780
							65296	,	//		65434	0xFF9A
							7936	,	//		6924	0x1B0C
							53248	,	//		62259	0xF333
							200	,	//	<TX_FILTER>	0	0x0
							231	,	//		0	0x0
							65437	,	//		0	0x0
							65157	,	//		0	0x0
							63711	,	//		0	0x0
							64443	,	//		0	0x0
							20569	,	//		0	0x0
							260	,	//	<RX_FILTER>	0	0x0
							378	,	//		0	0x0
							284	,	//		0	0x0
							65437	,	//		0	0x0
							64691	,	//		0	0x0
							64811	,	//		0	0x0
							18175	,	//		0	0x0
							32767	,	//		32767	0x7FFF
							2048	,	//		2048	0x800
							32767	,	//		32767	0x7FFF
							4255	,	//		4255	0x109F
							0	,	//		0	0x0
							500	,	//		500	0x1F4
							2048	,	//		2048	0x800
							8192	,	//		8192	0x2000
							8192	,	//		8192	0x2000
							250	,	//		250	0xFA
							70	,	//		70	0x46
							1	,	//		1	0x1
							767	,	//		767	0x2FF
							64	,	//		64	0x40
							32	,	//		32	0x20
							18000	,	//		18000	0x4650
							64	,	//		64	0x40
							16800	,	//		16800	0x41A0
							2048	,	//		2048	0x800
							99	,	//		99	0x63
							20000	,	//		20000	0x4E20
							20000	,	//		20000	0x4E20
							1	,	//		1	0x1
							22000	,	//		22000	0x55F0
							10000	,	//		10000	0x2710
							0	,	//		0	0x0
							200	,	//		200	0xC8
							256	,	//		256	0x100
							1024	,	//		1024	0x400
							512	,	//		512	0x200
							1024	,	//		1024	0x400
							768	,	//		768	0x300
							486	,	//		486	0x1E6
							400	,	//		400	0x190
							10361	,	//		10361	0x2879
							450	,	//		450	0x1C2
							12000	,	//		12000	0x2EE0
							4000	};	//		4000	0xFA0
int EAR_MSM_Data[] =	{	-1200	,	//	<RX_CALL_VOL>	-1500	-0x5DC
							-1200	,	//		-1500	-0x5DC
							-900	,	//		-1200	-0x4B0
							-900	,	//		-1200	-0x4B0
							-600	,	//		-900	-0x384
							-600	,	//		-900	-0x384
							-300	,	//		-600	-0x258
							-300	,	//		-600	-0x258
							0	,	//		-300	-0x12C
							0	,	//		-300	-0x12C
							300	,	//		0	0x0
							300	,	//		0	0x0
							500	,	//		300	0x12C
							500	,	//		300	0x12C
							-4800	,	//	<RX_DTMF_VOL>	-4800	-0x12C0
							-4800	,	//		-4800	-0x12C0
							-4600	,	//		-4600	-0x11F8
							-4600	,	//		-4600	-0x11F8
							-4200	,	//		-4200	-0x1068
							-4200	,	//		-4200	-0x1068
							-3900	,	//		-3900	-0xF3C
							-3900	,	//		-3900	-0xF3C
							-3600	,	//		-3600	-0xE10
							-3600	,	//		-3600	-0xE10
							-3200	,	//		-3200	-0xC80
							-3200	,	//		-3200	-0xC80
							-3000	,	//		-3000	-0xBB8
							-3000	,	//		-3000	-0xBB8
							8	,	//	<CODEC_GAIN>	0	0x0
							-12	,	//		-12	-0xC
							8	,	//		10	0xA
							2	,	//		-8	-0x8
							-84	,	//		-84	-0x54
							6	,	//		6	0x6
							2	,	//	<ECHO_CANCELLER>	2	0x2
							1	,	//	<TX_AGC>	1	0x1
							8192	,	//		0	0x0
							0	,	//		65535	0xFFFF
							3200	,	//		1920	0x780
							65440	,	//		65434	0xFF9A
							8448	,	//		6924	0x1B0C
							32768	,	//		62259	0xF333
							1	,	//	<RX_AGC>	1	0x1
							16345	,	//		32613	0x7F65
							0	,	//		0	0x0
							3200	,	//		1920	0x780
							65317	,	//		65434	0xFF9A
							7680	,	//		6924	0x1B0C
							40960	,	//		62259	0xF333
							65078	,	//	<TX_FILTER>	0	0x0
							355	,	//		0	0x0
							64993	,	//		0	0x0
							201	,	//		0	0x0
							63486	,	//		0	0x0
							62712	,	//		0	0x0
							17630	,	//		0	0x0
							0	,	//	<RX_FILTER>	0	0x0
							65505	,	//		0	0x0
							7	,	//		0	0x0
							160	,	//		0	0x0
							277	,	//		0	0x0
							1071	,	//		0	0x0
							13565	,	//		0	0x0
							32767	,	//		32767	0x7FFF
							2048	,	//		2048	0x800
							32767	,	//		32767	0x7FFF
							5279	,	//		5279	0x149F
							0	,	//		0	0x0
							20	,	//		20	0x14
							2048	,	//		2048	0x800
							8192	,	//		8192	0x2000
							8192	,	//		8192	0x2000
							512	,	//		512	0x200
							60	,	//		60	0x3C
							1	,	//		1	0x1
							767	,	//		767	0x2FF
							64	,	//		64	0x40
							32	,	//		32	0x20
							10000	,	//		10000	0x2710
							64	,	//		64	0x40
							16800	,	//		16800	0x41A0
							2048	,	//		2048	0x800
							99	,	//		99	0x63
							20000	,	//		20000	0x4E20
							20000	,	//		20000	0x4E20
							1	,	//		1	0x1
							18000	,	//		18000	0x4650
							3000	,	//		3000	0xBB8
							0	,	//		0	0x0
							300	,	//		300	0x12C
							300	,	//		300	0x12C
							1024	,	//		1024	0x400
							512	,	//		512	0x200
							512	,	//		512	0x200
							768	,	//		768	0x300
							600	,	//		600	0x258
							400	,	//		400	0x190
							7336	,	//		7336	0x1CA8
							900	,	//		900	0x384
							13000	,	//		13000	0x32C8
							4000	};	//		4000	0xFA0
int SPK_MSM_Data[] =	{	-900	,	//	<RX_CALL_VOL>	-900	-0x384
							-900	,	//		-900	-0x384
							-600	,	//		-600	-0x258
							-600	,	//		-600	-0x258
							-300	,	//		-300	-0x12C
							-300	,	//		-300	-0x12C
							0	,	//		0	0x0
							0	,	//		0	0x0
							300	,	//		300	0x12C
							300	,	//		300	0x12C
							600	,	//		600	0x258
							600	,	//		600	0x258
							900	,	//		900	0x384
							900	,	//		900	0x384
							-3000	,	//	<RX_DTMF_VOL>	-4200	-0x1068
							-2900	,	//		-4000	-0xFA0
							-2800	,	//		-3800	-0xED8
							-2700	,	//		-3600	-0xE10
							-2600	,	//		-3400	-0xD48
							-2500	,	//		-3200	-0xC80
							-2400	,	//		-3000	-0xBB8
							-2300	,	//		-2800	-0xAF0
							-2200	,	//		-2600	-0xA28
							-2100	,	//		-2400	-0x960
							-2000	,	//		-2200	-0x898
							-1900	,	//		-2000	-0x7D0
							-1800	,	//		-1800	-0x708
							-1700	,	//		-1600	-0x640
							10	,	//	<CODEC_GAIN>	7	0x7
							-12	,	//		-12	-0xC
							6	,	//		8	0x8
							2	,	//		5	0x5
							-84	,	//		-84	-0x54
							6	,	//		6	0x6
							4	,	//	<ECHO_CANCELLER>	4	0x4
							1	,	//	<TX_AGC>	1	0x1
							9191	,	//		32613	0x7F65
							0	,	//		0	0x0
							3328	,	//		1920	0x780
							65360	,	//		65434	0xFF9A
							8448	,	//		6924	0x1B0C
							32768	,	//		62259	0xF333
							1	,	//	<RX_AGC>	0	0x0
							12983	,	//		32613	0x7F65
							0	,	//		0	0x0
							2944	,	//		1920	0x780
							65306	,	//		65434	0xFF9A
							7424	,	//		6924	0x1B0C
							49152	,	//		62259	0xF333
							653	,	//	<TX_FILTER>	0	0x0
							1126	,	//		0	0x0
							331	,	//		0	0x0
							65193	,	//		0	0x0
							60491	,	//		0	0x0
							59071	,	//		0	0x0
							32767	,	//		0	0x0
							0	,	//	<RX_FILTER>	0	0x0
							0	,	//		0	0x0
							0	,	//		0	0x0
							0	,	//		0	0x0
							0	,	//		0	0x0
							0	,	//		0	0x0
							0	,	//		0	0x0
							32767	,	//		32767	0x7FFF
							2048	,	//		2048	0x800
							32767	,	//		32767	0x7FFF
							6047	,	//		6047	0x179F
							0	,	//		0	0x0
							20	,	//		20	0x14
							2048	,	//		2048	0x800
							8192	,	//		8192	0x2000
							18000	,	//		18000	0x4650
							512	,	//		512	0x200
							150	,	//		150	0x96
							1	,	//		1	0x1
							400	,	//		400	0x190
							64	,	//		64	0x40
							32	,	//		32	0x20
							14000	,	//		14000	0x36B0
							64	,	//		64	0x40
							16800	,	//		16800	0x41A0
							2048	,	//		2048	0x800
							99	,	//		99	0x63
							20000	,	//		20000	0x4E20
							20000	,	//		20000	0x4E20
							1	,	//		1	0x1
							19000	,	//		19000	0x4A38
							8000	,	//		8000	0x1F40
							0	,	//		0	0x0
							220	,	//		220	0xDC
							400	,	//		400	0x190
							7680	,	//		7680	0x1E00
							600	,	//		600	0x258
							1024	,	//		1024	0x400
							768	,	//		768	0x300
							486	,	//		486	0x1E6
							400	,	//		400	0x190
							8192	,	//		8192	0x2000
							700	,	//		700	0x2BC
							6000	,	//		6000	0x1770
							4000	};	//		4000	0xFA0
int BTH_MSM_Data[] =	{	400	,	//	<RX_CALL_VOL>	400	0x190
							400	,	//		400	0x190
							400	,	//		400	0x190
							400	,	//		400	0x190
							400	,	//		400	0x190
							400	,	//		400	0x190
							400	,	//		400	0x190
							400	,	//		400	0x190
							400	,	//		400	0x190
							400	,	//		400	0x190
							400	,	//		400	0x190
							400	,	//		400	0x190
							400	,	//		400	0x190
							400	,	//		400	0x190
							-4200	,	//	<RX_DTMF_VOL>	-4200	-0x1068
							-4000	,	//		-4000	-0xFA0
							-3800	,	//		-3800	-0xED8
							-3600	,	//		-3600	-0xE10
							-3400	,	//		-3400	-0xD48
							-3200	,	//		-3200	-0xC80
							-3000	,	//		-3000	-0xBB8
							-2800	,	//		-2800	-0xAF0
							-2600	,	//		-2600	-0xA28
							-2400	,	//		-2400	-0x960
							-2200	,	//		-2200	-0x898
							-2000	,	//		-2000	-0x7D0
							-1800	,	//		-1800	-0x708
							-1600	,	//		-1600	-0x640
							9	,	//	<CODEC_GAIN>	3	0x3
							-12	,	//		-12	-0xC
							10	,	//		0	0x0
							0	,	//		0	0x0
							-84	,	//		-84	-0x54
							6	,	//		6	0x6
							5	,	//	<ECHO_CANCELLER>	5	0x5
							1	,	//	<TX_AGC>	1	0x1
							9191	,	//		8192	0x2000
							0	,	//		0	0x0
							1408	,	//		1792	0x700
							65472	,	//		65408	0xFF80
							8832	,	//		9600	0x2580
							34048	,	//		32768	0x8000
							1	,	//	<RX_AGC>	1	0x1
							8192	,	//		8192	0x2000
							0	,	//		0	0x0
							4480	,	//		4480	0x1180
							65408	,	//		65282	0xFF02
							9600	,	//		9600	0x2580
							32768	,	//		32768	0x8000
							0	,	//	<TX_FILTER>	0	0x0
							0	,	//		0	0x0
							0	,	//		0	0x0
							0	,	//		0	0x0
							0	,	//		0	0x0
							0	,	//		0	0x0
							0	,	//		0	0x0
							0	,	//	<RX_FILTER>	0	0x0
							0	,	//		0	0x0
							0	,	//		0	0x0
							0	,	//		0	0x0
							0	,	//		0	0x0
							0	,	//		0	0x0
							0	,	//		0	0x0
							32767	,	//		32767	0x7FFF
							2048	,	//		2048	0x800
							8667	,	//		8667	0x21DB
							5279	,	//		5279	0x149F
							0	,	//		0	0x0
							120	,	//		120	0x78
							2048	,	//		2048	0x800
							8192	,	//		8192	0x2000
							8192	,	//		8192	0x2000
							250	,	//		250	0xFA
							160	,	//		160	0xA0
							2	,	//		2	0x2
							767	,	//		767	0x2FF
							64	,	//		64	0x40
							32	,	//		32	0x20
							14711	,	//		14711	0x3977
							64	,	//		64	0x40
							16800	,	//		16800	0x41A0
							2048	,	//		2048	0x800
							99	,	//		99	0x63
							20000	,	//		20000	0x4E20
							20000	,	//		20000	0x4E20
							2	,	//		2	0x2
							19000	,	//		19000	0x4A38
							6000	,	//		6000	0x1770
							0	,	//		0	0x0
							256	,	//		256	0x100
							256	,	//		256	0x100
							1024	,	//		1024	0x400
							512	,	//		512	0x200
							6418	,	//		6418	0x1912
							768	,	//		768	0x300
							600	,	//		600	0x258
							400	,	//		400	0x190
							7336	,	//		7336	0x1CA8
							200	,	//		200	0xC8
							11605	,	//		11605	0x2D55
							256	};	//		256	0x100

int get_nvm_data(void *data, unsigned int size)
{
	int fd, retval;
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
		request.cmd = FIFO_PKT_DRV;
		request.datasize = rx_packet->size +  sizeof(struct ipcPacketHeader);

		request.data = payload;

		_ipc_client_send(client, &request);

		break;

	case 0x1C:
		printf("KB: PMIC IPC packet received\n");

		int retval;
		unsigned char params[3];
		struct ipcPMICPacket *pmic_packet;

		pmic_packet = (struct ipcPMICPacket *)(resp->data);

		printf("KB: PMIC value = 0x%x\n", pmic_packet->value);

		params[0] = 1;
		params[1] = 0x9B; //SIMLTTV;
		if (pmic_packet->value >= 0x7D0)
			params[2] = 0x2D;
		else
			params[2] = 0x15;

		retval = ipc_client_modem_operations(client, params, IOCTL_MODEM_PMIC);

		printf("KB: ioctl return value = 0x%x\n", retval);

		_ipc_client_send(client, resp);

		break;

	case 0x17:
		printf("KB: SoundSetRequest IPC packet received\n");

		struct ipcNvPacket *sndSetRequest_packet;

		sndSetRequest_packet = (struct ipcNvPacket *)(resp->data);

		printf("KB: size = 0x%x\n", sndSetRequest_packet->size);

		tx_packet.header.ipcPacketType = 0x1B;
		tx_packet.header.reserved = 0;
		tx_packet.respBuf = NULL;

		payload = malloc((0x194) + sizeof(struct ipcPacketHeader));

		memcpy(payload, &tx_packet, sizeof(struct ipcPacketHeader));

		request.magic = 0xCAFECAFE;
		request.cmd = FIFO_PKT_DRV;
		request.datasize = 0x194 +  sizeof(struct ipcPacketHeader);

		memcpy(payload + sizeof(struct ipcPacketHeader), RCV_MSM_Data, sizeof(RCV_MSM_Data));

		request.data = payload;

		_ipc_client_send(client, &request);

		memcpy(payload + sizeof(struct ipcPacketHeader), EAR_MSM_Data, sizeof(EAR_MSM_Data));

		request.data = payload;

		_ipc_client_send(client, &request);

		memcpy(payload + sizeof(struct ipcPacketHeader), SPK_MSM_Data, sizeof(SPK_MSM_Data));

		request.data = payload;

		_ipc_client_send(client, &request);

		memcpy(payload + sizeof(struct ipcPacketHeader), BTH_MSM_Data, sizeof(BTH_MSM_Data));

		request.data = payload;

		_ipc_client_send(client, &request);

		tx_packet.header.ipcPacketType = 0x39;
		tx_packet.header.reserved = 0;
		tx_packet.respBuf = NULL;

		payload = malloc((0x14) + sizeof(struct ipcPacketHeader));

		memcpy(payload, &tx_packet, sizeof(struct ipcPacketHeader));

		request.magic = 0xCAFECAFE;
		request.cmd = FIFO_PKT_DRV;
		request.datasize = 0x14 +  sizeof(struct ipcPacketHeader);

		memcpy(payload + sizeof(struct ipcPacketHeader), jetFWVersion, sizeof(*jetFWVersion));

		request.data = payload;

		_ipc_client_send(client, &request);

		printf("KB: Sent all the sound packages\n");

		break;

	default :
    		printf("KB: IPC Packet type 0x%x is not yet handled\n", rx_header->ipcPacketType);

    		break;
    }

    printf("KB: Inside modem_response_ipc leaving\n");

}
