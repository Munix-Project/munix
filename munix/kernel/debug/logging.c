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

#ifdef STDOUT_TERM
UPoint cursor = {0,0};


void puts(char * str){
	for(unsigned i=0; i< strlen(str);i++){
		putc(str[i],cursor.X++,cursor.Y, 0b1111);
		if(cursor.X>79){
			cursor.X = 0;
			cursor.Y++;
		}
	}
}
#endif

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

#ifdef STDOUT_TERM
	// Output buffer:
	if(level!=NORMAL){
		puts(c_messages[level]);
		puts(": ");
	}
	puts(buffer);

	cursor.X=0; cursor.Y++;
	if(cursor.Y>25){ // Scroll down
		char * vidmem = (char*)0xb8000;
		for (uint32_t i = 0; i <= 25 * 80 * 2; i++){
			vidmem[i] = vidmem[i + 80*2];
			vidmem[i + 80*2] = 0;

		}
		cursor.Y = 24;
	}
#endif
}
