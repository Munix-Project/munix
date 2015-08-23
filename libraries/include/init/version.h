/*
 * This file is part of ToaruOS and is released under the terms
 * of the NCSA / University of Illinois License - see LICENSE.md
 * Copyright (C) 2015 Dale Weiler
 *
 */

#ifndef KERNEL_INCLUDE_VERSION_H_
#define KERNEL_INCLUDE_VERSION_H_

extern char * __kernel_name;
extern char * __kernel_version_format;

extern int    __kernel_version_major;
extern int    __kernel_version_minor;
extern int    __kernel_version_lower;

extern char * __kernel_version_suffix;
extern char * __kernel_version_codename;

extern char * __kernel_arch;

extern char * __kernel_build_date;
extern char * __kernel_build_time;

extern char * __kernel_compiler_version;

#endif /* KERNEL_INCLUDE_VERSION_H_ */
