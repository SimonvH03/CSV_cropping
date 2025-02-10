#include "crop.h"

static int	image_size(t_image *image, int fd)
{
	char	*entry = ft_get_next_line(fd);

	if (entry == NULL)
		return (memory_error());
	// printf("ENTRY LINE 0:\n%s\n", entry);

	for (int i = 0; entry != NULL; i++)
	{
		free(entry);
		entry = ft_get_next_line(fd);
		if (entry == NULL)
			break;
		char *temp = ft_strdup_d(entry, ',');
		if (temp == NULL)
			return (RETURN_ERROR);
		int x = ft_atoi(temp);
		free(temp);
		temp = ft_strdup_d(ft_strchr(entry, ',') + 1, ',');
		if (temp == NULL)
			return (RETURN_ERROR);
		int y = ft_atoi(temp);
		free(temp);
		if (x > image->width)
			image->width = x;
		if (y > image->height)
			image->height = y;
	}
	image->width++;
	image->height++;
}

int	image_init(t_image *image, char *filename)
{
	int		return_value;
	int		x;
	int		y;
	int		fd = open_inputfile(filename);

	if (fd == -1)
		return (RETURN_FAILURE);
	image->width = 0;
	image->height = 0;
	image->validCount = 0;
	image->valids = NULL;

	if (return_value = image_size(image, fd) != RETURN_SUCCESS)
		return (return_value);

	close(fd);

	image->pixels = (short **)malloc(sizeof(short *) * image->height);
	if (image->pixels == NULL)
		return (memory_error());
	for (int i = 0; i < image->height; i++)
	{
		(image->pixels)[i] = (short *)calloc(sizeof(short), image->width);
		if ((image->pixels)[i] == NULL)
			return (RETURN_ERROR);
	}
	return (RETURN_SUCCESS);
}

static int	pixel_isStrawberry(t_image *image, char *entry, int x, int y)
{
	char **split = ft_split(entry, ',');

	if (split == NULL)
		return (memory_error());
	for	(int i = WAVELENGTH_THRESHOLD; split[i] != NULL; i++)
	{
		if (ft_strncmp(split[i], SENSITIVITY_THRESHOLD, 3) > 0)
				return (true);
	}
	ft_arrclear((void **)split);
	return (false);
}

int	image_readCsv(t_image *image, char *filename)
{
	char	*entry;
	int		x;
	int		y;
	int		fd = open_inputfile(filename);
	int		ret;

	if (fd == -1)
		return (RETURN_FAILURE);
	entry = ft_get_next_line(fd);
	if (entry == NULL)
		return (memory_error());
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
		ret = pixel_isStrawberry(image, entry, x, y);
		if (ret == -1)
		{
			free(entry);
			return (RETURN_ERROR);
		}
		else if (ret == 1)
		{
			if (x < image->width && y < image->height)
				image->pixels[y][x] = STRAWBERRY;
		}
		else if (x < image->width && y < image->height)
				image->pixels[y][x] = EMPTY;
	}
	close(fd);
	return (RETURN_SUCCESS);
}
