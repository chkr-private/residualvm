/* Residual - Virtual machine to run LucasArts' 3D adventure games
 * Copyright (C) 2003-2006 The ScummVM-Residual Team (www.scummvm.org)
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.

 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.

 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA
 *
 * $URL$
 * $Id$
 *
 */

#ifndef COMMON_SYS_H
#define COMMON_SYS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <assert.h>
#include <ctype.h>
#include <math.h>

extern "C" int residual_main(int argc, char *argv[]);

#ifndef _MSC_VER
#include <stdint.h>
#include <dirent.h>
#include <unistd.h>
#endif

#ifdef _MSC_VER
#pragma once
#pragma warning( disable : 4068 ) // turn off "unknown pragma" warning
#pragma warning( disable : 4244 ) // turn off "conversion type" warning
#endif

#ifndef LOCAL_PI
#define LOCAL_PI 3.14159265358979323846
#endif

// Use config.h, generated by configure
#if defined(HAVE_CONFIG_H) 
#include "config.h" 
#endif

// In the following we configure various targets, in particular those
// which can't use our "configure" tool and hence don't use config.h.
//
// Some #defines that occur here frequently:
// SYSTEM_LITTLE_ENDIAN
//    - Define this on a little endian target
// SYSTEM_BIG_ENDIAN
//    - Define this on a big endian target
// SYSTEM_NEED_ALIGNMENT
//    - Define this if your system has problems reading e.g. an int32 from an odd address
// SYSTEM_USE_LONG_INT
//    - Define this if your port needs to use 'long' for the int32 datatype
//      (i.e. an integer with exactly 32 bits).
// SYSTEM_DONT_DEFINE_TYPES
//    - Define this if you need to provide your own typedefs, e.g. because your
//      system headers conflict with our typenames, or because you have odd
//      type requirements.
// SMALL_SCREEN_DEVICE
//    - ...
// ...

// We define all types in config.h, so we don't want to typedef those types
// here again!
#ifdef HAVE_CONFIG_H
#define SYSTEM_DONT_DEFINE_TYPES
#endif


#if defined(__SYMBIAN32__)

	#define strcasecmp stricmp

	#define SYSTEM_LITTLE_ENDIAN
	#define SYSTEM_NEED_ALIGNMENT

	#define SMALL_SCREEN_DEVICE

	// Enable Symbians own datatypes
	// This is done for two reasons
	// a) uint is already defined by Symbians libc component
	// b) Symbian is using its "own" datatyping, and the Scummvm port
	//    should follow this to ensure the best compability possible.
	#define SYSTEM_DONT_DEFINE_TYPES
	typedef unsigned char byte;

	typedef unsigned char uint8;
	typedef signed char int8;

	typedef unsigned short int uint16;
	typedef signed short int int16;

	typedef unsigned long int uint32;
	typedef signed long int int32;

#elif defined(_WIN32_WCE)

	#define strcasecmp stricmp

	#define SYSTEM_LITTLE_ENDIAN
	#define SYSTEM_NEED_ALIGNMENT

	#define SMALL_SCREEN_DEVICE

	typedef signed char int8_t;
	typedef signed short int16_t;
	typedef unsigned char uint8_t;
	typedef unsigned short uint16_t;

#elif defined(_MSC_VER)

	#define strcasecmp stricmp

	#define SYSTEM_LITTLE_ENDIAN

	typedef signed char int8_t;
	typedef signed short int16_t;
	typedef unsigned char uint8_t;
	typedef unsigned short uint16_t;

#elif defined(__MINGW32__)

	#define strcasecmp stricmp

	#define SYSTEM_LITTLE_ENDIAN

#elif defined(UNIX)

	#ifndef CONFIG_H
		/* need this for the SDL_BYTEORDER define */
		#include <SDL_byteorder.h>

		#if SDL_BYTEORDER == SDL_LIL_ENDIAN
		#define SCUMM_LITTLE_ENDIAN
		#elif SDL_BYTEORDER == SDL_BIG_ENDIAN
		#define SCUMM_BIG_ENDIAN
		#else
		#error Neither SDL_BIG_ENDIAN nor SDL_LIL_ENDIAN is set.
		#endif
	#endif

	// You need to set this manually if necessary
//	#define SYSTEM_NEED_ALIGNMENT

	#if defined(__DECCXX) // Assume alpha architecture
	#define INVERSE_MKID
	#define SYSTEM_NEED_ALIGNMENT
	#endif

#elif defined(__PALMOS_TRAPS__)	|| defined (__PALMOS_ARMLET__)

#ifdef __PALMOS_ARMLET__
	#include <extras_string.h>
#endif
	#define SYSTEM_LITTLE_ENDIAN

	#define strcasecmp stricmp

	#define SYSTEM_NEED_ALIGNMENT
	#define STRINGBUFLEN 256

#elif defined(__DC__)

	#define SYSTEM_LITTLE_ENDIAN
	#define SYSTEM_NEED_ALIGNMENT

#elif defined(__PLAYSTATION2__)

	#define SYSTEM_LITTLE_ENDIAN
	#define SYSTEM_NEED_ALIGNMENT

#elif defined(__PSP__)

	#define	SYSTEM_LITTLE_ENDIAN
	#define	SYSTEM_NEED_ALIGNMENT

#elif defined(__amigaos4__)

	#define	SYSTEM_BIG_ENDIAN
	#define	SYSTEM_NEED_ALIGNMENT

#elif defined (__DS__) //NeilM

	#define strcasecmp stricmp

	#define SYSTEM_NEED_ALIGNMENT
	#define SYSTEM_LITTLE_ENDIAN

	#include "nds/jtypes.h"

	#define SYSTEM_DONT_DEFINE_TYPES

	#define STRINGBUFLEN 256
	#define printf(fmt, ...)					consolePrintf(fmt, ##__VA_ARGS__)

#elif defined(__WII__)

	#define	SYSTEM_BIG_ENDIAN
	#define	SYSTEM_NEED_ALIGNMENT

#else
	#error No system type defined

#endif

//
// Typedef our system types unless SYSTEM_DONT_DEFINE_TYPES is set.
//
#ifndef SYSTEM_DONT_DEFINE_TYPES

	typedef unsigned char byte;

	typedef unsigned char uint8;
	typedef signed char int8;

	typedef unsigned short uint16;
	typedef signed short int16;

	#ifdef SYSTEM_USE_LONG_INT
	typedef unsigned long uint32;
	typedef signed long int32;
	typedef unsigned long uint;
	#else
	typedef unsigned int uint32;
	typedef signed int int32;
	typedef unsigned int uint;
	#endif
#endif

//
// Fallbacks / default values for various special macros
//
#ifndef FORCEINLINE
#define FORCEINLINE inline
#endif

#ifndef NORETURN
#define NORETURN
#endif

#ifndef STRINGBUFLEN
#define STRINGBUFLEN 1024
#endif

#ifndef MAXPATHLEN
#define MAXPATHLEN 256
#endif

#ifndef CDECL
#define CDECL
#endif

#ifndef NORETURN
#define NORETURN
#endif

#endif // COMMON_SYS_H
