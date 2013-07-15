#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <X11/Xlib.h>
#include <X11/Xauth.h>

Display *find_x_display()
{
	int i;
	Display *dpy;
	char dname[] = ":0";
	for (i = 0; i < 10; ++i) {
		dname[1] = i + '0';
		dpy = XOpenDisplay(dname);
		if (dpy) {
			printf("dname: %s\n", dname);
			return dpy;
		}
	}
	return NULL;
}
#include <xcb/xcb.h>

int main()
{
	Display *dpy;
#if 0
	char *fname = XauFileName();
	printf("aufile: %s\n", fname);
	setenv("XAUTHORITY", fname, 1);
	dpy = find_x_display();
	if (dpy == NULL) {
		printf("couldn't open display\n");
		return 1;
	}
	printf("display opened\n");
#endif
	dpy=XOpenDisplay(":1.0");
	for (;;) {
		printf("still alive\n");
		sleep(2);
	}
	XCloseDisplay(dpy);
	return 0;
}
