#include <bits/stdc++.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace std;

void framebuffer_size_callback(GLFWwindow * window, int width, int height);

void processInput(GLFWwindow * window);

void midpoint_fn(float xpos0, float ypos0, float xpos1, float ypos1);
void midpoint_circle_fn(float xCentre, float yCentre, int radius);
void calculate_circle_coords(float xCentre, float yCentre, float x_coords, float y_coords);
void midpoint_ellipse_fn(int xCentre, int yCentre, int a, int b);

int plotPoints = 0;
float allPoints[100000];
int process;
int polyVertices = 0;
float polygonVertices[20];
int n = 0, radius = 0;
float xCentre, yCentre;
int a,b;

int main()
{
    // 1. OpenGL content by GLFW

    float x0, y0, x1, y1;
    printf("What do you want to draw?\n 1. Default Shapes \n 2. Line\n 3. Polygon\n 4. Circle\n 5. Elipse\n\n");
    cin >> process;
    if(process == 2)
    {
    	printf("Enter x0, y0, x1, y1 in range -1.0 to 1.0 : \n");
   	cin >> x0;
    	cin >> y0;
    	cin >> x1;
    	cin >> y1;
	midpoint_fn(x0,y0,x1,y1);
    }
    else if (process == 3)
    {
    	printf("Enter number of vertices (max 10) : \n");
	cin >> polyVertices;
	for(int k=0; k<polyVertices; k++)
	{
		cin >> polygonVertices[n];
		n++;
		cin >> polygonVertices[n];
		n++;
	}
	for(int k=0; k<(polyVertices-1)*2; k++)
	{
		x0 = polygonVertices[k];
		y0 = polygonVertices[k+1];
		x1 = polygonVertices[k+2];
		y1 = polygonVertices[k+3];
		midpoint_fn(x0,y0,x1,y1);
		k++;
	}
	x0 = x1;
	y0 = y1;
	x1 = polygonVertices[0];
	y1 = polygonVertices[1];
	midpoint_fn(x0,y0,x1,y1);
    	
    }
    else if (process == 4)
    {
    	printf("Enter circle centre coordinates and radius :\n");
    	cin >> xCentre;
    	cin >> yCentre;
    	cin >> radius;
    	midpoint_circle_fn(xCentre, yCentre, radius);
    }
    else if (process == 5)
    {
    	printf("Enter elipse centre coordinates and x and y radius :\n");
	cin >> xCentre;
	cin >> yCentre;
	cin >> a;
	cin >> b;
	midpoint_ellipse_fn(xCentre, yCentre, a, b);
    }
    else if (process == 1)
    {
    	printf("Printing all default shapes.");
	//Polygon
    	midpoint_fn(0.2f, 0.5f, 0.5f, 0.5f);
    	midpoint_fn(0.5f, 0.5f, 0.5f, 0.9f);
    	midpoint_fn(0.5f, 0.9f, 0.4f, 0.7f);
    	midpoint_fn(0.4f, 0.7f, 0.2f, 0.5f);
        	
    	
	//Lines
	midpoint_fn(-0.2f, 0.3f, -0.5f, 0.5f); // 0<m<1
	midpoint_fn(-0.5f, 0.3f, -0.2f, 0.5f); // -1<m<0
   	midpoint_fn(-0.3f, 0.2f, -0.5f, 0.5f); // m>1
    	midpoint_fn(-0.3f, 0.5f, -0.5f, 0.2f); // m<-1
    	midpoint_fn(-0.8f, 0.3f, -0.8f, 0.7f); // vertical line
    	midpoint_fn(-0.3f, 0.1f, -0.5f, 0.1f); // horizontal line

	
	//Circle
	midpoint_circle_fn(0.0, 0.0, 50);

	//Elipse
	midpoint_ellipse_fn(0.5, 0.5, 30, 70);
    }

    // 1. OpenGL content by GLFW

    glfwInit(); //Initialize the window
    //Set options (enums) with the value in argument 2
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //Set major OpenGL version needed to 3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //Sen minor OpenGL version needed to 3
    //Set opengl profile as core profile so that we get access to smaller subset of features of opengl
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //Create a window with width, height and name as parameters
    GLFWwindow * window = glfwCreateWindow(800, 600, "Ayu_OpenGL", nullptr, nullptr);

    if (!window)
    {
        std::cout << std::unitbuf
                  << "[ERROR] " << __FILE__ << ':' << __LINE__ << ' ' << __PRETTY_FUNCTION__
                  << "\n[ERROR] " << "Failed to create GLFW window!"
                  << std::nounitbuf << std::endl;
        glfwTerminate();
        std::abort();
    }

    //Make the context for glfw window the current context.
    glfwMakeContextCurrent(window);
    //Register any callback functions created.
    //Registration of fucntions should be done before loop is rendered.
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // 2. load OpenGL functions by GLAD
    //GLAD returns glfwGetProcAddress which has correct function for current OS
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    {
        std::cout << std::unitbuf
                  << "[ERROR] " << __FILE__ << ':' << __LINE__ << ' ' << __PRETTY_FUNCTION__
                  << "\n[ERROR] " << "Failed to initialize GLAD!"
                  << std::nounitbuf << std::endl;

        std::abort();
    }

    // 3. compile & link shader programs

    // vertex shader
    //vertex shader definition
    const char * vertexShaderSource = "#version 330 core\n"
                                      "layout (location = 0) in vec3 aPos;\n"
                                      "void main()\n"
                                      "{\n"
                                      " gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                      "}\0";

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);

        std::cout << std::unitbuf
                  << "[ERROR] " << __FILE__ << ':' << __LINE__ << ' ' << __PRETTY_FUNCTION__
                  << "\n[ERROR] " << "Vertex shader compilation failed!"
                  << "\n[ERROR] " << infoLog
                  << std::nounitbuf << std::endl;

        std::abort();
    }

    // fragment shader
    const char * fragmentShaderSource = "#version 330 core\n"
                                        "out vec4 FragColor;\n"
                                        "void main()\n"
                                        "{\n"
                                        "    FragColor = vec4(1.0f, 0.0f, 0.5f, 1.0f);\n"
                                        "}\0";

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);

        std::cout << std::unitbuf
                  << "[ERROR] " << __FILE__ << ':' << __LINE__ << ' ' << __PRETTY_FUNCTION__
                  << "\n[ERROR] " << "Fragment shader compilation failed!"
                  << "\n[ERROR] " << infoLog
                  << std::nounitbuf << std::endl;

        std::abort();
    }

    // attach compiled shaders to shader program object and link them
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);

        std::cout << std::unitbuf
                  << "[ERROR] " << __FILE__ << ':' << __LINE__ << ' ' << __PRETTY_FUNCTION__
                  << "\n[ERROR] " << "Shader program linking failed!"
                  << "\n[ERROR] " << infoLog
                  << std::nounitbuf << std::endl;

        std::abort();
    }

    // Shaders are already attached to shaderProgram object.
    // Shaders themselves are now useless and should be deallocated.
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // 4. Vertex coordinate in Normalized Device Coordinate (NDC).
    float vertices[] = {
            0.5f, 0.5f, 0.0f,    // top right
            0.5f, -0.5f, 0.0f,   // bottom right
            -0.5f, -0.5f, 0.0f,  // bottom left
            -0.5f, 0.5f, 0.0f    // top left
    };
    //midpoint_fn(x0,y0,x1,y1); // 0<m<1
    //midpoint_fn(0.2f, 0.3f, 0.5f, 0.5f); // 0<m<1
    //midpoint_fn(0.5f, 0.3f, 0.2f, 0.5f); // -1<m<0
    //midpoint_fn(0.3f, 0.2f, 0.5f, 0.5f); // m>1
    //midpoint_fn(0.3f, 0.5f, 0.5f, 0.2f); // m<-1
    //midpoint_fn(0.1f, 0.3f, 0.1f, 0.7f); // vertical line
    //midpoint_fn(0.3f, 0.1f, 0.7f, 0.1f); // horizontal line

    unsigned int indices[] = {   // note that we start from 0!
            0, 1, 3,             // first triangle
            1, 2, 3              // second triangle
    };

    // 5.
    // Send vertex data to vertex shader
    // by creating memory (vertex buffer objects, VBO) on GPU where we store these vertex data.
    // VBOs store float arrays storing vertex coordinates
    // and how it should be interpreted into vec3 in GLSL (i.e. indexes, strides, offsets, etc.)

    // VBOs are stored and organized by vertex array object (VAO).
    // A VAO organizes MULTIPLE VBOs.
    // Once binded to OpenGL context by glBindVertexArray(), this AVO is active and will record
    // calls to functions specifying how VBO should be interpreted and their destinations in vertex shader:
    // glVertexAttribPointer(), glEnableVertexAttribArray() / glDisableVertexAttribArray()

    // A VAO may also has ONE element buffer object (EBO)
    // which is used together with glDrawElements(), where EBO determines which vertices form which triangle.
    // An active VAO stores the glBindBuffer() calls when the target is GL_ELEMENT_ARRAY_BUFFER.
    // This also means it stores its unbind calls.
    // So make sure you DON'T unbind the element array buffer before unbinding your VAO,
    // otherwise it doesn’t have an EBO configured.

    // VAO initialization code
    // Done once (unless your object frequently changes)
    // Bind VAO first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // VBO
    unsigned int VBO;
    glGenBuffers(1, &VBO);

    // Bind this buffer to OpenGL context GL_ARRAY_BUFFER.
    // Recall that OpenGL is a state machine, which means from now on,
    // any buffer call we make (on the GL_ARRAY_BUFFER target)
    // will be used to configure the currently bound buffer, which is VBO.
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // call glBufferData() function that copies the previously defined vertex data into the buffer’s memory
    glBufferData(GL_ARRAY_BUFFER, sizeof(allPoints), allPoints, GL_STATIC_DRAW);

    // tell opengl how to interpret current VBO into "layout (location = 0) in vec3 aPos"
    // current VBO is specified by global context GL_ARRAY_BUFFER
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), reinterpret_cast<void *>(0));
    glEnableVertexAttribArray(0);

    // EBO
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Note that this is allowed.
    // The call to glVertexAttribPointer registered VBO
    // as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens.
    // Modifying other VAOs requires a call to glBindVertexArray anyways
    // so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);

    // WARNING
    // A VAO stores the glBindBuffer calls when the target is GL_ELEMENT_ARRAY_BUFFER.
    // This also means it stores its unbind calls.
    // So make sure you DON'T unbind the element array buffer before unbinding your VAO,
    // otherwise it doesn’t have an EBO configured.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


    // 3. render loop
    //Set the dimensions of window to display data with respect to coordinates
    //Parameters are lower left corener x and y coordinates and width, height
    glViewport(0, 0, 800, 600);

    // draw in wireframe polygons or filled polygons
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    while (!glfwWindowShouldClose(window))
    {
        // process input
        processInput(window);

        // rendering code here

        // background
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // triangle
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        //Draw all points in allPoints array on window using Vertex Buffer
        glDrawArrays(GL_POINTS, 0, plotPoints );
        glBindVertexArray(0);

        // check and call events and swap the buffers
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    // de-allocate all resources once they've outlived their purpose:
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
}


void framebuffer_size_callback(GLFWwindow * window, int width, int height)
{
    glViewport(0, 0, width, height);
}


void processInput(GLFWwindow * window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}

void midpoint_fn(float x1, float y1, float x2, float y2)
{
    printf("Midpoint function called!\n");
    //Denormalize coordinates using width=800 and height = 600
    x1 = (x1 + 1)*400;
    x2 = (x2 + 1)*400;
    y1 = (y1 + 1)*300;
    y2 = (y2 + 1)*300;
    float i = 0, j = 0;
    
    //handle horizontal line
    if(y1 == y2)
    {
        for(i=x1; i<=x2; i++)
        {
            j = ((float)i/400) - 1;
            allPoints[plotPoints] = j;
            plotPoints++;
            allPoints[plotPoints] = ((float)y1/400)-1;
            plotPoints++;
            allPoints[plotPoints] = 0.0f;
            plotPoints++;
	    printf("Values in allPoints at %d is %f, %f, %f\n", plotPoints, allPoints[plotPoints-3],allPoints[plotPoints-2], allPoints[plotPoints-1]);
        }
        return;
    }
    //handle vertical line
    if(x1 == x2)
    {
        for(i=y1; i<=y2; i++)
         {
             j = ((float)i/400) - 1;
             allPoints[plotPoints] = ((float)x1/400)-1;
             plotPoints++;
             allPoints[plotPoints] = j;
             plotPoints++;
             allPoints[plotPoints] = 0.0f;
             plotPoints++;
	     printf("Values in allPoints at %d is %f, %f, %f\n", plotPoints, allPoints[plotPoints-3],allPoints[plotPoints-2], allPoints[plotPoints-1]);
         }
         return;
    }
    bool slope = abs(y2 - y1) > abs(x2 - x1);
    if(slope) {
        // swap x1 and y1
        int temp = x1;
        x1 = y1;
        y1 = temp;
        // swap x2 and y2
        temp = x2;
        x2 = y2;
        y2 = temp;
    }
    if(x1 > x2) {
        // swap x1 and x2
        int temp = x1;
        x1 = x2;
        x2 = temp;
        // swap y1 and y2
        temp = y1;
        y1 = y2;
        y2 = temp;
    }

    int dx, dy, error_val, y_coord, x, y;

    dx = x2 - x1;
    dy = abs(y2 - y1);
    error_val = dx / 2;
    y = y1;

    if(y1 < y2)
        y_coord = 1;
    else
        y_coord = -1;

    //glBegin(GL_POINTS);
    for (x = x1; x <= x2; x++) {
        if(slope){
            //glVertex2f(y, x);
            allPoints[plotPoints] = ((float)y/400)-1;
            plotPoints++;
            allPoints[plotPoints] = ((float)x/400)-1;
            plotPoints++;
            allPoints[plotPoints] = 0.0f;
            plotPoints++;
	    printf("Values in allPoints at %d is %f, %f, %f\n", plotPoints, allPoints[plotPoints-3],allPoints[plotPoints-2], allPoints[plotPoints-1]);
	}
        else{
            //glVertex2f(x, y);
            allPoints[plotPoints] = ((float)x/400)-1;
            plotPoints++;
            allPoints[plotPoints] = ((float)y/400)-1;
            plotPoints++;
            allPoints[plotPoints] = 0.0f;
            plotPoints++;
	    printf("Values in allPoints at %d is %f, %f, %f\n", plotPoints, allPoints[plotPoints-3],allPoints[plotPoints-2], allPoints[plotPoints-1]);
	}
        error_val -= dy;
        if (error_val < 0) {
            y += y_coord;
            error_val += dx;
        }
    }
    //glEnd();
}


void midpoint_circle_fn(float xCentre, float yCentre, int radius)
{
    int x_coord = radius, y_coord = 0;
    calculate_circle_coords(xCentre, yCentre, x_coord, y_coord);

    if (radius > 0)
    {
        calculate_circle_coords(xCentre, yCentre, x_coord, -y_coord);
        calculate_circle_coords(xCentre, yCentre, y_coord, x_coord);
        calculate_circle_coords(xCentre, yCentre, -y_coord, x_coord);
    }

    int param = 1 - radius;
    while (x_coord > y_coord)
    {
        y_coord++;
        if (param <= 0)
            param = param + 2*y_coord + 1;
        else
        {
            x_coord--;
            param = param + 2*y_coord - 2*x_coord + 1;
        }

        if (x_coord < y_coord)
            break;

        calculate_circle_coords(xCentre, yCentre, x_coord, y_coord);
        calculate_circle_coords(xCentre, yCentre, -x_coord, y_coord);
        calculate_circle_coords(xCentre, yCentre, x_coord, -y_coord);
        calculate_circle_coords(xCentre, yCentre, -x_coord, -y_coord);

        if (x_coord != y_coord)
        {
            calculate_circle_coords(xCentre, yCentre, y_coord, x_coord);
            calculate_circle_coords(xCentre, yCentre, -y_coord, x_coord);
            calculate_circle_coords(xCentre, yCentre, y_coord, -x_coord);
            calculate_circle_coords(xCentre, yCentre, -y_coord, -x_coord);
        }
    }
}


void midpoint_ellipse_fn(int xCentre, int yCentre, int a, int b)
{
    float x_coord = 0, y_coord = b;

    float param1 = (b*b)-(a*a*b)+(0.25*a*a);
    float px = 2*b*b*x_coord;
    float py = 2*a*a*y_coord;

    while (px < py)
    {
        calculate_circle_coords(xCentre, yCentre, x_coord, y_coord);
        calculate_circle_coords(xCentre, yCentre, -x_coord, y_coord);
        calculate_circle_coords(xCentre, yCentre, x_coord, -y_coord);
        calculate_circle_coords(xCentre, yCentre, -x_coord, -y_coord);

        if (param1 < 0)
        {
            x_coord++;
            px = px + (2*b*b);
            param1 = param1 + px + (b*b);
        }
        else
        {
            x_coord++;
            y_coord--;
            px = px + (2*b*b);
            py = py - (2*a*a);
            param1 = param1 + px - py + (b*b);
        }
    }

    float param2 = ((b*b)*((x_coord + 0.5)*(x_coord + 0.5))) + ((a*a)*((y_coord - 1)*(y_coord - 1))) - (a*a*b*b);

    while (y_coord >= 0)
    {
        calculate_circle_coords(xCentre, yCentre, x_coord, y_coord);
        calculate_circle_coords(xCentre, yCentre, -x_coord, y_coord);
        calculate_circle_coords(xCentre, yCentre, x_coord, -y_coord);
        calculate_circle_coords(xCentre, yCentre, -x_coord, -y_coord);

        if (param2 > 0)
        {
            y_coord--;
            py = py - (2*a*a);
            param2 = param2 + (a*a) - py;
        }
        else
        {
            y_coord--;
            x_coord++;
            px = px + (2*b*b);
            py = py - (2*a*a);
            param2 = param2 + px - py + (a*a);
        }
    }
}


void calculate_circle_coords(float xCentre, float yCentre, float x_coords, float y_coords)
{	
    allPoints[plotPoints] = ((float)(x_coords + (xCentre + 1)*400)/400)-1;
    plotPoints++;
    allPoints[plotPoints] = ((float)(y_coords + (yCentre + 1)*300)/300)-1;
    plotPoints++;
    allPoints[plotPoints] = 0.0f;
    plotPoints++;
    printf("Values in allPoints at %d is %f, %f, %f\n", plotPoints, allPoints[plotPoints-3],allPoints[plotPoints-2], allPoints[plotPoints-1]);
    	
}
