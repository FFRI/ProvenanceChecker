CC = clang
CFLAGS = -Wall -Wextra -std=c99

SRCS = $(wildcard *.c)
TARGETS = $(SRCS:.c=)

EXEC2_TARGETS = rename swap link
EXEC0_TARGETS = create
EXEC1_TARGETS = $(filter-out $(EXEC2_TARGETS) $(EXEC0_TARGETS),$(TARGETS))

all: $(TARGETS)

%: %.c
	$(CC) $(CFLAGS) -o $@ $<

copy: $(TARGETS)
	mkdir -p ./exec0 ./exec1 ./exec2
	$(foreach target,$(EXEC0_TARGETS),cp $(target) ./exec0/;)
	$(foreach target,$(EXEC1_TARGETS),cp $(target) ./exec1/;)
	$(foreach target,$(EXEC2_TARGETS),cp $(target) ./exec2/;)

clean:
	rm -f $(TARGETS)
	rm -f ./exec0/* ./exec1/* ./exec2/*
	rmdir ./exec0 ./exec1 ./exec2 2>/dev/null || true

.PHONY: all clean copy
