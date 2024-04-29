#include "miniRT.h"

t_data	d;

static void	d_init(int width, int height)
{
	d.env.size_x = width;
	d.env.size_y = height;
	// d->env.mlx = mlx_init(d->env.size_x, d->env.size_y, "miniRT", true);
	// d->img = mlx_new_image(d->env.mlx, d->env.size_x, d->env.size_y);
	d.img = malloc(sizeof(unsigned int) * width * height * 3);
	if (!d.img)
		ft_error(0, "Image init failure\n");
	ft_bzero(d.img, sizeof(unsigned int) * width * height * 3);
	
	d.shapes.cylindres = NULL;
	d.shapes.spheres = NULL;
	d.shapes.planes = NULL;
	d.cam_count = 0;
	d.light_count = 0;
	d.alight_count = 0;
}


// static void	render(GLFWwindow *window)
// {
// 	glClear(GL_COLOR_BUFFER_BIT);


// 	glfwSwapBuffers(window);
// }

// GLuint createTexture() {
//     GLuint textureID;
//     glGenTextures(1, &textureID);

//     // Bind texture
//     glBindTexture(GL_TEXTURE_2D, textureID);

//     // Set texture parameters
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

//     // Generate texture
//     glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, d.env.size_x, d.env.size_y, 0, GL_RGB,  GL_UNSIGNED_INT, d.img);

//     // Unbind texture
//     glBindTexture(GL_TEXTURE_2D, 0);

//     return (textureID);
// }

// static void draw(GLuint textureID) {
//     // Clear the screen
//     glClear(GL_COLOR_BUFFER_BIT);

//     // Set up 2D drawing mode
//     glMatrixMode(GL_PROJECTION);
//     glLoadIdentity();
//     gluOrtho2D(0, 1280, 0, 720); // Adjust the coordinates based on your window size

//     glMatrixMode(GL_MODELVIEW);
//     glLoadIdentity();

//     // Bind texture
//     glBindTexture(GL_TEXTURE_2D, textureID);

//     // Draw textured quad
//     glBegin(GL_QUADS);
//     glTexCoord2f(0.0f, 1.0f); glVertex2f(0, 0);
//     glTexCoord2f(1.0f, 1.0f); glVertex2f(1280, 0);
//     glTexCoord2f(1.0f, 0.0f); glVertex2f(1280, 720);
//     glTexCoord2f(0.0f, 0.0f); glVertex2f(0, 720);
//     glEnd();

//     // Unbind texture
//     glBindTexture(GL_TEXTURE_2D, 0);

// 	GLenum error = glGetError();
//     if (error != GL_NO_ERROR) {
//         fprintf(stderr, "OpenGL error: %d\n", error);
//     }
// }

// int	main(int ac, char **av)
// {
// 	(void)ac;

// 	//GLFW init
// 	if (!glfwInit())
// 		ft_error(0, "GLFW init failure\n");

// 	// raytracer init
// 	d_init(&d, 1280, 720);
// 	load_data(av[1]);
//     ray_trace();

// 	// window creation
// 	d.env.win = glfwCreateWindow(1280, 720, "MiniRT", NULL, NULL);
//     if (!d.env.win) {
//         glfwTerminate();
//         fprintf(stderr, "Failed to create GLFW window\n");
//         return -1;
//     }

//     // Make the window's context current
//     glfwMakeContextCurrent(d.env.win);
	
// 	GLuint textureID = createTexture();

// 	while (!glfwWindowShouldClose(d.env.win)) {
//         // Render here
//         draw(textureID);

//         // Swap front and back buffers
//         glfwSwapBuffers(d.env.win);

//         // Poll for and process events
//         glfwPollEvents();
//     }

// 	// Delete texture
// 	glDeleteTextures(1, &textureID);

//     // Terminate GLFW
//     glfwTerminate();

// 	// mlx_loops(&d);
// 	clean_up();
// 	return (0);
// }

static void	save_to_img(char *filename)
{
	printf("Saving image as PPM file...\n");
	int	fd = open(filename, O_WRONLY | O_APPEND | O_CREAT | O_TRUNC, 0644);
	char *ppm = canvas_to_ppm();
	ft_putstr_fd(ppm, fd);
	free(ppm);
	close(fd);
	printf("Success!\n");
	clean_up();
}

/* Handler for window-repaint event. Called back when the window first appears and
   whenever the window needs to be re-painted. */
void display() 
{
    // Clear color and depth buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	glMatrixMode(GL_MODELVIEW);     // Operate on model-view matrix

    /* Draw a quad */
	glBegin(GL_QUADS);
	glTexCoord2i(0, 0); glVertex2i(0, 0);
	glTexCoord2i(0, 1); glVertex2i(0, d.env.size_y);
	glTexCoord2i(1, 1); glVertex2i(d.env.size_x, d.env.size_y);
	glTexCoord2i(1, 0); glVertex2i(d.env.size_y, 0);
	glEnd();

    glutSwapBuffers();
} 

/* Handler for window re-size event. Called back when the window first appears and
   whenever the window is re-sized with its new width and height */
void reshape(GLsizei newwidth, GLsizei newheight) 
{  
    // Set the viewport to cover the new window
    glViewport(0, 0, d.env.size_x=newwidth, d.env.size_y=newheight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, d.env.size_x, d.env.size_y, 0.0, 0.0, 100.0);
    glMatrixMode(GL_MODELVIEW);

    glutPostRedisplay();
}

  
/* Initialize OpenGL Graphics */
void initGL(int w, int h) 
{
	glViewport(0, 0, w, h); // use a screen size of WIDTH x HEIGHT
	glEnable(GL_TEXTURE_2D);     // Enable 2D texturing

	glMatrixMode(GL_PROJECTION);     // Make a simple 2D projection on the entire window
	glLoadIdentity();
	glOrtho(0.0, w, h, 0.0, 0.0, 100.0);

	glMatrixMode(GL_MODELVIEW);    // Set the matrix mode to object modeling

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); 
	glClearDepth(0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the window
}

int	main(int ac, char **av)
{
	(void)ac;
	GLuint texid;

	// raytracer init
	d_init(300, 300);
	load_data(av[1]);
    ray_trace();

	if (av[2] && av[3] && ft_strncmp(av[2], "-S", 2) == 0)
	{
		save_to_img(av[3]);
		return (0);
	}


	/* GLUT init */
    glutInit(&ac, av);            // Initialize GLUT
	glutInitDisplayMode(GLUT_DOUBLE); // Enable double buffered mode
	glutInitWindowSize(d.env.size_x, d.env.size_y);   // Set the window's initial width & height
	glutCreateWindow(av[0]);      // Create window with the name of the executable
	glutDisplayFunc(display);       // Register callback handler for window re-paint event
	glutReshapeFunc(reshape);       // Register callback handler for window re-size event

    /* OpenGL 2D generic init */
    initGL(d.env.size_x, d.env.size_y);


	/* OpenGL texture binding of the image loaded by DevIL  */
	glGenTextures(1, &texid); /* Texture name generation */
	glBindTexture(GL_TEXTURE_2D, texid); /* Binding of texture name */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); /* We will use linear interpolation for magnification filter */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); /* We will use linear interpolation for minifying filter */
	// glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_BPP), ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT), 
	// 0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE, ilGetData()); /* Texture specification */
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, d.env.size_x, d.env.size_y, 0, GL_RGB,  GL_UNSIGNED_BYTE, d.img);
 
    /* Main loop */
    glutMainLoop();
    
    /* Delete used resources and quit */
    glDeleteTextures(1, &texid);

	// mlx_loops(&d);
	clean_up();
	return (0);
}
