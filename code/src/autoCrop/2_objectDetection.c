#include "crop.h"

static t_object	*newObject(int label, t_object *next)
{
	t_object *object = malloc(sizeof(t_object));
	if (!object)
	{
		printf("Error: Memory allocation failed!\n");
		return (NULL);
	}
	object->label = label;
	object->sumX = 0;
	object->sumY = 0;
	object->size = 0;
	object->next = next;
	return (object);
}

static t_seeker	*initSeeker(t_image *image)
{
	t_seeker *cs = &image->seeker;

	cs->objectCount = 1;
	cs->ref_image = image;
	cs->visited = malloc(image->height * sizeof(short *));
	if (cs->visited == NULL)
		return (NULL);
	for (int i = 0; i < image->height; i++)
	{
		cs->visited[i] = malloc(image->width * sizeof(short));
		if (cs->visited[i] == NULL)
			return (NULL);
		for (int j = 0; j < image->width; j++)
			cs->visited[i][j] = 0;
	}
	cs->dx[0] = 1;
	cs->dx[1] = -1;
	cs->dx[2] = 0;
	cs->dx[3] = 0;
	cs->dy[0] = 0;
	cs->dy[1] = 0;
	cs->dy[2] = 1;
	cs->dy[3] = -1;

	cs->objects = NULL;
	return (cs);
}

static int	floodFill(t_seeker *cs, t_object *object, int startX, int startY)
{
	int maxSize = cs->ref_image->width * cs->ref_image->height;
	t_point *queue = malloc(maxSize * sizeof(t_point));
	if (queue == NULL)
		return (memory_error());

	object->minX = startX;
	object->maxX = startX;
	object->minY = startY;
	object->maxY = startY;

	int front = 0, back = 0;
	queue[back++] = (t_point){startX, startY};
	cs->visited[startY][startX] = object->label;

	while (front != back)
	{
		t_point p = queue[front++];
		if (front >= maxSize)
			front = (front + 1) % maxSize; // Circular queue reset

		int x = p.x, y = p.y;

		if (x < object->minX)
			object->minX = x;
		else if (x > object->maxX)
			object->maxX = x;
		if (y < object->minY)
			object->minY = y;
		else if (y > object->maxY)
			object->maxY = y;

		object->sumX += x;
		object->sumY += y;
		object->size++;

		for (int i = 0; i < 4; i++) {
			int nx = x + cs->dx[i];
			int ny = y + cs->dy[i];

			if (nx >= 0 && nx < cs->ref_image->width
				&& ny >= 0 && ny < cs->ref_image->height
				&& cs->visited[ny][nx] == 0
				&& cs->ref_image->pixels[ny][nx] == STRAWBERRY)
			{
				cs->visited[ny][nx] = object->label;
				cs->ref_image->pixels[ny][nx] = object->label;

				queue[back++] = (t_point){nx, ny};
				if (back >= maxSize)
					back = (back + 1) % maxSize; // Circular queue reset
			}
		}
	}
	free(queue);
	return (RETURN_SUCCESS);
}

static int	tape_warning(int level)
{
	if (level <= 2)
		return (2);
	if (level <= 5)
		return (3);
	return (1);
}

static int	reportCenters(t_seeker *cs, t_image *image)
{
	int	return_value;
	int	validObjectCount = 0;

	printf("Detected %d objects.\n", cs->objectCount - 1);
	for (t_object *object = cs->objects; object != NULL; object = object->next)
	{
		int	check = 0;
		if (cs->visited[0][0] == object->label) check++;
		if (cs->visited[0][image->width / 2] == object->label) check++;
		if (cs->visited[0][image->width - 1] == object->label) check++;
		if (cs->visited[image->height / 2][0] == object->label) check++;
		if (cs->visited[image->height / 2][image->width - 1] == object->label) check++;
		if (cs->visited[image->height - 1][0] == object->label) check++;
		if (cs->visited[image->height - 1][image->width / 2] == object->label) check++;
		if (cs->visited[image->height - 1][image->width - 1] == object->label) check++;
		if (check > 0)
		{
			printf("\e[33mObject #%d may be tape:\e[0m detected on \e[3%dm%d/8\e[0m corners or edges\n", object->label, tape_warning(check), check);
			object->label = TAPE;
		}
		else
		{
			printf("Object #%d with center (%d, %d) and bounding box (%d, %d) <> (%d, %d)\n",
				object->label, object->centerY, object->centerX, object->minY, object->minX, object->maxY, object->maxX);
			object->label = ++validObjectCount;
		}
	}
	return (RETURN_SUCCESS);
}

// objects still in use by t_image
static void	clear(t_seeker *cs)
{
	for (int i = 0; i < cs->ref_image->height; i++)
		free(cs->visited[i]);
	free(cs->visited);
}

// seeker named cs (centerSeeker) for brevity
int findObjects(t_image *image)
{
	int			return_value;
	t_seeker	*cs = initSeeker(image);

	if (cs == NULL)
		return (memory_error());
	for (int y = 0; y < image->height; y++)
	{
		for (int x = 0; x < image->width; x++)
		{
			if (image->pixels[y][x] == STRAWBERRY && cs->visited[y][x] == 0)
			{
				// printf("seeking object on (%d, %d)...", y, x); // debug
				t_object *object = newObject(cs->objectCount, cs->objects);
				if (object == NULL)
					return (RETURN_ERROR);

				if (floodFill(cs, object, x, y) == RETURN_ERROR)
					return (RETURN_ERROR);
				if (object->size > OBJECT_SIZE_THRESHOLD)
				{
					object->centerY = object->sumY / object->size;
					object->centerX = object->sumX / object->size;
					cs->objectCount++;
					cs->objects = object;
					// printf("found with size %d (%d, %d)\n", object->size, object->sumY, object->sumX); // debug
				}
				else
				{
					// printf("discarded with size %d\n", object->size); // debug
					free(object);
				}
			}
		}
	}
	return_value = reportCenters(cs, image);
	clear(cs);
	if (return_value != RETURN_SUCCESS)
		return (return_value);
	return (cs->objectCount - 1);
}
