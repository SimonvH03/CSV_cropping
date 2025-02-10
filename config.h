#ifndef CONFIG_H
# define CONFIG_H

// READ CAREFULLY
// The program will read the input CSV file and copy a range of pixels into a new CSV file.
// The range of pixels copied will be determined by the parameters set below.
// The CSV files will be exported and named <input_filename>_crop_#.csv
// Using the program with the same input file multiple times will overwrite the previous output files.

// CONFIGURATION
// changing values of these defined constants will change the behaviour of the program.
// NEVER change the NAME of a constant, only the value.
// NEVER include symbols like #, <, >, = or ; in the values of the defined constants
// The comments (me, here, the green text you're reading) will refer to values with >these bois< around them, you will not
// MAKE SURE to keep values the same TYPE, e.g. >200< can not become >true< , and >"0.05"< can not become >0.05<
// set to >true< to enable, >false< to disable. (without the > and <, in case you missed it)

// # define INPUT_FILE			"data/test_crop_1.csv"
# define INPUT_FILE			"data/test.csv"

// SET CROPPING MODE
// if >true<, find objects of interest based on wavelength, size, and sensitivity THRESHOLDS
// if >false<, crop an image a set size (CROP_WIDTH, CROP_HEIGHT) around the center of the image
// in either case, only one set of parameters will be used, the other will be ignored, so don't worry about them conflicting
# define AUTO_DETECTION		false

	// IF AUTO DETECTION IS >false< SET PARAMETERS BELOW

		// width of the cropped image (in # of pixels)
		# define CROP_WIDTH				64
		// height of the cropped image (in # of pixels)
		# define CROP_HEIGHT			64


	// IF AUTO DETECTION IS >true< SET PARAMETERS BELOW

		// maximum side length (width x height) of CSV file to be created (in # of pixels)
		# define CROP_SIZE_LIMIT		true
			# define MAX_CROP_SIZE		64

		// pixels of margin to also copy around found object (if not exceeding SIZE_LIMIT)
		# define MARGIN					16

		// index of minimum wavelength to detect (not including Line#, Column#, can not be higher than 135)
		// e.g. 45 = 600nm+ = red, find LINE 0 in output or csv file for reference
		# define WAVELENGTH_THRESHOLD	45

		// minimum value/magnitude of desired wavelength in pixel to be considered part of a potential object of interest
		# define SENSITIVITY_THRESHOLD	"0.05"

		// minimum size (#of orthognonally adjacent pixels) of object to be considered an object of interest
		# define OBJECT_SIZE_THRESHOLD	1000


// Auto detection output includes optional preview of exported files, force sip or adjust size (max size 40 recommended)
# define ALWAYS_SKIP_PREVIEW			false
# define PREVIEW_SIZE					32

#endif
