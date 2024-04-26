#include "../inc/miniRT.h"

static void	error_message(int err, char *buf)
{
	fprintf(stderr, "(ERROR) ");
	switch (err)
	{
		case (1):
			fprintf(stderr, "Invalid data");
			break;

		case (2):
			fprintf(stderr, "Invalid number of parameters");
			break;

		case (3):
			fprintf(stderr, "Invalid ratio value");
			break;

		case (4):
			fprintf(stderr, "Invalid RGB values");
			break;
		
		case (5):
			fprintf(stderr, "Invalid position");
			break;

		case (6):
			fprintf(stderr, "Invalid shape parameter");
			break;

		case (7):
			fprintf(stderr, "Invalid Camera FOV");
			break;

		case (8):
			fprintf(stderr, "Invalid vector value");
			break;

		case (9):
			fprintf(stderr, "Memory allocation failure");
			break;

		default:
			break;
	}

	if (buf)
		fprintf(stderr, ": %s\n", buf);
	else
		fprintf(stderr, "\n");
}

void	ft_error(int ret, char *str)
{
	error_message(ret, str);
	clean_up();
	exit(EXIT_FAILURE);
}