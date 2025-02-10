#include "crop.h"

static int	copyPixelData(int fd_in, t_cropRange crop, char *filename)
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
	printf("✅ Exported Object to %s (%d x %d)", filename, crop.maxX - crop.minX, crop.maxY - crop.minY);
	free(filename);
	return (RETURN_SUCCESS);
}

static char *newFilename(char *filename)
{
	char	*newFilename = ft_strjoin(filename, "_crop");

	return (newFilename);
}

static void	determineCropSize(t_cropRange *crop, int totalheight, int totalwidth)
{
	crop->minY = (totalheight - CROP_HEIGHT) / 2;
	crop->minX = (totalwidth - CROP_WIDTH) / 2;

	if (crop->minY < 0)
		crop->minY = 0;
	if (crop->minX < 0)
		crop->minX = 0;
	if (crop->maxY > totalheight)
		crop->maxY = totalheight;
	if (crop->maxX > totalwidth)
		crop->maxX = totalwidth;
}

int centralcrop(t_image *image, char *filename)
{
	int			fd = open_inputfile(filename);
	t_cropRange	cropRange;
	char		response;

	if (fd == -1)
		return (RETURN_FAILURE);

	determineCropSize(&cropRange, image->height, image->width);
	printf("📝 Central Square will be of size (%d x %d)\n📤 Do you want to export it to CSV? (y/n)",
		(cropRange.maxX - cropRange.minX), (cropRange.maxY - cropRange.minY));
	while (1)
	{
		if (scanf(" %c", &response) == -1)
			return (RETURN_FAILURE);
		if (response == 'y' || response == 'Y')
		{
			printf("✅ Exporting Central Square...\n");
			if (copyPixelData(fd, cropRange, newFilename(filename)) == RETURN_ERROR)
				return (RETURN_ERROR);
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
	close(fd);
	return (RETURN_SUCCESS);
}
