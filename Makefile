CC := clang++
# TODO: Remove Wno's
CPPFLAGS ?= -std=c++20 -Wall -Wno-for-loop-analysis -Wno-unused-variable

INTX_PATH ?= ../intx
ETHASH_PATH ?= ../ethash

INTX_LIB_PATH ?= ${INTX_PATH}/include
ETHASH_LIB_PATH ?= ${ETHASH_PATH}/include
ETHASH_LINK_PATHS ?= $(shell find ${ETHASH_PATH}/build/lib -name '*.o')

INC_LIBS := -I ${INTX_LIB_PATH} -I ${ETHASH_LIB_PATH}
LINK_LIBS := ${ETHASH_LINK_PATHS}

BUILD_DIR := ./builds
BIN_DIR := ./bin
SRC_DIR := ./src

SRCS := $(shell find $(SRC_DIR) -name '*.cpp')
SRCS_WITH_SRC_STRIPPED := $(subst $(SRC_DIR)/,,$(SRCS))
OBJS := $(SRCS_WITH_SRC_STRIPPED:%=$(BUILD_DIR)/%.o)

all: proc-evm

clean:
	rm -rf ${BUILD_DIR} ${BIN_DIR}

proc-evm: ${OBJS}
	mkdir -p ${BIN_DIR}
	$(CC) $(CPPFLAGS) $(INC_LIBS) $(LINK_LIBS) $(OBJS) -o ${BIN_DIR}/proc-evm

${BUILD_DIR}/%.cpp.o: $(SRC_DIR)/%.cpp
	mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CXXFLAGS) $(INC_LIBS) -c $< -o $@

TEST_DIR := ./test
TEST_SNAPSHOT_FILE := ${TEST_DIR}/snapshot.json
TEST_BLOCK_CONTEXT_FILE := ${TEST_DIR}/blkContext.txt
TEST_TX_CONTEXT_FILE := ${TEST_DIR}/txContext.txt

run-test:
	${BIN_DIR}/proc-evm run --snapshotFile ${TEST_SNAPSHOT_FILE} --blockContextFile ${TEST_BLOCK_CONTEXT_FILE} --txContextFile ${TEST_TX_CONTEXT_FILE} --contractCode 600260040160005260206000f3

deploy-test:
	${BIN_DIR}/proc-evm deploy --snapshotFile ${TEST_SNAPSHOT_FILE} --blockContextFile ${TEST_BLOCK_CONTEXT_FILE} --txContextFile ${TEST_TX_CONTEXT_FILE} --contractCode 6001600201600a55600D6014600039600D6000F3600260040160005260206000F3

deploy-at-test:
	${BIN_DIR}/proc-evm deployAt --snapshotFile ${TEST_SNAPSHOT_FILE} --blockContextFile ${TEST_BLOCK_CONTEXT_FILE} --txContextFile ${TEST_TX_CONTEXT_FILE} --contractCode 6001600201600a55600D6014600039600D6000F3600260040160005260206000F3 --deployAddress 4200000000000000000000000000000000000aaa

call-test:
	${BIN_DIR}/proc-evm call --contractAddress 4200000000000000000000000000000000000aaa --snapshotFile ${TEST_SNAPSHOT_FILE} --blockContextFile ${TEST_BLOCK_CONTEXT_FILE} --txContextFile ${TEST_TX_CONTEXT_FILE}
