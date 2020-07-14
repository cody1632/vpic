#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include "vpic.h"

struct Page page;

struct PageLine *vpicPageAddLine(void) {
	if (debug)
		printf("## vpicPageAddLine(): start\n");
	struct PageLine *pl = malloc(sizeof(struct PageLine));
	if (page.first_line == NULL) {
		page.first_line = pl;
		pl->prev = NULL;
		pl->rank = 1;
	}
	else {
		page.last_line->next = pl;
		pl->prev = page.last_line;
		pl->rank = pl->prev->rank + 1;
	}
	pl->first_image = NULL;
	pl->last_image = NULL;
	page.last_line = pl;
	page.images_per_line = winW/110;
	++page.total_lines;
	if (debug) {
		printf("  images_per_line: %u\n", page.images_per_line);
		printf("  total_lines: %u\n", page.total_lines);
		printf("## vpicPageAddLine(): end (#%u)\n", page.total_lines);
	}
	
	return pl;
}

void vpicPageLineAddImage(struct ImageNode *in) {
	struct PageLine *pl;
	if (page.first_line == NULL || (in->rank % page.images_per_line) == 0)
		pl = vpicPageAddLine();
	else
		pl = page.last_line;
	
	if (pl->first_image == NULL)
		pl->first_image = in;
	
	pl->last_image = in;
	
	++page.total_images;
}

