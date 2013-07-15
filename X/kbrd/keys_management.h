/*      $Id: keys_management.h 21572 2006-05-07 14:29:21Z olivier $
 
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

#ifndef INC_KEY_MANAGEMENT_H
#define INC_KEY_MANAGEMENT_H

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <X11/Xlib.h>
#include <X11/keysym.h>

#define MODIFIER_MASK (ShiftMask | \
                       ControlMask | \
                       AltMask | \
                       MetaMask | \
                       SuperMask | \
                       HyperMask)

extern unsigned int KeyMask;
extern unsigned int ButtonMask;
extern unsigned int ButtonKeyMask;
extern unsigned int AltMask;
extern unsigned int MetaMask;
extern unsigned int NumLockMask;
extern unsigned int ScrollLockMask;
extern unsigned int SuperMask;
extern unsigned int HyperMask;

typedef struct _MyKey MyKey;
struct _MyKey
{
    KeyCode keycode;
    int modifier;
};

MyKey     * parseKeyString                  (char * str);
void        grab_key                        (MyKey *);
void        ungrab_key                      (MyKey *);
void        init_modifiers                  (void);

#endif /* INC_KEY_MANAGEMENT_H */
