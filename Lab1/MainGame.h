#pragma once
#include <SDL\SDL.h>
#include <GL/glew.h>
#include "Display.h" 
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include "transform.h"
#include "Audio.h"
#include "Overlay.h"

enum class GameState{PLAY, EXIT};

class MainGame
{
public:
	MainGame();
	~MainGame();

	void run();

private:

	void initSystems();
	void setExplosionShader();
	void processInput();
	void gameLoop();
	void drawGame();
	void playAudio(unsigned int Source, glm::vec3 pos);
	void setADSLighting();
	void setRefShader();
	void setBarrieShader();

	bool collision(glm::vec3 m1Pos, float m1Rad, glm::vec3 m2Pos, float m2Rad);

	//bool heatRise = true;
	//bool heatFall;

	void SkyBox();
	void boxTexture();
	
	GLuint skyboxVAO, skyboxVBO, cubemapTexture, mesh2Texture;
	vector<std::string> faces;

	void setUniform(Shader currentShader, const char* name, float x, float y, float z);
	void setUniform(Shader currentShader, const char* name, const glm::vec3& v);
	void setUniform(GLuint currentShader, glm::vec4 values, const GLchar* uniformName, const GLchar* uniformVarialbeName);
	void setUniform(Shader currentShader, const char* name, const glm::mat4& m);
	void setUniform(Shader currentShader, const char* name, const glm::mat3& m);
	void setUniform(Shader currentShader, const char* name, float val);
	void setUniform(Shader currentShader, const char* name, int val);
	void setUniform(Shader currentShader, const char* name, bool val);
	void printActiveUniforms(Shader currentShader);
	void printActiveAttribs(Shader currentShader);

	Display _gameDisplay;
	GameState _gameState;
	Mesh mesh1;
	Mesh mesh2;
	Mesh mesh3;

	Texture texture;
	Texture texture1;
	Texture skyBoxTexture;
	Shader shaderExplode;
	Shader barrieShader;
	Overlay overlay;
	Shader shaderSkyBox;
	Shader shaderRef;
	

	glm::mat4 modelView;

	Camera myCamera;
	Audio audioDevice;

	float counter;
	unsigned int whistle;
	unsigned int backGroundMusic;
};

