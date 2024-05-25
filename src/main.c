#include "miniRT.h"

t_data	d;

void display() 
{
    // Clear color and depth buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	glMatrixMode(GL_MODELVIEW);     // Operate on model-view matrix

    /* Draw a quad */
	glBegin(GL_QUADS);
	glTexCoord2i(0, 0); glVertex2i(0, 0);
	glTexCoord2i(0, 1); glVertex2i(0, (GLint)d.env.height);
	glTexCoord2i(1, 1); glVertex2i((GLint)d.env.width, (GLint)d.env.height);
	glTexCoord2i(1, 0); glVertex2i((GLint)d.env.width, 0);
	glEnd();

    glutSwapBuffers();
} 

/* Handler for window re-size event. Called back when the window first appears and
   whenever the window is re-sized with its new width and height */
void reshape(GLsizei newwidth, GLsizei newheight) 
{  
    // Set the viewport to cover the new window
    glViewport(0, 0, d.env.width=newwidth, d.env.height=newheight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, (GLdouble)d.env.width, (GLdouble)d.env.height, 0.0, 0.0, 100.0);
    glMatrixMode(GL_MODELVIEW);

    glutPostRedisplay();
}


/* Initialize OpenGL Graphics */
void initGL(int w, int h) 
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h); // use a screen size of WIDTH x HEIGHT
	glEnable(GL_TEXTURE_2D);     // Enable 2D texturing

	glMatrixMode(GL_PROJECTION);     // Make a simple 2D projection on the entire window
	glLoadIdentity();
	glOrtho(0.0, (GLdouble)w, (GLdouble)h, 0.0, 0.0, 100.0);

	glMatrixMode(GL_MODELVIEW);    // Set the matrix mode to object modeling

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); 
	glClearDepth(0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the window
}

static void	d_init(int width, int height)
{
	d.env.width = width;
	d.env.height = height;

	d.imgData = calloc(height * width, sizeof(uint32_t));
	if (!d.imgData)
		ft_error(0, "Image init failure\n");

	d.shapes.cylindres = NULL;
	d.shapes.spheres = NULL;
	d.shapes.planes = NULL;
	d.cam_count = 0;
	d.light_count = 0;
	d.alight_count = 0;
}

static void	save_to_img(char *filename)
{
	printf("Saving image as PPM file...\n");
	int	fd = open(filename, O_RDWR | O_APPEND | O_CREAT | O_TRUNC, 0644);
	char *ppm = canvas_to_ppm();
	ft_putstr_fd(ppm, fd);
	free(ppm);
	close(fd);
	printf("Success!\n");
}

int	main(int ac, char **av)
{
	if ((ac != 2 && ac != 4) ||
		(ac == 4 && strcmp(av[2], "-S") != 0))
	{
		printf("usage: ./miniRT scene_file [-S filename]\n  options:\n    -S filename	- Save your scene in ppm format\n");
		return(0);
	}

	d_init(600, 400);
	load_data(av[1]);

	glutInit(&ac, av);            // Initialize GLUT
	glutInitDisplayMode(GLUT_DOUBLE); // Enable double buffered mode
	glutInitWindowSize((int)d.env.width, (int)d.env.height);   // Set the window's initial width & height
	glutCreateWindow(av[0]);      // Create window with the name of the executable
	glutDisplayFunc(display);       // Register callback handler for window re-paint event
	glutReshapeFunc(reshape);       // Register callback handler for window re-size event

    /* OpenGL 2D generic init */
    initGL((int)d.env.width, (int)d.env.height);

	ray_trace(&d);

	if (ac == 4 && ft_strncmp(av[2], "-S", 2) == 0)
		save_to_img(av[3]); 
	
	GLuint	texid;
	/* OpenGL texture binding of the image loaded by DevIL  */
	glGenTextures(1, &texid); /* Texture name generation */
	glBindTexture(GL_TEXTURE_2D, texid); /* Binding of texture name */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); /* We will use linear interpolation for magnification filter */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); /* We will use linear interpolation for minifying filter */
	// glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_BPP), ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT), 
	// 0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE, ilGetData()); /* Texture specification */
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (GLsizei)d.env.width, (GLsizei)d.env.height, 0, GL_RGBA,  GL_UNSIGNED_INT_8_8_8_8_REV, d.imgData);

    /* Main loop */
    glutMainLoop();

    glDeleteTextures(1, &texid);
	clean_up();
	return (0);
}
