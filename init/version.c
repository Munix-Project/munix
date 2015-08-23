/*
 * This file is part of ToaruOS and is released under the terms
 * of the NCSA / University of Illinois License - see LICENSE.md
 * Copyright (C) 2015 Dale Weiler
 *
 */

#include <init/version.h>

char * __kernel_name = "minux";

char * __kernel_version_format = "%d.%d.%d-%s";

int    __kernel_version_major = 0;
int    __kernel_version_minor = 11;
int    __kernel_version_lower = 1;

#ifdef KERNEL_GIT_TAG
# define STR(x) #x
# define STRSTR(x) STR(x)
# define KERNEL_VERSION_SUFFIX STRSTR(KERNEL_GIT_TAG)
#else
# define KERNEL_VERSION_SUFFIX "r"
#endif
char * __kernel_version_suffix   = KERNEL_VERSION_SUFFIX;

char * __kernel_version_codename = "helios";

char * __kernel_arch = "i686";

char * __kernel_build_date = __DATE__;
char * __kernel_build_time = __TIME__;

#if (defined(__GNUC__) || defined(__GNUG__)) && !(defined(__clang__) || defined(__INTEL_COMPILER))
# define COMPILER_VERSION "gcc " __VERSION__
#elif (defined(__clang__))
# define COMPILER_VERSION "clang " __clang_version__
#else
# define COMPILER_VERSION "unknown-compiler how-did-you-do-that"
#endif

char * __kernel_compiler_version = COMPILER_VERSION;


