#include <gtk/gtk.h>

void enum_fmts(GdkPixbufFormat *f)
{
	char **list, **p;
	list = gdk_pixbuf_format_get_mime_types(f);
	for (p = list; *p; ++p) { 
		static int i = 0;		
		printf("\t%d %s\n", i, *p);
		++i;
	}

}

int main(int argc, char *argv[])
{
	GSList *l, *p;
	gtk_init(&argc, &argv);
	l = gdk_pixbuf_get_formats();
	for (p = l; p; p = p->next) {
		static int i = 0;
		printf("format %d\n", i);
		enum_fmts((GdkPixbufFormat*)p->data);
		++i;
	}
	g_slist_free(l);
	return 0;
}
