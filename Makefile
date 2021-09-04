# **************************************************************************** #
#                                                                              #
#    Makefile                                                                  #
#                                                                              #
#    By: Rashoru-Infinity <65536toaru@gmail.com>                               #
#                                                                              #
#    Created: 2021/09/05 04:25:12 by Rashoru-Infinity                          #
#    Updated: 2021/09/05 04:25:12 by Rashoru-Infinity                          #
#                                                                              #
# **************************************************************************** #


PWD	= $(shell pwd)
RM	= rm -f

all	:	gacha printdump

outdir	:
    ifneq ($(shell ls -1 | grep bin), bin)
		mkdir bin
    endif

gacha	:	outdir
	$(MAKE) -C srcs/gacha all
    ifneq ($(shell ls -1 bin | grep gacha), gacha)
		ln -s $(PWD)/srcs/gacha/gacha $(PWD)/bin/gacha
    endif

printdump	:	outdir
	$(MAKE) -C srcs/printdump all
    ifneq ($(shell ls -1 bin | grep printdump), printdump)
		ln -s $(PWD)/srcs/printdump/printdump $(PWD)/bin/printdump
    endif

clean	:
	$(MAKE) -C srcs/gacha clean
	$(MAKE) -C srcs/printdump clean

fclean	:
	$(MAKE) -C srcs/gacha fclean
	$(RM) bin/gacha
	$(MAKE) -C srcs/printdump fclean
	$(RM) bin/printdump

re	: fclean all

.PHONY	:	clean fclean all re gacha printdump
