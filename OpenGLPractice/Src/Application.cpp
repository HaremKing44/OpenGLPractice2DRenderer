#include "Shader.h"
#include <GLFW/glfw3.h>

#include <iostream>

void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
void ProcessInput(GLFWwindow* window);

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "Practice", NULL, NULL);
	if (!window)
	{
		std::cout << "Failed to create Window!" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to load GLAD!" << std::endl;
		return -1;
	}

	Shader ourShader("Res/Shader/Shader.vs", "Res/Shader/Shader.fs");
	Shader ourShader1("Res/Shader/Shader.vs", "Res/Shader/Shader1.fs");
	Shader ourShader2("Res/Shader/Shader.vs", "Res/Shader/Shader2.fs");
	Shader ourShader3("Res/Shader/Shader.vs", "Res/Shader/Shader3.fs");
	Shader ourShader4("Res/Shader/Shader.vs", "Res/Shader/Shader4.fs");

	float triangle1[]{
		0.8f, -0.4f, 0.f, 1.f, 1.f, 1.f,
		0.8f, 0.4f, 0.f, 1.f, 1.f, 1.f,
		0.6f, -0.4f, 0.f, 1.f, 1.f, 1.f
	};

	float triangle2[]{
		0.5f, -0.4f, 0.f, 1.f, 1.f, 1.f,
		0.7f, 0.4f, 0.f, 1.f, 1.f, 1.f,
		0.3f, 0.4f, 0.f, 1.f, 1.f, 1.f
	};

	float triangle3[]{
		0.4f, -0.4f, 0.f, 1.f, 1.f, 1.f,
		0.2f, 0.4f, 0.f, 1.f, 1.f, 1.f,
		-0.4f, 0.4f, 0.f, 1.f, 1.f, 1.f
	};

	float triangle4[]{
		0.3f, -0.4f, 0.f, 1.f, 1.f, 1.f,
		-0.5f, 0.4f, 0.f, 1.f, 1.f, 1.f,
		-0.7f, -0.4f, 0.f, 1.f, 1.f, 1.f
	};

	float triangle5[]{
		-0.8f, -0.4f, 0.f, 1.f, 1.f, 1.f,
		-0.6f, 0.4f, 0.f, 1.f, 1.f, 1.f,
		-0.8f, 0.4f, 0.f, 1.f, 1.f, 1.f
	};

	unsigned int vao[5], vbo[5];
	glGenVertexArrays(5, vao);
	glGenBuffers(5, vbo);

	//for triangle1.
	glBindVertexArray(vao[0]);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle1), &triangle1, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//for triangle2.
	glBindVertexArray(vao[1]);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle2), &triangle2, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//for triangle3.
	glBindVertexArray(vao[2]);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle3), &triangle3, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//for triangle4.
	glBindVertexArray(vao[3]);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[3]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle4), &triangle4, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//for triangle5.
	glBindVertexArray(vao[4]);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[4]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle5), &triangle5, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	float timeValue{}, timeValue1{}, timeValue2{}, timeValue3{}, timeValue4{};
	float colorValue{}, colorValue1{}, colorValue2{}, colorValue3{}, colorValue4{};

	float CurrentTime{}, DeltaTime{}, LastFrameTime{};

	while (!glfwWindowShouldClose(window))
	{
		//Calculate DeltaTime,
		CurrentTime = glfwGetTime();
		DeltaTime = CurrentTime - LastFrameTime;
		LastFrameTime = CurrentTime;

		ProcessInput(window);

		//To avoid Background triangle Duplicacy. 
		glClearColor(0.f, 0.f, 0.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);

		ourShader.Use();
		timeValue += DeltaTime;
		colorValue = (sin(timeValue) / 2.f) + 0.5f;
		ourShader.SetFloat("OurColor", colorValue);
		glBindVertexArray(vao[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		ourShader1.Use();
		if (timeValue > 1.f)
		{
			timeValue1 += DeltaTime;
			colorValue1 = (sin(timeValue1) / 2.f) + 0.5f;
		}
		else
		{
			colorValue1 = 0.f;
		}
		ourShader1.SetFloat("OurColor1", colorValue1);
		glBindVertexArray(vao[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		ourShader2.Use();
		if (timeValue1 > 1.f)
		{
			timeValue2 += DeltaTime;
			colorValue2 = (sin(timeValue2) / 2.f) + 0.5f;
		}
		else
		{
			colorValue2 = 0.f;
		}
		ourShader2.SetFloat("OurColor2", colorValue2);
		glBindVertexArray(vao[2]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		ourShader3.Use();
		if (timeValue2 > 1.f)
		{
			timeValue3 += DeltaTime;
			colorValue3 = (sin(timeValue3) / 2.f) + 0.5f;
		}
		else
		{
			colorValue3 = 0.f;
		}
		ourShader3.SetFloat("OurColor3", colorValue3);
		glBindVertexArray(vao[3]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		ourShader4.Use();
		if (timeValue3 > 1.f)
		{
			timeValue4 += DeltaTime;
			colorValue4 = (sin(timeValue4) / 2.f) + 0.5f;
		}
		else
		{
			colorValue4 = 0.f;
		}
		ourShader4.SetFloat("OurColor4", colorValue4);
		glBindVertexArray(vao[4]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	
	glDeleteVertexArrays(1, vao);
	glDeleteBuffers(1, vbo);
	ourShader.Delete();
	ourShader1.Delete();
	ourShader2.Delete();
	ourShader3.Delete();
	ourShader4.Delete();

	glfwTerminate();
	return 0;
}

void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void ProcessInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}