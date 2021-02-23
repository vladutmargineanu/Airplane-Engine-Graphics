#include "Tema2.h"

#include <vector>
#include <string>
#include <iostream>

#include <Core/Engine.h>

using namespace std;

namespace pool {
	Tema2::Tema2()
	{
	}

	Tema2::~Tema2()
	{
	}

	void Tema2::Init()
	{
		{
			camera_ = new pool::Camera(window->props.aspectRatio);
		}
		{
			vector<VertexFormat> vertices
			{
				VertexFormat(glm::vec3(-1, -1,  1), glm::vec3(0, 1, 1), glm::vec3(0.2, 0.8, 0.2)),
				VertexFormat(glm::vec3(1, -1,  1), glm::vec3(1, 0, 1), glm::vec3(0.9, 0.4, 0.2)),
				VertexFormat(glm::vec3(-1,  1,  1), glm::vec3(1, 0, 0), glm::vec3(0.7, 0.7, 0.1)),
				VertexFormat(glm::vec3(1,  1,  1), glm::vec3(0, 1, 0), glm::vec3(0.7, 0.3, 0.7)),
				VertexFormat(glm::vec3(-1, -1, -1), glm::vec3(1, 1, 1), glm::vec3(0.3, 0.5, 0.4)),
				VertexFormat(glm::vec3(1, -1, -1), glm::vec3(0, 1, 1), glm::vec3(0.5, 0.2, 0.9)),
				VertexFormat(glm::vec3(-1,  1, -1), glm::vec3(1, 1, 0), glm::vec3(0.7, 0.0, 0.7)),
				VertexFormat(glm::vec3(1,  1, -1), glm::vec3(0, 0, 1), glm::vec3(0.1, 0.5, 0.8)),
			};

			vector<unsigned short> indices =
			{
				0, 1, 2,		1, 3, 2,
				2, 3, 7,		2, 7, 6,
				1, 7, 3,		1, 5, 7,
				6, 7, 4,		7, 5, 4,
				0, 4, 1,		1, 4, 5,
				2, 6, 4,		0, 2, 4,
			};

			CreateMesh("cube", vertices, indices);
		}

		// Create a shader program for drawing face polygon with the color of the normal
		{
			Shader* shader = new Shader("ShaderTema2");
			shader->AddShader("Source/Laboratoare/Tema2/Shaders/VertexShader.glsl", GL_VERTEX_SHADER);
			shader->AddShader("Source/Laboratoare/Tema2/Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
			shader->CreateAndLink();
			shaders[shader->GetName()] = shader;
		}

		//Light & material properties
		{
			lightPosition = glm::vec3(0, 1, 1);
			materialShininess = 30;
			materialKd = 0.5;
			materialKs = 0.5;
		}

	}

	void Tema2::FrameStart()
	{
		// clears the color buffer (using the previously set color) and depth buffer
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::ivec2 resolution = window->GetResolution();
		// sets the screen area where to draw
		glViewport(0, 0, resolution.x, resolution.y);
	}

	void Tema2::RenderPlane(float angularWingStep, float translate) {
		// Corpul

		{
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 2 * translate, 0));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(0.4, 0.2, 0.9));
			RenderSimpleMesh(meshes["cube"], shaders["ShaderTema2"], modelMatrix, glm::vec3(0, 4, 0));
		}

		// Aripa 1
		{
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.5, 2 * translate, 0));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(0.8, 0.2, 0.2));
			RenderSimpleMesh(meshes["cube"], shaders["ShaderTema2"], modelMatrix, glm::vec3(1, 0, 0));
		}

		// Aripa 2

		{
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(0.5, 2 * translate, 0));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(0.8, 0.2, 0.2));
			RenderSimpleMesh(meshes["cube"], shaders["ShaderTema2"], modelMatrix, glm::vec3(1, 0, 0));
		}

		// Coada
		{
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 2 * translate, -1));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2, 0.2, 0.2));
			RenderSimpleMesh(meshes["cube"], shaders["ShaderTema2"], modelMatrix, glm::vec3(0.3f, 0.74f, 0.3f));
		}

		// Elicea suport
		{
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 2 * translate, 1));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2, 0.2, 0.2));
			RenderSimpleMesh(meshes["cube"], shaders["ShaderTema2"], modelMatrix, glm::vec3(0.3f, 0.74f, 0));
		}

		// Elicea 
		{
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 2 * translate, 1.3));
			modelMatrix = glm::rotate(modelMatrix, angularWingStep, glm::vec3(0, 0, 1));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5, 0.1, 0.1));
			RenderSimpleMesh(meshes["cube"], shaders["ShaderTema2"], modelMatrix, glm::vec3(1, 0.4, 0));
		}
	}


	void Tema2::RenderCloud(float angularCloudStep, int i) {
		// Cube 1

		{
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(i % 10, 3.5, i));
			modelMatrix = glm::rotate(modelMatrix, RADIANS(30.0f), glm::vec3(i, i, 0));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2, 0.2, 0.2));
			RenderSimpleMesh(meshes["cube"], shaders["ShaderTema2"], modelMatrix, glm::vec3(0.3, 1, 0.9));
		}

		// Cube 2
		{
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(-(i % 10), 3.5, i));
			modelMatrix = glm::rotate(modelMatrix, angularCloudStep, glm::vec3(i, i, 1));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2, 0.2, 0.2));
			RenderSimpleMesh(meshes["cube"], shaders["ShaderTema2"], modelMatrix, glm::vec3(0.3, 1, 0.9));
		}

		// Cube 3

		{
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(i % 10, 3.5, i));
			modelMatrix = glm::rotate(modelMatrix, angularCloudStep, glm::vec3(i, i, 1));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2, 0.2, 0.2));
			RenderSimpleMesh(meshes["cube"], shaders["ShaderTema2"], modelMatrix, glm::vec3(0.3, 1, 0.9));
		}

		// Cube 4
		{
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(-(i % 10), 3.5, i));
			modelMatrix = glm::rotate(modelMatrix, RADIANS(60.0f), glm::vec3(i, i, 0));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2, 0.2, 0.2));
			RenderSimpleMesh(meshes["cube"], shaders["ShaderTema2"], modelMatrix, glm::vec3(0.3, 1, 0.9));
		}
	}

	void Tema2::Update(float deltaTimeSeconds)
	{

		angularWingStep = deltaTimeSeconds;
		translate = 1;


		if (angularWingStep >= -M_PI) {
			angularWingStep -= deltaTimeSeconds * 1000;
		}
		else if (angularWingStep <= M_PI) {
			angularWingStep += deltaTimeSeconds * 1000;
		}

		angularCloudStep = deltaTimeSeconds;


		if (angularCloudStep >= -M_PI) {
			angularCloudStep -= deltaTimeSeconds * 1000;
		}
		else if (angularCloudStep <= M_PI) {
			angularCloudStep += deltaTimeSeconds * 1000;
		}


		RenderPlane(angularWingStep, translate);
		int i;
		for (i = 0; i <= 10; i++) {

			RenderCloud(angularCloudStep, i);
		}

		{
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 1, 0));
			RenderSimpleMesh(meshes["sphere"], shaders["ShaderTema2"], modelMatrix, glm::vec3(0, 0, 1));
		}

		{
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(2, 0.5f, 0));
			modelMatrix = glm::rotate(modelMatrix, RADIANS(60.0f), glm::vec3(1, 0, 0));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));
			RenderSimpleMesh(meshes["box"], shaders["ShaderTema2"], modelMatrix, glm::vec3(1, 0, 0));
		}

		{
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(-2, 0.5f, 0));
			modelMatrix = glm::rotate(modelMatrix, RADIANS(60.0f), glm::vec3(1, 1, 0));
			RenderSimpleMesh(meshes["box"], shaders["ShaderTema2"], modelMatrix, glm::vec3(0, 0.5, 0));
		}

		// Render ground
		{
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0.01f, 0));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(0.25f));
			RenderSimpleMesh(meshes["plane"], shaders["ShaderTema2"], modelMatrix, glm::vec3(0.603, 0.603, 0.603));
		}

		// Render the point light in the scene
		{
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, lightPosition);
			modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1f));
			RenderMesh(meshes["sphere"], shaders["Simple"], modelMatrix);
		}
	}

	void Tema2::FrameEnd()
	{
		// DrawCoordinatSystem();
		DrawCoordinatSystem(camera_->GetViewMatrix(), camera_->GetProjectionMatrix());
	}

	Mesh* Tema2::CreateMesh(const char* name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned short>& indices)
	{
		unsigned int VAO = 0;
		// TODO: Create the VAO and bind it
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		// TODO: Create the VBO and bind it
		unsigned int VBO;
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		// TODO: Send vertices data into the VBO buffer
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

		// TODO: Crete the IBO and bind it
		unsigned int IBO;
		glGenBuffers(1, &IBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

		// TODO: Send indices data into the IBO buffer
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);

		// ========================================================================
		// This section describes how the GPU Shader Vertex Shader program receives data

		// set vertex position attribute
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 0);

		// set vertex normal attribute
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(sizeof(glm::vec3)));

		// set texture coordinate attribute
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3)));

		// set vertex color attribute
		//glm::vec3 color = glm::vec3(1.0f, 0.5f, 0.8f);
		//glUniform3fv(location, 1, glm::value_ptr(color));
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3) + sizeof(glm::vec2)));
		// ========================================================================

		// Unbind the VAO
		glBindVertexArray(0);

		// Check for OpenGL errors
		CheckOpenGLError();

		// Mesh information is saved into a Mesh object
		meshes[name] = new Mesh(name);
		meshes[name]->InitFromBuffer(VAO, static_cast<unsigned short>(indices.size()));
		meshes[name]->vertices = vertices;
		meshes[name]->indices = indices;
		return meshes[name];
	}

	void Tema2::RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color)
		{
			if (!mesh || !shader || !shader->GetProgramID())
				return;

			// render an object using the specified shader and the specified position
			glUseProgram(shader->program);

			// TODO : get shader location for uniform mat4 "Model"
			int location = glGetUniformLocation(shader->program, "Model");

			// TODO : set shader uniform "Model" to modelMatrix
			glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(modelMatrix));

			// TODO : get shader location for uniform mat4 "View"
			location = glGetUniformLocation(shader->program, "View");

			// TODO : set shader uniform "View" to viewMatrix
			glm::mat4 viewMatrix = camera_->GetViewMatrix();
			glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(viewMatrix));

			// TODO : get shader location for uniform mat4 "Projection"
			location = glGetUniformLocation(shader->program, "Projection");

			// TODO : set shader uniform "Projection" to projectionMatrix
			//glm::mat4 projectionMatrix = camera->GetProjectionMatrix();
			glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

			location = glGetUniformLocation(shader->program, "Color");
			glUniform3fv(location, 1, glm::value_ptr(color));


			// Draw the object
			glBindVertexArray(mesh->GetBuffers()->VAO);
			glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);
		}
	// Documentation for the input functions can be found in: "/Source/Core/Window/InputController.h" or
	// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/Window/InputController.h

	void Tema2::OnInputUpdate(float deltaTime, int mods)
	{
		float speed = 2;

		// move the camera only if MOUSE_RIGHT button is pressed
		if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
		{
			if (!window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT)) {
				if (mods == GLFW_MOD_CONTROL) {
					// Control light position using CTRL + W, A, S, D, E, Q
					glm::vec3 up = glm::vec3(0, 1, 0);
					glm::vec3 right = glm::vec3(1, 0, 0);
					glm::vec3 forward = glm::vec3(0, 0, 1);

					if (window->KeyHold(GLFW_KEY_W))
						lamp_position_ -= forward * deltaTime * kMovementSpeed;
					if (window->KeyHold(GLFW_KEY_A))
						lamp_position_ -= right * deltaTime * kMovementSpeed;
					if (window->KeyHold(GLFW_KEY_S))
						lamp_position_ += forward * deltaTime * kMovementSpeed;
					if (window->KeyHold(GLFW_KEY_D))
						lamp_position_ += right * deltaTime * kMovementSpeed;
					if (window->KeyHold(GLFW_KEY_E))
						lamp_position_ += up * deltaTime * kMovementSpeed;
					if (window->KeyHold(GLFW_KEY_Q))
						lamp_position_ -= up * deltaTime * kMovementSpeed;
				}
			}
			else if (stage_ == GameStage::LOOK_AROUND) {
				// Move camera using W, A, S, D, E, Q
				if (window->KeyHold(GLFW_KEY_W)) camera_->TranslateForward(deltaTime);
				if (window->KeyHold(GLFW_KEY_A)) camera_->TranslateRight(-deltaTime);
				if (window->KeyHold(GLFW_KEY_S)) camera_->TranslateForward(-deltaTime);
				if (window->KeyHold(GLFW_KEY_D)) camera_->TranslateRight(deltaTime);
				if (window->KeyHold(GLFW_KEY_Q)) camera_->TranslateUpword(-deltaTime);
				if (window->KeyHold(GLFW_KEY_E)) camera_->TranslateUpword(deltaTime);
			}

		}
	}

	void Tema2::OnKeyPress(int key, int mods)
	{
		// add key press event
	}

	void Tema2::OnKeyRelease(int key, int mods)
	{
		// add key release event
	}

	void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
	{
		// add mouse move event
		if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT)) {
	
			if (stage_ == GameStage::LOOK_AROUND) {
				// Move camera left/right/up/down
				camera_->RotateOy((float)-deltaX * kSensitivity);
				camera_->RotateOx((float)-deltaY * kSensitivity);
			}
		}
	}


	void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
	{
		// add mouse button press event
	}

	void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
	{
		// add mouse button release event
	}

	void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
	{
	}

	void Tema2::OnWindowResize(int width, int height)
	{
	}

	void Tema2::RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix)
	{
		if (!mesh || !shader || !shader->program)
			return;

		// render an object using the specified shader and the specified position
		shader->Use();
		glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera_->GetViewMatrix()));
		glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
		glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

		mesh->Render();
	}

	void Tema2::Break() {
		std::cout << std::endl
			<< " is breaking. Good luck!"
			<< std::endl;
		std::cout
			<< "Place the cue ball using the WASD keys, then press SPACE to start"
			<< std::endl
			<< "your shot. You can press H at any time to view detailed controls."
			<< std::endl;

		prev_stage_ = stage_ = GameStage::BREAK;
		camera_->TopDown();
	}

	void Tema2::LookAround() {
		if (print_help_[GameStage::LOOK_AROUND]) {
			std::cout << std::endl
				<< "Look around using the mouse and the WASDEQ keys" << std::endl
				<< "(first-person view) by pressing RIGHT_MOUSE_BUTTON. Press V "
				<< std::endl
				<< "again to go back to the previous mode." << std::endl;
			print_help_[GameStage::LOOK_AROUND] = false;
		}

		if (stage_ != GameStage::LOOK_AROUND) {
			prev_stage_ = stage_;
			stage_ = GameStage::LOOK_AROUND;
			camera_->FirstPerson();
		}
		else {
			switch (prev_stage_) {
			case GameStage::BREAK:
				Break();
				break;
			default:
				break;
			}
		}
	}
}