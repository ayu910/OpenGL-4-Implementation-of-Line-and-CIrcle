Computer Graphics Programming Assignment 1

About the project :
1. The pa1.cpp file uses opengl 3.3+, glfw and glad to create and display 2D objects in a window.
2. The glad.h and glad.cpp files are for the GLAD library functions.
3. CMakeLists.txt creates executable file for pa1.cpp using cmake and make
4. Executable file can be found in bin folder

Functionalities Implemented :
1. Line Drawing using Midpoint Algorithm
2. Using the vertices provided by user, all line coordinates are calculated by midpoint algorithm
and provided to the Vertex Shader for displaying on window using GL_POINTS.
3. Line Drawing works for vertical line, horizontal line, 0 < m < 1, -1 < m < 0, m > 1, m < -1
4. Multiple Vertices can be provided to draw multiple lines which form a polygon.
5. Midpoint Algorithm is extended to create a circle.
6. Midpoint Algortihm is extended to create an ellipse.

Functinalities Not Implemented :
1. Mouse Input
2. Curve drawing of cubic equation.

Compile the program :
1. In the folder build : run cmake /path-to-CmakeLists.txt/
2. A MakeFile will be formed
3. Run command make
4. Executable should be created pa1
5. Run ./pa1
6. Options will be available to either display Default Shapes or create a new line/circle/polygon/elipse.
7. Choose option and enter normalised coordinates appropriately
8. Radius of Circle and Elipse are integer values (eg : 50, 60). Please use larger values.

