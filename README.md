glits
-----

glits is an opencv based OpenGL (image) testing suite.

Usage
-----

use the various check functions, their usage should be self explanatory or is documented. Currently implemented:
 - check_texture
 - check_buffer
 - check_framebuffer
They return false, if the mean or stddeviation exceed the given values.

it's possible autogenerating the testdata, by defining the flag "GLITS_GENERATE_DATA" and running the program. The check functions then save the current data to the files (and overwriting the current ones!).

