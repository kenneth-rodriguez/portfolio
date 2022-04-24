/*
 * Ken Rodriguez
 * CS-330: Comp Graphic and Visualization
 * Module 7: Project
 * 
 * Built using Tutorial 2.8 and the initial test assignment as scaffolding.
 * 
 * In addition to Q and E, the standard "FPS controls" of spacebar and left
 * control have been implemented for easier camera navigation.
 */

// #include libraries	
#include <iostream>
#include <cstdlib>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "camera.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>


// GLM math header #include
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Shader program
#ifndef GLSL
#define GLSL(Version, Source) "#version " #Version " core \n" #Source
#endif


// using the standard namespace
using namespace std;

// unnamed namespace
namespace
{
	const char* const WINDOW_TITLE = "Project Submission by Ken Rodriguez";

	// variables for window height/width
	const int WINDOW_WIDTH = 1000;
	const int WINDOW_HEIGHT = 800;

	// main GFLW window
	GLFWwindow* gWindow = nullptr;

	// define mesh structure
	struct GLMesh {
		GLuint vao;			// handle for Vertex Array Object
		GLuint vbos[2];		// handle for the Vertex Buffer Objects
		GLuint nIndices;	// number of mesh indices
	};

	// mesh data
	// each object has been separated in the event that I decide to keep practicing
	// and toggle objects on/off in realtime
	GLMesh lightMesh;				// light source
	GLMesh planeMesh;				// plane 
	GLMesh bookMesh;				// book 
	GLMesh pedalMesh;				// guitar pedal
	GLMesh penMesh;					// pen
	GLMesh dutchOvenMesh;			// dutch oven

	// Shader programs
	GLuint gProgramId;
	GLuint gLightId;

	// Texture scale
	glm::vec2 gUVScale(5.0f, 5.0f);

	// camera
	Camera gCamera(glm::vec3(0.0f, 0.0f, 3.0f));
	float gLastX = WINDOW_WIDTH / 2.0f;
	float gLastY = WINDOW_HEIGHT / 2.0f;
	bool gFirstMouse = true;

	// timing
	float gDeltaTime = 0.0f; // time between current frame and last frame
	float gLastFrame = 0.0f;

	// set default projection perspective
	glm::mat4 projection = glm::perspective(glm::radians(gCamera.Zoom), (GLfloat)WINDOW_WIDTH / (GLfloat)WINDOW_HEIGHT, 0.1f, 100.0f);

	// perspective/orthographic
	bool orthographicView = false;

	/*
	 * LIGHT VALUES (white, magenta, cyan, yellow)
	 */
	// light 1 color, position, and scale
	glm::vec3 gLightColor(1.0f, 1.0f, 1.0f);			// White
	glm::vec3 gLightPosition(00.0f, 30.0f, 20.0f);		
	glm::vec3 gLightScale(2.0f);						

	// light 2 color, position, and scale
	glm::vec3 gLightColor2(1.0f, 0.5f, 1.0f);			// Magenta
	glm::vec3 gLightPosition2(-22.0f, 15.0f, -15.0f);
	glm::vec3 gLightScale2(4.0f);

	// light 3 color, position, and scale
	glm::vec3 gLightColor3(0.5f, 1.0f, 1.0f);			// Cyan
	glm::vec3 gLightPosition3(15.0f, 10.0f, 0.0f);
	glm::vec3 gLightScale3(2.0f);

	// light 4 color, position, and scale
	glm::vec3 gLightColor4(1.0f, 1.0f, 1.0f);			// White
	glm::vec3 gLightPosition4(-0.0f, 20.0f, -20.0f);
	glm::vec3 gLightScale4(1.0f);
}
	// Initialize functions here.
	bool UInitialize(int, char* [], GLFWwindow** window);
	void UResizeWindow(GLFWwindow* window, int width, int height);
	void UProcessInput(GLFWwindow* window);
	void UDestroyMesh(GLMesh& mesh);
	void URender();
	bool UCreateShaderProgram(const char* vtxShaderSource, const char* fragShaderSource, GLuint& programId);
	void UDestroyShaderProgram(GLuint programId);
	void UMousePositionCallback(GLFWwindow* window, double xpos, double ypos);
	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	void defineTextures();
	void PhongUniforms();

	// Initialize mesh generation functions
	void CreateLight(GLMesh& mesh, glm::mat4 view, glm::mat4 projection);
	void generatePlane(GLMesh& mesh, glm::mat4 view, glm::mat4 projection);
	void generateCover(GLMesh& mesh, glm::mat4 view, glm::mat4 projection);
	void generatePages(GLMesh& mesh, glm::mat4 view, glm::mat4 projection);
	void generatePedalCase(GLMesh& mesh, glm::mat4 view, glm::mat4 projection);
	void generatePedalGlass(GLMesh& mesh, glm::mat4 view, glm::mat4 projection);
	void generatePedalElectronics(GLMesh& mesh, glm::mat4 view, glm::mat4 projection);
	void generatePenBody(GLMesh& mesh, glm::mat4 view, glm::mat4 projection);
	void generatePenTip(GLMesh& mesh, glm::mat4 view, glm::mat4 projection);
	void generatePenStylus(GLMesh& mesh, glm::mat4 view, glm::mat4 projection);
	void generateDutchOven(GLMesh& mesh, glm::mat4 view, glm::mat4 projection);
	void generateOvenHandle(GLMesh& mesh, glm::mat4 view, glm::mat4 projection);

	// Texture generation fields
	int width, height, nrChannels;

	/*
	 * DECLARE TEXTURES
	 */
	// plane texture
	unsigned int texture1;
	const char* planeTex = "../textureFiles/plane.png";
	// book cover texture
	unsigned int texture2;
	const char* coverTex = "../textureFiles/cover.jpg";
	// book page texture (it's a wood texture, but looks likes pages when it's stretched. I promise.)
	unsigned int texture3;
	const char* pageTex = "../textureFiles/pages.jpg";
	// guitar pedal casing texture
	unsigned int texture4;
	const char* pedalTex = "../textureFiles/pedalcase.jpg";
	// guitar pedal electronics texture
	unsigned int texture5;
	const char* pedalTex2 = "../textureFIles/electronics.jpg";
	// guitar pedal glass texture
	unsigned int texture6;
	const char* pedalTex3 = "../textureFiles/screen.jpg";
	// pen body texture
	unsigned int texture7;
	const char* penTex1 = "../textureFiles/pen.jpg";
	// pen tip texture
	unsigned int texture8;
	const char* penTex2 = "../textureFiles/pentip.jpg";
	// dutch oven texture
	unsigned int texture9;
	const char* dutchOvenTex = "../textureFiles/dutchOven.jpg";
	// dutch oven handle texture
	unsigned int texture10;
	const char* handleTex = "../textureFiles/handle.jpg";


	// Vertex shader source
	const GLchar* vertexShaderSource = GLSL(440,

		layout(location = 0) in vec3 position; // VAP position 0 for vertex position data
		layout(location = 1) in vec3 normal; // VAP position 1 for normals
		layout(location = 2) in vec2 textureCoordinate;

		out vec3 vertexNormal; // For outgoing normals to fragment shader
		out vec3 vertexFragmentPos; // For outgoing color / pixels to fragment shader
		out vec2 vertexTextureCoordinate;

		//Uniform / Global variables for the  transform matrices
		uniform mat4 model;
		uniform mat4 view;
		uniform mat4 projection;

		void main()
		{
			gl_Position = projection * view * model * vec4(position, 1.0f); // Transforms vertices into clip coordinates

			vertexFragmentPos = vec3(model * vec4(position, 1.0f)); // Gets fragment / pixel position in world space only (exclude view and projection)

			vertexNormal = mat3(transpose(inverse(model))) * normal; // get normal vectors in world space only and exclude normal translation properties
			vertexTextureCoordinate = textureCoordinate;
		}
	);

	// Vertex shader source
	const GLchar* vertexShaderSource2 = GLSL(440,

		layout(location = 0) in vec3 position; // VAP position 0 for vertex position data
		layout(location = 1) in vec3 normal; // VAP position 1 for normals
		layout(location = 2) in vec2 textureCoordinate;

		out vec3 vertexNormal; // For outgoing normals to fragment shader
		out vec3 vertexFragmentPos; // For outgoing color / pixels to fragment shader
		out vec2 vertexTextureCoordinate;

		//Uniform / Global variables for the  transform matrices
		uniform mat4 model;
		uniform mat4 view;
		uniform mat4 projection;

		void main()
		{
			gl_Position = projection * view * model * vec4(position, 1.0f); // Transforms vertices into clip coordinates

			vertexFragmentPos = vec3(model * vec4(position, 1.0f)); // Gets fragment / pixel position in world space only (exclude view and projection)

			vertexNormal = mat3(transpose(inverse(model))) * normal; // get normal vectors in world space only and exclude normal translation properties
			vertexTextureCoordinate = textureCoordinate;
		}
	);


	// Fragment shader source
	/* Object Fragment Shader Source Code*/
	const GLchar* fragmentShaderSource = GLSL(440,

		in vec3 vertexNormal; // For incoming normals
		in vec3 vertexFragmentPos; // For incoming fragment position
		in vec2 vertexTextureCoordinate;

		out vec4 fragmentColor; // For outgoing cube color to the GPU

		// Uniform / Global variables for object color, light color, light position, and camera/view position
		uniform vec3 objectColor;
		uniform vec3 lightColor;
		uniform vec3 lightPos;
		uniform vec3 viewPosition;
		uniform sampler2D uTexture; // Useful when working with multiple textures
		uniform vec2 uvScale;

		// Uniform / Global variables for light 2
		uniform vec3 objectColor2;
		uniform vec3 lightColor2;
		uniform vec3 lightPos2;
		uniform vec3 viewPosition2;
		uniform vec2 uvScale2;

		// Uniform / global variables for light 3
		uniform vec3 objectColor3;
		uniform vec3 lightColor3;
		uniform vec3 lightPos3;
		uniform vec3 viewPosition3;
		uniform vec2 uvScale3;

		// Uniform / globale variables for light 4
		uniform vec3 objectColor4;
		uniform vec3 lightColor4;
		uniform vec3 lightPos4;
		uniform vec3 viewPosition4;
		uniform vec2 uvScale4;

		void main()
		{
			/*Phong lighting model calculations to generate ambient, diffuse, and specular components*/

			//Calculate Ambient lighting (just a clean white to make other colors pop and add visibility to the scene and its textures
			float ambientStrength = 0.02f; // Set ambient or global lighting strength
			vec3 ambient = ambientStrength * lightColor; // Generate ambient light color


			/*
			 * Phong Light 1
			 */


			//Calculate Diffuse lighting*/
			vec3 norm = normalize(vertexNormal); // Normalize vectors to 1 unit
			vec3 lightDirection = normalize(lightPos - vertexFragmentPos); // Calculate distance (light direction) between light source and fragments/pixels on cube
			float impact = max(dot(norm, lightDirection), 0.0);// Calculate diffuse impact by generating dot product of normal and light
			vec3 diffuse = impact * lightColor; // Generate diffuse light color

			//Calculate Specular lighting*/
			float specularIntensity = 0.5f; // Set specular light strength
			float highlightSize = 32.0f; // Set specular highlight size
			vec3 viewDir = normalize(viewPosition - vertexFragmentPos); // Calculate view direction
			vec3 reflectDir = reflect(-lightDirection, norm);// Calculate reflection vector
			//Calculate specular component
			float specularComponent = pow(max(dot(viewDir, reflectDir), 0.0), highlightSize);
			vec3 specular = specularIntensity * specularComponent * lightColor;



			/*
			 * Phong Light 2
			 */

			//Calculate Diffuse lighting*/
			vec3 norm2 = normalize(vertexNormal); // Normalize vectors to 1 unit
			vec3 lightDirection2 = normalize(lightPos2 - vertexFragmentPos); // Calculate distance (light direction) between light source and fragments/pixels on cube
			float impact2 = max(dot(norm2, lightDirection2), 0.0);// Calculate diffuse impact by generating dot product of normal and light
			vec3 diffuse2 = impact2 * lightColor2; // Generate diffuse light color

			//Calculate Specular lighting*/
			float specularIntensity2 = 0.5f; // Set specular light strength
			float highlightSize2 = 32.0f; // Set specular highlight size
			vec3 viewDir2 = normalize(viewPosition2 - vertexFragmentPos); // Calculate view direction
			vec3 reflectDir2 = reflect(-lightDirection2, norm2);// Calculate reflection vector
			//Calculate specular component
			float specularComponent2 = pow(max(dot(viewDir2, reflectDir2), 0.0), highlightSize2);
			vec3 specular2 = specularIntensity2 * specularComponent2 * lightColor2;


			/*
			 * Phong Light 3
			 */

			 //Calculate Diffuse lighting*/
			vec3 norm3 = normalize(vertexNormal); // Normalize vectors to 1 unit
			vec3 lightDirection3 = normalize(lightPos3 - vertexFragmentPos); // Calculate distance (light direction) between light source and fragments/pixels on cube
			float impact3 = max(dot(norm3, lightDirection3), 0.0);// Calculate diffuse impact by generating dot product of normal and light
			vec3 diffuse3 = impact3 * lightColor3; // Generate diffuse light color

			//Calculate Specular lighting*/
			float specularIntensity3 = 0.5f; // Set specular light strength
			float highlightSize3 = 32.0f; // Set specular highlight size
			vec3 viewDir3 = normalize(viewPosition3 - vertexFragmentPos); // Calculate view direction
			vec3 reflectDir3 = reflect(-lightDirection3, norm3);// Calculate reflection vector
			//Calculate specular component
			float specularComponent3 = pow(max(dot(viewDir3, reflectDir3), 0.0), highlightSize3);
			vec3 specular3 = specularIntensity3 * specularComponent3 * lightColor3;


			/*
			 * Phong Light 4
			 */

			 //Calculate Diffuse lighting*/
			vec3 norm4 = normalize(vertexNormal); // Normalize vectors to 1 unit
			vec3 lightDirection4 = normalize(lightPos4 - vertexFragmentPos); // Calculate distance (light direction) between light source and fragments/pixels on cube
			float impact4 = max(dot(norm4, lightDirection4), 0.0);// Calculate diffuse impact by generating dot product of normal and light
			vec3 diffuse4 = impact4 * lightColor4; // Generate diffuse light color

			//Calculate Specular lighting*/
			float specularIntensity4 = 0.5f; // Set specular light strength
			float highlightSize4 = 32.0f; // Set specular highlight size
			vec3 viewDir4 = normalize(viewPosition4 - vertexFragmentPos); // Calculate view direction
			vec3 reflectDir4 = reflect(-lightDirection4, norm4);// Calculate reflection vector
			//Calculate specular component
			float specularComponent4 = pow(max(dot(viewDir4, reflectDir4), 0.0), highlightSize4);
			vec3 specular4 = specularIntensity4 * specularComponent4 * lightColor4;

			/* General Phong equations */

			// Texture holds the color to be used for all three components
			vec4 textureColor = texture(uTexture, vertexTextureCoordinate * uvScale);

			// Calculate phong result (add ambient diffuse and specular lights from each phong light)
			vec3 phong = (ambient + diffuse + specular 
								  + diffuse2 + specular2 
								  + diffuse3 + specular3 
								  + diffuse4 + specular4) * textureColor.xyz;

			fragmentColor = vec4(phong, 1.0); // Send lighting results to GPU
		}
	);


	/* Lamp Shader Source Code*/
	const GLchar* lampVertexShaderSource = GLSL(440,

		layout(location = 0) in vec3 position; // VAP position 0 for vertex position data

		//Uniform / Global variables for the  transform matrices
		uniform mat4 model;
		uniform mat4 view;
		uniform mat4 projection;

		void main()
		{
			gl_Position = projection * view * model * vec4(position, 1.0f); // Transforms vertices into clip coordinates
		}
	);

	/* Fragment Shader Source Code*/
	const GLchar* lampFragmentShaderSource = GLSL(440,

		out vec4 fragmentColor; // For outgoing lamp color (smaller cube) to the GPU

		void main()
		{
			fragmentColor = vec4(1.0f); // Set color to white (1.0f,1.0f,1.0f) with alpha 1.0
		}
	);


	// Main function.
	int main(int argc, char* argv[]) {
		if (!UInitialize(argc, argv, &gWindow))
			return EXIT_FAILURE;	

		if (!UCreateShaderProgram(vertexShaderSource, fragmentShaderSource, gProgramId))
			return EXIT_FAILURE;
		if (!UCreateShaderProgram(lampVertexShaderSource, lampFragmentShaderSource, gLightId))
			return EXIT_FAILURE;

		defineTextures();

		glUseProgram(gProgramId);

		// set the background color (implicitly used by glClear and defaults to black)
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);	

		// render loop
		while (!glfwWindowShouldClose(gWindow))
		{
			// timing
	        float currentFrame = glfwGetTime();
			gDeltaTime = currentFrame - gLastFrame;
			gLastFrame = currentFrame;

			// Input
			UProcessInput(gWindow);

			// Render this frame
			URender();

			glfwPollEvents();
		}

		// release mesh data
		UDestroyMesh(bookMesh);
		UDestroyMesh(pedalMesh);
		UDestroyMesh(planeMesh);

		// release shader program
		UDestroyShaderProgram(gProgramId);
		UDestroyShaderProgram(gLightId);

		// terminate the program
		exit(EXIT_SUCCESS);
	}

	// function to render a frame
	void URender() {

		// Enable z-depth
		glEnable(GL_DEPTH_TEST);

		//Clear the background
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// set the "view" part of the MVP matrix and initialize the "projection" part
		glm::mat4 view = gCamera.GetViewMatrix();


		// set the "projection" part of the MVP matrix
		if (orthographicView) {
			glm::mat4 projection = glm::ortho(-5.0f, 5.0f, -2.0f, 5.0f, -100.0f, 100.0f);

			PhongUniforms();

			// create meshes
			CreateLight(lightMesh, view, projection);
			generatePlane(planeMesh, view, projection);
			generateCover(bookMesh, view, projection);
			generatePages(bookMesh, view, projection);
			generatePedalCase(pedalMesh, view, projection);
			generatePedalGlass(pedalMesh, view, projection);
			generatePedalElectronics(pedalMesh, view, projection);
			generatePenBody(penMesh, view, projection);
			generatePenTip(penMesh, view, projection);
			generatePenStylus(penMesh, view, projection);
			generateDutchOven(dutchOvenMesh, view, projection);
			generateOvenHandle(dutchOvenMesh, view, projection);



			// activate VAOs
			glBindVertexArray(planeMesh.vao);
			glBindVertexArray(bookMesh.vao);
			glBindVertexArray(pedalMesh.vao);
			glBindVertexArray(penMesh.vao);
			glBindVertexArray(dutchOvenMesh.vao);


			// deactivate VAO
			glBindVertexArray(0);

			// GLFW: swap buffers and poll IO
			glfwSwapBuffers(gWindow);
		}
		else {
			glm::mat4 projection = glm::perspective(glm::radians(gCamera.Zoom), (GLfloat)WINDOW_WIDTH / (GLfloat)WINDOW_HEIGHT, 0.1f, 100.0f);

			PhongUniforms();

			// create meshes
			CreateLight(lightMesh, view, projection);
			generatePlane(planeMesh, view, projection);
			generateCover(bookMesh, view, projection);
			generatePages(bookMesh, view, projection);
			generatePedalCase(pedalMesh, view, projection);
			generatePedalGlass(pedalMesh, view, projection);
			generatePedalElectronics(pedalMesh, view, projection);
			generatePenBody(penMesh, view, projection);
			generatePenTip(penMesh, view, projection);
			generatePenStylus(penMesh, view, projection);
			generateDutchOven(dutchOvenMesh, view, projection);
			generateOvenHandle(dutchOvenMesh, view, projection);

			// activate VAOs
			glBindVertexArray(planeMesh.vao);
			glBindVertexArray(bookMesh.vao);
			glBindVertexArray(pedalMesh.vao);
			glBindVertexArray(penMesh.vao);
			glBindVertexArray(dutchOvenMesh.vao);

			// deactivate VAO
			glBindVertexArray(0);

			// GLFW: swap buffers and poll IO
			glfwSwapBuffers(gWindow);
		}
	}

	// implement the CreateLight function to better visualize a light source
	void CreateLight(GLMesh& mesh, glm::mat4 view, glm::mat4 projection) {
		// use the LIGHT shader
		glUseProgram(gLightId);

		// FORMAT: (x,y,z, tex coordinate1, tex coordinate2 -> next v)
		GLfloat verts[] =
		{
			// Vertex coords xyz		// Tex coords		// normals 
			-0.5f, -0.5f, -0.5f,		0.0f, 0.0f,			0.0f, 0.0f, -1.0f,		// 0 back left bottom
			0.5f, -0.5f, -0.5f,			1.0f, 0.0f,			0.0f, 0.0f, -1.0f,		// 1 back right bottom
			-0.5f, 0.5f, -0.5f,			0.0f, 1.0f,			0.0f, 0.0f, -1.0f,		// 2 front left bottom
			0.5f, 0.5f, -0.5f,			1.0f, 1.0f,			0.0f, 0.0f, -1.0f,		// 3 front right bottom

			-0.5f, -0.5f, 0.5f,			0.0f, 0.0f,			0.0f, 0.0f, -1.0f,		// 4 back left top
			0.5f, -0.5, 0.5f,			1.0f, 1.0f,			0.0f, 0.0f, -1.0f,		// 5 back right top
			-0.5f, 0.5f, 0.5f,			0.0f, 1.0f,			0.0f, 0.0f, -1.0f,		// 6 front left top
			0.5f, 0.5f, 0.5f,			1.0f, 1.0f,			0.0f, 0.0f, -1.0f,		// 7 front right top	
		};

		// Index to share position data
		// this is set up in groups of 3 to create triangles
		GLushort indices[] = {
			// "side" faces
			// bottom
			0, 1, 2,
			1, 2, 3,

			// top
			4, 5, 6,
			5, 6, 7,

			// back side
			0, 1, 4,
			1, 4, 5,

			// left side
			0, 2, 4,
			2, 4, 6,

			// right side
			1, 3, 5,
			3, 5, 7,

			// front side
			2, 3, 6,
			3, 6, 7,
		};

		const GLuint floatsPerVertex = 3;
		const GLuint floatsPerUV = 2;
		const GLuint floatsPerNormal = 3;

		// generate 'n' bind vertex arrays
		glGenVertexArrays(1, &mesh.vao);
		glBindVertexArray(mesh.vao);

		// create 2 buffers for vertex data, then indices
		glGenBuffers(2, mesh.vbos);
		glBindBuffer(GL_ARRAY_BUFFER, mesh.vbos[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);


		mesh.nIndices = sizeof(indices) / sizeof(indices[0]);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.vbos[1]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		// strides between coords is 6, a tightly packed stride is 0
		//GLint stride = sizeof(float) * (floatsPerVertex + floatsPerColor + floatsPerUV);
		GLint stride = sizeof(float) * (floatsPerVertex + floatsPerUV + floatsPerNormal);

		// creates the vertex attribute pointer
		glVertexAttribPointer(0, floatsPerVertex, GL_FLOAT, GL_FALSE, stride, 0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, floatsPerNormal, GL_FLOAT, GL_FALSE, stride, 0);
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, floatsPerUV, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * floatsPerVertex));
		glEnableVertexAttribArray(2);

		// Transforms
		glm::mat4 scale = glm::scale(gLightScale);	//2.0f by default
		glm::mat4 rotation = glm::rotate(glm::radians(0.0f), glm::vec3(1.0f, 0.4f, 0.2f));
		glm::mat4 translation = glm::translate(gLightPosition);

		// "model" matrix
		glm::mat4 model = translation * rotation * scale;

		// Retrieve our MVP matrices, send them to the shader program
		GLint modelLoc = glGetUniformLocation(gLightId, "model");
		GLint viewLoc = glGetUniformLocation(gLightId, "view");
		GLint projLoc = glGetUniformLocation(gLightId, "projection");

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		GLint UVScaleLoc = glGetUniformLocation(gLightId, "uvScale");
		glUniform2fv(UVScaleLoc, 1, glm::value_ptr(gUVScale));

		// Draw the triangle
		glDrawElements(GL_TRIANGLES, mesh.nIndices, GL_UNSIGNED_SHORT, NULL);
	}


	// Generate scene plane
	void generatePlane(GLMesh& mesh, glm::mat4 view, glm::mat4 projection) {
		// set texture -> create mesh -> transforms -> MVP matrix in that order

		// use the OBJECT shaders
		glUseProgram(gProgramId);


		// bind texture to the VBO
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);

		// Specify the normalized device coordinates and color for pyramid verts
		// FORMAT: (x,y,z, texX, texY, normals -> next vertice)
		GLfloat planeVerts[] =
		{
			// plane vertices
			// surface plane
			-10.0f,  0.0f, -10.0f,	0.0f, 1.0f,		0.0f, 1.0f, 0.0f,		//0 top left corner
			-10.0f,  0.0f, 10.0f,	0.0f, 0.0f,		0.0f, 1.0f, 0.0f,		//1 bottom left corner
			 10.0f,  0.0f, 10.0f,	1.0f, 0.0f,		0.0f, 1.0f, 0.0f,		//2 bottom right corner?
			 10.0f,  0.0f, -10.0f,   1.0f, 1.0f,	0.0f, 1.0f, 0.0f,		//3 top right corner


		};

		// Index to share position data
		// this is set up in groups of 3 to create triangles
		GLushort planeIndices[] = {
			// plane (temporary, until I figure this out)
			0, 1, 2,
			0, 2, 3,
		};

		// Index vertices and UV coords
		const GLuint floatsPerVertex = 3;
		const GLuint floatsPerUv = 2;
		const GLuint floatsPerNormal = 3;

		// generate 'n' bind vertex arrays
		glGenVertexArrays(1, &mesh.vao);
		glBindVertexArray(mesh.vao);

		// create 2 buffers for vertex data, then indices
		glGenBuffers(2, mesh.vbos);
		glBindBuffer(GL_ARRAY_BUFFER, mesh.vbos[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(planeVerts), planeVerts, GL_STATIC_DRAW);

		mesh.nIndices = sizeof(planeIndices) / sizeof(planeIndices[0]);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.vbos[1]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(planeIndices), planeIndices, GL_STATIC_DRAW);


		// strides between coords is 6, a tightly packed stride is 0
		GLint stride = sizeof(float) * (floatsPerVertex + floatsPerUv + floatsPerNormal);


		// creates the vertex attribute pointers
		glVertexAttribPointer(0, floatsPerVertex, GL_FLOAT, GL_FALSE, stride, 0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, floatsPerNormal, GL_FLOAT, GL_FALSE, stride, 0);
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, floatsPerUv, GL_FLOAT, GL_FALSE, stride, (char*)(sizeof(float) * floatsPerVertex));
		glEnableVertexAttribArray(2);

		
		// Transforms
		glm::mat4 scale = glm::scale(glm::vec3(0.75f, 0.75f, 0.75f));
		glm::mat4 rotation = glm::rotate(glm::radians(0.f), glm::vec3(1.0f, 0.0f, 0.0f));
		glm::mat4 translation = glm::translate(glm::vec3(0.0f, -0.5f, 0.0f));

		// model matrix
		glm::mat4 model = translation * rotation * scale;

		// retrieve our MVP matrices 'n' send 'em to the shader
		GLint modelLoc = glGetUniformLocation(gProgramId, "model");
		GLint viewLoc = glGetUniformLocation(gProgramId, "view");
		GLint projLoc = glGetUniformLocation(gProgramId, "projection");

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		GLint UVScaleLoc = glGetUniformLocation(gProgramId, "uvScale");
		glUniform2fv(UVScaleLoc, 1, glm::value_ptr(gUVScale));

		// Draw the triangles
		glDrawElements(GL_TRIANGLES, mesh.nIndices, GL_UNSIGNED_SHORT, NULL);

	}


	// Generate Cover Mesh
	void generateCover(GLMesh& mesh, glm::mat4 view, glm::mat4 projection) {

		// use the OBJECT shader
		glUseProgram(gProgramId);

		// bind texture to the VBO
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture2);

		// Specify the normalized device coordinates and color for pyramid verts
		// FORMAT: (x,y,z, texX, texY, normals xyz -> next vertice)
		GLfloat coverVerts[] =
		{
			// bottom cover
			//bottom
		   -1.0f,  0.0f,  2.0f,		0.0f, 0.1f,		 0.0f, -1.0f,  0.0f,	// 0 upper-left corner, bottom cover
			1.0f,  0.0f,  2.0f,		0.1f, 0.1f,		 0.0f, -1.0f,  0.0f,	// 1 upper-right corner, bottom cover		SPINE
			1.0f,  0.0f,  0.0f,		0.1f, 0.0f,		 0.0f, -1.0f,  0.0f,	// 2 bottom-right corner, bottom cover		SPINE
		   -1.0f,  0.0f,  0.0f,		0.0f, 0.0f,		 0.0f, -1.0f,  0.0f,	// 3 bottom-left corner, bottom cover

		   //top
		   -1.0f,  0.1f,  2.0f,		0.0f, 0.1f,		 0.0f,  1.0f,  0.0f,	// 4 upper-left corner, bottom cover
			1.0f,  0.1f,  2.0f,		0.1f, 0.1f,		 0.0f,  1.0f,  0.0f,	// 5 upper-right corner, bottom cover
			1.0f,  0.1f,  0.0f,		0.1f, 0.0f,		 0.0f,  1.0f,  0.0f,	// 6 bottom-right corner, bottom cover
		   -1.0f,  0.1f,  0.0f,		0.0f, 0.0f,		 0.0f,  1.0f,  0.0f,	// 7 bottom-left corner, bottom cover

		    // top cover
			// bottom
		   -1.0f,  0.4f,  2.0f,		0.0f, 0.1f,		0.0f, -1.0f,  0.0f,		// 8 upper-left corner, top cover
			1.0f,  0.4f,  2.0f,		0.1f, 0.1f,		0.0f, -1.0f,  0.0f,		// 9 upper-right corner, top cover
			1.0f,  0.4f,  0.0f,		0.1f, 0.0f,		0.0f, -1.0f,  0.0f,		// 10 bottom-right corner, top cover
		   -1.0f,  0.4f,  0.0f,		0.0f, 0.0f,		0.0f, -1.0f,  0.0f,		// 11 bottom-left corner, top cover
		   
		   // top
		   -1.0f,  0.5f,  2.0f,		0.0f, 0.1f,		0.0f,  1.0f,  0.0f,		// 12 upper-left corner, top cover
			1.0f,  0.5f,  2.0f,		0.1f, 0.1f,		0.0f,  1.0f,  0.0f,		// 13 upper-right corner, top cover			SPINE
			1.0f,  0.5f,  0.0f,		0.1f, 0.0f,		0.0f,  1.0f,  0.0f,		// 14 bottom-right corner, top cover		SPINE
		   -1.0f,  0.5f,  0.0f,		0.0f, 0.0f,		0.0f,  1.0f,  0.0f,		// 15 bottom-left corner, top cover

		   /* BOTTOM COVER SIDES */

		   // bottom cover top, outward (front face)
		   -1.0f, 0.0f, 2.0f,		0.0f, 0.0f,		0.0f,  1.0f,  0.0f,		// 16 bottom-left corner
		    1.0f, 0.0f, 2.0f,		0.1f, 0.0f,		0.0f,  1.0f,  0.0f,		// 17 bottom-right corner
		   -1.0f, 0.1f, 2.0f,		0.0f, 0.1f,		0.0f,  1.0f,  0.0f,		// 18 top-left corner
		    1.0f, 0.1f, 2.0f,		0.1f, 0.1f,		0.0f,  1.0f,  0.0f,		// 19 top-right corner

		   // bottom cover left side (left face)
		   -1.0f, 0.0f, 2.0f,		0.0f, 0.0f,		-1.0f, 0.0f, 0.0f,		// 20 bottom-left corner
		   -1.0f, 0.0f, 0.0f,		0.1f, 0.0f,		-1.0f, 0.0f, 0.0f,		// 21 bottom-right corner
		   -1.0f, 0.1f, 2.0f,		0.0f, 0.1f,		-1.0f, 0.0f, 0.0f,		// 22 top-left corner
		   -1.0f, 0.1f, 0.0f,		0.1f, 0.1f,		-1.0f, 0.0f, 0.0f,		// 23 top-right corner

		   // bottom cover bottom outward (back face)
		   1.0f,  0.0f, 0.0f,		0.0f, 0.0f,		0.0f, -1.0f,  0.0f,		// 24 bottom-left corner
		   -1.0f, 0.0f, 0.0f,		0.1f, 0.0f,		0.0f, -1.0f,  0.0f,		// 25 bottom-right corner
		   1.0f,  0.1f, 0.0f,		0.0f, 0.1f,		0.0f, -1.0f,  0.0f,		// 26 top-left corner
		   -1.0f, 0.1f, 0.0f,		0.1f, 0.1f,		0.0f, -1.0f,  0.0f,		// 27 top-right corner

		   /* TOP COVER SIDES */

		   // top cover top, outward 
		   -1.0f, 0.4f, 2.0f,		0.0f, 0.0f,		0.0f,  1.0f,  0.0f,		// 28 bottom-left corner
		    1.0f, 0.4f, 2.0f,		0.1f, 0.0f,		0.0f,  1.0f,  0.0f,		// 29 bottom-right corner
		   -1.0f, 0.5f, 2.0f,		0.0f, 0.1f,		0.0f,  1.0f,  0.0f,		// 30 top-left corner
		    1.0f, 0.5f, 2.0f,		0.1f, 0.1f,		0.0f,  1.0f,  0.0f,		// 31 top-right corner

		   // top cover left side
		   -1.0f, 0.4f, 2.0f,		0.0f, 0.0f,		-1.0f, 0.0f, 0.0f,		// 32 bottom-left corner
		   -1.0f, 0.4f, 0.0f,		0.1f, 0.0f,		-1.0f, 0.0f, 0.0f,		// 33 bottom-right corner
		   -1.0f, 0.5f, 2.0f,		0.0f, 0.1f,		-1.0f, 0.0f, 0.0f,		// 34 top-left corner
		   -1.0f, 0.5f, 0.0f,		0.1f, 0.1f,		-1.0f, 0.0f, 0.0f,		// 35 top-right corner

		   // top cover bottom outward
		    1.0f, 0.4f, 0.0f,		0.0f, 0.0f,		0.0f, -1.0f, 0.0f,		// 36 bottom-left corner
		   -1.0f, 0.4f, 0.0f,		0.1f, 0.0f,		0.0f, -1.0f, 0.0f,		// 37 bottom-right corner
		    1.0f, 0.5f, 0.0f,		0.0f, 0.1f,		0.0f, -1.0f, 0.0f,		// 38 top-left corner
		   -1.0f, 0.5f, 0.0f,		0.1f, 0.1f,		0.0f, -1.0f, 0.0f,		// 39 top-right corner
		   
		   /* SPINE VERTICES */
		   // just all the vertices marked "spine"
		   // easy enough
		   1.0f, 0.0f, 2.0f,		0.0f, 0.0f,		1.0f, 0.0f, 0.0f,		// 40 bottom-left corner
		   1.0f, 0.0f, 0.0f,		0.1f, 0.0f,		1.0f, 0.0f, 0.0f,		// 41 bottom-right corner
		   1.0f, 0.5f, 2.0f,		0.0f, 0.1f,		1.0f, 0.0f, 0.0f,		// 42 top-left corner
		   1.0f, 0.5f, 0.0f,		0.1f, 0.1f,		1.0f, 0.0f, 0.0f,		// 43 top-right corner
		};

		// Index to share position data
		// this is set up in groups of 3 to create triangles
		GLushort coverIndices[] = {
			// BOTTOM COVER
			// bottom
			0, 1, 2,
			0, 2, 3,

			// top
			4, 5, 6,
			4, 6, 7,

			// bottom cover top outward
			16, 17, 18,
			17, 18, 19,

			// bottom cover outward
			20, 21, 22,
			21, 22, 23,

			// bottom cover bottom outward
			24, 25, 26,
			25, 26, 27,

			// TOP COVER
			// bottom
			8, 9, 10,
			8, 10, 11,

			// top
			12, 13, 14,
			12, 14, 15,

			// bottom cover top outward
			28, 29, 30,
			29, 30, 31,

			// bottom cover outward
			32, 33, 34,
			33, 34, 35,

			// bottom cover outward bottom
			36, 37, 38,
			37, 38, 39,

			// spine
			40, 41, 42,
			41, 42, 43,
		};

		// Index vertices and UV coords
		const GLuint floatsPerVertex = 3;
		const GLuint floatsPerUv = 2;
		const GLuint floatsPerNormal = 3;

		// generate 'n' bind vertex arrays
		glGenVertexArrays(1, &mesh.vao);
		glBindVertexArray(mesh.vao);

		// create 2 buffers for vertex data, then indices
		glGenBuffers(2, mesh.vbos);
		glBindBuffer(GL_ARRAY_BUFFER, mesh.vbos[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(coverVerts), coverVerts, GL_STATIC_DRAW);

		mesh.nIndices = sizeof(coverIndices) / sizeof(coverIndices[0]);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.vbos[1]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(coverIndices), coverIndices, GL_STATIC_DRAW);


		// strides between coords is 6, a tightly packed stride is 0
		GLint stride = sizeof(float) * (floatsPerVertex + floatsPerUv + floatsPerNormal);


		// creates the vertex attribute pointers
		glVertexAttribPointer(0, floatsPerVertex, GL_FLOAT, GL_FALSE, stride, 0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, floatsPerNormal, GL_FLOAT, GL_FALSE, stride, 0);
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, floatsPerUv, GL_FLOAT, GL_FALSE, stride, (char*)(sizeof(float)* floatsPerVertex));
		glEnableVertexAttribArray(2);


		// Transforms
		glm::mat4 scale = glm::scale(glm::vec3(1.5f, 1.0f, 1.5f));
		// turn it on its side
		glm::mat4 rotation = glm::rotate(glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		glm::mat4 translation = glm::translate(glm::vec3(2.8f, -0.5f, -0.4f));

		// model matrix
		glm::mat4 model = translation * rotation * scale;

		// retrieve our MVP matrices 'n' send 'em to the shader
		GLint modelLoc = glGetUniformLocation(gProgramId, "model");
		GLint viewLoc = glGetUniformLocation(gProgramId, "view");
		GLint projLoc = glGetUniformLocation(gProgramId, "projection");

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		GLint UVScaleLoc = glGetUniformLocation(gProgramId, "uvScale");
		glUniform2fv(UVScaleLoc, 1, glm::value_ptr(gUVScale));

		// Draw the triangles
		glDrawElements(GL_TRIANGLES, mesh.nIndices, GL_UNSIGNED_SHORT, NULL);
	}


	// Generate book page mesh
	void generatePages(GLMesh& mesh, glm::mat4 view, glm::mat4 projection) {
		// use the OBJECT shader
		glUseProgram(gProgramId);

		// bind texture to the VBO
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture3);

		// Specify the normalized device coordinates and color for pyramid verts
		// FORMAT: (x,y,z, x, y, -> next vertice)
		GLfloat pageVerts[] =
		{
			// PAGES
			// bottom face
		   -0.9f,   0.11f,   0.9f,		0.0f, 0.1f,		0.0f,  -1.0f, 0.0f,		// 0 upper-left corner
			0.99f,  0.11f,   0.9f,		0.1f, 0.1f,		0.0f,  -1.0f, 0.0f,		// 1 upper-right corner					SPINE
			0.99f,  0.11f,  -0.9f,		0.1f, 0.0f,		0.0f,  -1.0f, 0.0f,		// 2 bottom-right corner				SPINE
		   -0.9f,   0.11f,  -0.9f,		0.0f, 0.0f,		0.0f,  -1.0f, 0.0f,		// 3 bottom-left corner


		   // top face
		   -0.9f,   0.39f,   0.9f,		0.0f, 0.1f,		0.0f,  1.0f, 1.0f,		// 4 upper-left corner 
			0.99f,  0.39f,   0.9f,		0.1f, 0.1f,		0.0f,  1.0f, 1.0f,		// 5 upper-right corner 				SPINE
			0.99f,  0.39f,  -0.9f,		0.1f, 0.0f,		0.0f,  1.0f, 1.0f,		// 6 bottom-right corner 				SPINE
		   -0.9f,   0.39f,  -0.9f,		0.0f, 0.0f,		0.0f,  1.0f, 1.0f,		// 7 bottom-left corner 

		   // "outward" face (left side)
		   -0.9f,	0.1f,  0.9f,		0.0f, 0.0f,		-1.0f, 0.0f, 0.0f,		// 8 outward-facing bottom-left
		   -0.9f,   0.1f, -0.9f,		0.1f, 0.0f,		-1.0f, 0.0f, 0.0f,		// 9 outward-facing bottom-right
		   -0.9f,	0.4f,  0.9f,		0.0f, 0.1f,		-1.0f, 0.0f, 0.0f,		// 10 outward-facing top-left
		   -0.9f,   0.4f, -0.9f,		0.1f, 0.1f,		-1.0f, 0.0f, 0.0f,		// 11 outward-facing top-right

		   // top "outward" face
		   0.99f, 0.1f, 0.9f,			0.0f, 0.0f,		0.0f, 0.0f, 1.0f,		// 12 outward-facing bottom-left		
		   -0.9f, 0.1f, 0.9f,			0.1f, 0.0f,		0.0f, 0.0f, 1.0f,		// 13 outward-facing bottom-right
		   0.99f, 0.4f, 0.9f,			0.0f, 0.1f,		0.0f, 0.0f, 1.0f,		// 14 outward-facing top-left			
		   -0.9f, 0.4f, 0.9f,			0.1f, 0.1f,		0.0f, 0.0f, 1.0f,		// 15 outward-facing top-right

		   // bottom "outward" face
			0.99f, 0.1f, -0.9f,			0.0f, 0.0f,		0.0f, -1.0f, 0.0f,		// 16 outward-facing bottom-right		
		   -0.9f,  0.1f, -0.9f,			0.1f, 0.0f,		0.0f, -1.0f, 0.0f,		// 17 outward-facing bottom-left
			0.99f, 0.4f, -0.9f,			0.0f, 0.1f,		0.0f, -1.0f, 0.0f,		// 18 outward-facing top-right			
		   -0.9f,  0.4f, -0.9f,			0.1f, 0.1f,		0.0f, -1.0f, 0.0f,		// 19 outward-facing top-left
		};

		// Index to share position data
		// this is set up in groups of 3 to create triangles
		GLushort pageIndices[] = {
			// bottom
			0, 1, 2,
			0, 2, 3,

			// top
			4, 5, 6,
			4, 6, 7,

			// "outward" face
			8, 9, 10,
			9, 10, 11,

			// "outward" top face
			12, 13, 14,
			13, 14, 15,
			
			// "outward" bottom face
			16, 17, 18,
			17, 18, 19,

			// spine face
			1, 2, 5,
			2, 5, 6,

		};

		// Index vertices and UV coords
		const GLuint floatsPerVertex = 3;
		const GLuint floatsPerUv = 2;
		const GLuint floatsPerNormal = 3;

		// generate 'n' bind vertex arrays
		glGenVertexArrays(1, &mesh.vao);
		glBindVertexArray(mesh.vao);

		// create 2 buffers for vertex data, then indices
		glGenBuffers(2, mesh.vbos);
		glBindBuffer(GL_ARRAY_BUFFER, mesh.vbos[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(pageVerts), pageVerts, GL_STATIC_DRAW);

		mesh.nIndices = sizeof(pageVerts) / sizeof(pageIndices[0]);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.vbos[1]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(pageIndices), pageIndices, GL_STATIC_DRAW);

		// strides between coords is 6, a tightly packed stride is 0
		GLint stride = sizeof(float) * (floatsPerVertex + floatsPerUv + floatsPerNormal);


		// creates the vertex attribute pointers
		glVertexAttribPointer(0, floatsPerVertex, GL_FLOAT, GL_FALSE, stride, 0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, floatsPerNormal, GL_FLOAT, GL_FALSE, stride, 0);
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, floatsPerUv, GL_FLOAT, GL_FALSE, stride, (char*)(sizeof(float) * floatsPerVertex));
		glEnableVertexAttribArray(2);


		// Transforms
		glm::mat4 scale = glm::scale(glm::vec3(1.5f, 1.0f, 1.5f));
		// turn it on its side
		glm::mat4 rotation = glm::rotate(glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		glm::mat4 translation = glm::translate(glm::vec3(2.8f, -0.5f, 1.1f));

		// retrieve our MVP matrices 'n' send 'em to the shader
		GLint modelLoc = glGetUniformLocation(gProgramId, "model");
		GLint viewLoc = glGetUniformLocation(gProgramId, "view");
		GLint projLoc = glGetUniformLocation(gProgramId, "projection");

		// model matrix
		glm::mat4 model = translation * rotation * scale;


		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		GLint UVScaleLoc = glGetUniformLocation(gProgramId, "uvScale");
		glUniform2fv(UVScaleLoc, 1, glm::value_ptr(gUVScale));

		// Draw the triangles
		glDrawElements(GL_TRIANGLES, mesh.nIndices, GL_UNSIGNED_SHORT, NULL);

	}


	// Generate guitar pedal casing
	void generatePedalCase(GLMesh& mesh, glm::mat4 view, glm::mat4 projection) {
		// use the OBJECT shader
		glUseProgram(gProgramId);

		// bind texture to the VBO
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture4);

		// Specify the normalized device coordinates and color for pyramid verts
		// FORMAT: (x,y,z, x, y, -> next vertice)
		GLfloat caseVerts[] =
		{
			// BOTTOM CASING
			// bottom face
		   -0.4f,  0.0f,  -0.7f,		0.0f, 0.0f,		0.0f, -1.0f, 0.0f,		// 0 back-left corner
			0.4f,  0.0f,  -0.7f,		0.1f, 0.0f,		0.0f, -1.0f, 0.0f,		// 1 back-right corner
		   -0.4f,  0.0f,   0.7f,		0.0f, 0.1f,		0.0f, -1.0f, 0.0f,		// 2 front-left corner
			0.4f,  0.0f,   0.7f,		0.1f, 0.1f,		0.0f, -1.0f, 0.0f,		// 3 front-right corner

		   // left face
		   -0.4f,  0.0f,  -0.7f,		0.0f, 0.0f,		-1.0f, 0.0f, 0.0f,		// 4 back-left bottom
		   -0.4f,  0.3f,  -0.7f,		0.0f, 0.1f,		-1.0f, 0.0f, 0.0f,		// 5 back-left top
		   -0.4f,  0.0f,   0.7f,		0.1f, 0.0f,		-1.0f, 0.0f, 0.0f,		// 6 front-left bottom
		   -0.4f,  0.2f,   0.7f,		0.1f, 0.1f,		-1.0f, 0.0f, 0.0f,		// 7 front-left top			
		   -0.4f,  0.0f,   -0.2f,		0.05f,0.0f,		-1.0f, 0.0f, 0.0f,		// 8 center-left bottom		(center)
		   -0.4f,  0.3f,   -0.2f,		0.05f,0.1f,		-1.0f, 0.0f, 0.0f,		// 9 center-left top		(center)

		   // right face
			0.4f,  0.0f,  -0.7f,		0.0f, 0.0f,		1.0f,  0.0f, 0.0f,		// 10 back-right bottom		
			0.4f,  0.3f,  -0.7f,		0.0f, 0.1f,		1.0f,  0.0f, 0.0f,		// 11 back-right top
			0.4f,  0.0f,   0.7f,		0.1f, 0.0f,		1.0f,  0.0f, 0.0f,		// 12 front-right bottom			
			0.4f,  0.2f,   0.7f,		0.1f, 0.1f,		1.0f,  0.0f, 0.0f,		// 13 front-right top
			0.4f,  0.3f,   -0.2f,		0.05f,0.1f,		1.0f,  0.0f, 0.0f,		// 14 center-right top		(center)
			0.4f,  0.0f,   -0.2f,		0.05f,0.0f,		1.0f,  0.0f, 0.0f,		// 15 center-right bottom	(center)

		   // front face
		   -0.4f,  0.0f,   0.7f,		0.0f, 0.0f,		0.0f, 0.0f, 1.0f,		// 16 bottom-left		
			0.4f,  0.0f,   0.7f,		0.1f, 0.0f,		0.0f, 0.0f, 1.0f,		// 17 bottom-right
		   -0.4f,  0.2f,   0.7f,		0.0f, 0.1f,		0.0f, 0.0f, 1.0f,		// 18 top-left			
			0.4f,  0.2f,   0.7f,		0.1f, 0.1f,		0.0f, 0.0f, 1.0f,		// 19 top-right

			// back face
			-0.4f,  0.0f,  -0.7f,		0.0f, 0.0f,		0.0f, 0.0f, -1.0f,		// 20 bottom-left
			 0.4f,  0.0f,  -0.7f,		0.1f, 0.0f,		0.0f, 0.0f, -1.0f,		// 21 bottom-right
			-0.4f,  0.3f,  -0.7f,		0.0f, 0.1f,		0.0f, 0.0f, -1.0f,		// 22 top-left
			 0.4f,  0.3f,  -0.7f,		0.1f, 0.1f,		0.0f, 0.0f, -1.0f,		// 23 top-right

			// top face (metal half)
		    -0.4f,  0.3f, -0.2f,		0.0f, 0.1f,		0.0f,  1.0f, 0.0f,		// 24 back-left corner 
			 0.4f,  0.3f, -0.2f,		0.1f, 0.1f,		0.0f,  1.0f, 0.0f,		// 25 back-right corner 				
		    -0.4f,  0.2f,  0.7f,		0.0f, 0.0f,		0.0f,  1.0f, 0.0f,		// 26 front-left corner		(bottom of the pedal)
			 0.4f,  0.2f,  0.7f,		0.1f, 0.0f,		0.0f,  1.0f, 0.0f,		// 27 front-right corner	(bottom of the pedal)


			 // FOOTSWITCH
			 // to save some headache, our faces will clip into our pedal body.
			 // back face
			-0.35f, 0.25f, -0.1f,		0.0f, 0.0f,		0.0f, 0.0f, -1.0f,		// 28 back left bottom
			 0.35f, 0.25f, -0.1f,		0.1f, 0.0f,		0.0f, 0.0f, -1.0f,		// 29 back right bottom
			-0.35f, 0.4f, -0.1f,		0.0f, 0.1f,		0.0f, 0.0f, -1.0f,		// 30 back left top
			 0.35f, 0.4f, -0.1f,		0.1f, 0.1f,		0.0f, 0.0f, -1.0f,		// 31 back right top

			 // left face
			-0.35f, 0.25f,-0.1f,		0.0f, 0.0f,		-1.0f, 0.0f, 0.0f,		// 32 bottom-left
			-0.35f, 0.15f, 0.67f,		0.1f, 0.0f,		-1.0f, 0.0f, 0.0f,		// 33 bottom-right
			-0.35f, 0.4f, -0.1f,		0.0f, 0.1f,		-1.0f, 0.0f, 0.0f,		// 34 top-left
			-0.35f, 0.4f,  0.67f,		0.1f, 0.1f,		-1.0f, 0.0f, 0.0f,		// 35 top-right

			// right face
			0.35f, 0.25f, -0.1f,		0.0f, 0.0f,		 1.0f, 0.0f, 0.0f,		// 36 bottom-left
			0.35f, 0.15f,  0.67f,		0.1f, 0.0f,		 1.0f, 0.0f, 0.0f,		// 37 bottom-right
			0.35f, 0.4f,  -0.1f,		0.0f, 0.1f,		 1.0f, 0.0f, 0.0f,		// 38 top-left
			0.35f, 0.4f,   0.67f,		0.1f, 0.1f,		 1.0f, 0.0f, 0.0f,		// 39 top-right

			// front face
			-0.35f, 0.15f,  0.67f,		0.0f, 0.0f,		 0.0f, 0.0f, 1.0f,		// 40 bottom-left
			 0.35f, 0.15f,  0.67f,		0.1f, 0.0f,		 0.0f, 0.0f, 1.0f,		// 41 bottom-right
			-0.35f, 0.4f,   0.67f,		0.0f, 0.1f,		 0.0f, 0.0f, 1.0f,		// 42 top-left
			 0.35f, 0.4f,   0.67f,		0.1f, 0.1f,		 0.0f, 0.0f, 1.0f,		// 43 top-right

			// footswitch top
			-0.35f, 0.4f,	-0.1f,		0.0f, 0.0f,		 0.0f, 1.0f, 0.0f,		// 44 bottom-left
			 0.35f, 0.4f,	-0.1f,		0.1f, 0.0f,		 0.0f, 1.0f, 0.0f,		// 45 bottom-right
			-0.35f, 0.4f,	 0.2f,		0.0f, 0.1f,		 0.0f, 1.0f, 0.0f,		// 46 top-left
			 0.35f, 0.4f,	 0.2f,		0.1f, 0.1f,		 0.0f, 1.0f, 0.0f,		// 47 top-right
		};

		// Index to share position data
		// this is set up in groups of 3 to create triangles
		// 24 triangles
		GLushort caseIndices[] = {
			// bottom
			0, 1, 2,
			1, 2, 3,

			// left
			4, 5, 8,			// bottom, top, bottom center
			5, 8, 9,			// top, bottom center, top center
			8, 6, 7,			// center bottom, front bottom, front top
			8, 9, 7,			// center bottom, center top, front top
			
			// right
			10, 11, 15,			// bottom, top, bottom center
			11, 15, 14,			// top, bottom center, top center
			15, 12, 13,			// bottom center, front bottom, front top
			15, 14, 13,			// bottom center, top center, front top

			// front
			16, 17, 18,
			17, 18, 19,

			// back
			20, 21, 22,
			21, 22, 23,

			// top half-face
			24, 25, 26,
			25, 26, 27,

			// footswitch
			// back
			28, 29, 30,
			29, 30, 31,

			// left face
			32, 33, 34,
			33, 34, 35,

			// right face
			36, 37, 38,
			37, 38, 39,

			// front face
			40, 41, 42,
			41, 42, 43,

			// top face
			44, 45, 46,
			45, 46, 47,
		};

		// Index vertices and UV coords
		const GLuint floatsPerVertex = 3;
		const GLuint floatsPerUv = 2;
		const GLuint floatsPerNormal = 3;

		// generate 'n' bind vertex arrays
		glGenVertexArrays(1, &mesh.vao);
		glBindVertexArray(mesh.vao);

		// create 2 buffers for vertex data, then indices
		glGenBuffers(2, mesh.vbos);
		glBindBuffer(GL_ARRAY_BUFFER, mesh.vbos[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(caseVerts), caseVerts, GL_STATIC_DRAW);

		mesh.nIndices = sizeof(caseVerts) / sizeof(caseIndices[0]);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.vbos[1]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(caseIndices), caseIndices, GL_STATIC_DRAW);

		// strides between coords is 6, a tightly packed stride is 0
		GLint stride = sizeof(float) * (floatsPerVertex + floatsPerUv + floatsPerNormal);


		// creates the vertex attribute pointers
		glVertexAttribPointer(0, floatsPerVertex, GL_FLOAT, GL_FALSE, stride, 0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, floatsPerNormal, GL_FLOAT, GL_FALSE, stride, 0);
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, floatsPerUv, GL_FLOAT, GL_FALSE, stride, (char*)(sizeof(float) * floatsPerVertex));
		glEnableVertexAttribArray(2);


		// Transforms
		glm::mat4 scale = glm::scale(glm::vec3(1.3f, 1.6f, 1.3f));
		glm::mat4 rotation = glm::rotate(glm::radians(-20.0f), glm::vec3(0.0f, 0.3f, 0.0f));
		glm::mat4 translation = glm::translate(glm::vec3(0.0f, -0.5f, 2.0f));

		// retrieve our MVP matrices 'n' send 'em to the shader
		GLint modelLoc = glGetUniformLocation(gProgramId, "model");
		GLint viewLoc = glGetUniformLocation(gProgramId, "view");
		GLint projLoc = glGetUniformLocation(gProgramId, "projection");

		// model matrix
		glm::mat4 model = translation * rotation * scale;


		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		GLint UVScaleLoc = glGetUniformLocation(gProgramId, "uvScale");
		glUniform2fv(UVScaleLoc, 1, glm::value_ptr(gUVScale));

		// Draw the triangles
		glDrawElements(GL_TRIANGLES, mesh.nIndices, GL_UNSIGNED_SHORT, NULL);

	}


	// Generate guitar pedal electronics/rubber
	void generatePedalElectronics(GLMesh& mesh, glm::mat4 view, glm::mat4 projection) {
		// use the OBJECT shader
		glUseProgram(gProgramId);

		// bind texture to the VBO
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture5);

		// Specify the normalized device coordinates and color for pyramid verts
		// FORMAT: (x,y,z, x, y, -> next vertice)
		GLfloat electronicVerts[] =
		{
			// FOOTSWITCH RUBBER 
			-0.35f, 0.4f, 0.2f,			0.0f, 0.0f,		0.0f, 1.0f, 0.0f,		// 0 bottom-left corner
			 0.35f, 0.4f, 0.2f,			0.1f, 0.0f,		0.0f, 1.0f, 0.0f,		// 1 bottom-right corner
			-0.35f, 0.4f, 0.67f,		0.0f, 0.1f,		0.0f, 1.0f, 0.0f,		// 2 top-left corner
			 0.35f, 0.4f, 0.67f,		0.1f, 0.1f,		0.0f, 1.0f, 0.0f,		// 3 top-right corner

			// FOOTSWITCH THUMBSCREW
			// front
			-0.05f,	0.25f, 0.715f,		0.0f, 0.0f,		0.0f, 0.0f, 1.0f,		// 4 bottom-left corner
			 0.05f, 0.25f, 0.715f,		0.1f, 0.0f,		0.0f, 0.0f, 1.0f,		// 5 bottom-right corner
			-0.05f, 0.35f, 0.715f,		0.0f, 0.1f,		0.0f, 0.0f, 1.0f,		// 6 top-left corner
			 0.05f, 0.35f, 0.715f,		0.1f, 0.1f,		0.0f, 0.0f, 1.0f,		// 7 top-right corner

			// top
			-0.05f, 0.35f, 0.715f,		0.0f, 0.0f,		0.0f, 1.0f, 0.0f,		// 8 bottom-left corner
			 0.05f, 0.35f, 0.715f,		0.1f, 0.0f,		0.0f, 1.0f, 0.0f,		// 9 bottom-right corner
			-0.05f, 0.35f, 0.6f,		0.0f, 0.1f,		0.0f, 1.0f, 0.0f,		// 10 top-left corner
			 0.05f, 0.35f, 0.6f,		0.1f, 0.1f,		0.0f, 1.0f, 0.0f,		// 11 top-right corner

			// bottom
			-0.05f, 0.25f, 0.715f,		0.0f, 0.0f,		0.0f, -1.0f, 0.0f,		// 12 bottom-left corner
			 0.05f, 0.25f, 0.715f,		0.1f, 0.0f,		0.0f, -1.0f, 0.0f,		// 13 bottom-right corner
			-0.05f, 0.25f, 0.6f,		0.0f, 0.1f,		0.0f, -1.0f, 0.0f,		// 14 top-left corner
			 0.05f, 0.25f, 0.6f,		0.1f, 0.1f,		0.0f, -1.0f, 0.0f,		// 15 top-right corner

			// left side
			-0.05f, 0.25f, 0.6f,		0.0f, 0.0f,		-1.0f, 0.0f, 0.0f,		// 16 bottom-left corner
			-0.05f, 0.25f, 0.715f,		0.1f, 0.0f,		-1.0f, 0.0f, 0.0f,		// 17 bottom-right corner
			-0.05f, 0.35f, 0.6f,		0.0f, 0.1f,		-1.0f, 0.0f, 0.0f,		// 18 top-left corner
			-0.05f, 0.35f, 0.715f,		0.1f, 0.1f,		-1.0f, 0.0f, 0.0f,		// 19 top-right corner

			// right side
			 0.05f, 0.25f, 0.6f,		0.0f, 0.0f,		 1.0f, 0.0f, 0.0f,		// 20 bottom-left corner
			 0.05f, 0.25f, 0.715f,		0.1f, 0.0f,		 1.0f, 0.0f, 0.0f,		// 21 bottom-right corner
			 0.05f, 0.35f, 0.6f,		0.0f, 0.1f,		 1.0f, 0.0f, 0.0f,		// 22 top-left corner
			 0.05f, 0.35f, 0.715f,		0.1f, 0.1f,		 1.0f, 0.0f, 0.0f,		// 23 top-right corner
		};

		// Index to share position data
		// this is set up in groups of 3 to create triangles
		GLushort electronicIndices[] = {
			// footswitch rubber
			0, 1, 2,
			1, 2, 3,

			// thumbscrew front
			4, 5, 6,
			5, 6, 7,

			// thumbscrew top
			8, 9, 10,
			9, 10, 11,

			// thumbscrew bottom
			12, 13, 14,
			13, 14, 15,

			// left side
			16, 17, 18,
			17, 18, 19,

			// right side
			20, 21, 22,
			21, 22, 23,
		};

		// Index vertices and UV coords
		const GLuint floatsPerVertex = 3;
		const GLuint floatsPerUv = 2;
		const GLuint floatsPerNormal = 3;

		// generate 'n' bind vertex arrays
		glGenVertexArrays(1, &mesh.vao);
		glBindVertexArray(mesh.vao);

		// create 2 buffers for vertex data, then indices
		glGenBuffers(2, mesh.vbos);
		glBindBuffer(GL_ARRAY_BUFFER, mesh.vbos[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(electronicVerts), electronicVerts, GL_STATIC_DRAW);

		mesh.nIndices = sizeof(electronicVerts) / sizeof(electronicIndices[0]);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.vbos[1]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(electronicIndices), electronicIndices, GL_STATIC_DRAW);

		// strides between coords is 6, a tightly packed stride is 0
		GLint stride = sizeof(float) * (floatsPerVertex + floatsPerUv + floatsPerNormal);


		// creates the vertex attribute pointers
		glVertexAttribPointer(0, floatsPerVertex, GL_FLOAT, GL_FALSE, stride, 0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, floatsPerNormal, GL_FLOAT, GL_FALSE, stride, 0);
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, floatsPerUv, GL_FLOAT, GL_FALSE, stride, (char*)(sizeof(float) * floatsPerVertex));
		glEnableVertexAttribArray(2);


		// Transforms
		glm::mat4 scale = glm::scale(glm::vec3(1.3f, 1.6f, 1.3f));
		glm::mat4 rotation = glm::rotate(glm::radians(-20.0f), glm::vec3(0.0f, 0.3f, 0.0f));
		glm::mat4 translation = glm::translate(glm::vec3(0.0f, -0.5f, 2.0f));

		// retrieve our MVP matrices 'n' send 'em to the shader
		GLint modelLoc = glGetUniformLocation(gProgramId, "model");
		GLint viewLoc = glGetUniformLocation(gProgramId, "view");
		GLint projLoc = glGetUniformLocation(gProgramId, "projection");

		// model matrix
		glm::mat4 model = translation * rotation * scale;


		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		GLint UVScaleLoc = glGetUniformLocation(gProgramId, "uvScale");
		glUniform2fv(UVScaleLoc, 1, glm::value_ptr(gUVScale));

		// Draw the triangles
		glDrawElements(GL_TRIANGLES, mesh.nIndices, GL_UNSIGNED_SHORT, NULL);

	}


	// Generate guitar pedal glass
	void generatePedalGlass(GLMesh& mesh, glm::mat4 view, glm::mat4 projection) {
		// use the OBJECT shader
		glUseProgram(gProgramId);

		// bind texture to the VBO
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture6);

		// Specify the normalized device6 coordinates and color for pyramid verts
		// FORMAT: (x,y,z, x, y, -> next vertice)
		GLfloat glassVerts[] =
		{
			// top face (keeping the vertices here for a sec)
			// half display is 
			-0.4f,  0.3f,  -0.2f,		0.0f, 0.1f,		0.0f,  1.0f, 0.0f,		// 0 back-left corner 
			 0.4f,  0.3f,  -0.2f,		0.1f, 0.1f,		0.0f,  1.0f, 0.0f,		// 1 back-right corner 				
			-0.4f,  0.3f,  -0.7f,		0.0f, 0.0f,		0.0f,  1.0f, 0.0f,		// 2 front-left corner (top of the pedal)
			 0.4f,  0.3f,  -0.7f,		0.1f, 0.0f,		0.0f,  1.0f, 0.0f,		// 3 front-right corner (top of the pedal)
		};

		// Index to share position data
		// this is set up in groups of 3 to create triangles
		GLushort glassIndices[] = {
			// bottom
			0, 1, 2,
			1, 2, 3,
		};

		// Index vertices and UV coords
		const GLuint floatsPerVertex = 3;
		const GLuint floatsPerUv = 2;
		const GLuint floatsPerNormal = 3;

		// generate 'n' bind vertex arrays
		glGenVertexArrays(1, &mesh.vao);
		glBindVertexArray(mesh.vao);

		// create 2 buffers for vertex data, then indices
		glGenBuffers(2, mesh.vbos);
		glBindBuffer(GL_ARRAY_BUFFER, mesh.vbos[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glassVerts), glassVerts, GL_STATIC_DRAW);

		mesh.nIndices = sizeof(glassVerts) / sizeof(glassIndices[0]);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.vbos[1]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(glassIndices), glassIndices, GL_STATIC_DRAW);

		// strides between coords is 6, a tightly packed stride is 0
		GLint stride = sizeof(float) * (floatsPerVertex + floatsPerUv + floatsPerNormal);


		// creates the vertex attribute pointers
		glVertexAttribPointer(0, floatsPerVertex, GL_FLOAT, GL_FALSE, stride, 0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, floatsPerNormal, GL_FLOAT, GL_FALSE, stride, 0);
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, floatsPerUv, GL_FLOAT, GL_FALSE, stride, (char*)(sizeof(float) * floatsPerVertex));
		glEnableVertexAttribArray(2);


		// Transforms
		glm::mat4 scale = glm::scale(glm::vec3(1.3f, 1.6f, 1.3f));
		glm::mat4 rotation = glm::rotate(glm::radians(-20.0f), glm::vec3(0.0f, 0.3f, 0.0f));
		glm::mat4 translation = glm::translate(glm::vec3(0.0f, -0.5f, 2.0f));

		// retrieve our MVP matrices 'n' send 'em to the shader
		GLint modelLoc = glGetUniformLocation(gProgramId, "model");
		GLint viewLoc = glGetUniformLocation(gProgramId, "view");
		GLint projLoc = glGetUniformLocation(gProgramId, "projection");

		// model matrix
		glm::mat4 model = translation * rotation * scale;


		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		GLint UVScaleLoc = glGetUniformLocation(gProgramId, "uvScale");
		glUniform2fv(UVScaleLoc, 1, glm::value_ptr(gUVScale));

		// Draw the triangles
		glDrawElements(GL_TRIANGLES, mesh.nIndices, GL_UNSIGNED_SHORT, NULL);

	}


	// Generate pen body
	void generatePenBody(GLMesh& mesh, glm::mat4 view, glm::mat4 projection) {
		// use the OBJECT shader
		glUseProgram(gProgramId);

		// bind texture to the VBO
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture7);

		// Specify the normalized device6 coordinates and color for pyramid verts
		// FORMAT: (x,y,z, texture x, y, normal x, y, z, -> next vertice)
		GLfloat penVerts[] =
		{
			// helpful distances
			// LENGTH: 0.25
			// WIDTH: 0.025
			// Hexagonal shape


			// bottom
			-0.015f, 0.0f, -0.25f,		0.0f, 0.0f,		0.0f, -1.0f, 0.0f,		// 0 back left vertex
			 0.015f, 0.0f, -0.25f,		0.1f, 0.0f,		0.0f, -1.0f, 0.0f,		// 1 back right vertex
			-0.015f, 0.0f,  0.25f,		0.0f, 0.1f,		0.0f, -1.0f, 0.0f,		// 2 front left vertex
			 0.015f, 0.0f,  0.25f,		0.1f, 0.1f,		0.0f, -1.0f, 0.0f,		// 3 front right vertex

			// top
			-0.015f, 0.05f, -0.25f,		0.0f, 0.0f,		0.0f, 1.0f, 0.0f,		// 4 back left
			 0.015f, 0.05f, -0.25f,		0.1f, 0.0f,		0.0f, 1.0f, 0.0f,		// 5 back right
			-0.015f, 0.05f,  0.25f,		0.0f, 0.1f,		0.0f, 1.0f, 0.0f,		// 6 front left
			 0.015f, 0.05f,  0.25f,		0.1f, 0.1f,		0.0f, 1.0f, 0.0f,		// 7 front right

			// bottom left
			-0.015f, 0.0f, -0.25f,		0.0f, 0.0f,		-0.5f, -0.5f, 0.0f,		// 8 back left
			-0.015f, 0.0f,	0.25f,		0.1f, 0.0f,		-0.5f, -0.5f, 0.0f,		// 9 back right
			-0.03f,  0.025f,-0.25f,		0.0f, 0.1f,		-0.5f, -0.5f, 0.0f,		// 10 front left
			-0.03f,  0.025f,0.25f,		0.1f, 0.1f,		-0.5f, -0.5f, 0.0f,		// 11 front right

			// top left
			-0.03f, 0.025f, -0.25f,		0.0f, 0.0f,		-0.5f, 0.5f, 0.0f,		// 12 back left
			-0.03f, 0.025f,  0.25f,		0.1f, 0.0f,		-0.5f, 0.5f, 0.0f,		// 13 back right
			-0.015f,0.05f,  -0.25f,		0.0f, 0.1f,		-0.5f, 0.5f, 0.0f,		// 14 front left
			-0.015f,0.05f,	 0.25f,		0.1f, 0.1f,		-0.5f, 0.5f, 0.0f,		// 15 front right

			// bottom right
			0.015f, 0.0f,-0.25f,		0.0f, 0.0f,		0.5f, -0.5f, 0.0f,		// 16 back left
			0.015f, 0.0f, 0.25f,		0.1f, 0.0f,		0.5f, -0.5f, 0.0f,		// 17 back right
			0.03f,	0.025f,-0.25f,		0.0f, 0.1f,		0.5f, -0.5f, 0.0f,		// 18 front left
			0.03f,  0.025f, 0.25f,		0.1f, 0.1f,		0.5f, -0.5f, 0.0f,		// 19 front right
			
			// top right
			0.03f, 0.025f, -0.25f,		0.0f, 0.0f,		0.5f, 0.5f, 0.0f,		// 20 back left
			0.03f, 0.025f,  0.25f,		0.1f, 0.0f,		0.5f, 0.5f, 0.0f,		// 21 back right
			0.015f,  0.05f,  -0.25f,		0.0f, 0.1f,		0.5f, 0.5f, 0.0f,	// 22 frton left
			0.015f,  0.05f,   0.25f,		0.1f, 0.1f,		0.5f, 0.5f, 0.0f,	// 23 front right
		};

		// Index to share position data
		// this is set up in groups of 3 to create triangles
		GLushort penIndices[] = {
			// bottom
			0, 1, 2,
			1, 2, 3,
			
			// top
			4, 5, 6,
			5, 6, 7,

			// bottom left
			8, 9, 10,
			9, 10, 11,

			// top left
			12, 13, 14,
			13, 14, 15,

			// bottom right
			16, 17, 18,
			17, 18, 19,

			// top right
			20, 21, 22,
			21, 22, 23,
		};

		// Index vertices and UV coords
		const GLuint floatsPerVertex = 3;
		const GLuint floatsPerUv = 2;
		const GLuint floatsPerNormal = 3;

		// generate 'n' bind vertex arrays
		glGenVertexArrays(1, &mesh.vao);
		glBindVertexArray(mesh.vao);

		// create 2 buffers for vertex data, then indices
		glGenBuffers(2, mesh.vbos);
		glBindBuffer(GL_ARRAY_BUFFER, mesh.vbos[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(penVerts), penVerts, GL_STATIC_DRAW);

		mesh.nIndices = sizeof(penVerts) / sizeof(penIndices[0]);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.vbos[1]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(penIndices), penIndices, GL_STATIC_DRAW);

		// strides between coords is 6, a tightly packed stride is 0
		GLint stride = sizeof(float) * (floatsPerVertex + floatsPerUv + floatsPerNormal);


		// creates the vertex attribute pointers
		glVertexAttribPointer(0, floatsPerVertex, GL_FLOAT, GL_FALSE, stride, 0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, floatsPerNormal, GL_FLOAT, GL_FALSE, stride, 0);
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, floatsPerUv, GL_FLOAT, GL_FALSE, stride, (char*)(sizeof(float) * floatsPerVertex));
		glEnableVertexAttribArray(2);


		// Transforms
		glm::mat4 scale = glm::scale(glm::vec3(2.0f, 2.0f, 3.0f));
		glm::mat4 rotation = glm::rotate(glm::radians(230.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glm::mat4 translation = glm::translate(glm::vec3(3.5f, 0.007f, 0.7f));

		// retrieve our MVP matrices 'n' send 'em to the shader
		GLint modelLoc = glGetUniformLocation(gProgramId, "model");
		GLint viewLoc = glGetUniformLocation(gProgramId, "view");
		GLint projLoc = glGetUniformLocation(gProgramId, "projection");

		// model matrix
		glm::mat4 model = translation * rotation * scale;


		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		GLint UVScaleLoc = glGetUniformLocation(gProgramId, "uvScale");
		glUniform2fv(UVScaleLoc, 1, glm::value_ptr(gUVScale));

		// Draw the triangles
		glDrawElements(GL_TRIANGLES, mesh.nIndices, GL_UNSIGNED_SHORT, NULL);

	}


	// Generate pen tip
	void generatePenTip(GLMesh& mesh, glm::mat4 view, glm::mat4 projection) {
		// use the OBJECT shader
		glUseProgram(gProgramId);

		// bind texture to the VBO
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture8);

		// Specify the normalized device6 coordinates and color for pyramid verts
		// FORMAT: (x,y,z, texture x, y, normal x, y, z, -> next vertice)
		GLfloat tipVerts[] =
		{
			// point vertex
			 0.0f, 0.025f, -0.33f,		0.5f, 0.1f,		0.0f, 0.0f, 0.0f,		// 0 center vertex

			// bottom face
			-0.015f, 0.0f,   -0.25f,	0.0f, 0.0f,		0.0f, -1.0f, 0.0f,		// 1 bottom left
			 0.015f, 0.0f,   -0.25f,	0.1f, 0.0f,		0.0f, -1.0f, 0.0f,		// 2 bottom right
			
			// bottom left face
			 -0.015f, 0.0f,  -0.25f,	0.0f, 0.0f,		-0.5f, -0.5f, 0.0f,		// 3 back left
			 -0.03f,  0.025f,-0.25f,	0.1f, 0.0f,		-0.5f, -0.5f, 0.0f,		// 4 back right

			// top left face
			-0.03f,  0.025f, -0.25f,	0.0f, 0.0f,		-0.5f, 0.5f, 0.0f,		// 5 back left
			-0.015f, 0.05f,	 -0.25f,	0.1f, 0.0f,		-0.5f, 0.5f, 0.0f,		// 6 back right

			// bottom right face
			 0.015f, 0.0f,    -0.25f,	0.0f, 0.0f,		 0.5f,-0.5f, 0.0f,		// 7 back left
			 0.03f,  0.025f,  -0.25f,	0.1f, 0.0f,		 0.5f,-0.5f, 0.0f,		// 8 back right

			// top right face
			 0.03f,  0.025f,  -0.25f,	0.0f, 0.0f,		 0.5f, 0.5f, 0.0f,		// 9 back left
			 0.015f, 0.05f,   -0.25f,	0.1f, 0.0f,		 0.5f, 0.5f, 0.0f,		// 10back right

			// top face
			-0.015f, 0.05f,	  -0.25f,	0.0f, 0.0f,		 0.0f, 1.0f, 0.0f,		// 11back left
			 0.015f, 0.05f,   -0.25f,	0.1f, 0.0f,		 0.0f, 1.0f, 0.0f,		// 12backright
		};

		// Index to share position data
		// this is set up in groups of 3 to create triangles
		GLushort tipIndices[] = {
			1, 2, 0,
			3, 4, 0,
			5, 6, 0,
			7, 8, 0,
			9, 10, 0, 
			11, 12, 0,
		};

		// Index vertices and UV coords
		const GLuint floatsPerVertex = 3;
		const GLuint floatsPerUv = 2;
		const GLuint floatsPerNormal = 3;

		// generate 'n' bind vertex arrays
		glGenVertexArrays(1, &mesh.vao);
		glBindVertexArray(mesh.vao);

		// create 2 buffers for vertex data, then indices
		glGenBuffers(2, mesh.vbos);
		glBindBuffer(GL_ARRAY_BUFFER, mesh.vbos[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(tipVerts), tipVerts, GL_STATIC_DRAW);

		mesh.nIndices = sizeof(tipVerts) / sizeof(tipIndices[0]);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.vbos[1]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(tipIndices), tipIndices, GL_STATIC_DRAW);

		// strides between coords is 6, a tightly packed stride is 0
		GLint stride = sizeof(float) * (floatsPerVertex + floatsPerUv + floatsPerNormal);


		// creates the vertex attribute pointers
		glVertexAttribPointer(0, floatsPerVertex, GL_FLOAT, GL_FALSE, stride, 0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, floatsPerNormal, GL_FLOAT, GL_FALSE, stride, 0);
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, floatsPerUv, GL_FLOAT, GL_FALSE, stride, (char*)(sizeof(float) * floatsPerVertex));
		glEnableVertexAttribArray(2);


		// Transforms
		glm::mat4 scale = glm::scale(glm::vec3(2.0f, 2.0f, 3.0f));
		glm::mat4 rotation = glm::rotate(glm::radians(230.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glm::mat4 translation = glm::translate(glm::vec3(3.5f, 0.007f, 0.7f));

		// retrieve our MVP matrices 'n' send 'em to the shader
		GLint modelLoc = glGetUniformLocation(gProgramId, "model");
		GLint viewLoc = glGetUniformLocation(gProgramId, "view");
		GLint projLoc = glGetUniformLocation(gProgramId, "projection");

		// model matrix
		glm::mat4 model = translation * rotation * scale;


		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		GLint UVScaleLoc = glGetUniformLocation(gProgramId, "uvScale");
		glUniform2fv(UVScaleLoc, 1, glm::value_ptr(gUVScale));

		// Draw the triangles
		glDrawElements(GL_TRIANGLES, mesh.nIndices, GL_UNSIGNED_SHORT, NULL);

	}


	// Generate pen stylus
	void generatePenStylus(GLMesh& mesh, glm::mat4 view, glm::mat4 projection) {
		// use the OBJECT shader
		glUseProgram(gProgramId);

		// bind texture to the VBO
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture8);

		// Specify the normalized device6 coordinates and color for pyramid verts
		// FORMAT: (x,y,z, texture x, y, normal x, y, z, -> next vertice)
		GLfloat tipVerts[] =
		{
			// centerpoint vertex
			 0.0f, 0.025f,	  0.3f,	0.5f, 0.1f,		0.0f, 0.0f, 0.0f,		// 0 center vertex

			// bottom face
			-0.015f, 0.0f,    0.25f,	0.0f, 0.0f,		0.0f, -1.0f, 0.0f,		// 1 bottom left
			 0.015f, 0.0f,    0.25f,	0.1f, 0.0f,		0.0f, -1.0f, 0.0f,		// 2 bottom right
			-0.015f, 0.0f,	  0.3f,		0.0f, 0.1f,		0.0f, -1.0f, 0.0f,		// 3 top left
			 0.015f, 0.0f,    0.3f,		0.1f, 0.1f,		0.0f, -1.0f, 0.0f,		// 4 top right

			// bottom left face
			 -0.015f, 0.0f,   0.25f,	0.0f, 0.0f,		-0.5f, -0.5f, 0.0f,		// 5 back left
			 -0.03f,  0.025f, 0.25f,	0.1f, 0.0f,		-0.5f, -0.5f, 0.0f,		// 6 back right
			 -0.015f, 0.0f,	  0.3f,		0.0f, 0.1f,		-0.5f, -0.5f, 0.0f,		// 7 front left
			 -0.03f,  0.025f, 0.3f,		0.1f, 0.1f,		-0.5f, -0.5f, 0.0f,		// 8 front right

			// top left face
			-0.03f,  0.025f,  0.25f,	0.0f, 0.0f,		-0.5f, 0.5f, 0.0f,		// 9 back left
			-0.015f, 0.05f,	  0.25f,	0.1f, 0.0f,		-0.5f, 0.5f, 0.0f,		// 10 back right
			-0.03f,  0.025f,  0.3f,		0.0f, 0.1f,		-0.5f, 0.5f, 0.0f,		// 11 front left
			-0.015f, 0.05f,	  0.3f,		0.1f, 0.1f,		-0.5f, 0.5f, 0.0f,		// 12 front right

			// bottom right face
			 0.015f, 0.0f,     0.25f,	0.0f, 0.0f,		 0.5f,-0.5f, 0.0f,		// 13 back left
			 0.03f,  0.025f,   0.25f,	0.1f, 0.0f,		 0.5f,-0.5f, 0.0f,		// 14 back right
			 0.015f, 0.0f,	   0.3f,    0.0f, 0.1f,		 0.5f,-0.5f, 0.0f,		// 15 front left
			 0.03f,  0.025f,   0.3f,	0.1f, 0.1f,		 0.5f,-0.5f, 0.0f,		// 16 front right

			// top right face
			 0.03f,  0.025f,   0.25f,	0.0f, 0.0f,		 0.5f, 0.5f, 0.0f,		// 17 back left
			 0.015f, 0.05f,    0.25f,	0.1f, 0.0f,		 0.5f, 0.5f, 0.0f,		// 18back right
			 0.03f,  0.025f,   0.3f,    0.0f, 0.1f,		 0.5f, 0.5f, 0.0f,		// 19top left
			 0.015f, 0.05f,	   0.3f,	0.1f, 0.1f,		 0.5f, 0.5f, 0.0f,		// 20top right

			// top face
			-0.015f, 0.05f,	   0.25f,	0.0f, 0.0f,		 0.0f, 1.0f, 0.0f,		// 21back left
			 0.015f, 0.05f,    0.25f,	0.1f, 0.0f,		 0.0f, 1.0f, 0.0f,		// 22back right
			-0.015f, 0.05f,	   0.3f,    0.0f, 0.1f,		 0.0f, 1.0f, 0.0f,		// 23top left
			 0.015f, 0.05f,	   0.3f,	0.1f, 0.1f,		 0.0f, 1.0f, 0.0f,		// 24top right

			 // top surface face
			-0.015f, 0.0f,	   0.3f,	0.03f, 0.0f,	 0.0f, 0.0f, 1.0f,		// 25 bottom center left vert
			 0.015f, 0.0f,     0.3f,	0.06f, 0.0f,	 0.0f, 0.0f, 1.0f,		// 26 bottom center right vert
			-0.015f, 0.0f,	   0.3f,	0.03f, 0.0f,	 0.0f, 0.0f, 1.0f,		// 27 bottom left bottom vert
			-0.03f,  0.025f,   0.3f,	0.0f, 0.05f,	 0.0f, 0.0f, 1.0f,		// 28 bottom left top vert			CENTER
			-0.03f,  0.025f,   0.3f,	0.0f, 0.05f,	 0.0f, 0.0f, 1.0f,		// 29 top left bottom vert			CENTER
			-0.015f, 0.05f,	   0.3f,	0.03f, 0.1f,	 0.0f, 0.0f, 1.0f,		// 30 top left top vert
			 0.015f, 0.0f,	   0.3f,    0.06f, 0.0f,	 0.0f, 0.0f, 1.0f,		// 31 bottom right bottom vert
			 0.03f,  0.025f,   0.3f,	0.1f, 0.05f,	 0.0f, 0.0f, 1.0f,		// 32 bottom right top vert			CENTER
			 0.03f,  0.025f,   0.3f,    0.1f, 0.05f,	 0.0f, 0.0f, 1.0f,		// 33 top right bottom vert			CENTER
			 0.015f, 0.05f,	   0.3f,	0.06f, 0.1f,	 0.0f, 0.0f, 1.0f,		// 34 top right top vert			
			-0.015f, 0.05f,	   0.3f,    0.03f, 0.1f,	 0.0f, 0.0f, 1.0f,		// 35 top center left
			 0.015f, 0.05f,	   0.3f,	0.06f, 0.1f,	 0.0f, 0.0f, 1.0f,		// 36 top center right
		};

		// Index to share position data
		// this is set up in groups of 3 to create triangles
		GLushort tipIndices[] = {
			// bottom
			1, 2, 3,
			2, 3, 4,

			// bottom left
			5, 6, 7,
			6, 7, 8,

			// top left
			9, 10, 11,
			10, 11, 12,
			
			// bottom right
			13, 14, 15,
			14, 15, 16,

			// top right
			17, 18, 19,
			18, 19, 20,

			// top
			21, 22, 23,
			22, 23, 24,
			/*
			// flat face
			3, 4, 0,
			7, 8, 0,
			11, 12, 0,
			15, 16, 0,
			19, 20, 0,
			23, 24, 0,
			*/

			// flat surface
			25, 26, 0,
			27, 28, 0,
			29, 30, 0,
			31, 32, 0,
			33, 34, 0,
			35, 36, 0,
		};

		// Index vertices and UV coords
		const GLuint floatsPerVertex = 3;
		const GLuint floatsPerUv = 2;
		const GLuint floatsPerNormal = 3;

		// generate 'n' bind vertex arrays
		glGenVertexArrays(1, &mesh.vao);
		glBindVertexArray(mesh.vao);

		// create 2 buffers for vertex data, then indices
		glGenBuffers(2, mesh.vbos);
		glBindBuffer(GL_ARRAY_BUFFER, mesh.vbos[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(tipVerts), tipVerts, GL_STATIC_DRAW);

		mesh.nIndices = sizeof(tipVerts) / sizeof(tipIndices[0]);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.vbos[1]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(tipIndices), tipIndices, GL_STATIC_DRAW);

		// strides between coords is 6, a tightly packed stride is 0
		GLint stride = sizeof(float) * (floatsPerVertex + floatsPerUv + floatsPerNormal);


		// creates the vertex attribute pointers
		glVertexAttribPointer(0, floatsPerVertex, GL_FLOAT, GL_FALSE, stride, 0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, floatsPerNormal, GL_FLOAT, GL_FALSE, stride, 0);
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, floatsPerUv, GL_FLOAT, GL_FALSE, stride, (char*)(sizeof(float) * floatsPerVertex));
		glEnableVertexAttribArray(2);


		// Transforms
		glm::mat4 scale = glm::scale(glm::vec3(2.0f, 2.0f, 3.0f));
		glm::mat4 rotation = glm::rotate(glm::radians(230.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glm::mat4 translation = glm::translate(glm::vec3(3.5f, 0.007f, 0.7f));

		// retrieve our MVP matrices 'n' send 'em to the shader
		GLint modelLoc = glGetUniformLocation(gProgramId, "model");
		GLint viewLoc = glGetUniformLocation(gProgramId, "view");
		GLint projLoc = glGetUniformLocation(gProgramId, "projection");

		// model matrix
		glm::mat4 model = translation * rotation * scale;


		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		GLint UVScaleLoc = glGetUniformLocation(gProgramId, "uvScale");
		glUniform2fv(UVScaleLoc, 1, glm::value_ptr(gUVScale));

		// Draw the triangles
		glDrawElements(GL_TRIANGLES, mesh.nIndices, GL_UNSIGNED_SHORT, NULL);

	}

	// Generate dutch oven
	void generateDutchOven(GLMesh& mesh, glm::mat4 view, glm::mat4 projection) {
		// use the OBJECT shader
		glUseProgram(gProgramId);

		// bind texture to the VBO
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture9);

		// Specify the normalized device6 coordinates and color for pyramid verts
		// FORMAT: (x,y,z, texture x, y, normal x, y, z, -> next vertice)
		GLfloat bodyLidVerts[] =
		{
			// eight sides. let's go.

			/*
			 * Main vessel
			 */
			
			// front center face
			-0.2f, 0.0f, 0.0f,		0.0f, 0.0f,		0.0f, 0.0f, -1.0f,		// 0  bottom left vertex
			 0.2f, 0.0f, 0.0f,		0.1f, 0.0f,		0.0f, 0.0f, -1.0f,		// 1  bottom right vertex
			-0.2f, 0.4f, 0.0f,		0.0f, 0.1f,		0.0f, 0.0f, -1.0f,		// 2  top left vertex
			 0.2f, 0.4f, 0.0f,		0.1f, 0.1f,		0.0f, 0.0f, -1.0f,		// 3  top right vertex

			// front left face
			-0.2f, 0.0f, 0.0f,		0.0f, 0.0f,		-0.5f, 0.0f, -0.5f,		// 4  front-left bottom left vertex
			-0.4f, 0.0f, 0.2f,		0.1f, 0.0f,		-0.5f, 0.0f, -0.5f,		// 5  front-left bottom right vertex
			-0.2f, 0.4f, 0.0f,		0.0f, 0.1f,		-0.5f, 0.0f, -0.5f,		// 6  front-left top left vertex
			-0.4f, 0.4f, 0.2f,		0.1f, 0.1f,		-0.5f, 0.0f, -0.5f,		// 7  front-left top right vertex

			// left face
			-0.4f, 0.0f, 0.2f,		0.0f, 0.0f,		-1.0f, 0.0f, 0.0f,		// 8  left bottom left vertex
			-0.4f, 0.0f, 0.6f,		0.1f, 0.0f,		-1.0f, 0.0f, 0.0f,		// 9  left bottom right vertex
			-0.4f, 0.4f, 0.2f,		0.0f, 0.1f,		-1.0f, 0.0f, 0.0f,		// 10 left top left vertex
			-0.4f, 0.4f, 0.6f,		0.1f, 0.1f,		-1.0f, 0.0f, 0.0f,		// 11 left top right vertex

			// back left face
			-0.4f, 0.0f, 0.6f,		0.0f, 0.0f,		-0.5f, 0.0f, 0.5f,		// 12 back-left bottom left vertex
			-0.2f, 0.0f, 0.8f,		0.1f, 0.0f,		-0.5f, 0.0f, 0.5f,		// 13 back-left bottom right vertex
			-0.4f, 0.4f, 0.6f,		0.0f, 0.1f,		-0.5f, 0.0f, 0.5f,		// 14 back-left top left vertex
			-0.2f, 0.4f, 0.8f,		0.1f, 0.1f,		-0.5f, 0.0f, 0.5f,		// 15 back-left top right vertex

			// back face
			-0.2f, 0.0f, 0.8f,		0.0f, 0.0f,		 0.0f, 0.0f, 1.0f,		// 16 back bottom left vertex
			 0.2f, 0.0f, 0.8f,		0.1f, 0.0f,		 0.0f, 0.0f, 1.0f,		// 17 back bottom right vertex
			-0.2f, 0.4f, 0.8f,		0.0f, 0.1f,		 0.0f, 0.0f, 1.0f,		// 18 back top left vertex
			 0.2f, 0.4f, 0.8f,		0.1f, 0.1f,		 0.0f, 0.0f, 1.0f,		// 19 back top right vertex

			// back right face
			 0.2f, 0.0f, 0.8f,		0.0f, 0.0f,		 0.5f, 0.0f, 0.5f,		// 20 back bottom left vertex
			 0.4f, 0.0f, 0.6f,		0.1f, 0.0f,		 0.5f, 0.0f, 0.5f,		// 21 back bottom right vertex
			 0.2f, 0.4f, 0.8f,		0.0f, 0.1f,		 0.5f, 0.0f, 0.5f,		// 22 back top left vertex
			 0.4f, 0.4f, 0.6f,		0.1f, 0.1f,		 0.5f, 0.0f, 0.5f,		// 23 back top right vertex

			// right face
			 0.4f, 0.0f, 0.6f,		0.0f, 0.0f,		 1.0f, 0.0f, 0.0f,		// 24 right bottom left vertex
			 0.4f, 0.0f, 0.2f,		0.1f, 0.0f,		 1.0f, 0.0f, 0.0f,		// 25 right bottom right vertex
			 0.4f, 0.4f, 0.6f,		0.0f, 0.1f,		 1.0f, 0.0f, 0.0f,		// 26 right top left vertex
			 0.4f, 0.4f, 0.2f,		0.1f, 0.1f,		 1.0f, 0.0f, 0.0f,		// 27 right top right vertex
			
			// front right face
			 0.4f, 0.0f, 0.2f,		0.0f, 0.0f,		 0.5f, 0.0f, -0.5f,		// 28 front-right bottom left vertex
			 0.2f, 0.0f, 0.0f,		0.1f, 0.0f,		 0.5f, 0.0f, -0.5f,		// 29 front-right bottom right vertex
			 0.4f, 0.4f, 0.2f,		0.0f, 0.1f,		 0.5f, 0.0f, -0.5f,		// 30 front-right top left vertex
			 0.2f, 0.4f, 0.0f,		0.1f, 0.1f,		 0.5f, 0.0f, -0.5f,		// 31 front-right top right vertex
			 

			 /*
			  * Lid
			  */

			// front center face
			-0.23f, 0.4f, -0.03f,	0.0f, 0.0f,		0.0f, 0.0f, -1.0f,		// 32  bottom left vertex
			 0.23f, 0.4f, -0.03f,	0.1f, 0.0f,		0.0f, 0.0f, -1.0f,		// 33  bottom right vertex

			// front left face
			-0.23f, 0.4f, -0.03f,	0.0f, 0.0f,		-0.5f, 0.0f, -0.5f,		// 34  front-left bottom left vertex
			-0.43f, 0.4f, 0.23f,	0.1f, 0.0f,		-0.5f, 0.0f, -0.5f,		// 35  front-left bottom right vertex

			// left face
			-0.43f, 0.4f, 0.23f,	0.0f, 0.0f,		-1.0f, 0.0f, 0.0f,		// 36  left bottom left vertex
			-0.43f, 0.4f, 0.63f,	0.1f, 0.0f,		-1.0f, 0.0f, 0.0f,		// 37  left bottom right vertex

			// back left face
			-0.43f, 0.4f, 0.63f,	0.0f, 0.0f,		-0.5f, 0.0f, 0.5f,		// 38 back-left bottom left vertex
			-0.23f, 0.4f, 0.83f,	0.1f, 0.0f,		-0.5f, 0.0f, 0.5f,		// 39 back-left bottom right vertex

			// back face
			-0.23f, 0.4f, 0.83f,	0.0f, 0.0f,		 0.0f, 0.0f, 1.0f,		// 40 back bottom left vertex
			 0.23f, 0.4f, 0.83f,	0.1f, 0.0f,		 0.0f, 0.0f, 1.0f,		// 41 back bottom right vertex

			// back right face
			 0.23f, 0.4f, 0.83f,	0.0f, 0.0f,		 0.5f, 0.0f, 0.5f,		// 42 back bottom left vertex
			 0.43f, 0.4f, 0.63f,	0.1f, 0.0f,		 0.5f, 0.0f, 0.5f,		// 43 back bottom right vertex

			// right face
			 0.43f, 0.4f, 0.63f,	0.0f, 0.0f,		 1.0f, 0.0f, 0.0f,		// 44 right bottom left vertex
			 0.43f, 0.4f, 0.23f,	0.1f, 0.0f,		 1.0f, 0.0f, 0.0f,		// 45 right bottom right vertex

			// front right face
			 0.43f, 0.4f, 0.23f,	0.0f, 0.0f,		 0.5f, 0.0f, -0.5f,		// 46 front-right bottom left vertex
			 0.23f, 0.4f, -0.03f,	0.1f, 0.0f,		 0.5f, 0.0f, -0.5f,		// 47 front-right bottom right vertex

			// center cylinder
			 0.0f, 0.5f, 0.4f,		0.5f, 0.1f,		 0.0f, 1.0f, 0.0f,		// 48 set 1
			 0.0f, 0.4f, 0.4f,		0.0f, 0.0f,		 0.0f, 1.0f, 0.0f,		// 49 bottom center point

			/*
			 * Handles
			 */

			// left handle front
			-0.4f, 0.35f, 0.25f,	0.0f, 0.0f,		 0.0f, 1.0f, 0.0f,		// 50  left bottom left vertex
			-0.4f, 0.35f, 0.3f,		0.1f, 0.0f,		 0.0f, 1.0f, 0.0f,		// 51  left bottom right vertex
			-0.5f, 0.35f, 0.25f,	0.0f, 0.1f,		 0.0f, 1.0f, 0.0f,		// 52 left top left vertex
			-0.5f, 0.35f, 0.3f,		0.1f, 0.1f,		 0.0f, 1.0f, 0.0f,		// 53 left top right vertex

			// left handle back
			-0.4f, 0.35f, 0.55f,	0.0f, 0.0f,		 0.0f, 1.0f, 0.0f,		// 54 left bottom left vertex
			-0.4f, 0.35f, 0.5f,		0.1f, 0.0f,		 0.0f, 1.0f, 0.0f,		// 55 left bottom right vertex
			-0.5f, 0.35f, 0.55f,		0.0f, 0.1f,		 0.0f, 1.0f, 0.0f,		// 56 left top left vertex
			-0.5f, 0.35f, 0.5f,		0.1f, 0.1f,		 0.0f, 1.0f, 0.0f,		// 57 left top right vertex

			// left handle loop
			-0.5f, 0.35f, 0.25f,		0.0f, 0.1f,		 0.0f, 1.0f, 0.0f,		// 58 left bottom left vertex
			-0.55f,0.35f, 0.25f,	0.0f, 0.0f,		 0.0f, 1.0f, 0.0f,		// 59 left bottom right vertex
			-0.5f, 0.35f, 0.55f,		0.0f, 0.1f,		 0.0f, 1.0f, 0.0f,		// 60 left top left vertex
			-0.55f,0.35f, 0.55f,	0.0f, 0.0f,		 0.0f, 1.0f, 0.0f,		// 61 left top right vertex

			// right handle front
			 0.4f, 0.35f, 0.25f,	0.0f, 0.0f,		 0.0f, 1.0f, 0.0f,		// 62 right bottom left vertex
			 0.4f, 0.35f, 0.3f,		0.1f, 0.0f,		 0.0f, 1.0f, 0.0f,		// 63 right bottom right vertex
			 0.5f, 0.35f, 0.25f,	0.0f, 0.1f,		 0.0f, 1.0f, 0.0f,		// 64 right top left vertex
			 0.5f, 0.35f, 0.3f,		0.1f, 0.1f,		 0.0f, 1.0f, 0.0f,		// 65 right top right vertex

			// right handle back
			 0.4f, 0.35f, 0.55f,	0.0f, 0.0f,		 0.0f, 1.0f, 0.0f,		// 66 right bottom left vertex
			 0.4f, 0.35f, 0.5f,		0.1f, 0.0f,		 0.0f, 1.0f, 0.0f,		// 67 right bottom right vertex
			 0.5f, 0.35f, 0.55f,		0.0f, 0.1f,		 0.0f, 1.0f, 0.0f,		// 68 right top left vertex
			 0.5f, 0.35f, 0.5f,		0.1f, 0.1f,		 0.0f, 1.0f, 0.0f,		// 69 right top right vertex

			// right handle loop
			 0.5f, 0.35f, 0.25f,	0.0f, 0.1f,		 0.0f, 1.0f, 0.0f,		// 70 right bottom left vertex
			 0.55f,0.35f, 0.25f,	0.0f, 0.0f,		 0.0f, 1.0f, 0.0f,		// 71 right bottom right vertex
			 0.5f, 0.35f, 0.55f,	0.0f, 0.1f,		 0.0f, 1.0f, 0.0f,		// 72 right top left vertex
			 0.55f,0.35f, 0.55f,	0.0f, 0.0f,		 0.0f, 1.0f, 0.0f,		// 73 right top right vertex
		};

		// Index to share position data
		// this is set up in groups of 3 to create triangles
		GLushort bodyLidIndices[] = {
			// front face
			0, 1, 2,
			1, 2, 3,

			// front left face
			4, 5, 6,
			5, 6, 7,

			// left face
			8, 9, 10,
			9, 10, 11,
			
			// back left face
			12, 13, 14,
			13, 14, 15,

			// back face
			16, 17, 18,
			17, 18, 19,
			
			// back right face
			20, 21, 22,
			21, 22, 23,

			// right face
			24, 25, 26,
			25, 26, 27,

			// right front face
			28, 29, 30,
			29, 30, 31,

			// lid vertices
			32, 33, 48,
			32, 33, 49,

			34, 35, 48,
			34, 35, 49,

			36, 37, 48,
			36, 37, 49,

			38, 39, 48,
			38, 39, 49,

			40, 41, 48,
			40, 41, 49,

			42, 43, 48,
			42, 43, 49,

			44, 45, 48,
			44, 45, 49,

			46, 47, 48,
			46, 47, 49,

			// left handle
			50, 51, 52,
			51, 52, 53,
			54, 55, 56,
			55, 56, 57,
			58, 59, 60,
			59, 60, 61,

			// right handle
			62, 63, 64,
			63, 64, 65,
			66, 67, 68,
			67, 68, 69,
			70, 71, 72,
			71, 72, 73,

			// phew. what a doozy.
		};

		// Index vertices and UV coords
		const GLuint floatsPerVertex = 3;
		const GLuint floatsPerUv = 2;
		const GLuint floatsPerNormal = 3;

		// generate 'n' bind vertex arrays
		glGenVertexArrays(1, &mesh.vao);
		glBindVertexArray(mesh.vao);

		// create 2 buffers for vertex data, then indices
		glGenBuffers(2, mesh.vbos);
		glBindBuffer(GL_ARRAY_BUFFER, mesh.vbos[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(bodyLidVerts), bodyLidVerts, GL_STATIC_DRAW);

		mesh.nIndices = sizeof(bodyLidVerts) / sizeof(bodyLidIndices[0]);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.vbos[1]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(bodyLidIndices), bodyLidIndices, GL_STATIC_DRAW);

		// strides between coords is 6, a tightly packed stride is 0
		GLint stride = sizeof(float) * (floatsPerVertex + floatsPerUv + floatsPerNormal);


		// creates the vertex attribute pointers
		glVertexAttribPointer(0, floatsPerVertex, GL_FLOAT, GL_FALSE, stride, 0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, floatsPerNormal, GL_FLOAT, GL_FALSE, stride, 0);
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, floatsPerUv, GL_FLOAT, GL_FALSE, stride, (char*)(sizeof(float) * floatsPerVertex));
		glEnableVertexAttribArray(2);


		// Transforms
		glm::mat4 scale = glm::scale(glm::vec3(3.5f, 3.5f, 3.5f));
		glm::mat4 rotation = glm::rotate(glm::radians(40.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glm::mat4 translation = glm::translate(glm::vec3(-2.8f,-0.5f, -2.0f));

		// retrieve our MVP matrices 'n' send 'em to the shader
		GLint modelLoc = glGetUniformLocation(gProgramId, "model");
		GLint viewLoc = glGetUniformLocation(gProgramId, "view");
		GLint projLoc = glGetUniformLocation(gProgramId, "projection");

		// model matrix
		glm::mat4 model = translation * rotation * scale;


		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		GLint UVScaleLoc = glGetUniformLocation(gProgramId, "uvScale");
		glUniform2fv(UVScaleLoc, 1, glm::value_ptr(gUVScale));

		// Draw the triangles
		glDrawElements(GL_TRIANGLES, mesh.nIndices, GL_UNSIGNED_SHORT, NULL);

	}

	// Generate pen tip
	void generateOvenHandle(GLMesh& mesh, glm::mat4 view, glm::mat4 projection) {
		// use the OBJECT shader
		glUseProgram(gProgramId);

		// bind texture to the VBO
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture10);

		// Specify the normalized device6 coordinates and color for pyramid verts
		// FORMAT: (x,y,z, texture x, y, normal x, y, z, -> next vertice)
		GLfloat handleVerts[] =
		{
			// two pieces: handle stem front, then the knob
			// stem will be a cube and the knob will be a hexagon
			// starting height: 0.5f
			// center start: 0.04f
	
			// handle stem front
		    -0.05f, 0.4f, 0.35f,		0.0f, 0.0f,		0.0f, 0.0f, 1.0f,	//  0 bottom left vertex
			 0.05f, 0.4f, 0.35f,		0.1f, 0.0f,		0.0f, 0.0f, 1.0f,	//  1 bottom right vertex
			-0.05f, 0.52f,0.35f,		0.0f, 0.1f,		0.0f, 0.0f, 1.0f,	//  2 top left vertex
			 0.05f, 0.52f,0.35f,		0.1f, 0.1f,		0.0f, 0.0f, 1.0f,	//  3 top right vertex

			// handle stem left
			-0.05f, 0.4f, 0.35f,		0.0f, 0.0f,		-1.0f, 0.0f, 0.0f,	//  4 bottom left
			-0.05f, 0.4f, 0.45f,		0.1f, 0.0f,		-1.0f, 0.0f, 0.0f,	//  5 bottom right
			-0.05f, 0.52f,0.35f,		0.0f, 0.1f,		-1.0f, 0.0f, 0.0f,	//  6 top left
			-0.05f, 0.52f,0.45f,		0.1f, 0.1f,		-1.0f, 0.0f, 0.0f,	//  7 top right

			// handle stem right
			 0.05f, 0.4f, 0.35f,		0.0f, 0.0f,		 1.0f, 0.0f, 0.0f,	//  8 bottom left
			 0.05f, 0.4f, 0.45f,		0.1f, 0.0f,		 1.0f, 0.0f, 0.0f,	//  9 bottom right
			 0.05f, 0.52f,0.35f,		0.0f, 0.1f,		 1.0f, 0.0f, 0.0f,	// 10 top left
			 0.05f, 0.52f,0.45f,		0.1f, 0.1f,		 1.0f, 0.0f, 0.0f,	// 11 top right

			// handle stem back
			-0.05f, 0.4f, 0.45f,		0.0f, 0.0f,		0.0f, 0.0f, -1.0f,	// 12 bottom left vertex
			 0.05f, 0.4f, 0.45f,		0.1f, 0.0f,		0.0f, 0.0f, -1.0f,	// 13 bottom right vertex
			-0.05f, 0.52f,0.45f,		0.0f, 0.1f,		0.0f, 0.0f, -1.0f,	// 14 top left vertex
			 0.05f, 0.52f,0.45f,		0.1f, 0.1f,		0.0f, 0.0f, -1.0f,	// 15 top right vertex

			// now the fun part.
			// knob

			// back face
			-0.07f, 0.52f, 0.32f,		0.0f, 0.0f,		0.0f, 0.0f, -1.0f,	// 16 bottom left
			 0.07f, 0.52f, 0.32f,		0.1f, 0.0f,		0.0f, 0.0f, -1.0f,	// 17 bottom right
			-0.07f, 0.56f, 0.32f,		0.0f, 0.1f,		0.0f, 0.0f, -1.0f,  // 18 top left
			 0.07f, 0.56f, 0.32f,		0.1f, 0.1f,		0.0f, 0.0f, -1.0f,	// 19 top right

			// back left face
			-0.07f, 0.52f, 0.32f,		0.0f, 0.0f,		-0.5f,0.0f, -0.5f,	// 20 bottom left
			-0.09f,	0.52f, 0.4f,		0.1f, 0.0f,		-0.5f,0.0f, -0.5f,	// 21 bottom right
			-0.07f, 0.56f, 0.32f,		0.0f, 0.1f,		-0.5f,0.0f, -0.5f,	// 22 top left
			-0.09f, 0.56f, 0.4f,		0.1f, 0.1f,		-0.5f,0.0f, -0.5f,	// 23 top right

			// front left face
			-0.09f, 0.52f, 0.4f,		0.0f, 0.0f,		-0.5f,0.0f, 0.5f,	// 24 bottom left
			-0.07f, 0.52f, 0.48f,		0.1f, 0.0f,		-0.5f,0.0f, 0.5f,	// 25 bottom right
			-0.09f, 0.56f, 0.4f,		0.0f, 0.1f,		-0.5f,0.0f, 0.5f,	// 26 top left
			-0.07f, 0.56f, 0.48f,		0.1f, 0.1f,		-0.5f,0.0f, 0.5f,	// 27 top right

			// front face
			-0.07f, 0.52f, 0.48f,		0.0f, 0.0f,		0.0f, 0.0f, 1.0f,	// 28 bottom left
			 0.07f, 0.52f, 0.48f,		0.1f, 0.0f,		0.0f, 0.0f, 1.0f,	// 29 bottom right
			-0.07f, 0.56f, 0.48f,		0.0f, 0.1f,		0.0f, 0.0f, 1.0f,	// 30 top left
			 0.07f, 0.56f, 0.48f,		0.1f, 0.1f,		0.0f, 0.0f, 1.0f,	// 31 top right

			// front right face
			 0.09f, 0.52f, 0.4f,		0.0f, 0.0f,		 0.5f,0.0f, 0.5f,	// 32 bottom left
			 0.07f, 0.52f, 0.48f,		0.1f, 0.0f,		 0.5f,0.0f, 0.5f,	// 33 bottom right
			 0.09f, 0.56f, 0.4f,		0.0f, 0.1f,		 0.5f,0.0f, 0.5f,	// 34 top left
			 0.07f, 0.56f, 0.48f,		0.1f, 0.1f,		 0.5f,0.0f, 0.5f,	// 35 top right

			// back right face
			 0.07f, 0.52f, 0.32f,		0.0f, 0.0f,		 0.5f,0.0f, -0.5f,	// 36 bottom left
			 0.09f,	0.52f, 0.4f,		0.1f, 0.0f,		 0.5f,0.0f, -0.5f,	// 37 bottom right
			 0.07f, 0.56f, 0.32f,		0.0f, 0.1f,		 0.5f,0.0f, -0.5f,	// 38 top left
			 0.09f, 0.56f, 0.4f,		0.1f, 0.1f,		 0.5f,0.0f, -0.5f,	// 39 top right

			// center vertex
			0.0f, 0.56f, 0.4f,			0.5f, 0.1f,		 0.0f,1.0f, 0.0f,	// 40 top center
			0.0f, 0.52f, 0.4f,			0.5f, 0.1f,		 0.0f,-1.0f,0.0f,	// 41 bottom center
		};

		// Index to share position data
		// this is set up in groups of 3 to create triangles
		GLushort handleIndices[] = {
			// 
			// stem
			// 
			
			// front
			0, 1, 2,
			1, 2, 3,

			// left
			4, 5, 6,
			5, 6, 7,

			// right
			8, 9, 10,
			9, 10, 11,

			// back
			12, 13, 14,
			13, 14, 15,

			//
			// handle
			//

			// back
			16, 17, 18,
			17, 18, 19,

			// back left
			20, 21, 22,
			21, 22, 23,

			// front left
			24, 25, 26,
			25, 26, 27,

			// front
			28, 29, 30,
			29, 30, 31,

			// front right
			32, 33, 34,
			33, 34, 35,

			// back right
			36, 37, 38,
			37, 38, 39,

			// top face
			18, 19, 40,
			22, 23, 40,
			26, 27, 40,
			30, 31, 40,
			34, 35, 40,
			38, 39, 40,

			// bottom face
			16, 17, 41,
			20, 21, 41,
			24, 25, 41,
			28, 29, 41,
			32, 33, 41,
			36, 37, 41,
		};

		// Index vertices and UV coords
		const GLuint floatsPerVertex = 3;
		const GLuint floatsPerUv = 2;
		const GLuint floatsPerNormal = 3;

		// generate 'n' bind vertex arrays
		glGenVertexArrays(1, &mesh.vao);
		glBindVertexArray(mesh.vao);

		// create 2 buffers for vertex data, then indices
		glGenBuffers(2, mesh.vbos);
		glBindBuffer(GL_ARRAY_BUFFER, mesh.vbos[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(handleVerts), handleVerts, GL_STATIC_DRAW);

		mesh.nIndices = sizeof(handleVerts) / sizeof(handleIndices[0]);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.vbos[1]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(handleIndices), handleIndices, GL_STATIC_DRAW);

		// strides between coords is 6, a tightly packed stride is 0
		GLint stride = sizeof(float) * (floatsPerVertex + floatsPerUv + floatsPerNormal);


		// creates the vertex attribute pointers
		glVertexAttribPointer(0, floatsPerVertex, GL_FLOAT, GL_FALSE, stride, 0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, floatsPerNormal, GL_FLOAT, GL_FALSE, stride, 0);
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, floatsPerUv, GL_FLOAT, GL_FALSE, stride, (char*)(sizeof(float) * floatsPerVertex));
		glEnableVertexAttribArray(2);


		// Transforms
		glm::mat4 scale = glm::scale(glm::vec3(3.5f, 3.5f, 3.5f));
		glm::mat4 rotation = glm::rotate(glm::radians(40.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glm::mat4 translation = glm::translate(glm::vec3(-2.8f, -0.5f, -2.0f));

		// retrieve our MVP matrices 'n' send 'em to the shader
		GLint modelLoc = glGetUniformLocation(gProgramId, "model");
		GLint viewLoc = glGetUniformLocation(gProgramId, "view");
		GLint projLoc = glGetUniformLocation(gProgramId, "projection");

		// model matrix
		glm::mat4 model = translation * rotation * scale;


		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		GLint UVScaleLoc = glGetUniformLocation(gProgramId, "uvScale");
		glUniform2fv(UVScaleLoc, 1, glm::value_ptr(gUVScale));

		// Draw the triangles
		glDrawElements(GL_TRIANGLES, mesh.nIndices, GL_UNSIGNED_SHORT, NULL);

	}





	// initialize GLFW, GLEW, and create a window
	bool UInitialize(int argc, char* argv[], GLFWwindow** window) {
		// GLFW: initialize and configure
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

		//GLFW: window creation
		*window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);
		if (*window == NULL) {
			std::cout << "Failed to create GLFW window" << std::endl;
			glfwTerminate();
			return false;
		}

		glfwMakeContextCurrent(*window);
		glfwSetFramebufferSizeCallback(*window, UResizeWindow);
		glfwSetCursorPosCallback(*window, UMousePositionCallback);
		glfwSetScrollCallback(*window, scroll_callback);

		// GLFW: capture the mouse
		glfwSetInputMode(*window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		// GLEW: initialize
		glewExperimental = GL_TRUE;
		GLenum GlewInitResult = glewInit();

		if (GLEW_OK != GlewInitResult)
		{
			std::cerr << glewGetErrorString(GlewInitResult) << std::endl;
			return false;
		}

		// display the GPU's openGL version
		cout << "INFO: OpenGL Version: " << glGetString(GL_VERSION) << endl;

		return true;
	}

	/* 
	 * PROCESS INPUT
	 */
	void UProcessInput(GLFWwindow* window) {
		static const float cameraSpeed = 2.5f;

		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);

		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			gCamera.ProcessKeyboard(FORWARD, gDeltaTime);
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			gCamera.ProcessKeyboard(BACKWARD, gDeltaTime);
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			gCamera.ProcessKeyboard(LEFT, gDeltaTime);
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			gCamera.ProcessKeyboard(RIGHT, gDeltaTime);


		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
			gCamera.ProcessKeyboard(UP, gDeltaTime);
		if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
			gCamera.ProcessKeyboard(DOWN, gDeltaTime);

		// If "P" is pressed, set orthographic/perspective view
		// can't believe I forgot to add my curly braces. those one-line "if" statements really sneak up on you
		if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
			std::cout << "P has been pressed." << endl;
			if (orthographicView)
				orthographicView = false;
			else
				orthographicView = true;
		}
	}

	// function to resize window
	void UResizeWindow(GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);
	}

	// whenever the mouse moves, callback
	void UMousePositionCallback(GLFWwindow* window, double xpos, double ypos)
	{
		if (gFirstMouse)
		{
			gLastX = xpos;
			gLastY = ypos;
			gFirstMouse = false;
		}

		float xoffset = xpos - gLastX;
		float yoffset = gLastY - ypos; // reversed since y-coordinates go from bottom to top

		gLastX = xpos;
		gLastY = ypos;

		gCamera.ProcessMouseMovement(xoffset, yoffset);
	}

	// whenever the mousewheel is scrolled, call this
	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
		gCamera.ProcessMouseScroll(yoffset);
	}


	void UDestroyMesh(GLMesh& mesh) {
		glDeleteVertexArrays(1, &mesh.vao);
		glDeleteBuffers(2, mesh.vbos);
	}

	// Implement the UCreateShaders function
	bool UCreateShaderProgram(const char* vtxShaderSource, const char* fragShaderSource, GLuint& programId){
		// compilation and linkage error report
		int success = 0;
		char infoLog[512];

		// create a shader program object
		programId = glCreateProgram();

		// create the vertex and fragment shader objects
		GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
		GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

		// retrieve the shader source
		glShaderSource(vertexShaderId, 1, &vtxShaderSource, NULL);
		glShaderSource(fragmentShaderId, 1, &fragShaderSource, NULL);

		// compile the vertex shader and print compilation errors
		glCompileShader(vertexShaderId);

		// check for shader compilation errors
		glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(vertexShaderId, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;

			return false;
		}

		// compile the fragment shader
		glCompileShader(fragmentShaderId);

		// check for compilation errors
		if (!success)
		{
			glGetShaderInfoLog(fragmentShaderId, sizeof(infoLog), NULL, infoLog);
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;

			return false;
		}

		// attach compiled shaders to the shader program
		glAttachShader(programId, vertexShaderId);
		glAttachShader(programId, fragmentShaderId);

		// link to the shader program
		glLinkProgram(programId);

		// check for linking errors
		glGetProgramiv(programId, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(programId, sizeof(infoLog), NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;

			return false;
		}

		// use the shader program
		glUseProgram(programId);

		return true;
	}

	void UDestroyShaderProgram(GLuint programId) {
		glDeleteProgram(programId);
	}

	// Method to keep textures out of the way
	// Only the first texture is commented to act as a scaffolding and provide some context
	// All textures are licensed under the Creative Commons license.
	void defineTextures() {
		// plane surface texture
		// texture 1
		// --------- 
		// generate ONE new texture for the memory location &texture1
		glGenTextures(1, &texture1);

		// bind that texture
		glBindTexture(GL_TEXTURE_2D, texture1);

		// set the texture wrapping parameters
		// NOTE: S stands in for the X-axis, T stands in for the y-axis, and R stands in for the z-axis.
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		// set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// load image, create texture and generate mipmaps
		stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
		unsigned char* data = stbi_load(planeTex, &width, &height, &nrChannels, 0);

		// If data is present in the named texture (planeTex here), generate a new texture with our parameters
		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		// if data is not present at that item's name, shoot out a console message and don't render anything
		else
		{
			std::cout << "Failed to load plane texture" << std::endl;
		}
		// free the image data, then generate a mipmap
		stbi_image_free(data);


		//	book cover texture
		//  texture 2
		// ---------
		glGenTextures(1, &texture2);
		glBindTexture(GL_TEXTURE_2D, texture2);
		// set the texture wrapping parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// load image, create texture and generate mipmaps
		data = stbi_load(coverTex, &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "Failed to load cover texture" << std::endl;
		}
		stbi_image_free(data);


		//	book page texture
		//  texture 3
		// ---------
		glGenTextures(1, &texture3);
		glBindTexture(GL_TEXTURE_2D, texture3);
		// set the texture wrapping parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// load image, create texture and generate mipmaps
		data = stbi_load(pageTex, &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "Failed to load page texture" << std::endl;
		}
		stbi_image_free(data);

		//	guitar pedal casing texture
		//  texture 4
		// ---------
		glGenTextures(1, &texture4);
		glBindTexture(GL_TEXTURE_2D, texture4);
		// set the texture wrapping parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		// load image, create texture and generate mipmaps
		data = stbi_load(pedalTex, &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "Failed to load pedal case texture" << std::endl;
		}
		stbi_image_free(data);

		//	guitar pedal electronics texture
		//  texture 5
		// ---------
		glGenTextures(1, &texture5);
		glBindTexture(GL_TEXTURE_2D, texture5);
		// set the texture wrapping parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// load image, create texture and generate mipmaps
		data = stbi_load(pedalTex2, &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "Failed to load pedal electronics texture" << std::endl;
		}
		stbi_image_free(data);

		//	guitar pedal screen texture
		//  texture 6
		// ---------
		glGenTextures(1, &texture6);
		glBindTexture(GL_TEXTURE_2D, texture6);
		// set the texture wrapping parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// load image, create texture and generate mipmaps
		data = stbi_load(pedalTex3, &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "Failed to load pedal screen texture" << std::endl;
		}
		stbi_image_free(data);


		//	pen body texture
		//  texture 7
		// ---------
		glGenTextures(1, &texture7);
		glBindTexture(GL_TEXTURE_2D, texture7);
		// set the texture wrapping parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// load image, create texture and generate mipmaps
		data = stbi_load(penTex1, &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "Failed to load pen body texture" << std::endl;
		}
		stbi_image_free(data);

		//	pen tip texture
		//  texture 8
		// ---------
		glGenTextures(1, &texture8);
		glBindTexture(GL_TEXTURE_2D, texture8);
		// set the texture wrapping parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// load image, create texture and generate mipmaps
		data = stbi_load(penTex2, &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "Failed to load pen tip texture" << std::endl;
		}
		stbi_image_free(data);


		// dutch oven texture
		// texture 9
		// --------
		glGenTextures(1, &texture9);
		glBindTexture(GL_TEXTURE_2D, texture9);
		// set texture wrapping parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// load image, create texture and generate mipmaps
		data = stbi_load(dutchOvenTex, &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "Failed to load pen tip texture" << std::endl;
		}
		stbi_image_free(data);


		// dutch oven handle texture
		// texture 10
		// --------
		glGenTextures(1, &texture10);
		glBindTexture(GL_TEXTURE_2D, texture10);
		// set texture wrapping parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// load image, create texture and generate mipmaps
		data = stbi_load(handleTex, &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "Failed to load pen tip texture" << std::endl;
		}
		stbi_image_free(data);
	}

	// Image flip function to ensure the y-axis lines up properly
	void flipImageVertically(unsigned char* image, int width, int height, int channels) {
		for (int i = 0; i < height / 2; ++i) {
			int index1 = i * width * channels;
			int index2 = (height - 1 - i) * width * channels;

			for (int j = width * channels; j > 0; --j) {
				unsigned char tmp = image[index1];
				image[index1] = image[index2];
				image[index2] = tmp;
				++index1;
				++index2;
			}

		}
	};

	// method to keep phong shader data out of the way
	void PhongUniforms() {
		// matrix uniforms for phong shader 1
		GLint objectColorLoc = glGetUniformLocation(gProgramId, "objectColor");
		GLint lightColorLoc = glGetUniformLocation(gProgramId, "lightColor");
		GLint keyLightColorLoc = glGetUniformLocation(gProgramId, "keyLightColor");
		GLint lightPositionLoc = glGetUniformLocation(gProgramId, "lightPos");
		GLint viewPositionLoc = glGetUniformLocation(gProgramId, "viewPosition");

		// Pass color, light, and camera data to the Cube Shader program's corresponding uniforms
		glUniform3f(lightColorLoc, gLightColor.r, gLightColor.g, gLightColor.b);
		glUniform3f(lightPositionLoc, gLightPosition.x, gLightPosition.y, gLightPosition.z);
		const glm::vec3 cameraPosition = gCamera.Position;
		glUniform3f(viewPositionLoc, cameraPosition.x, cameraPosition.y, cameraPosition.z);
		

		// matrix uniforms for phong shader 2
		GLint objectColorLoc2 = glGetUniformLocation(gProgramId, "objectColor2");
		GLint lightColorLoc2 = glGetUniformLocation(gProgramId, "lightColor2");
		GLint keyLightColorLoc2 = glGetUniformLocation(gProgramId, "keyLightColor2");
		GLint lightPositionLoc2 = glGetUniformLocation(gProgramId, "lightPos2");
		GLint viewPositionLoc2 = glGetUniformLocation(gProgramId, "viewPosition2");

		// Pass color, light, and camera data to the Cube Shader program's corresponding uniforms
		glUniform3f(lightColorLoc2, gLightColor2.r, gLightColor2.g, gLightColor2.b);
		glUniform3f(lightPositionLoc2, gLightPosition2.x, gLightPosition2.y, gLightPosition2.z);
		glUniform3f(viewPositionLoc2, cameraPosition.x, cameraPosition.y, cameraPosition.z);


		// matrix uniforms for phong shader 3
		GLint objectColorLoc3 = glGetUniformLocation(gProgramId, "objectColor3");
		GLint lightColorLoc3 = glGetUniformLocation(gProgramId, "lightColor3");
		GLint keyLightColorLoc3 = glGetUniformLocation(gProgramId, "keyLightColor3");
		GLint lightPositionLoc3 = glGetUniformLocation(gProgramId, "lightPos3");
		GLint viewPositionLoc3 = glGetUniformLocation(gProgramId, "viewPosition3");

		// Pass color, light, and camera data to the Cube Shader program's corresponding uniforms
		glUniform3f(lightColorLoc3, gLightColor3.r, gLightColor3.g, gLightColor3.b);
		glUniform3f(lightPositionLoc3, gLightPosition3.x, gLightPosition3.y, gLightPosition3.z);
		glUniform3f(viewPositionLoc3, cameraPosition.x, cameraPosition.y, cameraPosition.z);


		// matrix uniforms for phong shader 4
		GLint objectColorLoc4 = glGetUniformLocation(gProgramId, "objectColor4");
		GLint lightColorLoc4 = glGetUniformLocation(gProgramId, "lightColor4");
		GLint keyLightColorLoc4 = glGetUniformLocation(gProgramId, "keyLightColor4");
		GLint lightPositionLoc4 = glGetUniformLocation(gProgramId, "lightPos4");
		GLint viewPositionLoc4 = glGetUniformLocation(gProgramId, "viewPosition4");

		// Pass color, light, and camera data to the Cube Shader program's corresponding uniforms
		glUniform3f(lightColorLoc4, gLightColor4.r, gLightColor4.g, gLightColor4.b);
		glUniform3f(lightPositionLoc4, gLightPosition4.x, gLightPosition4.y, gLightPosition4.z);
		glUniform3f(viewPositionLoc4, cameraPosition.x, cameraPosition.y, cameraPosition.z);
	}