#include <gtk/gtk.h>
#include <glib/gi18n.h>

GtkStatusIcon *icon;
GtkMenu *menu;

static void
gpm_tray_icon_popup_menu_cb (GtkStatusIcon *status_icon,
                             guint          button,
                             guint32        timestamp,
                             gpointer icon)
{
	printf("%s\n", __func__);
//	gtk_widget_show_all (GTK_WIDGET (menu));
	gtk_menu_popup (GTK_MENU(menu), NULL, NULL,
                        gtk_status_icon_position_menu, status_icon,
                        button, timestamp);

}
static void
gpm_tray_icon_activate_cb (GtkStatusIcon *status_icon,
                           void   *icon)
{

	printf("%s\n", __func__);   
//	gtk_widget_show_all (GTK_WIDGET (menu));
        gtk_menu_popup (GTK_MENU(menu), NULL, NULL,
                        gtk_status_icon_position_menu, status_icon,
                        1, gtk_get_current_event_time());

}

void create_menu()
{
	menu = (GtkMenu*) gtk_menu_new ();
        GtkWidget *item;
        GtkWidget *image;
 
        /* Preferences */
        item = gtk_image_menu_item_new_with_mnemonic (_("_Preferences"));
        image = gtk_image_new_from_icon_name (GTK_STOCK_PREFERENCES, GTK_ICON_SIZE_MENU);
        gtk_image_menu_item_set_image (GTK_IMAGE_MENU_ITEM (item), image);
        //g_signal_connect (G_OBJECT (item), "activate",  G_CALLBACK (gpm_tray_icon_show_preferences_cb), icon);
        gtk_menu_shell_append (GTK_MENU_SHELL (menu), item);

        /* Statistics */
        item = gtk_image_menu_item_new_with_mnemonic (_("Power _History"));
        image = gtk_image_new_from_icon_name (GTK_STOCK_OK, GTK_ICON_SIZE_MENU);
        gtk_image_menu_item_set_image (GTK_IMAGE_MENU_ITEM (item), image);
        //g_signal_connect (G_OBJECT (item), "activate",     G_CALLBACK (gpm_tray_icon_show_statistics_cb), icon);
        gtk_menu_shell_append (GTK_MENU_SHELL (menu), item);

        /* Separator for HIG? */
        item = gtk_separator_menu_item_new ();
        gtk_menu_shell_append (GTK_MENU_SHELL (menu), item);

        /* Help */
        item = gtk_image_menu_item_new_with_mnemonic (_("_Help"));
        image = gtk_image_new_from_icon_name (GTK_STOCK_HELP, GTK_ICON_SIZE_MENU);
        gtk_image_menu_item_set_image (GTK_IMAGE_MENU_ITEM (item), image);
        //g_signal_connect (G_OBJECT (item), "activate",  G_CALLBACK (gpm_tray_icon_show_help_cb), icon);
        gtk_menu_shell_append (GTK_MENU_SHELL (menu), item);
gtk_widget_show_all (GTK_WIDGET (menu));
}
int main(int argc, char *argv[])
{
	gtk_init(&argc, &argv);
	
	create_menu();
	icon = gtk_status_icon_new_from_file("./emacs.png");
	gtk_status_icon_set_tooltip(icon, "hello");
	g_signal_connect_object (G_OBJECT(icon),
                                 "popup_menu",
                                 G_CALLBACK(gpm_tray_icon_popup_menu_cb),
                                 icon, 0);
        g_signal_connect_object (G_OBJECT(icon),
                                 "activate",
                                 G_CALLBACK (gpm_tray_icon_activate_cb),
                                 icon, 0);

	gtk_main();
	return 0;
}
