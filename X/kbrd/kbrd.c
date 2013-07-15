#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _(t) t
#include <gtk/gtk.h>
#include <gdk/gdkx.h>
#include <X11/Xlib.h>
#include "keys_management.h"

#define RCDIR       "mcs_settings"
#define OLD_RCDIR   "settings"

#define CHANNEL1    "settings"
#define RCFILE1     "gtk.xml"

#define CHANNEL2    "keyboard"
#define RCFILE2     "keyboard.xml"

#define CHANNEL3    "shortcuts"
#define RCFILE3     "shortcuts.xml"
static gboolean
is_modifier (guint keycode)
{
    XModifierKeymap *keymap;
    gboolean result = FALSE;
    gint n;
    GdkDisplay *gdisplay;

    gdisplay = gdk_display_get_default ();

    keymap = XGetModifierMapping (gdk_display);
    for (n = 0; n < keymap->max_keypermod * 8; ++n)
    {
        if (keycode == keymap->modifiermap[n])
        {
            result = TRUE;
            break;
        }
    }

    XFreeModifiermap (keymap);

    return result;
}

/*
typedef struct _KeyboardMcsDialog KeyboardMcsDialog;
struct _KeyboardMcsDialog
{

    gboolean theme_modified;

    GtkWidget *checkbutton_blink;
    GtkWidget *checkbutton_repeat;
    GtkWidget *checkbutton_sticky;
    GtkWidget *checkbutton_sticky_ltl;
    GtkWidget *checkbutton_sticky_tk;
    GtkWidget *checkbutton_bounce;
    GtkWidget *scale_debounce_delay;
    GtkWidget *checkbutton_slow;
    GtkWidget *scale_slow_keys_delay;

    GtkWidget *scale_repeat_rate;
    GtkWidget *scale_repeat_delay;
    GtkWidget *scale_blink_time;
    GtkWidget *dialog_keyboard;
    GtkWidget *theme_swindow;
    GtkWidget *treeview_maps;

    GtkWidget *scrolledwindow_themes;
    GtkWidget *treeview_themes;
    GtkWidget *button_add_theme;
    GtkWidget *button_del_theme;
    GtkWidget *menu_popup_themes;
    GtkWidget *menuitem_popup_rename_theme;
    GtkWidget *menuitem_popup_add_theme;
    GtkWidget *menuitem_popup_del_theme;

    GtkWidget *scrolledwindow_shortcuts;
    GtkWidget *treeview_shortcuts;
    GtkWidget *button_add_shortcut;
    GtkWidget *button_del_shortcut;
    GtkWidget *menu_popup_shortcuts;
    GtkWidget *menuitem_popup_edit_shortcut;
    GtkWidget *menuitem_popup_add_shortcut;
    GtkWidget *menuitem_popup_del_shortcut;

    GtkWidget *button_close;
    GtkWidget *button_help;
};

GtkWidget* shortcuts_plugin_create_dialog (KeyboardMcsDialog *);
void shortcuts_plugin_setup_dialog (KeyboardMcsDialog *);
void shortcuts_plugin_init(McsPlugin *);
void shortcuts_plugin_load_theme (KeyboardMcsDialog *);
void shortcuts_plugin_save_theme (KeyboardMcsDialog *);
gboolean shortcuts_plugin_save_settings (McsPlugin *);
*/
/****************************/
/* Low-level events filter  */
/****************************/
static int wait_release;

static void
handleKeyPress (XKeyPressedEvent * ev)
{
    GSList *element;
    int state;
    printf("press : %d %d\n", ev->state, ev->keycode);
    state = ev->state & MODIFIER_MASK;

    if (wait_release)
    {
        return;
    }
}

static void
handleKeyRelease (XKeyReleasedEvent * ev)
{
    wait_release = FALSE;
}

static void
handleMappingNotify (XMappingEvent * ev)
{
    GSList *element;

    /* Clear up the flag as the keyboard mapping changes, we may never receive the release event */
    wait_release = FALSE;

    /* Refreshes the stored modifier and keymap information */
    XRefreshKeyboardMapping (ev);

    /* Update internal modifiers masks if necessary */
    if (ev->request == MappingModifier)
    {
        init_modifiers ();
    }

    /* Regrab all keys if the notify is for keyboard (ie not pointer) */
    gdk_error_trap_push ();
    if (ev->request != MappingPointer)
    {
        
    }
    gdk_flush();
    gdk_error_trap_pop ();
}

static void
handle_event (XEvent * ev)
{
	switch (ev->type)
	{
        case KeyPress:
		handleKeyPress ((XKeyPressedEvent *) ev);
		break;
        case KeyRelease:
		handleKeyRelease ((XKeyReleasedEvent *) ev);
		break;
        case MappingNotify:
		handleMappingNotify ((XMappingEvent *) ev);
		break;
        default:
		break;
	}
}

static GdkFilterReturn
event_filter (GdkXEvent *gdk_xevent, GdkEvent *event, gpointer data)
{
	printf("eent\n");
	handle_event ((XEvent *) gdk_xevent);

	return GDK_FILTER_CONTINUE;
}

static gboolean
cb_compose_shortcut (GtkWidget * widget, GdkEventKey * event, gpointer data)
{
	//KeyboardMcsDialog *dialog = (KeyboardMcsDialog *) data;
	GdkModifierType consumed_modifiers = 0;
	gchar shortcut_string[80] = "";
	guint keyval;
	guint modifiers;
	gchar *accelerator;
	gchar **shortcuts;
	gchar **current_shortcut;
	//shortcut_tree_foreach_struct stfs;
	GtkTreeModel *model;
	GtkTreeSelection *selection;
	GtkTreeIter iter;
	GSList *element;
	gchar *command;
	gboolean res;
	printf("%s\n", __func__);
	if (is_modifier (event->hardware_keycode))
		return TRUE;

	res = gdk_keymap_translate_keyboard_state (gdk_keymap_get_default (), 
					     event->hardware_keycode, event->state, event->group, NULL, NULL, NULL, &consumed_modifiers);
	printf("event key: %d %d; (%d)\n", event->keyval, event->hardware_keycode, res);
	keyval = gdk_keyval_to_lower (event->keyval);
	printf("event keyval: %d\n", keyval);
	return FALSE;
	switch (keyval)
	{
        case GDK_ISO_Left_Tab:
		keyval = GDK_Tab;
		break;
        case GDK_ISO_Level3_Latch:
        case GDK_ISO_Level3_Lock:
        case GDK_ISO_Level3_Shift:
        case GDK_Scroll_Lock:
		return TRUE;
		break;
        default:
		break;
	}
	/* Release keyboard */
	gdk_keyboard_ungrab (GDK_CURRENT_TIME);

	/*
	 * gtk_accelerator_get_default_mod_mask () limits the number of modifiers.
	 * That's a good thing because we don't want the "fake" modifiers such as
	 * Scroll/Num/Caps Lock to be taken into account.
	 *
	 * Unfortunately, at this time of writing, gdk doesn't know about all of the
	 * modifiers, like META, SUPER or HYPER, but just SHIFT, ALT and CONTROL...
	 *
	 * It means that ppl won't be able to use the "Windows" key as a modifier...
	 * Too bad, that's life, you may gently ask the gtk+ maintainers about it.
	 *
	 * Things may change in the future? See this thread:
	 *
	 * http://mail.gnome.org/archives/gtk-devel-list/2005-September/msg00024.html
	 *
	 * (Olivier)
	 */

	modifiers = event->state & (~consumed_modifiers | GDK_MODIFIER_MASK);
	modifiers = modifiers & gtk_accelerator_get_default_mod_mask ();
	accelerator = gtk_accelerator_name (keyval, modifiers);
	printf("acc: %s; (%d, %d, %d)\n", accelerator, strlen(accelerator), keyval, modifiers);
	shortcuts = g_strsplit_set (accelerator, "<>", 0);	
	current_shortcut = shortcuts;
	while (*current_shortcut)
	{
		if (strlen (*current_shortcut))
		{
			strcat (shortcut_string, *current_shortcut);
			strcat (shortcut_string, "+");
		}
		current_shortcut++;
	}
	printf("step 1\n");
	shortcut_string[strlen (shortcut_string) - 1] = '\0';       /* replace the trailing '+' */
	g_free (accelerator);
	g_strfreev (shortcuts);
	printf("step 2\n");
	/* check if shorcut already exists */
	//selection = gtk_tree_view_get_selection (GTK_TREE_VIEW (dialog->treeview_shortcuts));
	//gtk_tree_selection_get_selected (selection, &model, &iter);

	/*stfs.shortcut = shortcut_string;
	stfs.found = FALSE;
	stfs.selection = selection;
	gtk_tree_model_foreach (model, &shortcut_tree_foreach_func, &stfs);

	if (stfs.found)
	{
		GtkTreePath *path_old;
		GtkTreeIter iter_old;
		GtkWidget *dialog;

		dialog = gtk_message_dialog_new (GTK_WINDOW (widget),
						 GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_QUESTION, GTK_BUTTONS_YES_NO, _("Shortcut already in use !\nAre you sure you want to use it ?"));

		if (gtk_dialog_run (GTK_DIALOG (dialog)) == GTK_RESPONSE_NO)
		{
			gtk_dialog_response (GTK_DIALOG (widget), GTK_RESPONSE_OK);
			return TRUE;
		}

		path_old = gtk_tree_path_new_from_string (stfs.path);
		gtk_tree_model_get_iter (model, &iter_old, path_old);
		g_free (stfs.path);
		gtk_tree_path_free (path_old);

		gtk_list_store_set (GTK_LIST_STORE (model), &iter_old, COLUMN_SHORTCUT, "", -1);
	}

	gtk_list_store_set (GTK_LIST_STORE (model), &iter, COLUMN_SHORTCUT, shortcut_string, -1);

	gtk_tree_model_get (model, &iter, COLUMN_COMMAND, &command, -1);
	*/
	gdk_error_trap_push ();/*
	if ((element = search_key_in_shortcut_list (shortcut_string)) != NULL)
	{
		/* Change the command associated with the shortcut 
		launcher *launcher_data = (launcher *) element->data;

		free_launcher_data (launcher_data);
		launcher_data->key = parseKeyString (shortcut_string);
		launcher_data->command = g_strdup (command);
		grab_key (launcher_data->key);
	}
	else
	{
		/* Add the shortcut to the list 
		launcher *launcher_data;

		launcher_data = g_new (launcher, 1);
		launcher_data->key = parseKeyString (shortcut_string);
		launcher_data->command = g_strdup (command);
		grab_key (launcher_data->key);
		shortcut_list = g_slist_append (shortcut_list, launcher_data);
	}*/
	gdk_flush();
	gdk_error_trap_pop ();
	//g_free (command);

	/* End operations */
	//dialog->theme_modified = TRUE;
	gtk_dialog_response (GTK_DIALOG (widget), GTK_RESPONSE_OK);

	return TRUE;
}


void show_dialog(void)
{
/*	GtkTreeSelection *selection;
        GtkTreeModel *model;
        GtkTreeIter iter;
*/      gchar *command = NULL;
        gchar *shortcut = NULL;
        GtkWidget *dialog_compose;
        GtkWidget *hbox;
        GdkPixbuf *icon = NULL;
        GtkWidget *image;
        GtkWidget *label;
        GtkWidget *button;
        GSList *element;
        gint response;
        gchar *dialog_text = NULL;

        /* Get shortcut name */

        dialog_text = g_markup_printf_escaped ("<i>%s</i>\n<b>%s</b>", _("Set shortcut for command:"), command);

        /* Create dialog */
        dialog_compose = gtk_dialog_new_with_buttons (_("Set shortcut"), 
						      NULL,//GTK_WINDOW (gtk_widget_get_toplevel(dialog->dialog_keyboard)),
						      GTK_DIALOG_MODAL, NULL);

	button = gtk_button_new_from_stock(GTK_STOCK_CANCEL);
        gtk_widget_show (button);
        gtk_dialog_add_action_widget (GTK_DIALOG (dialog_compose), button, GTK_RESPONSE_CANCEL);

        button = gtk_button_new_from_stock(GTK_STOCK_CLEAR);
        gtk_widget_show (button);
        gtk_dialog_add_action_widget (GTK_DIALOG (dialog_compose), button, GTK_RESPONSE_NO);
#define BORDER 5
        hbox = gtk_hbox_new (FALSE, BORDER);
        gtk_container_set_border_width (GTK_CONTAINER (hbox), BORDER);
        gtk_widget_show (hbox);
/*
        icon = xfce_themed_icon_load ("xfce4-keys.png", 48);
        if (icon)
        {
		image = gtk_image_new_from_pixbuf (icon);
		gtk_widget_show (image);
		gtk_box_pack_start (GTK_BOX (hbox), image, FALSE, TRUE, 0);
        }*/

        label = gtk_label_new (dialog_text);
        gtk_label_set_use_markup (GTK_LABEL (label), TRUE);
        gtk_label_set_justify (GTK_LABEL (label), GTK_JUSTIFY_CENTER);
        gtk_widget_show (label);
        gtk_box_pack_start (GTK_BOX (hbox), label, FALSE, TRUE, 0);

        gtk_box_pack_start (GTK_BOX (GTK_DIALOG (dialog_compose)->vbox), hbox, FALSE, TRUE, 0);

        /* Center cancel button */
        gtk_button_box_set_layout (GTK_BUTTON_BOX (GTK_DIALOG (dialog_compose)->action_area), GTK_BUTTONBOX_SPREAD);

        /* Connect signals */
        g_signal_connect (G_OBJECT (dialog_compose), "key-release-event", G_CALLBACK (cb_compose_shortcut), NULL);//dialog);

        /* Take control on the keyboard */
        if (gdk_keyboard_grab (gtk_widget_get_root_window (dialog_compose), TRUE, GDK_CURRENT_TIME) != GDK_GRAB_SUCCESS)
        {
		g_warning ("Cannot grab the keyboard");
		g_free (dialog_text);
		g_free (shortcut);
		g_free (command);
		return;
        }

        /* Stop our own event filter so that it doesn's interfere with gtk+ */
        gdk_window_remove_filter (NULL, event_filter, (gpointer) NULL);

        /* Show dialog */
	printf("run\n");
        response = gtk_dialog_run (GTK_DIALOG (dialog_compose));
	printf("run\n");
        /* Put back our event filter */
	gdk_window_add_filter (NULL, event_filter, (gpointer) NULL);
	printf("filter\n");
        if (response == GTK_RESPONSE_NO)
        {
		printf("no\n");
		//gtk_list_store_set (GTK_LIST_STORE (model), &iter, COLUMN_SHORTCUT, "", -1);
		//dialog->theme_modified = TRUE;
        }else {
		printf("yes\n");
	}

        /* Release keyboard if not yet done */
        gdk_keyboard_ungrab (GDK_CURRENT_TIME);

        gtk_widget_destroy (dialog_compose);
        g_free (dialog_text);
        g_free (command);
        g_free (shortcut);
}

int main(int argc, char*argv[])
{
	GtkWidget *win;
	gtk_init(&argc, &argv);	
	gdk_window_add_filter (NULL, event_filter, (gpointer) NULL);
	/*
	win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_widget_show(win);
	gtk_main();
	//*/
	show_dialog();
	
	return 0;
}
