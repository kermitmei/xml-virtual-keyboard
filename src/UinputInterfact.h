#ifndef _UINPUTINTERFACT_H_
#define _UINPUTINTERFACT_H_

#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/input.h>
#include <linux/uinput.h>
#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

extern int uinp_fd;
extern struct uinput_user_dev uinp;  // uInput device structure
extern struct input_event event;     // Input device structure


int setup_uinput_device();

void send_click_events();

void send_a_button();

void send_a_key(__u16 keyCode);

void send_press_key(__u16 keyCode);
void send_release_key(__u16 keyCode);
#endif//_UINPUTINTERFACT_H_
