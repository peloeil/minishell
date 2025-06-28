# 色付き出力
# https://qiita.com/ko1nksm/items/095bdb8f0eca6d327233#%E3%81%8A%E3%81%BE%E3%81%912-%E8%89%B2%E5%A4%89%E6%95%B0%E5%AE%9A%E7%BE%A9
ESC := $(shell printf '\033')
END := $(ESC)[m

BOLD := $(ESC)[1m
FAINT := $(ESC)[2m
ITALIC := $(ESC)[3m
UNDERLINE := $(ESC)[4m
BLINK := $(ESC)[5m
FAST_BLINK := $(ESC)[6m
REVERSE := $(ESC)[7m
CONCEAL := $(ESC)[8m
STRIKE := $(ESC)[9m

GOTHIC := $(ESC)[20m
DOUBLE_UNDERLINE := $(ESC)[21m
NORMAL := $(ESC)[22m
NO_ITALIC := $(ESC)[23m
NO_UNDERLINE := $(ESC)[24m
NO_BLINK := $(ESC)[25m
NO_REVERSE := $(ESC)[27m
NO_CONCEAL := $(ESC)[28m
NO_STRIKE := $(ESC)[29m
BLACK := $(ESC)[30m
RED := $(ESC)[31m
GREEN := $(ESC)[32m
YELLOW := $(ESC)[33m
BLUE := $(ESC)[34m
MAGENTA := $(ESC)[35m
CYAN := $(ESC)[36m
WHITE := $(ESC)[37m
DEFAULT := $(ESC)[39m
BG_BLACK := $(ESC)[40m
BG_RED := $(ESC)[41m
BG_GREEN := $(ESC)[42m
BG_YELLOW := $(ESC)[43m
BG_BLUE := $(ESC)[44m
BG_MAGENTA := $(ESC)[45m
BG_CYAN := $(ESC)[46m
BG_WHITE := $(ESC)[47m
BG_DEFAULT := $(ESC)[49m

# 現在の行を置き換えて出力
# https://stackoverflow.com/questions/2388090/how-to-delete-and-replace-last-line-in-the-terminal-using-bash
CLEAR := $(ESC)[K

# コンパイルの設定
CC := gcc
CFLAGS := -Wall -Wextra -Werror -ggdb3
# CC := clang
# CFLAGS := -Wall -Wextra -Werror
ARFLAGS := -rcs

# ディレクトリの設定
OBJS_DIR := objs
SRCS_DIR := srcs
TESTS_DIR := unit_tests
INCLUDES_DIR := includes
