
TARGETS =	$(TARGET1)

#==============================================================================

FILENAME1 =	str_lib
TARGET1 =	$(FILENAME1).a

HEADERS1 = 	\
		$(NULL)

CCFILES1 =	\
		str_len.c \
		str_null.c \
		strclean.c \
		strlcat.c \
		strlcpy.c \
		$(NULL)

OBJS1 =		${CCFILES1:.c=.o}

LIBS1 = 	\
		$(NULL)

#==============================================================================

CC =		gcc

COPTS =		-O3 -g -Wall 

INCLUDES = 	\
		$(NULL)

LIBDIRS = 	\
		$(NULL)

ifndef $(TARGET_OS)
TARGET_OS =     UNIX
endif
 
CFLAGS =	$(COPTS) $(INCLUDES) -DDEBUG -D$(TARGET_OS)

LFLAGS =	$(LIBDIRS)

#default compilation rules
%.o:		%.c
		$(CC) -c $< $(CFLAGS) -o $@

all: 		$(TARGETS)

default:	$(TARGETS)

new:		clean default

#==============================================================================

$(TARGET1):	$(OBJS1) $(HEADERS1) $(LIBS1)
		rm -f $(TARGET1)
		ar rcs $(TARGET1) $(OBJS1)
		ranlib $(TARGET1)

indent:
		dos2unix *.h *.c
		indent -kr -i4 *.h *.c 

clean:
		rm -f $(TARGETS) *.o *.a core a.out *~
 
