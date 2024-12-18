# 色付き出力
# https://qiita.com/ko1nksm/items/095bdb8f0eca6d327233#%E3%81%8A%E3%81%BE%E3%81%912-%E8%89%B2%E5%A4%89%E6%95%B0%E5%AE%9A%E7%BE%A9
ESC := $(shell printf '\033')
END := $(ESC)[m

RED := $(ESC)[31m
GREEN := $(ESC)[32m
CYAN := $(ESC)[36m

# 現在の行を置き換えて出力
# https://stackoverflow.com/questions/2388090/how-to-delete-and-replace-last-line-in-the-terminal-using-bash
CLEAR := $(ESC)[K

# コンパイルの設定
CC := cc
CFLAGS := -Wall -Wextra -Werror
ARFLAGS := -rcs

# ディレクトリの設定
OBJS_DIR := objs
SRCS_DIR := srcs
TESTS_DIR := tests
INCLUDES_DIR := includes
