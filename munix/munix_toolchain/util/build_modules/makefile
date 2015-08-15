MODULES_SRC_PATH = modules
MODULES_SRC = $(filter %.c , $(shell find ./${MODULES_SRC_PATH} -type f))
MODULES_OUT_PATH = munix_toolchain/modules

EMPTY :=
SPACE := $(EMPTY) $(EMPTY)
MODULES_OBJ_ = $(notdir ${MODULES_SRC:.c=.ko})
MODULES_OBJ = ${MODULES_OUT_PATH}/$(subst ${SPACE}, ${MODULES_OUT_PATH}/,${MODULES_OBJ_})
MODULES_LIB_PATH = libraries/include

CC=i686-pc-toaru-gcc

CFLAGS  = -O2 -std=c99
CFLAGS += -finline-functions -ffreestanding
CFLAGS += -Wall -Wextra -Wno-unused-function -Wno-unused-parameter -Wno-format
CFLAGS += -pedantic -fno-omit-frame-pointer
CFLAGS += -D_KERNEL_

HEADERS = $(shell find ${MODULES_LIB_PATH}/ -type f -name '*.h')

all: ${MODULES_OBJ}
	@echo "Done building modules!"

${MODULES_OUT_PATH}/%.ko: ${MODULES_SRC} ${HEADERS}
	${CC} $(filter %/$(notdir $(@:.ko=.c)), ${MODULES_SRC}) -o ${MODULES_OUT_PATH}/$(notdir $@) -T ${MODULES_SRC_PATH}/link.ld -I${MODULES_LIB_PATH} -nostdlib ${CFLAGS} -c
