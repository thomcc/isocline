/* ----------------------------------------------------------------------------
  Copyright (c) 2021, Daan Leijen
  This is free software; you can redistribute it and/or modify it
  under the terms of the MIT License. A copy of the license can be
  found in the "LICENSE" file at the root of this distribution.
-----------------------------------------------------------------------------*/
#pragma once
#ifndef RP_TTY_H
#define RP_TTY_H

#include "common.h"

#if defined(_WIN32)
#include <windows.h>
#include <io.h>
#else
#include <termios.h>
#endif

typedef int code_t;

#define ESC               "\x1B"

#define KEY_NONE          (0)
#define KEY_TAB           (9)
#define KEY_LINEFEED      (10)  // ctrl/shift + enter/tab is considered KEY_LINEFEED
#define KEY_ENTER         (13)
#define KEY_ESC           (27)
#define KEY_SPACE         (32)
#define KEY_BACKSP        (127)

#define KEY_VIRT          0x100   
#define KEY_UP            (KEY_VIRT+0)
#define KEY_DOWN          (KEY_VIRT+1)
#define KEY_LEFT          (KEY_VIRT+2)
#define KEY_RIGHT         (KEY_VIRT+3)
#define KEY_HOME          (KEY_VIRT+4)
#define KEY_END           (KEY_VIRT+5)
#define KEY_DEL           (KEY_VIRT+6)
#define KEY_PAGEUP        (KEY_VIRT+7)
#define KEY_PAGEDOWN      (KEY_VIRT+8)
#define KEY_INS           (KEY_VIRT+9)

#define KEY_F1            (KEY_VIRT+11)
#define KEY_F2            (KEY_VIRT+12)
#define KEY_F3            (KEY_VIRT+13)
#define KEY_F4            (KEY_VIRT+14)
#define KEY_F5            (KEY_VIRT+15)
#define KEY_F6            (KEY_VIRT+16)
#define KEY_F7            (KEY_VIRT+17)
#define KEY_F8            (KEY_VIRT+18)
#define KEY_F9            (KEY_VIRT+19)
#define KEY_F10           (KEY_VIRT+20)
#define KEY_F11           (KEY_VIRT+21)
#define KEY_F12           (KEY_VIRT+22)

#define KEY_CTRP_UP       (KEY_VIRT+100)
#define KEY_CTRP_DOWN     (KEY_VIRT+101)
#define KEY_CTRP_LEFT     (KEY_VIRT+102)
#define KEY_CTRP_RIGHT    (KEY_VIRT+103)
#define KEY_CTRP_HOME     (KEY_VIRT+104)
#define KEY_CTRP_END      (KEY_VIRT+105)
#define KEY_CTRP_DEL      (KEY_VIRT+106)
#define KEY_CTRP_PAGEUP   (KEY_VIRT+107)
#define KEY_CTRP_PAGEDOWN (KEY_VIRT+108)
#define KEY_CTRP_INS      (KEY_VIRT+109)

// We treat ctrl+<tab/enter> and shift+<tab/enter> as '\n' for portability. 
// - shift+tab  works across linux/macos/windows.
// - ctrl+enter works on linux/windows but not macos.


#define KEY_EVENT_RESIZE  (KEY_VIRT+1000)


#define KEY_CTRL(x)  (x - 'A' + 1)

#define TTY_PUSH_MAX (32)

typedef struct tty_s {
  int     fin;  
  bool    raw_enabled;
  bool    is_utf8;
  code_t  pushbuf[TTY_PUSH_MAX];
  ssize_t pushed;
  char    cpushbuf[TTY_PUSH_MAX];
  ssize_t cpushed;
  #if defined(_WIN32)
  HANDLE  hcon;
  DWORD   hcon_orig_mode;
  #else
  struct termios default_ios;
  struct termios raw_ios;
  #endif
} tty_t;

// Primitives
internal bool tty_init(tty_t* tty, int fin);
internal void tty_done(tty_t* tty);
internal void tty_start_raw(tty_t* tty);
internal void tty_end_raw(tty_t* tty);
internal code_t tty_read(tty_t* tty);
internal bool tty_readc_peek(tty_t* tty, char* c);   // used in term.c
internal void tty_code_pushback( tty_t* tty, code_t c );

internal bool code_is_char(tty_t*, code_t c, char* chr );
internal bool code_is_follower( tty_t*, code_t c, char* chr);
internal bool code_is_extended( tty_t*, code_t c, char* chr, int* tofollow);
internal bool code_is_key( tty_t*, code_t c );

#endif // RP_TTY_H
