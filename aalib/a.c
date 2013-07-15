#include <aalib.h>
#include <stdlib.h>
#include <string.h>
int
main (int argc, char **argv)
{
  aa_context *context;       /* The information about currently
       				initialized device.  */
  aa_palette palette;        /* Emulatted palette (optional) */
  
  char *framebuffer;
  int i;
  
  /* Parse command line options and output the help text.  */
  if (!aa_parseoptions (NULL, NULL, &argc, argv) || argc != 1) {
      printf ("%s", aa_help);
      exit (1);
    }
  
  /* Initialize output driver.  */
  context = aa_autoinit (&aa_defparams);
  if (context == NULL)   {
    printf ("Failed to initialize aalib\n");
    exit (1);
  }
  
  /* Pointer to the emulated videoram.  */
  framebuffer = aa_image (context);
  memset(framebuffer, 0, 100);
  
  /* Create palette if needed: */
  for (i = 0; i < 256; i++)
    aa_setpalette (palette, i, i, i, i);/* R value 0..255 */ 

  /* Draw something using: */
  for (i = 0; i < 256; ++i)
    aa_putpixel (context, rand() % 60, rand() % 60, i | (i << 8));//* X coord */ , /* Y coord */ , /* Color */ );

  /* Render whole screen: */

  aa_renderpalette (context, palette, &aa_defrenderparams,
     		    /* Top left conner of rendered area: */ 0, 0,
     		    /* Bottom right */  aa_scrwidth (context), aa_scrheight (context));

  /* If you don't use palette use following function:
     aa_render (context, aa_defrenderparams,
     0, 0, aa_scrwidth (context), aa_scrheight (context));
  */

  /* And make it visible: */
  aa_flush (context);
  scanf("%*c");
  /* And uninitialize the AA_lib (this probably makes the picture invisible
     again) */
  aa_close (context);

  return 1;
}

