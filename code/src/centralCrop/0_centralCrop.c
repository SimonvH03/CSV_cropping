#include "crop.h"

static int	image_size(t_image *image, int fd)
{
	char	*entry = ft_get_next_line(fd);

	if (entry == NULL)
		return (memory_error());
	// printf("ENTRY LINE 0:\n%s\n", entry);

	image->width = 0;
	image->height = 0;
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
		if (i == 0)
			image->coordstart[0] = x;
		free(temp);
		temp = ft_strdup_d(ft_strchr(entry, ',') + 1, ',');
		if (temp == NULL)
			return (RETURN_ERROR);
		int y = ft_atoi(temp);
		if (i == 0)
			image->coordstart[1]= y;
		free(temp);
		if (x > image->width)
			image->width = x;
		if (y > image->height)
			image->height = y;
	}
	image->width += 1 - image->coordstart[0];
	image->height += 1 - image->coordstart[1];
	// printf("Input File has size %d x %d\n", image->width, image->height);
	// printf("first pixel has coordinates %d, %d\n", image->coordstart[0], image->coordstart[1]); // debug
	return (RETURN_SUCCESS);
}

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

static char *newFilename(char *filename)
{
	char	*newFilename;
	char	*temp;
	
	newFilename = ft_strdup_d(filename, '.');
	newFilename[ft_strlen(newFilename) - 1] = '\0';

	temp = ft_strjoin(newFilename, "_centralcrop");
	free(newFilename);
	newFilename = temp;

	temp = ft_strjoin(newFilename, ".csv");
	free(newFilename);
	newFilename = temp;

	return (newFilename);
}

static void	determineCropSize(t_cropRange *crop, int totalheight, int totalwidth)
{
	crop->minY = (totalheight - CROP_HEIGHT) / 2 + 1;
	crop->minX = (totalwidth - CROP_WIDTH) / 2 + 1;
	crop->maxY = (totalheight + CROP_HEIGHT) / 2;
	crop->maxX = (totalwidth + CROP_WIDTH) / 2;

	if (crop->minY < 0)
		crop->minY = 0;
	if (crop->minX < 0)
		crop->minX = 0;
	if (crop->maxY > totalheight)
		crop->maxY = totalheight;
	if (crop->maxX > totalwidth)
		crop->maxX = totalwidth;
}

static int	confirm_export(t_image *image, char *filename)
{
	int			fd = open_inputfile(filename);
	int			return_value;
	char		response;
	t_cropRange	cropRange;

	if (fd == -1)
		return (RETURN_FAILURE);
	determineCropSize(&cropRange, image->height, image->width);
	printf("📝 Central Square will be of size (%d x %d)\n",
		(cropRange.maxX - cropRange.minX + 1), (cropRange.maxY - cropRange.minY + 1));
	printf("📤 \e[1;35mDo you want to export it to CSV? \e[0;2m(y/n) \e[0m");
	while (1)
	{
		if (scanf(" %c", &response) == -1)
			return (RETURN_FAILURE);
		if (response == 'y' || response == 'Y')
		{
			printf("✅ Exporting Central Square...\n");
			if (return_value = copyPixelData(fd, cropRange, image, newFilename(filename)) != RETURN_SUCCESS)
				return (return_value);
			break ;
		}
		else if (response == 'n' || response == 'N')
		{
			printf("❌ Export cancelled...");
			break ;
		}
		else
			printf("⚠️ Invalid input. Please enter 'y' or 'n'.\n");
	}
	printf("✅ All Objects done\n\n");
	close(fd);
	return (RETURN_SUCCESS);
}

int centralcrop(t_image *image, char *filename)
{
	int			return_value;
	int			fd = open_inputfile(filename);
	char		response;

	if (fd == -1)
		return (RETURN_FAILURE);

	if (return_value = image_size(image, fd) != RETURN_SUCCESS)
		return (return_value);
	close(fd);

	if (return_value = confirm_export(image, filename) != RETURN_SUCCESS)
		return (return_value);

	return (RETURN_SUCCESS);
}
