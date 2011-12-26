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

#ifndef __DEVICE_JET_FM_H__
#define __DEVICE_JET_FM_H__

//PACKETTYPE 0x6 FmPacket
struct fmPacketHeader {
	unsigned int fmPacketType; 	//(stored as type-0xEFFFFFFF, just take first byte substract 1 to get actual type)
	unsigned int reserved1; 		//dummy, unused?
	unsigned int packetLen; 		//equal to n, equal to packetLength-16 (headersize)
	unsigned int reqCounter; 	// has to be the same in responsepacket, probably fm request counter
};

struct fmRequest {
	struct fmPacketHeader *header; 	// has to be the same in responsepacket, probably fm request counter
	unsigned char *reqBuf; 		//usually first comes unsigned int params, and then string containing name
};

struct fmResponse {
	struct fmPacketHeader *header; 	// has to be the same in responsepacket, probably fm request counter
	int funcRet; 		//called function return value
	int errorVal; 		//0 if func_ret == 0, otherwise retvalue of platform LastError()
	unsigned char *respBuf;
};

struct fmArgs {
	unsigned int mode;
	char *fileName;
	unsigned int fileHandle;
	void *readBuf;
	void *writeBuf;
	unsigned int size;
	unsigned int numRead;
	unsigned int offset;
	unsigned int origin;
};

//fmPacketType
#define FM_OPENFILE 		0
#define FM_CLOSEFILE 		1
#define FM_CREATEFILE 		2
#define FM_READFILE 		3
#define FM_WRITEFILE 		4
#define FM_FLUSHFILE 		5
#define FM_SEEKFILE 		6
#define FM_TELLFILE 		7
#define FM_REMOVEFILE 		8
#define FM_MOVEFILE 		9
#define FM_GETFILEATTR 		10
#define FM_FGETFILEATTR 	11
#define FM_SETFILEATTR 		12
#define FM_TRUNCATEFILE 	13
#define FM_OPENDIR 			14
#define FM_CLOSEDIR 		15
#define FM_READDIR 			16
#define FM_CREATEDIR 		17
#define FM_REMOVEDIR 		18
#define FM_GETQUOTASPACE 	19
#define FM_INVALID 			20

#define MAX_FILE_OPS 		20

int FmOpenFile(struct fmRequest *, struct fmResponse *);
int FmCloseFile(struct fmRequest *, struct fmResponse *);
int FmCreateFile(struct fmRequest *, struct fmResponse *);
int FmReadFile(struct fmRequest *, struct fmResponse *);
int FmWriteFile(struct fmRequest *, struct fmResponse *);
int FmFlushFile(struct fmRequest *, struct fmResponse *);
int FmSeekFile(struct fmRequest *, struct fmResponse *);
int FmTellFile(struct fmRequest *, struct fmResponse *);
int FmRemoveFile(struct fmRequest *, struct fmResponse *);
int FmMoveFile(struct fmRequest *, struct fmResponse *);
int FmGetFileAttrFile(struct fmRequest *, struct fmResponse *);
int FmFGetFileAttrFile(struct fmRequest *, struct fmResponse *);
int FmSetFileAttrFile(struct fmRequest *, struct fmResponse *);
int FmTruncateFile(struct fmRequest *, struct fmResponse *);
int FmOpenDirFile(struct fmRequest *, struct fmResponse *);
int FmCloseDirFile(struct fmRequest *, struct fmResponse *);
int FmReadDirFile(struct fmRequest *, struct fmResponse *);
int FmCreateDirFile(struct fmRequest *, struct fmResponse *);
int FmRemoveDirFile(struct fmRequest *, struct fmResponse *);
int FmGetQuotaSpaceFile(struct fmRequest *, struct fmResponse *);
//int FmInvalidFile(unsigned int mode, const char *fileName);


#endif
