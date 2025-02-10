#include "crop.h"

int	memory_error()
{
	printf("\e[31mERROR: Memory allocation failed");
	return (RETURN_ERROR);
}

int	open_inputfile(char *filename)
{
	int fd = open(filename, O_RDONLY);

	if (fd == -1)
	{
		printf("Error: Could not open file '%s': %s\n", filename, strerror(errno));
		return (-1);
	}
	return (fd);
}

int	main(void)
{
	int		return_value;
	t_image	image;

	if (AUTO_DETECTION == true)
	{
		printf("📂 Running Program in AUTO_DETECTION mode...\n");
		printf("📄 \e[33mInput File: \e[32m>> %s <<\e[0m\n", INPUT_FILE);
		printf("⚙️ \e[33m Parameters:\e[0m\nWavelength:\tindex %d\nSensitivity:\t%s\nObject Size:\t%d pixels\n",
			WAVELENGTH_THRESHOLD, SENSITIVITY_THRESHOLD, OBJECT_SIZE_THRESHOLD);
		if (CROP_SIZE_LIMIT == true)
			printf("File Size:\t%d x %d pixels\n", MAX_CROP_SIZE, MAX_CROP_SIZE);
		else
			printf("File Size:\t n.a.\n");
		return_value = autocrop(&image, INPUT_FILE);
		if (return_value != RETURN_SUCCESS)
		{
			printf("\e[31mError executing 'autocrop', exiting program...\e[0m\n");
			return (return_value);
		}
	}
	else
	{
		printf("📂 Running Program in CENTRAL_SQUARE mode...\n");
		printf("📄 \e[33mInput File: \e[32m>> %s <<\e[0m\n", INPUT_FILE);
		printf("\e[33m⚙️  Parameters:\e[0m\nFile Size:\t%d x %d\n", CROP_WIDTH, CROP_HEIGHT);
		return_value = centralcrop(&image, INPUT_FILE);
		if (return_value != RETURN_SUCCESS)
		{
			printf("\e[31mError executing 'centralcrop', exiting program...\e[0m\n");
			return (return_value);
		}
	}
	return (RETURN_SUCCESS);
}
