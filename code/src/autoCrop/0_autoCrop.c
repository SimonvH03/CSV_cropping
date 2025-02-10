#include "crop.h"

static void	image_printInfo(t_image *image)
{
	int	scale;

	if (image->width < image->height)
		scale = (image->width / PREVIEW_SIZE);
	else
		scale = (image->height / PREVIEW_SIZE);
	if (scale <= 0) scale = 1;

	printf("🟥\tObject of interest\n🟩\tExported file border\n⬛\tnone of the above?\n");
	printf("PREVIEW (%d x %d)\n", image->width, image->height);
	for (int i = 0; i < image->height; i++)
	{
		if ((i % scale))
			continue ;
		for (int j = 0; j < image->width; j++)
		{
			if ((j % scale))
				continue ;
			if (image->pixels[i][j] > 0)
				printf("🟥");
			else if (image->pixels[i][j] < 0)
				printf("🟩");
			else
				printf("⬛");
		}
		printf("\n");
	}
	printf("\n");
}

static void clear(t_image *image)
{
	for (int i = 0; i < image->height; i++)
		free(image->pixels[i]);
	free(image->pixels);
	t_object *object = image->seeker.objects;
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
		printf("\n\e[2mSize Limit set, exported files will not exceed %d x %d pixels\e[0m\n",
			MAX_CROP_SIZE, MAX_CROP_SIZE);
	else
		printf("\n\e[2mNo Size Limit set, exported files will contain entire object + margin of %d pixels\e[0m\n",
			MARGIN);
}

static int	confirm_export(t_image *image, char *filename)
{
	char	response;
	int		i = 1;

	announceCropMode();
	if (image->seeker.objectCount - 1 == 1)
		printf("🔍 1 Object found:\n");
	else
		printf("🔍 %d Objects found:\n", image->seeker.objectCount - 1);
	image->exportCount = 0;
	for (t_object *object = image->seeker.objects; object != NULL; object = object->next)
	{
		printf("📝 Object #%d ", i);
		if (object->label == TAPE)
			printf("(labeled \e[33mTAPE\e[0m]) has size %d\n", object->size);
		else
			printf("(labeled %d) has size %d\n", object->label, object->size);
		printf("📤 \e[1;35mDo you want to export Object #%d to CSV? \e[0;2m(y/n) \e[0m", i);
		while (1)
		{
			if (scanf(" %c", &response) == -1)
				return (RETURN_FAILURE);
			if (response == 'y' || response == 'Y')
			{
				printf("✅ Exporting Object %d...\n", i);
				if (exportObject(image, object, filename) == RETURN_ERROR)
					return (RETURN_ERROR);
				image->exportCount++;
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
	printf("✅ All objects evaluated: \e[33m%d files exported\e[0m\n\n", image->exportCount);
	return (RETURN_SUCCESS);
}

static void	confirm_preview(t_image *image)
{
	char	response;

	while (1)
	{
		printf("🔍 \e[1;35mDo you want to see a preview of the exported objects? \e[0;2m(y/n) \e[0m");
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

	if (return_value = findObjects(image) == RETURN_ERROR)
		return (return_value);

	if (return_value = confirm_export(image, filename) != RETURN_SUCCESS)
		return (return_value);

	if (image->exportCount > 0 && ALWAYS_SKIP_PREVIEW != true)
		confirm_preview(image);

	clear(image);
	return (RETURN_SUCCESS);
}
