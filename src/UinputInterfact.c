#include "UinputInterfact.h"

/* Globals */
int uinp_fd = -1;
struct uinput_user_dev uinp;  // uInput device structure
struct input_event event;     // Input device structure

#ifdef _X86_UINPUT_

/* Setup the uinput device */
int setup_uinput_device()
{
    // Temporary variable
    int i=0;
    // Open the input device
    uinp_fd = open("/dev/uinput", O_WRONLY | O_NDELAY);
    if (uinp_fd == 0)
    {
	printf("Unable to open /dev/uinput\n");
	return -1;
    }

    memset(&uinp,0,sizeof(uinp)); // Intialize the uInput device to NULL
    strncpy(uinp.name, "PolyVision Touch Screen", UINPUT_MAX_NAME_SIZE);
    uinp.id.version = 4;
    uinp.id.bustype = BUS_USB;
    // Setup the uinput device
    ioctl(uinp_fd, UI_SET_EVBIT, EV_KEY);
    ioctl(uinp_fd, UI_SET_EVBIT, EV_REL);
    ioctl(uinp_fd, UI_SET_RELBIT, REL_X);
    ioctl(uinp_fd, UI_SET_RELBIT, REL_Y);
    for (i=0; i < 256; i++) {
	ioctl(uinp_fd, UI_SET_KEYBIT, i);
    }

    ioctl(uinp_fd, UI_SET_KEYBIT, BTN_MOUSE);
    ioctl(uinp_fd, UI_SET_KEYBIT, BTN_TOUCH);
    ioctl(uinp_fd, UI_SET_KEYBIT, BTN_MOUSE);
    ioctl(uinp_fd, UI_SET_KEYBIT, BTN_LEFT);
    ioctl(uinp_fd, UI_SET_KEYBIT, BTN_MIDDLE);
    ioctl(uinp_fd, UI_SET_KEYBIT, BTN_RIGHT);
    ioctl(uinp_fd, UI_SET_KEYBIT, BTN_FORWARD);
    ioctl(uinp_fd, UI_SET_KEYBIT, BTN_BACK);


    /* Create input device into input sub-system */
    ssize_t ret = write(uinp_fd, &uinp, sizeof(uinp));
    if(ret == 0) {
	printf("ret == 0\n");
	return 0;
    }


    if (ioctl(uinp_fd, UI_DEV_CREATE))
    {
	printf("Unable to create UINPUT device.");
	return -1;
    }
    return 1;
}

void send_click_events( )
{
    // Move pointer to (0,0) location
    memset(&event, 0, sizeof(event));
    gettimeofday(&event.time, NULL);
    event.type = EV_REL;
    event.code = REL_X;
    event.value = 100;
    ssize_t ret = write(uinp_fd, &event, sizeof(event));
    event.type = EV_REL;
    event.code = REL_Y;
    event.value = 100;
    ret = write(uinp_fd, &event, sizeof(event));
    event.type = EV_SYN;
    event.code = SYN_REPORT;
    event.value = 0;
    ret = write(uinp_fd, &event, sizeof(event));
    // Report BUTTON CLICK - PRESS event
    memset(&event, 0, sizeof(event));
    gettimeofday(&event.time, NULL);
    event.type = EV_KEY;
    event.code = BTN_LEFT;
    event.value = 1;
    ret = write(uinp_fd, &event, sizeof(event));
    event.type = EV_SYN;
    event.code = SYN_REPORT;
    event.value = 0;
    ret = write(uinp_fd, &event, sizeof(event));
    // Report BUTTON CLICK - RELEASE event
    memset(&event, 0, sizeof(event));
    gettimeofday(&event.time, NULL);
    event.type = EV_KEY;
    event.code = BTN_LEFT;
    event.value = 0;
    ret = write(uinp_fd, &event, sizeof(event));

    event.type = EV_SYN;
    event.code = SYN_REPORT;
    event.value = 0;
    ret = write(uinp_fd, &event, sizeof(event));
}

void send_a_button()
{
    // Report BUTTON CLICK - PRESS event
    memset(&event, 0, sizeof(event));
    gettimeofday(&event.time, NULL);
    event.type = EV_KEY;
    event.code = KEY_A;
    event.value = 1;
    ssize_t ret = write(uinp_fd, &event, sizeof(event));
    event.type = EV_SYN;
    event.code = SYN_REPORT;
    event.value = 0;
    ret = write(uinp_fd, &event, sizeof(event));
    // Report BUTTON CLICK - RELEASE event
    memset(&event, 0, sizeof(event));
    gettimeofday(&event.time, NULL);
    event.type = EV_KEY;
    event.code = KEY_A;
    event.value = 0;
    ret = write(uinp_fd, &event, sizeof(event));

    event.type = EV_SYN;
    event.code = SYN_REPORT;
    event.value = 0;
    ret = write(uinp_fd, &event, sizeof(event));
}

void send_a_key(__u16 keyCode)
{
    // Report BUTTON CLICK - PRESS event
    //for gentoo keycode
    keyCode = keyCode - 8;
    
    memset(&event, 0, sizeof(event));
    gettimeofday(&event.time, NULL);
    event.type = EV_KEY;
    event.code = keyCode;
    event.value = 1;
    ssize_t ret = write(uinp_fd, &event, sizeof(event));


    event.type = EV_SYN;
    event.code = SYN_REPORT;
    event.value = 0;
    ret = write(uinp_fd, &event, sizeof(event));

    // Report BUTTON CLICK - RELEASE event
    memset(&event, 0, sizeof(event));
    gettimeofday(&event.time, NULL);
    event.type = EV_KEY;
    event.code = keyCode;
    event.value = 0;
    ret = write(uinp_fd, &event, sizeof(event));

    event.type = EV_SYN;
    event.code = SYN_REPORT;
    event.value = 0;
    ret = write(uinp_fd, &event, sizeof(event));
}

void send_press_key(__u16 keyCode)
{
    //for gentoo keycode
    keyCode = keyCode - 8;

    // Report BUTTON CLICK - PRESS event
    memset(&event, 0, sizeof(event));
    gettimeofday(&event.time, NULL);
    event.type = EV_KEY;
    event.code = keyCode;
    event.value = 1;
    ssize_t ret = write(uinp_fd, &event, sizeof(event));

    event.type = EV_SYN;
    event.code = SYN_REPORT;
    event.value = 0;
    ret = write(uinp_fd, &event, sizeof(event));
}

void send_release_key(__u16 keyCode)
{
    //for gentoo keycode
    keyCode = keyCode - 8;

    // Report BUTTON CLICK - RELEASE event
    memset(&event, 0, sizeof(event));
    gettimeofday(&event.time, NULL);
    event.type = EV_KEY;
    event.code = keyCode;
    event.value = 0;
    ssize_t ret = write(uinp_fd, &event, sizeof(event));

    event.type = EV_SYN;
    event.code = SYN_REPORT;
    event.value = 0;
    ret = write(uinp_fd, &event, sizeof(event));
}

#else  //No _X86_UINPUT_

int setup_uinput_device()
{
    return 0;
}

void send_click_events()
{
    return ;
}

void send_a_button()
{
    return ;
}

void send_a_key(__u16 keyCode)
{
    keyCode = 0;
    return ;
}


#endif //_X86_UINPUT_
