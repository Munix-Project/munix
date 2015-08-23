/*
 * This file is part of ToaruOS and is released under the terms
 * of the NCSA / University of Illinois License - see LICENSE.md
 * Copyright (C) 2015 Dale Weiler
 *
 */

#ifndef KERNEL_INCLUDE_LOGGING_H_
#define KERNEL_INCLUDE_LOGGING_H_

#define log_clrscr() for(unsigned i=0;i<80;i++)\
	for(unsigned j=0;j<25;j++) \
		putc(' ',i,j,0b1111);
#define log_reset() cursor.X = 0; cursor.Y = 0;

typedef enum {
	INFO = 0, /* Unimportant */
	NOTICE,   /* Important, but not bad */
	WARNING,  /* Not what was expected, but still okay */
	ERROR,    /* This is bad... */
	CRITICAL, /* Shit */
	INSANE,
	NORMAL /* Doesn't output itself into the screen, and is equivalent to the INFO */
} log_type_t;

extern log_type_t debug_level;
extern void * debug_file;
extern void _debug_print(char * title, int line_no, log_type_t level, char *fmt, ...);
extern void (*debug_hook)(void *, char *);
extern void (*debug_video_crash)(char **);

#ifndef MODULE_NAME
#define MODULE_NAME __FILE__
#endif

#ifndef QUIET
#define debug_print(level, ...) _debug_print(MODULE_NAME, __LINE__, level, __VA_ARGS__)
#else
#define debug_print(level, ...)
#endif

#endif /* KERNEL_INCLUDE_LOGGING_H_ */
