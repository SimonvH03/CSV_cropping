#ifndef CROP_H
# define CROP_H

# include "libft/libft.h"
# include <fcntl.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>
# include <unistd.h>
# include <stdbool.h>
# include <errno.h>
# include <string.h>

# include "../config.h"

# define STRAWBERRY		1
# define EMPTY 			0

// STRUCTS
typedef struct s_image	t_image;
typedef struct s_object	t_object;

typedef struct s_cropRange
{
	int			minY;
	int			minX;
	int			maxY;
	int			maxX;
}	t_cropRange;

typedef struct s_point
{
	int			x;
	int			y;
}	t_point;


typedef	struct s_object
{
	int			label;
	int			size;
	int			sumY;
	int			sumX;
	int			minY;
	int			minX;
	int			maxY;
	int			maxX;
	int			centerY;
	int			centerX;
	t_object	*next;
}	t_object;

typedef struct s_seeker
{
	t_object	*objects;
	int			objectCount;
	short		**visited;
	int			dy[4];
	int			dx[4];
	t_image		*ref_image;
}	t_seeker;

typedef struct s_image
{
	int			width;
	int			height;
	short		**pixels;
	t_seeker	seeker;
	int			validCount;
	t_object	*valids;
}	t_image;


// FUNCTIONS

// centralcrop/
int		centralcrop(t_image *image, char *filename);


// autocrop
int		autocrop(t_image *image, char *filename);
// exportCrops.c
int		exportObject(t_image *image, t_object *object, char *filename);
// centerReport.c
int		findObjects(t_image *image);
// readCsv.c
int		image_init(t_image *image, char *filename);
int		image_readCsv(t_image *image, char *filename);

// utils (main.c)
int		memory_error();
int		open_inputfile(char *filename);

#endif
