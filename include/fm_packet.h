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
#define FM_OPENFILE 0 //FmOpenFile((unsigned int)(*reqBuf+0), reqBuf+4) //mode, name
#define FM_CLOSEFILE 1 //FmCloseFile((unsigned int)(*reqBuf+0)) //handle
#define FM_CREATEFILE 2 //FmCreateFile((unsigned int)(*reqBuf+0), reqBuf+4) //mode, name
#define FM_READFILE 3 //FmReadFile((unsigned int)(*reqBuf+0), respBuf+4, (unsigned int)(*reqBuf+4), respBuf) //handle, outBuf, len, &readLen //n = 4+(*respBuf+4)
#define FM_WRITEFILE 4 //FmWriteFile((unsigned int)(*reqBuf+0), reqBuf+8, (unsigned int)(*reqBuf+4)) //handle, buf, len
#define FM_FLUSHFILE 5 //FmFlushFile((unsigned int)(*reqBuf+0)) //handle
#define FM_SEEKFILE 6 //FmSeekFile((unsigned int)(*reqBuf+0), (unsigned int)(*reqBuf+4), (unsigned int)(*reqBuf+8)) //handle, offset, origin
#define FM_TELLFILE 7
#define FM_REMOVEFILE 8
#define FM_MOVEFILE 9
#define FM_GETFILEATTR 10
#define FM_FGETFILEATTR 11
#define FM_SETFILEATTR 12
#define FM_TRUNCATEFILE 13
#define FM_OPENDIR 14
#define FM_CLOSEDIR 15
#define FM_READDIR 16
#define FM_CREATEDIR 17
#define FM_REMOVEDIR 18
#define FM_GETQUOTASPACE 19
#define FM_INVALID 20

#define MAX_FILE_OPS 20

#if 0
int FmOpenFile(unsigned int mode, const char *fileName); //mode, name
int FmCloseFile(int fileHandle); //handle
int FmCreateFile(unsigned int mode, const char *fileName); //mode, name
int FmReadFile(int fileHandle, void *readData, unsigned int size, unsigned int * numRead); //handle, outBuf, len, &readLen //n = 4+(*respBuf+4)
int FmWriteFile(int fileHandle, void *writeData, unsigned int size); //handle, buf, len
int FmFlushFile(int fileHandle); //handle
int FmSeekFile(int fileHandle, unsigned int offset, unsigned int origin); //handle, offset, origin
int FmTellFile(unsigned int mode, const char *fileName); //handle, offset, origin
int FmRemoveFile(unsigned int mode, const char *fileName); //mode, name
int FmMoveFile(unsigned int mode, const char *fileName); //mode, name
int FmGetFileAttrFile(unsigned int mode, const char *fileName); //mode, name
int FmFGetFileAttrFile(unsigned int mode, const char *fileName); //mode, name
int FmSetFileAttrFile(unsigned int mode, const char *fileName); //mode, name
int FmTruncateFile(unsigned int mode, const char *fileName); //mode, name
int FmOpenDirFile(unsigned int mode, const char *fileName); //mode, name
int FmCloseDirFile(unsigned int mode, const char *fileName); //mode, name
int FmReadDirFile(unsigned int mode, const char *fileName); //mode, name
int FmCreateDirFile(unsigned int mode, const char *fileName); //mode, name
int FmRemoveDirFile(unsigned int mode, const char *fileName); //mode, name
int FmGetQuotaSpaceFile(unsigned int mode, const char *fileName); //mode, name
//int FmInvalidFile(unsigned int mode, const char *fileName); //mode, name
#endif

int FmOpenFile(struct fmRequest *, struct fmResponse *); //mode, name
int FmCloseFile(struct fmRequest *, struct fmResponse *); //handle
int FmCreateFile(struct fmRequest *, struct fmResponse *); //mode, name
int FmReadFile(struct fmRequest *, struct fmResponse *); //handle, outBuf, len, &readLen //n = 4+(*respBuf+4)
int FmWriteFile(struct fmRequest *, struct fmResponse *); //handle, buf, len
int FmFlushFile(struct fmRequest *, struct fmResponse *); //handle
int FmSeekFile(struct fmRequest *, struct fmResponse *); //handle, offset, origin
int FmTellFile(struct fmRequest *, struct fmResponse *); //handle, offset, origin
int FmRemoveFile(struct fmRequest *, struct fmResponse *); //mode, name
int FmMoveFile(struct fmRequest *, struct fmResponse *); //mode, name
int FmGetFileAttrFile(struct fmRequest *, struct fmResponse *); //mode, name
int FmFGetFileAttrFile(struct fmRequest *, struct fmResponse *); //mode, name
int FmSetFileAttrFile(struct fmRequest *, struct fmResponse *); //mode, name
int FmTruncateFile(struct fmRequest *, struct fmResponse *); //mode, name
int FmOpenDirFile(struct fmRequest *, struct fmResponse *); //mode, name
int FmCloseDirFile(struct fmRequest *, struct fmResponse *); //mode, name
int FmReadDirFile(struct fmRequest *, struct fmResponse *); //mode, name
int FmCreateDirFile(struct fmRequest *, struct fmResponse *); //mode, name
int FmRemoveDirFile(struct fmRequest *, struct fmResponse *); //mode, name
int FmGetQuotaSpaceFile(struct fmRequest *, struct fmResponse *); //mode, name
//int FmInvalidFile(unsigned int mode, const char *fileName); //mode, name


#endif
