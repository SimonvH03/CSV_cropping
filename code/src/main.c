#include "../crop.h"

// using printf to utilize buffering for better performance
void	image_printInfo(t_image *image)
{
	printf("TEST PRINT W/H %d/%d\n\n", image->width, image->height);

	// adjust scale for more precise or more managable output (skips n pixels per readout)
	const int scale = SCALE;

	for (int i = 0; i < image->height; i++)
	{
		if ((i % scale))
			continue ;
		for (int j = 0; j < image->width; j++)
		{
			if ((j % scale))
				continue ;
			if (image->pixels[i][j] > 0)
				printf("%c ", image->pixels[i][j] + 48);
			else
				printf("  ");
		}
		printf("\n");
	}
}

static void clear(t_image *image)
{
	for (int i = 0; i < image->height; i++)
		free(image->pixels[i]);
	free(image->pixels);
	t_object *object = image->valids;
	while (object)
	{
		t_object *next = object->next;
		free(object);
		object = next;
	}
}

int	main(int argc, char **argv)
{
	t_image	image;
	int		fd;

	if (argc < 2)
	{
		printf("Usage: %s <filename.csv>\n", argv[0]);
		return (1);
	}

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		printf("Error: Could not open file %s\n", argv[1]);
		return (1);
	}

	// find size of image, malloc for it
	image_init(&image, fd);
	
	close(fd);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		printf("Error: Could not open file %s\n", argv[1]);
		return (1);
	}

	// read from csv file into image 'pixel'data
	if (image_readCsv(&image, fd))
		return (1);

	close(fd);

	findCenters(&image);

	exportAllObjects(&image, argv[1]);

	// ascii preview of image and cropped copies
	if (argc == 3 && (!ft_strncmp(argv[2], "-v", 3) || !ft_strncmp(argv[2], "--verbose", 10)))
		image_printInfo(&image);

	clear(&image);

	return (0);
}
