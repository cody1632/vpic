#include <stdio.h>
#include <string.h>
#include <X11/Xlib.h>

#include "vpic.h"

unsigned int draw_once = 10;
unsigned int fps;
char strfps[20];

void vpicRender(void) {
	struct PageLine *pl = page.first_line;
	struct ImageNode *in = pl->first_image;
	int cnt = 0;
	while (1) {
		++cnt;
		XPutImage(display, window, gc, in->ximage, 0, 0, 
			in->x, in->y, 100, 100);
		XDrawImageString(display, window, gc, in->x, in->y + 110,
			in->original_name, strlen(in->original_name));

		if (in->next == pl->last_image) {
			if (pl->next == NULL)
				break;
			else {
				pl = pl->next;
				if (pl->first_image != NULL)
					in = pl->first_image;
				else if (in->next != NULL)
					in = in->next;
			}
		}
		else if (in->next == NULL)
			break;
		else
			in = in->next;
	}
}

