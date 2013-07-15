include $(top_srcdir)/examples/Makefile.am_fragment

#Build the executable, but don't install it.
noinst_PROGRAMS = example
example_SOURCES = example.cc

#example.glade is read at runtime, and edited by glade-2.
#It seems that example.gladep must exist also, when editing basic.glade,
#so that glade-2 knows that it should not add libgnomeui widgets instead of GTK+ widgets.

EXTRA_DIST = example.glade example.gladep
