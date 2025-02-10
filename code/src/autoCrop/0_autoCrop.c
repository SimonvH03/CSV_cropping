#include "crop.h"

static void	image_printInfo(t_image *image)
{
	printf("TEST PRINT W/H %d/%d\n\n", image->width, image->height);

	for (int i = 0; i < image->height; i++)
	{
		if ((i % SCALE))
			continue ;
		for (int j = 0; j < image->width; j++)
		{
			if ((j % SCALE))
				continue ;
			if (image->pixels[i][j] > 0)
				printf("%c ", image->pixels[i][j] + 48);
			else if (image->pixels[i][j] < 0)
				printf("# ");
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

static void announceCropMode(void)
{
	if (CROP_SIZE_LIMIT == true)
		printf("\nSize Limit set, exported files will not exceed %d x %d pixels\n",
			MAX_CROP_SIZE, MAX_CROP_SIZE);
	else
		printf("\nNo Size Limit set, exported files will contain entire object + margin of %d pixels\n",
			MARGIN);
}

static int	confirm_export(t_image *image, char *filename)
{
	char	response;
	int		i = 1;

	announceCropMode();
	printf("%d Objects found:", image->validCount);
	for (t_object *object = image->valids; object != NULL; object = object->next)
	{
		printf("Object %d (labeled %d) has size %d\nDo you want to export it to CSV? (y/n)",
			i, object->label, object->size);
		while (1)
		{
			if (scanf(" %c", &response) == -1)
				return (RETURN_FAILURE);
			if (response == 'y' || response == 'Y')
			{
				printf("✅ Exporting Object %d...\n", i);
				if (exportObject(image, object, filename) == RETURN_ERROR)
					return (RETURN_ERROR);
				break ;
			}
			else if (response == 'n' || response == 'N')
			{
				printf("❌ Object %d Skipped.\n", i);
				break ;
			}
			else
				printf("⚠️ Invalid input. Please enter 'y' or 'n'.\n");
		}
		i++;
	}
	printf("✅ All Objects done");
}

static void	confirm_preview(t_image *image)
{
	char	response;

	while (1)
	{
		printf("Do you wish to see a preview of the exported objects? (y/n)\n");
		if (scanf(" %c", &response) == -1)
			return ;
		if (response == 'y' || response == 'Y')
		{
			image_printInfo(image);
			return ;
		}
		else if (response == 'n' || response == 'N')
			return ;
		else
			printf("⚠️ Invalid input. Please enter 'y' or 'n'.\n");
	}
}

int	autocrop(t_image *image, char *filename)
{
	int	return_value;

	if (return_value = image_init(image, filename) != RETURN_SUCCESS)
		return (return_value);

	if (return_value = image_readCsv(image, filename) != RETURN_SUCCESS)
		return (return_value);

	if (return_value = findObjects(image) != RETURN_SUCCESS)
		return (return_value);

	if (return_value = confirm_export(image, filename) != RETURN_SUCCESS)
		return (return_value);

	confirm_preview(image);

	clear(image);
}
