#include <gdk-pixbuf/gdk-pixbuf.h>
#include <gdk/gdk.h>

int main(int argc, char*argv[])
{

	GdkPixbuf *pixbuf;
	int x; int y;
	guchar red; guchar green; guchar blue; guchar alpha; 
	int width, height, rowstride, n_channels;
	guchar *pixels, *p;

	gdk_init(&argc, &argv);                               
	
	pixbuf = gdk_pixbuf_new(GDK_COLORSPACE_RGB,
				TRUE, 8, 640, 480);
	
	n_channels = gdk_pixbuf_get_n_channels (pixbuf);
	g_assert (gdk_pixbuf_get_colorspace (pixbuf) == GDK_COLORSPACE_RGB);
	g_assert (gdk_pixbuf_get_bits_per_sample (pixbuf) == 8);
//	g_assert (gdk_pixbuf_get_has_alpha (pixbuf));
	g_assert (n_channels == 4);
	
	width = gdk_pixbuf_get_width (pixbuf);
	height = gdk_pixbuf_get_height (pixbuf);

	//g_assert (x >= 0 && x < width);
	//g_assert (y >= 0 && y < height);

	rowstride = gdk_pixbuf_get_rowstride (pixbuf);
	pixels = gdk_pixbuf_get_pixels (pixbuf);

	red = 0xff;
	green = 0xff;
	blue = 0xff;
	alpha = 0xff;
	
	for (x = 0; x < width; ++x) {
		for (y = 0; y < height; ++y) {
			p = pixels + y * rowstride + x * n_channels;
			p[0] = red;
			p[1] = green;
			p[2] = blue;
			p[3] = alpha;
		}
	}
	gdk_pixbuf_save (pixbuf, "f.png", "png", NULL, NULL);
	g_object_unref(pixbuf);

	pixbuf = gdk_pixbuf_new_from_file("f.png", NULL);
	printf("%d\n", gdk_pixbuf_get_has_alpha (pixbuf));
	g_object_unref(pixbuf);

	return 0;
}
