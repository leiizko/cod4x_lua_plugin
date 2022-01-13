## Output file name
PLUGIN_NAME=lua

## Platform specific 
INCLUDEDIR_UNIX_MYSQL=-IInclude/mysql/unix/include
INCLUDEDIR_WIN32_MYSQL=-IInclude/mysql/windows/include

UNIX_LIB=Include/LuaJIT/unix/libluajit.a Include/iconv/unix/libiconv.a Include/mysql/unix/lib/libmysqlclient.a
WIN32_LIB=Include/LuaJIT/windows/libluajit.a Include/iconv/windows/libiconv.a Include/mysql/windows/lib/libmysql.lib

## Common
CC=gcc
CFLAGS=-m32 -O0 -Wall -g -static-libgcc -static-libstdc++
C_MODULES=$(wildcard *.c)
C_OBJECTS=$(patsubst %.c,obj/%.o,$(C_MODULES))
OBJECTS=$(C_OBJECTS)

ifeq ($(OS),Windows_NT)
LIBS=../libcom_plugin.a $(WIN32_LIB)
INCLUDEDIR=$(INCLUDEDIR_WIN32_MYSQL)
else
LIBS=$(UNIX_LIB)
INCLUDEDIR=$(INCLUDEDIR_UNIX_MYSQL)
endif

## Recipies
ifeq ($(OS),Windows_NT)
all: win32
clean: win32_clean
else
all: unix
clean: unix_clean
endif

obj/%.o: %.c
	@echo $(CC)    "$^ -> $@"
	@$(CC) $(CFLAGS) $(INCLUDEDIR) -o $@ -c $<

## Windows
win32: bin/$(PLUGIN_NAME).dll

bin/$(PLUGIN_NAME).dll: $(OBJECTS)
	@echo link   "$@"
	@$(CC) -shared $(CFLAGS) -o $@ $^ $(LIBS)

win32_clean:
	@del $(subst /,\\,$(OBJECTS))
	@echo Clear

## Unix
unix: bin/$(PLUGIN_NAME).so

bin/$(PLUGIN_NAME).so: $(OBJECTS)
	@echo link   "$@"
	@$(CC) -shared $(CFLAGS) -o $@ $^ $(LIBS)

unix_clean:
	@rm -r $(OBJECTS)
	@echo Clear