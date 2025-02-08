#include "../crop.h"

static void	determineCrop(t_cropRange *crop, t_object *object, int height, int width)
{
	crop->minY = object->minY - BOUNDINGBOX_MARGIN;
	crop->minX = object->minX - BOUNDINGBOX_MARGIN;
	crop->maxY = object->maxY + BOUNDINGBOX_MARGIN;
	crop->maxX = object->maxX + BOUNDINGBOX_MARGIN;
	if ((crop->maxY - crop->minY > CENTER_HEIGHT)
		&& (FORCE_BOUNDINGBOX != 1 || FORCE_CENTER == 1))
	{
		crop->minY = object->centerY - CENTER_HEIGHT / 2;
		crop->maxY = object->centerY + CENTER_HEIGHT / 2;
	}
	if ((crop->maxX - crop->minX > CENTER_WIDTH)
		&& (FORCE_BOUNDINGBOX != 1 || FORCE_CENTER == 1))
	{
		crop->minX = object->centerX - CENTER_WIDTH / 2;
		crop->maxX = object->centerX + CENTER_WIDTH / 2;
	}
	if (crop->minY < 0)
		crop->minY = 0;
	if (crop->minX < 0)
		crop->minX = 0;
	if (crop->maxY > height)
		crop->maxY = height;
	if (crop->maxX > width)
		crop->maxX = width;
}

static char *newFilename(char *filename, int label)
{
	char	*newFilename;
	char	*labelStr;

	labelStr = ft_itoa(label);
	newFilename = ft_strjoin(filename, "_crop_");
	newFilename = ft_strjoin(newFilename, labelStr);
	free(labelStr);
	return (newFilename);
}

static int	exportObject(int fd_in, t_cropRange crop, char *filename)
{
	int		fd_out;
	char	*entry;
	char	*temp;

	fd_out = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd_out == -1)
	{
		printf("Error: Could not create file %s\n", filename);
		free(filename);
		return (1);
	}
	entry = ft_get_next_line(fd_in);
	ft_putstr_fd(entry, fd_out);
	for (int i = 0; entry != NULL; i++)
	{
		free(entry);
		entry = ft_get_next_line(fd_in);
		if (entry == NULL)
			break;
		temp = ft_strdup_d(entry, ',');
		int x = ft_atoi(temp);
		free(temp);
		if (x < crop.minX || x > crop.maxX)
			continue ;
		temp = ft_strdup_d(ft_strchr(entry, ',') + 1, ',');
		int y = ft_atoi(temp);
		free(temp);
		if (y < crop.minY || y > crop.maxY)
			continue ;
		ft_putstr_fd(entry, fd_out);
	}
	printf("Succesfully Exported %s ( %d x %d )\n", filename, crop.maxX - crop.minX, crop.maxY - crop.minY);
	free(filename);
}

static void drawBoundingBox(t_image *image, t_object *object, t_cropRange *crop)
{
	for (int x = crop->minX; x < crop->maxX; x++)
	{
		for (int y = 0; y <= SCALE; y++)
		{
			if (!(x < 0 || x >= image->width
				|| crop->minY + y < 0 || crop->minY + y >= image->height))
				image->pixels[crop->minY + y][x] = -1;
			if (!(x < 0 || x >= image->width
				|| crop->maxY - y < 0 || crop->maxY - y >= image->height))
				image->pixels[crop->maxY - y][x] = -1;
		}
	}
	for (int y = crop->minY; y < crop->maxY; y++)
	{
		for (int x = 0; x <= SCALE; x++)
		{
			if (!(crop->minX + x < 0 || crop->minX + x >= image->width
				|| y < 0 || y >= image->height))
				image->pixels[y][crop->minX + x] = -1;
			if (!(crop->maxX - x < 0 || crop->maxX - x >= image->width
				|| y < 0 || y >= image->height))
				image->pixels[y][crop->maxX - x] = -1;
		}
	}
}

static void announceCropMode(void)
{
	printf("\n");
	if (FORCE_BOUNDINGBOX == FORCE_CENTER)
	{
		if (FORCE_BOUNDINGBOX == 1)
			printf("Warning: Both FORCE_BOUNDINGBOX and FORCE_CENTER are set to 1\n");
		printf("Cropping mode not set: default\n");
	}
	else
	{
		if (FORCE_BOUNDINGBOX == 1)
			printf("Cropping mode set to force BoundingBox\n");
		else
			printf("Cropping mode set to force Center\n");
	}
}

int exportAllObjects(t_image *image, char *filename)
{
	int			fd;
	int			count = 0;
	t_object	*object;
	t_cropRange	cropRange;
	
	object = image->valids;

	announceCropMode();
	while (object)
	{
		fd = open(filename, O_RDONLY);
		if (fd == -1)
		{
			printf("Error: Could not open file %s\n", filename);
			return (1);
		}
		count++;
		determineCrop(&cropRange, object, image->height, image->width);
		exportObject(fd, cropRange, newFilename(filename, object->label));
		close(fd);
		drawBoundingBox(image, object, &cropRange);
		object = object->next;
	}
	printf("Exported %d cropped files from %s\n\n", count, filename);
	return (0);
}
