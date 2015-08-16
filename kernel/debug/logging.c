/*
 * logging.c
 *
 *  Created on: Aug 13, 2015
 *      Author: miguel
 */

#include <system.h>
#include <libc.h>
#include <list.h>
#include <logging.h>
#include <va_list.h>
#include <printf.h>

log_type_t debug_level = NOTICE;
void * debug_file = NULL;
void (*debug_hook)(void *, char *) = NULL;
void (*debug_video_crash)(char **) = NULL;

char * c_messages[] = {
	"INFO",
	"NOTICE",
	"WARNING",
	"ERROR",
	"CRITICAL",
	"INSANE"
};

static char buffer[1024];

void _debug_print(char * title, int line_no, log_type_t level, char *fmt, ...) {
	va_list args;
	va_start(args, fmt);
	vasprintf(buffer, fmt, args);
	va_end(args);

	char * type;
	if (level > INSANE) {
		type = "";
	} else {
		type = c_messages[level];
	}

	fprintf(debug_file, "[%10d.%3d:%s:%d]%s %s\n", timer_ticks, timer_subticks, title, line_no, type, buffer);
}
