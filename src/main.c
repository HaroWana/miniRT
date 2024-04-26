#include "miniRT.h"

t_data	d;

static void	d_init(t_data *d, int width, int height)
{
	d->env.size_x = width;
	d->env.size_y = height;
	// d->env.mlx = mlx_init(d->env.size_x, d->env.size_y, "miniRT", true);
	// d->img = mlx_new_image(d->env.mlx, d->env.size_x, d->env.size_y);
	d->img = malloc(sizeof(unsigned char) * width * height * 3);
	if (!d->img)
		ft_error(0, "Image init failure\n");
	
	d->shapes.cylindres = NULL;
	d->shapes.spheres = NULL;
	d->shapes.planes = NULL;
	d->cam_count = 0;
	d->light_count = 0;
	d->alight_count = 0;
}

static void	render(GLFWwindow *window)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture first
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, d.env.size_x, d.env.size_y, 0, GL_RGB, GL_UNSIGNED_BYTE, d.img);

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex2f(-1, -1);
	glTexCoord2f(1, 0); glVertex2f(1, -1);
	glTexCoord2f(1, 1); glVertex2f(1, 1);
	glTexCoord2f(0, 1); glVertex2f(-1, 1);
	glEnd();

	glfwSwapBuffers(window);
}

int	main(int ac, char **av)
{
	(void)ac;
	if (!glfwInit())
		ft_error(0, "GLFW init failure\n");
	d_init(&d, 1280, 720);
	load_data(av[1]);

	d.env.win = glfwCreateWindow(1280, 720, "MiniRT", NULL, NULL);
    if (!d.env.win) {
        glfwTerminate();
        fprintf(stderr, "Failed to create GLFW window\n");
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(d.env.win);

    // Set up OpenGL state
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black background

    // Set up texture
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glViewport(0, 0, 1280, 720);

	ray_trace(&d);

	

	while (!glfwWindowShouldClose(d.env.win)) {
        // Render here
        render(d.env.win);

        // Poll for and process events
        glfwPollEvents();
    }

    // Terminate GLFW
    glfwTerminate();

	// mlx_loops(&d);
	clean_up();
	return (0);
}
