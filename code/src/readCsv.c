#include "../crop.h"

void	image_init(t_image *image, int fd)
{
	char	*entry;
	int		x;
	int		y;

	image->width = 0;
	image->height = 0;
	image->validCount = 0;
	image->valids = NULL;
	entry = ft_get_next_line(fd);
	printf("ENTRY LINE 0:\n%s\n", entry);
	for (int i = 0; entry != NULL; i++)
	{
		free(entry);
		entry = ft_get_next_line(fd);
		if (entry == NULL)
			break;
		char *temp = ft_strdup_d(entry, ',');
		int x = ft_atoi(temp);
		free(temp);
		temp = ft_strdup_d(ft_strchr(entry, ',') + 1, ',');
		int y = ft_atoi(temp);
		free(temp);
		if (x > image->width)
			image->width = x;
		if (y > image->height)
			image->height = y;
	}
	image->width++;
	image->height++;
	printf("height: %d\nwidth: %d\n", image->height, image->width);

	image->pixels = (short **)malloc(sizeof(short *) * image->height);
	for (int i = 0; i < image->height; i++)
		(image->pixels)[i] = (short *)calloc(sizeof(short), image->width);
}

static int	pixel_isStrawberry(t_image *image, char *entry, int x, int y)
{
	char **split = ft_split(entry, ',');

	for	(int i = WAVELENGTH_CUTOFF; split[i] != NULL; i++)
	{
		if (ft_strncmp(split[i], SENSITIVITY_THRESHOLD, 3) > 0)
				return (true);
	}
	ft_arrclear((void **)split);
	return (false);
}

int	image_readCsv(t_image *image, int fd)
{
	char	*entry;
	int		x;
	int		y;

	entry = ft_get_next_line(fd);
	for (int i = 0; entry != NULL; i++)
	{
		free(entry);
		entry = ft_get_next_line(fd);
		if (entry == NULL)
			break;
		char *temp = ft_strdup_d(entry, ',');
		int x = ft_atoi(temp);
		free(temp);
		temp = ft_strdup_d(ft_strchr(entry, ',') + 1, ',');
		int y = ft_atoi(temp);
		free(temp);
		if (pixel_isStrawberry(image, entry, x, y) == 1)
		{
			if (x < image->width && y < image->height)
				image->pixels[y][x] = STRAWBERRY;
		}
		else if (x < image->width && y < image->height)
				image->pixels[y][x] = EMPTY;
	}
}
