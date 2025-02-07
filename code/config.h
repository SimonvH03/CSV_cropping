#ifndef CONFIG_H
# define CONFIG_H

// CONFIGURATION
// Adjust below values for more reliable and accurate detection

// index of minimum wavelength to detect (not including Line#, Column#, can not be higher than 135) 45 = 600nm+ = red
# define WAVELENGTH_CUTOFF		45

// minimum value/magnitude of desired wavelength detected to be considered a strawberry
# define SENSITIVITY_THRESHOLD	"0.05"

// minimum size (#of orthognonally adjacent pixels) of object to be considered a strawberry
# define OBJECT_SIZE_THRESHOLD	50

// Adjust below values for desired fromatting of output csv files

// set only one of the following to force centering or bounding box cropping mode, default is a combination of both
# define FORCE_BOUNDINGBOX		0
# define FORCE_CENTER			0

// default will crop new file to bounding box of a strawberry, with a margin of B_MARGIN pixels
//  width or heihgt of new csv file will not exceed C_WIDTH or C_HEIGHT respectively
# define BOUNDINGBOX_MARGIN		10				
# define CENTER_WIDTH			224
# define CENTER_HEIGHT			224

// note that an object's center is it's weighted center, not the center of it's bounding box

// scale for output, 1 will print every pixel, 2 will skip every other pixel, etc.
#  define SCALE					1

#endif