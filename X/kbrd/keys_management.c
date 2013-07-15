/*      $Id: keys_management.c 25675 2007-05-04 08:11:59Z olivier $

        This program is free software; you can redistribute it and/or modify
        it under the terms of the GNU General Public License as published by
        the Free Software Foundation; either version 2, or (at your option)
        any later version.
 
        This program is distributed in the hope that it will be useful,
        but WITHOUT ANY WARRANTY; without even the implied warranty of
        MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
        GNU General Public License for more details.
 
        You should have received a copy of the GNU General Public License
        along with this program; if not, write to the Free Software
        Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 
        keys_management - (c) 2002-2006 Olivier Fourdan
 
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <X11/Xlib.h>
#include <X11/keysym.h>

#include <glib.h>
#include <gdk/gdk.h>
#include <gdk/gdkx.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "keys_management.h"

unsigned int KeyMask = 0;
unsigned int ButtonMask = 0;
unsigned int ButtonKeyMask = 0;
unsigned int AltMask = 0;
unsigned int MetaMask = 0;
unsigned int NumLockMask = 0;
unsigned int ScrollLockMask = 0;
unsigned int SuperMask = 0;
unsigned int HyperMask = 0;

MyKey *
parseKeyString (char *str)
{
    MyKey *my_key;
    GdkDisplay *gdisplay;
    char *k;

    gdisplay = gdk_display_get_default ();

    g_return_val_if_fail (str != NULL, NULL);

    my_key = g_new (MyKey, 1);
    my_key->keycode = 0;
    my_key->modifier = 0;

    k = strrchr (str, '+');
    if (k)
    {
        /* There is a modifier */
        gchar *tmp;

        tmp = g_ascii_strdown ((gchar *) str, strlen (str));

        my_key->keycode = XKeysymToKeycode (GDK_DISPLAY_XDISPLAY (gdisplay), XStringToKeysym (++k));
        if (strstr (tmp, "shift"))
        {
            my_key->modifier = my_key->modifier | ShiftMask;
        }
        if (strstr (tmp, "control"))
        {
            my_key->modifier = my_key->modifier | ControlMask;
        }
        if (strstr (tmp, "alt"))
        {
            my_key->modifier = my_key->modifier | AltMask;
        }
        if (strstr (tmp, "meta"))
        {
            my_key->modifier = my_key->modifier | MetaMask;
        }
        if (strstr (tmp, "super"))
        {
            my_key->modifier = my_key->modifier | SuperMask;
        }
        if (strstr (tmp, "hyper"))
        {
            my_key->modifier = my_key->modifier | HyperMask;
        }
        if (strstr (tmp, "mod1"))
        {
            my_key->modifier = my_key->modifier | Mod1Mask;
        }
        if (strstr (tmp, "mod2"))
        {
            my_key->modifier = my_key->modifier | Mod2Mask;
        }
        if (strstr (tmp, "mod3"))
        {
            my_key->modifier = my_key->modifier | Mod3Mask;
        }
        if (strstr (tmp, "mod4"))
        {
            my_key->modifier = my_key->modifier | Mod4Mask;
        }
        if (strstr (tmp, "mod5"))
        {
            my_key->modifier = my_key->modifier | Mod5Mask;
        }
        g_free (tmp);
    }
    else
    {
        my_key->keycode = XKeysymToKeycode (GDK_DISPLAY_XDISPLAY (gdisplay), XStringToKeysym (str));
        my_key->modifier = 0;
    }

    return (my_key);
}

/* 
 * Beware, this can cause BadAccess X errors, enclose the call to this
 * routine within gdk_error_trap_push ()/gdk_error_trap_pop ().
 * This is not performed here because that could potentially cause
 * a performance hit when grabbing several keys.
 */
void
grab_key (MyKey * key)
{
    gint i, nscreens;
    GdkDisplay *gdisplay;

    gdisplay = gdk_display_get_default ();
    nscreens = gdk_display_get_n_screens(gdisplay);

    for(i = 0; i < nscreens; i++) 
    {
        GdkScreen *gscr;
        Window w;
        
        gscr = gdk_display_get_screen(gdisplay, i);
        w = GDK_WINDOW_XWINDOW (gdk_screen_get_root_window (gscr));

        if (key->keycode)
        {
            if (key->modifier == 0)
            {
                XGrabKey (GDK_DISPLAY_XDISPLAY (gdisplay), key->keycode, AnyModifier, 
                          w, FALSE, GrabModeAsync, GrabModeAsync);
            }
            else
            {
                /* Here we grab all combinations of well known modifiers */
                XGrabKey (GDK_DISPLAY_XDISPLAY (gdisplay), key->keycode, 
                          key->modifier, w, FALSE, GrabModeAsync, GrabModeAsync);
                XGrabKey (GDK_DISPLAY_XDISPLAY (gdisplay), key->keycode, 
                          key->modifier | ScrollLockMask, w, FALSE, GrabModeAsync, GrabModeAsync);
                XGrabKey (GDK_DISPLAY_XDISPLAY (gdisplay), key->keycode, 
                          key->modifier | NumLockMask, w, FALSE, GrabModeAsync, GrabModeAsync);
                XGrabKey (GDK_DISPLAY_XDISPLAY (gdisplay), key->keycode, 
                          key->modifier | LockMask, w, FALSE, GrabModeAsync, GrabModeAsync);
                XGrabKey (GDK_DISPLAY_XDISPLAY (gdisplay), key->keycode, 
                          key->modifier | ScrollLockMask | NumLockMask, w, FALSE, GrabModeAsync, GrabModeAsync);
                XGrabKey (GDK_DISPLAY_XDISPLAY (gdisplay), key->keycode, 
                          key->modifier | ScrollLockMask | LockMask, w, FALSE, GrabModeAsync, GrabModeAsync);
                XGrabKey (GDK_DISPLAY_XDISPLAY (gdisplay), key->keycode, 
                          key->modifier | LockMask | NumLockMask, w, FALSE, GrabModeAsync, GrabModeAsync);
                XGrabKey (GDK_DISPLAY_XDISPLAY (gdisplay), key->keycode,
                          key->modifier | ScrollLockMask | LockMask | NumLockMask, w, FALSE, GrabModeAsync, GrabModeAsync);
            }
        }
    }
}

void
ungrab_key (MyKey * key)
{
    gint i, nscreens;
    GdkDisplay *gdisplay;

    gdisplay = gdk_display_get_default ();
    nscreens = gdk_display_get_n_screens(gdisplay);

    for(i = 0; i < nscreens; i++) 
    {
        GdkScreen *gscr;
        Window w;
        
        gscr = gdk_display_get_screen(gdisplay, i);
        w = GDK_WINDOW_XWINDOW (gdk_screen_get_root_window (gscr));

        if (key->keycode)
        {
            if (key->modifier == 0)
            {
                XUngrabKey (GDK_DISPLAY_XDISPLAY (gdisplay), key->keycode, AnyModifier, w);
            }
            else
            {
                XUngrabKey (GDK_DISPLAY_XDISPLAY (gdisplay), key->keycode, 
                            key->modifier, w);
                XUngrabKey (GDK_DISPLAY_XDISPLAY (gdisplay), key->keycode, 
                            key->modifier | ScrollLockMask, w);
                XUngrabKey (GDK_DISPLAY_XDISPLAY (gdisplay), key->keycode, 
                            key->modifier | NumLockMask, w);
                XUngrabKey (GDK_DISPLAY_XDISPLAY (gdisplay), key->keycode, 
                            key->modifier | LockMask, w);
                XUngrabKey (GDK_DISPLAY_XDISPLAY (gdisplay), key->keycode, 
                            key->modifier | ScrollLockMask | NumLockMask, w);
                XUngrabKey (GDK_DISPLAY_XDISPLAY (gdisplay), key->keycode, 
                            key->modifier | ScrollLockMask | LockMask, w);
                XUngrabKey (GDK_DISPLAY_XDISPLAY (gdisplay), key->keycode, 
                            key->modifier | LockMask | NumLockMask, w);
                XUngrabKey (GDK_DISPLAY_XDISPLAY (gdisplay), key->keycode, 
                            key->modifier | ScrollLockMask | LockMask | NumLockMask, w);
            }
        }
    }
}

void
init_modifiers (void)
{
    GdkDisplay *gdisplay;
    GdkScreen *gscr;
    Window w;

    XModifierKeymap *modmap;
    KeySym *keymap;
    unsigned int keycode;
    int min_keycode;
    int max_keycode;
    int keysyms_per_keycode;
    int i;

    gdisplay = gdk_display_get_default ();
    gscr = gdk_display_get_default_screen (gdisplay);
    w = GDK_WINDOW_XWINDOW (gdk_screen_get_root_window (gscr));

    AltMask = 0;
    MetaMask = 0;
    NumLockMask = 0;
    ScrollLockMask = 0;
    SuperMask = 0;
    HyperMask = 0;
    keysyms_per_keycode = 0;
    min_keycode = 0;
    max_keycode = 0;

    XDisplayKeycodes (GDK_DISPLAY_XDISPLAY (gdisplay), &min_keycode, &max_keycode);
    modmap = XGetModifierMapping (GDK_DISPLAY_XDISPLAY (gdisplay));
    keymap = XGetKeyboardMapping (GDK_DISPLAY_XDISPLAY (gdisplay), min_keycode, max_keycode - min_keycode + 1, &keysyms_per_keycode);

    if (modmap && keymap)
    {    
        for (i = 3 * modmap->max_keypermod; i < 8 * modmap->max_keypermod; i++)
        {
            keycode = modmap->modifiermap[i];
            if ((keycode >= min_keycode) && (keycode <= max_keycode))
            {
                int j;
                KeySym *syms = keymap + (keycode - min_keycode) * keysyms_per_keycode;

                for (j = 0; j < keysyms_per_keycode; j++)
                {
                    if (!NumLockMask && (syms[j] == XK_Num_Lock))
                    {
                        NumLockMask = (1 << (i / modmap->max_keypermod));
                    }
                    else if (!ScrollLockMask && (syms[j] == XK_Scroll_Lock))
                    {
                        ScrollLockMask = (1 << (i / modmap->max_keypermod));
                    }
                    else if (!AltMask && ((syms[j] == XK_Alt_L) || (syms[j] == XK_Alt_R)))
                    {
                        AltMask = (1 << (i / modmap->max_keypermod));
                    }
                    else if (!SuperMask && ((syms[j] == XK_Super_L) || (syms[j] == XK_Super_R)))
                    {
                        SuperMask = (1 << (i / modmap->max_keypermod));
                    }
                    else if (!HyperMask && ((syms[j] == XK_Hyper_L) || (syms[j] == XK_Hyper_R)))
                    {
                        HyperMask = (1 << (i / modmap->max_keypermod));
                    }       
                    else if (!MetaMask && ((syms[j] == XK_Meta_L) || (syms[j] == XK_Meta_R)))
                    {
                        MetaMask = (1 << (i / modmap->max_keypermod));
                    }
                }
            }
        }
    }

    /* Cleanup memory */
    if (modmap)
    {
        XFreeModifiermap (modmap);
    }

    if (keymap)
    {
        XFree (keymap);
    }

    /* In case we didn't find AltMask, use Mod1Mask */
    if (AltMask == 0)
    {
        AltMask = Mod1Mask;
    }
}
