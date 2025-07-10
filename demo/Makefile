CC = clang
CFLAGS = -std=c99 -Wall -Wextra

all: a.out b.dylib reflective_loader

a.out: loader.c
	$(CC) $(CFLAGS) -arch x86_64 -o $@ $<

b.dylib: dylib.c
	$(CC) $(CFLAGS) -arch x86_64 -dynamiclib -o $@ $<

reflective_loader: reflective_loader.m
	$(CC) -arch x86_64 -o $@ $< -framework Foundation

clean:
	rm -f a.out b.dylib reflective_loader
