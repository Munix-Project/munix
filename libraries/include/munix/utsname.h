/*
 * This file is part of ToaruOS and is released under the terms
 * of the NCSA / University of Illinois License - see LICENSE.md
 * Copyright (C) 2015 Dale Weiler
 *
 */

#ifndef KERNEL_INCLUDE_UTSNAME_H_
#define KERNEL_INCLUDE_UTSNAME_H_

#define _UTSNAME_LENGTH 256

struct utsname {
	char  sysname[_UTSNAME_LENGTH];
	char nodename[_UTSNAME_LENGTH];
	char  release[_UTSNAME_LENGTH];
	char  version[_UTSNAME_LENGTH];
	char  machine[_UTSNAME_LENGTH];
	char domainname[_UTSNAME_LENGTH];
};

#ifndef _KERNEL_
int uname(struct utsname *);
#endif

#endif /* KERNEL_INCLUDE_UTSNAME_H_ */
