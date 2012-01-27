/**
 * This file is part of libsamsung-ipc.
 *
 * Copyright (C) 2010-2011 Joerie de Gram <j.de.gram@gmail.com>
 *               2011 Simon Busch <morphis@gravedo.de>
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

#include <fm_packet.h>
#include <ipc_packet.h>
#include <tapi_packet.h>

#include <dlfcn.h>

int client_fd = -1;
int state = 0;
int seq = 0;
int in_call = 0;
int out_call = 0;
int call_done = 0;

char sim_pin[8];

void modem_response_boot(struct ipc_client *client, struct modem_io *resp)
{
	DEBUG_I("Inside modem_response_boot\n");
	int retval, count;
	struct ipcPacketHeader *rx_header;
	struct ipcRequest tx_packet;

	struct modem_io request;
    void *frame;
    uint8_t *payload;
    int frame_length;

    struct fifoPacketHeader *ipc;

    char data[4][0x04] = {
    			  {0x06,0,0,0},
    };

    static struct modem_io sysDataToCP [1] = {
    		{
    			.magic = 0xCAFECAFE,
    			.cmd = 0x96,
    			.datasize = 0x04,
    			//.data = data1,
    		},
    };

	DEBUG_I("Frame header = 0x%x\n Frame type = 0x%x\n Frame length = 0x%x\n", resp->magic, resp->cmd, resp->datasize);

	hexdump(resp->data, resp->datasize);

	for(count = 0; count < 1; count++)
	{
		DEBUG_I("sending frame no. %d\n", count);
		payload = malloc(sysDataToCP[count].datasize);

		memcpy(payload, data[count], sysDataToCP[count].datasize);
		DEBUG_I("Copying data %d\n", count);

		request.magic = sysDataToCP[count].magic;
		request.cmd = sysDataToCP[count].cmd;
		request.datasize = sysDataToCP[count].datasize;

		request.data = payload;
		DEBUG_I("Before sending\n");

		_ipc_client_send(client, &request);
		DEBUG_I("sent frame no. %d\n", count);

	}
    DEBUG_I("Inside modem_response_boot leaving\n");

}

void modem_response_dbg_level(struct ipc_client *client, struct modem_io *resp)
{
	DEBUG_I("Inside modem_response_dbg_level\n");
	int retval, count;
	struct ipcPacketHeader *rx_header;
	struct ipcRequest tx_packet;

	struct modem_io request;
    void *frame;
    uint8_t *payload;
    int32_t frame_length;

    struct fifoPacketHeader *ipc;

    char data[4][0x33] = {
    			  {0x01,0,0,0},
    			  {0x0B,0,0,0,1,0,0,0},
    			  {0x02,0,0,0,0,0,0,0,0x11,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'3','7','3','2','4','6','1','1','2',0,0,0,0,0,0,0,0},
    			  {0x0C,0,0,0,'t','e','s','t',0x20,'F','W',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    };

    static struct modem_io sysDataToCP [4] = {
    		{
    			.magic = 0xCAFECAFE,
    			.cmd = 0x2E,
    			.datasize = 0x04,
    			//.data = data1,
    		},
    		{
    			.magic = 0xCAFECAFE,
    			.cmd = 0x0F,
    			.datasize = 0x08,
    			//.data = data2,
    		},
    		{
    			.magic = 0xCAFECAFE,
    			.cmd = 0x96,
    			.datasize = 0x33,
    			//.data = data3,
    		},
    		{
    			.magic = 0xCAFECAFE,
    			.cmd = 0x0F,
    			.datasize = 0x24,
    			//.data = data4,
    		},
    };

	DEBUG_I("Frame header = 0x%x\n Frame type = 0x%x\n Frame length = 0x%x\n", resp->magic, resp->cmd, resp->datasize);

	hexdump(resp->data, resp->datasize);

	for(count = 0; count < 4; count++)
	{
		DEBUG_I("sending frame no. %d\n", count);
		payload = malloc(sysDataToCP[count].datasize);

		memcpy(payload, data[count], sysDataToCP[count].datasize);
		DEBUG_I("Copying data %d\n", count);

		request.magic = sysDataToCP[count].magic;
		request.cmd = sysDataToCP[count].cmd;
		request.datasize = sysDataToCP[count].datasize;

		request.data = payload;
		DEBUG_I("Before sending\n");

		_ipc_client_send(client, &request);
		DEBUG_I("sent frame no. %d\n", count);

	}
    DEBUG_I("Inside modem_response_dbg_level leaving\n");

}

void modem_response_dbg(struct ipc_client *client, struct modem_io *resp)
{

	DEBUG_I("Debug string - %s\n", (char *)(resp->data));

}

void modem_response_handle(struct ipc_client *client, struct modem_io *resp)
{

	int32_t ret;

	switch(resp->cmd)
    {
        case FIFO_PKT_FILE:
        	ret = modem_response_fm(client, resp);
        	if (ret)
        		modem_response_tapi_init(client, resp);
        break;
        case FIFO_PKT_DVB_H_DebugLevel:
            //modem_response_dbg_level(client, resp);
        break;
        case FIFO_PKT_BOOT:
            //modem_response_boot(client, resp);
        break;
        case FIFO_PKT_DRV:
        	modem_response_ipc(client, resp);
        break;
        case FIFO_PKT_DEBUG:
        	modem_response_dbg(client, resp);
        break;
        case FIFO_PKT_TAPI:
        	modem_response_tapi(client, resp);
        break;
        case FIFO_PKT_SIM:
        	modem_response_sim(client, resp);
        break;
        default :
        	DEBUG_I("Packet type 0x%x not yet handled\n", resp->cmd);
        	DEBUG_I("Frame header = 0x%x\n Frame type = 0x%x\n Frame length = 0x%x\n", resp->magic, resp->cmd, resp->datasize);
        	hexdump(resp->data, resp->datasize);

    }

}

int32_t modem_read_loop(struct ipc_client *client)
{
    struct modem_io resp;
    int32_t fd = client_fd;
    DEBUG_I("dpram fd = 0x%x\n", fd);
    int32_t rc;
    fd_set fds;

    if(fd < 0) {
        return -1;
    }

    memset(&resp, 0, sizeof(resp));

    FD_ZERO(&fds);
    FD_SET(fd, &fds);

    while(1) {
        //usleep(3000);

        select(fd + 1, &fds, NULL, NULL, NULL);

        if(FD_ISSET(fd, &fds))
        {
            rc = ipc_client_recv(client, &resp);

            if(rc > 0) {
                DEBUG_E("Can't RECV from modem: please run this again\n");
                break;
            }

            modem_response_handle(client, &resp);

            if(resp.data != NULL)
                free(resp.data);
        }
    }

    return 0;
}

void modem_log_handler(char *message, void *user_data)
{
    int32_t i, l;
    l = strlen(message);

    if(l > 1) {
        for(i=l ; i > 0 ; i--)
        {
            if(message[i] == '\n') {
                message[i] = 0;
            } else if(message[i] != 0) {
                break;
            }
        }

        DEBUG_I("%s\n", message);
    }
}

void modem_log_handler_quiet(const char *message, void *user_data)
{
    return;
}

int32_t modem_start(struct ipc_client *client)
{
    int32_t rc = -1;

    rc = ipc_client_set_all_handlers_data(client, &client_fd);

    if(rc < 0)
        DEBUG_I("error in setting handlers_data\n");

    ipc_client_bootstrap_modem(client);

    usleep(300);

    DEBUG_I("Opening modem_ctl\n");

    rc = ipc_client_open(client);

    DEBUG_I("Addr of Client_fd = 0x%x, value of Client_fd = %d\n", &client_fd, client_fd);

    if(rc < 0)
        return -1;

    DEBUG_I("Power on modem\n");

    rc = ipc_client_power_on(client);
    if(rc < 0)
        return -1;

    return 0;
}

int32_t modem_stop(struct ipc_client *client)
{
    ipc_client_power_off(client);
    ipc_client_close(client);

    return 0;
}

void print_help()
{
    printf("usage: modemctrl <command>\n");
    printf("commands:\n");
    printf("\tstart                 bootstrap modem and start read loop\n");
    printf("\tpower-on              power on the modem\n");
    printf("\tpower-off             power off the modem\n");
    printf("arguments:\n");
    printf("\t--debug               enable debug messages\n");
    printf("\t--pin=[PIN]           provide SIM card PIN\n");
}

/* KB:
 * TODO: Implement in a separate thread which will be used as mainLoop in final vendor RIL implementation
 * 		 This will be called from RIL_Init function
 */
int main(int argc, char *argv[])
{
    struct ipc_client *client_fmt;
    int c = 0;
	int opt_i = 0;
    int rc = -1;

    struct option opt_l[] = {
        {"debug",   no_argument,        0,  0 },
        {"pin",     required_argument,  0,  0 },
        {0,         0,                  0,  0 }
    };

    if (argc < 2) {
        print_help();
        exit(1);
    }

    client_fmt = ipc_client_new(IPC_CLIENT_TYPE_FMT);
    ipc_client_set_log_handler(client_fmt, modem_log_handler_quiet, NULL);

    while(c >= 0) {
        c = getopt_long(argc, argv, "", opt_l, &opt_i);
        if(c < 0)
            break;

        switch(c) {
            case 0:
                if(strcmp(opt_l[opt_i].name, "debug") == 0) {
                    ipc_client_set_log_handler(client_fmt, modem_log_handler, NULL);
                    DEBUG_I("Debug enabled\n");
                } else if(strcmp(opt_l[opt_i].name, "pin") == 0) {
                    if(optarg) {
                        if(strlen(optarg) < 8) {
                            DEBUG_I("Got SIM PIN!\n");
                            memcpy(sim_pin, optarg, 8);
                        } else {
                            DEBUG_E("SIM PIN is too long!\n");
                            return 1;
                        }
                    }
                }
            break;
        }
    }

        while(opt_i < argc) {
            if(strncmp(argv[optind], "power-on", 8) == 0) {
                ipc_client_power_on(client_fmt);
                goto modem_quit;
            } else if(strncmp(argv[optind], "power-off", 9) == 0) {
                ipc_client_power_off(client_fmt);
                goto modem_quit;
            } else if(strncmp(argv[optind], "start", 5) == 0) {
                DEBUG_I("Starting modem on FMT client\n");
                rc = modem_start(client_fmt);
                if(rc > 0) {
                    DEBUG_E("Something went wrong\n");
                    modem_stop(client_fmt);
                    return 1;
                }

                DEBUG_I("Starting modem_read_loop on FMT client\n");
                /*
                 * TODO: Create thread for modem_read_loop which will be used as readerLoop in RIL implementation
                 */
                modem_read_loop(client_fmt);

                modem_stop(client_fmt);
            } else {
                DEBUG_E("Unknown argument: '%s'\n", argv[optind]);
                print_help();
                return 1;
            }

            optind++;
        }

modem_quit:
    ipc_client_free(client_fmt);

    return 0;
}
