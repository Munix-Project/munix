/*
 * This file is part of ToaruOS and is released under the terms
 * of the NCSA / University of Illinois License - see LICENSE.md
 * Copyright (C) 2015 Dale Weiler
 *
 */

#ifndef KERNEL_INCLUDE_VIDEO_H_
#define KERNEL_INCLUDE_VIDEO_H_

#define IO_VID_WIDTH  0x5001
#define IO_VID_HEIGHT 0x5002
#define IO_VID_DEPTH  0x5003
#define IO_VID_ADDR   0x5004
#define IO_VID_RST	  0x5005 /* 	Reset video 	*/
#define IO_VID_STP	  0x5006 /* 	Video Stop 		*/
#define IO_VID_RESZ	  0x5007 /* 	Resize Video 	*/
#define IO_VID_GETSZ  0x5008 /* 	Get Video Size 	*/

#endif /* KERNEL_INCLUDE_VIDEO_H_ */
