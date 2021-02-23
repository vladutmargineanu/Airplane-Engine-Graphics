#pragma once
#include <Component/SimpleScene.h>
#include <Component/Transform/Transform.h>
#include <Core/GPU/Mesh.h>

#include <Laboratoare\Tema2\sea.h>
#include <Laboratoare\Tema2\ship.h>
#include "camera.h"
#include <include/math.h>


namespace pool {
	typedef struct {
		int shininess;
		float kd, ks;
	} MaterialProperties;

	enum class GameStage { BREAK, LOOK_AROUND };

	class Tema2 : public SimpleScene
	{
	public:
		Tema2();
		~Tema2();

		void Init() override;
		Mesh* CreateMesh(const char* name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned short>& indices);


	private:
		void FrameStart() override;
		void Update(float deltaTimeSeconds) override;
		void FrameEnd() override;

		void RenderPlane(float angularWingStep, float translate);
		void RenderCloud(float angularCloudStep, int deltaTimeSeconds);

		void RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix) override;
		void RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color = glm::vec3(1));
		void OnInputUpdate(float deltaTime, int mods) override;
		void OnKeyPress(int key, int mods) override;
		void OnKeyRelease(int key, int mods) override;
		void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
		void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
		void OnWindowResize(int width, int height) override;
		void Break();
		void LookAround();

		glm::mat4 projectionMatrix;
		glm::vec3 lightPosition;
		glm::vec3 lightDirection;
		unsigned int materialShininess;
		float materialKd;
		float materialKs;
		float angularWingStep = 3.14f;
		float angularCloudStep = 3.14f;
		float translate = 1;

		int isSpot = 0;
		float angle;

		pool::Camera* camera_;
		Mesh* lamp_;
		glm::vec3 lamp_position_;
		bool render_lamp_;
		static const float kMovementSpeed, kSensitivity;

		GameStage stage_, prev_stage_;
		std::unordered_map<GameStage, bool> print_help_;

	};

}
