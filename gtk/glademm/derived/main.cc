//$Id: main.cc,v 1.1 2003/08/23 17:21:06 murrayc Exp $ -*- c++ -*-

/* libglademm example Copyright (C) 2003 libglademm development team
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#include "deriveddialog.h"
#include <iostream>

int main (int argc, char **argv)
{
  Gtk::Main kit(argc, argv);

  //Load the Glade file and instiate its widgets:
  Glib::RefPtr<Gnome::Glade::Xml> refXml;
  try
  {
    refXml = Gnome::Glade::Xml::create("basic.glade");
  }
  catch(const Gnome::Glade::XmlError& ex)
  {
    std::cerr << ex.what() << std::endl;
    return 1;
  }

  //Get the Glade-instantiated dialog::
  DerivedDialog* pDialog = 0;
  refXml->get_widget_derived("DialogBasic", pDialog);
  if(pDialog)
  {
    //See the DerivedDialog constructor for more Glade::Xml stuff.

    //Start:
    kit.run(*pDialog);
  }

  delete pDialog;
    

  return 0;
}

