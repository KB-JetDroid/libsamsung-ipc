/**
 * This file is part of libsamsung-ipc.
 *
 * Copyright (C) 2012 Dominik Marszk <dmarszk@gmail.com>
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

#ifndef __DEVICE_WAVE_NETWORK_H__
#define __DEVICE_WAVE_NETWORK_H__

/**
 * All the TAPI Network context structures specific to Wave will be defined here
 */

enum TAPI_NETWORK_TYPE
{
	//TAPI_NETWORK_APIREQ 	= <unknown yet>,
	TAPI_NETWORK_INIT 		= 0x45,	
	TAPI_NETWORK_STARTUP	= 0x46,
	TAPI_NETWORK_SETSUBMODE	= 0x52,
	TAPI_NETWORK_SELECTNET	= 0x54,
	TAPI_NETWORK_RADIOINFO 	= 0x57,	
	TAPI_NETWORK_COMMONERROR = 0x58,
	TAPI_NETWORK_CELLINFO	= 0x59,
};
 
 
#endif
