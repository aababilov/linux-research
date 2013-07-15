#include <gtk/gtk.h>
#include <gtkextra/gtkextra.h>

GtkWidget *window;
GtkWidget *plot;
GdkDrawable *pixmap;
GtkWidget *button;
GtkWidget *box1, *darea;
int ttl;

gdouble plfunc(GtkPlot *plot, GtkPlotData *data,
	       gdouble x,
	       gboolean *error)
{
	return 0;
}

static void hello(GtkWidget *widget,
		  gpointer   data )
{
	GdkRectangle r = {0, 0, 200, 20};
	char c;
	printf("paint\n");
	ttl = 0;
	gtk_plot_set_range(GTK_PLOT(plot), 0, 10, 2, 8);
	gtk_plot_paint(GTK_PLOT(plot));
	printf("hello %d\n", gtk_plot_axis_visible(
		       gtk_plot_get_axis(GTK_PLOT(plot), GTK_PLOT_AXIS_LEFT)));
	gtk_plot_refresh(GTK_PLOT(plot), &r);
}

int main(int argc, char *argv[])
{
	GtkPlotData *d;
	
	gtk_init(&argc, &argv);
	
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    
	g_signal_connect(G_OBJECT(window), "delete_event",
			 G_CALLBACK(gtk_false), NULL);    
	g_signal_connect(G_OBJECT(window), "destroy",
			 G_CALLBACK(gtk_main_quit), NULL);
    
	gtk_container_set_border_width(GTK_CONTAINER(window), 10);
	pixmap = gdk_pixmap_new(NULL, 640, 480, 24);
    
	plot = gtk_plot_new_with_size(pixmap, 640, 480);
	
	d = gtk_plot_add_function(GTK_PLOT(plot), plfunc);
	button = gtk_button_new_with_mnemonic("_Hello World");
	g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(hello), NULL);
	box1 = gtk_vbox_new(FALSE, 0);
	darea = gtk_drawing_area_new();
	
	gtk_widget_set_size_request(darea, 400, 200);
	gtk_widget_set_size_request(plot, 400, 200);
	gtk_widget_set_size_request(GTK_WIDGET(d), 400, 200);
	gtk_container_add(GTK_CONTAINER(window), box1);
    
	gtk_container_add(GTK_CONTAINER(box1), darea);
	gtk_container_add(GTK_CONTAINER(box1), button);
	gtk_container_add(GTK_CONTAINER(box1), plot);
	gtk_container_add(GTK_CONTAINER(box1), GTK_WIDGET(d));
	gtk_widget_show_all(window);
	gtk_main();
    
	return 0;
}
