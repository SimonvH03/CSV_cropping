#include "crop.h"

static int	copyPixelData(int fd_in, t_cropRange crop, t_image *image, char *filename)
{
	int		fd_out;
	char	*entry;
	char	*temp;

	if (filename == NULL)
		return (memory_error());
	fd_out = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd_out == -1)
	{
		printf("Error: Could not create file %s\n", filename);
		free(filename);
		return (RETURN_ERROR);
	}

	entry = ft_get_next_line(fd_in);
	if (entry == NULL)
		return (RETURN_ERROR);
	ft_putstr_fd(entry, fd_out);
	for (int i = 0; entry != NULL; i++)
	{
		free(entry);
		entry = ft_get_next_line(fd_in);
		if (entry == NULL)
			break;
		temp = ft_strdup_d(entry, ',');
		int x = ft_atoi(temp) - image->coordstart[0];
		free(temp);
		if (x < crop.minX || x > crop.maxX)
			continue ;
		temp = ft_strdup_d(ft_strchr(entry, ',') + 1, ',');
		int y = ft_atoi(temp) - image->coordstart[1];
		free(temp);
		if (y < crop.minY || y > crop.maxY)
			continue ;
		ft_putstr_fd(entry, fd_out);
	}
	printf("✅ Exported Object to %s (%d x %d)\n", filename,
		(crop.maxX - crop.minX + 1), (crop.maxY - crop.minY + 1));
	free(filename);
	return (RETURN_SUCCESS);
}

static char *newFilename(char *filename, int label)
{
	char	*newFilename;
	char	*temp;
	char	*labelStr;

	if (label == TAPE)
		label = 0;
	labelStr = ft_itoa(label);

	newFilename = ft_strdup_d(filename, '.');
	newFilename[ft_strlen(newFilename) - 1] = '\0';
	temp = ft_strjoin(newFilename, "_autocrop_");

	free(newFilename);
	newFilename = temp;
	temp = ft_strjoin(newFilename, labelStr);
	free(newFilename);
	newFilename = temp;

	temp = ft_strjoin(newFilename, ".csv");
	free(newFilename);
	newFilename = temp;
	free(labelStr);

	return (newFilename);
}

static void	determineCropSize(t_cropRange *crop, t_object *object, int height, int width)
{
	crop->minY = object->minY - MARGIN;
	crop->minX = object->minX - MARGIN;
	crop->maxY = object->maxY + MARGIN;
	crop->maxX = object->maxX + MARGIN;
	if (crop->minY < 0) crop->minY = 0;
	if (crop->minX < 0) crop->minX = 0;
	if (crop->maxY > height) crop->maxY = height;
	if (crop->maxX > width) crop->maxX = width;
	if ((crop->maxY - crop->minY + 1 >= MAX_CROP_SIZE) && (CROP_SIZE_LIMIT == 1))
	{
		crop->minY = object->centerY - MAX_CROP_SIZE / 2 + 1;
		crop->maxY = object->centerY + MAX_CROP_SIZE / 2;
	}
	if ((crop->maxX - crop->minX + 1 >= MAX_CROP_SIZE) && (CROP_SIZE_LIMIT == 1))
	{
		crop->minX = object->centerX - MAX_CROP_SIZE / 2 + 1;
		crop->maxX = object->centerX + MAX_CROP_SIZE / 2;
	}
	if (crop->minY < 0) crop->minY = 0;
	if (crop->minX < 0) crop->minX = 0;
	if (crop->maxY > height) crop->maxY = height;
	if (crop->maxX > width) crop->maxX = width;
	// printf("cropping from (%d, %d) to (%d, %d) size (%d x %d)\n",
	// 	crop->minX, crop->minY, crop->maxX, crop->maxY,
	// 	crop->maxX - crop->minX + 1, crop->maxY - crop->minY + 1); // debug
}

static void drawBoundingBox(t_image *image, t_object *object, t_cropRange *crop)
{
	int	scale;

	if (image->width < image->height)
		scale = image->width / PREVIEW_SIZE;
	else
		scale = image->height / PREVIEW_SIZE;
	if (scale <= 0) scale = 1;

	for (int x = crop->minX; x < crop->maxX; x++)
	{
		for (int y = 0; y < scale; y++)
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
		for (int x = 0; x < scale; x++)
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

int exportObject(t_image *image, t_object *object, char *filename)
{
	int			return_value;
	int			fd = open_inputfile(filename);
	t_cropRange	cropRange;

	if (fd == -1)
		return (RETURN_FAILURE);

	determineCropSize(&cropRange, object, image->height, image->width);
	if (return_value = copyPixelData(fd, cropRange, image, newFilename(filename, object->label)) != RETURN_SUCCESS)
		return (return_value);

	close(fd);
	drawBoundingBox(image, object, &cropRange);
	return (RETURN_SUCCESS);
}
