MODULES_SRC = $(filter %.c , $(shell find ./modules -type f))
MODULES_SRC_PATH = modules
MODULES_OUT_PATH = munix_toolchain/modules

EMPTY :=
SPACE := $(EMPTY) $(EMPTY)
MODULES_OBJ_ = $(notdir ${MODULES_SRC:.c=.ko})
MODULES_OBJ = ${MODULES_OUT_PATH}/$(subst ${SPACE}, ${MODULES_OUT_PATH}/,${MODULES_OBJ_})

CC=i686-pc-toaru-gcc

CFLAGS  = -O2 -std=c99
CFLAGS += -finline-functions -ffreestanding
CFLAGS += -Wall -Wextra -Wno-unused-function -Wno-unused-parameter -Wno-format
CFLAGS += -pedantic -fno-omit-frame-pointer
CFLAGS += -D_KERNEL_

HEADERS = $(shell find libraries/include/ -type f -name '*.h')

all: ${MODULES_OBJ}
	@echo "Done building modules!"

munix_toolchain/modules/%.ko: ${MODULES_SRC} ${HEADERS}
	${CC} $(filter %/$(notdir $(@:.ko=.c)), ${MODULES_SRC}) -o munix_toolchain/modules/$(notdir $@) -T modules/link.ld -Ilibraries/include -nostdlib ${CFLAGS} -c
