#include "MainGame.h"
#include "Camera.h"
#include <iostream>
#include <string>

Transform transform;

MainGame::MainGame()
{
	_gameState = GameState::PLAY;
	Display* _gameDisplay = new Display(); 
    Mesh* mesh1();
	Mesh* mesh2();
	Mesh* mesh3();
	Audio* audioDevice();
	Texture* texture(); 
	Texture* texture1(); 
	Overlay* overlay(); 
	Shader* shaderG();
	Shader* shaderBlur();
	Shader* shaderToon();
	Shader* shaderRim();
	Shader* barrieShader();
}

MainGame::~MainGame() 
{
}

void MainGame::run()
{
	initSystems(); 
	gameLoop();


}

void MainGame::initSystems()
{
	_gameDisplay.initDisplay(); 
	whistle = audioDevice.loadSound("..\\res\\bang.wav");
	backGroundMusic = audioDevice.loadSound("..\\res\\background.wav");
	texture.init("..\\res\\bricks.jpg");
	texture1.init("..\\res\\water.jpg"); 


	shaderSkyBox.init("..\\res\\shaderSkyboxxx.vert", "..\\res\\shaderSkyboxxx.frag"); 

	
	
	shaderRef.init("..\\res\\shaderReflect.vert", "..\\res\\shaderReflect.frag"); 
	shaderExplode.init2("..\\res\\shaderExplode.vert", "..\\res\\shaderExplode.frag", "..\\res\\shaderExplode.geom");
	barrieShader.init("..\\res\\barrieShader.vert", "..\\res\\barrieShader.frag");
	overlay.init("..\\res\\bricks.jpg");

	mesh1.loadModel("..\\res\\Hand.obj");
	mesh2.loadModel("..\\res\\tree.obj");
	mesh3.loadModel("..\\res\\monkey.obj");
	
	myCamera.initCamera(glm::vec3(0, 0, -10.0), 70.0f, (float)_gameDisplay.getWidth()/_gameDisplay.getHeight(), 0.01f, 1000.0f);

	counter = 1.0f;

	vector<std::string> faces
	{
		"..\\res\\skybox\\right.jpg",
		"..\\res\\skybox\\left.jpg",
		"..\\res\\skybox\\top.jpg",
		"..\\res\\skybox\\bottom.jpg",
		"..\\res\\skybox\\front.jpg",
		"..\\res\\skybox\\back.jpg"
	};
	cubemapTexture = skyBoxTexture.loadCubemap(faces);
	
	mesh2Texture = skyBoxTexture.loadCubemap(faces); //---------------------------------------------------------------
	//an attempt to texture the cube that then became the tree after I failed to texture it------------------------------

	float skyboxVertices[] = {
		         
		-6.0f,  6.0f, -6.0f,
		-6.0f, -6.0f, -6.0f,
		 6.0f, -6.0f, -6.0f,
		 6.0f, -6.0f, -6.0f,
		 6.0f,  6.0f, -6.0f,
		-6.0f,  6.0f, -6.0f,

		-6.0f, -6.0f,  6.0f,
		-6.0f, -6.0f, -6.0f,
		-6.0f,  6.0f, -6.0f,
		-6.0f,  6.0f, -6.0f,
		-6.0f,  6.0f,  6.0f,
		-6.0f, -6.0f,  6.0f,

		6.0f, -6.0f, -6.0f,
		6.0f, -6.0f,  6.0f,
		6.0f,  6.0f,  6.0f,
		6.0f,  6.0f,  6.0f,
		6.0f,  6.0f, -6.0f,
		6.0f, -6.0f, -6.0f,

		-6.0f, -6.0f,  6.0f,
		-6.0f,  6.0f,  6.0f,
		 6.0f,  6.0f,  6.0f,
		 6.0f,  6.0f,  6.0f,
		 6.0f, -6.0f,  6.0f,
		-6.0f, -6.0f,  6.0f,

		-6.0f,  6.0f, -6.0f,
		 6.0f,  6.0f, -6.0f,
		 6.0f,  6.0f,  6.0f,
		 6.0f,  6.0f,  6.0f,
		-6.0f,  6.0f,  6.0f,
		-6.0f,  6.0f, -6.0f,

		-6.0f, -6.0f, -6.0f,
		-6.0f, -6.0f,  6.0f,
		 6.0f, -6.0f, -6.0f,
		 6.0f, -6.0f, -6.0f,
		-6.0f, -6.0f,  6.0f,
		 6.0f, -6.0f,  6.0f
	};

	
	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);
	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

}

void MainGame::setExplosionShader() {
	shaderExplode.setMat4("transform", transform.GetModel());
	shaderExplode.setFloat("time", 1.0f + (counter * 5.0f));
}

void MainGame::gameLoop()
{
	while (_gameState != GameState::EXIT)
	{
		processInput();
		drawGame();
		playAudio(backGroundMusic, glm::vec3(0.0f,0.0f,0.0f));
		collision(mesh1.getSpherePos(), mesh1.getSphereRadius(), mesh2.getSpherePos(), mesh2.getSphereRadius());
	}
}



void MainGame::processInput()
{
	SDL_Event evnt;

	while(SDL_PollEvent(&evnt))
	{
		switch (evnt.type)
		{
			case SDL_QUIT:
				_gameState = GameState::EXIT;
				break;
				
				//--------------------------------------------------------------------------------------------------
				//an attempt to make the model look like the heat is going up and down when the player presses a key
			//case SDL_KEYDOWN:
			//	if (SDLK_d)
			//	{
			//		heatRise = true;
			//		heatFall = false;
			//	}
			//	else if (SDLK_a)
			//	{
			//		heatRise = false;
			//		heatFall = true;
			//	}
				//--------------------------------------------------------------------------------------------------
		}
	}
	
}

bool MainGame::collision(glm::vec3 m1Pos, float m1Rad, glm::vec3 m2Pos, float m2Rad)
{
	float distance = glm::sqrt((m2Pos.x - m1Pos.x) * (m2Pos.x - m1Pos.x) + (m2Pos.y - m1Pos.y) * (m2Pos.y - m1Pos.y) + (m2Pos.z - m1Pos.z) * (m2Pos.z - m1Pos.z));

	if (distance < (m1Rad + m2Rad))
	{
		return true;
	}
	else
	{
		return false;
	}
}


void MainGame::SkyBox()
{
	glDepthFunc(GL_LEQUAL);
	shaderSkyBox.Bind();
	shaderSkyBox.setInt("skybox", 0);
	
	shaderSkyBox.setMat4("view", myCamera.GetView());
	shaderSkyBox.setMat4("projection", myCamera.GetProjection());
	
	glBindVertexArray(skyboxVAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	glDepthFunc(GL_LESS); 
}

void MainGame::boxTexture()
{
	//trying to figure out how to attach this skybox texture to the cube in the scene...
	glDepthFunc(GL_LEQUAL);
	shaderSkyBox.Bind();
	shaderSkyBox.setInt("skybox", 0);

	shaderSkyBox.setMat4("view", myCamera.GetView());
	shaderSkyBox.setMat4("projection", myCamera.GetProjection());

	glBindVertexArray(skyboxVAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
	
	glBindVertexArray(0);
	glDepthFunc(GL_LESS);
}




void MainGame::playAudio(unsigned int Source, glm::vec3 pos)
{
	ALint state; 
	alGetSourcei(Source, AL_SOURCE_STATE, &state);
}



//setting my shader--------------------------------------------------------------------------------------------------------
void MainGame::setBarrieShader()
{


	//if (heatRise == true)
	//{
		barrieShader.setVec3("heatIntensity", glm::vec3(sinf(counter / 2), sinf(counter / 4), sinf(counter / 6)));
	//}
	//else if (heatFall == true)
	//{
	//	barrieShader.setVec3("lightDirection", glm::vec3(0.1, 0.1, 0.1));
	//}
	
	//barrieShader.setVec3("colourChange", glm::vec3(counter, counter, counter)); nothing happens...
	//tried to make the colours of the model fluctuate and change----------------------------------

	//see lines 164-175 for explanation of the commented-out if statements-------------------------

}



void MainGame::setRefShader()
{
	shaderRef.setMat4("model", transform.GetModel());
	shaderRef.setMat4("view", myCamera.GetView());
	shaderRef.setMat4("projection", myCamera.GetProjection());
	shaderRef.setVec3("cameraPos", myCamera.getPos());
	shaderRef.setInt("skybox", 0);

}

void MainGame::drawGame()
{
	_gameDisplay.clearDisplay(0.0f, 0.0f, 0.0f, 1.0f);
	
	SkyBox();

	//TREE IS EXPLODING SHADER------------------------------------------------------------------------------------
	//HAND IS ENVIRONMENT MAPPING SHADER--------------------------------------------------------------------------
	//MONKEY IS MY OWN SHADER-------------------------------------------------------------------------------------

	//model 1
	//----------------------------------------------------------------------
	transform.SetPos(glm::vec3(3, 0, -3));
	transform.SetRot(glm::vec3(0, counter / 2, 1.5));
	transform.SetScale(glm::vec3(6, 6, 6));
		
    shaderRef.Bind();
	setRefShader();
	shaderRef.Update(transform, myCamera);
	texture.Bind(0);
	mesh1.draw();

	//model 2
	//----------------------------------------------------------------------
	transform.SetPos(glm::vec3(0, -2, -1));
	transform.SetRot(glm::vec3(0, 0, 0));
	transform.SetScale(glm::vec3(0.15, 0.15, 0.15));

	overlay.drawOL(GL_REPEAT);
	shaderExplode.Bind();
	setExplosionShader();
	shaderExplode.Update(transform, myCamera);
	texture1.Bind(0); //cannot figure out how to make this texture work
	mesh2.draw();
	mesh2.updateSphereData(*transform.GetPos(), 0.1f);

	//model 3
	//----------------------------------------------------------------------	
	transform.SetPos(glm::vec3(-4, (sinf(counter) / 2), -1));
	transform.SetRot(glm::vec3(counter / 8, counter / 10, 0.0));
	transform.SetScale(glm::vec3(1, 1, 1));
	
	barrieShader.Bind();
	setBarrieShader();
	barrieShader.Update(transform, myCamera);
	
	mesh3.draw();
	
	//----------------------------------------------------------------------
	counter = counter + 0.01f;
	glEnableClientState(GL_COLOR_ARRAY); 
	glEnd();
	_gameDisplay.swapBuffer();
} 