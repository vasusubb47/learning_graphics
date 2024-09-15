#include <glad/glad.h>
#include <iostream>

unsigned int complie_shader_code(const char* shader_code, unsigned int shader_type) {
	unsigned int shader_id;
	shader_id = glCreateShader(shader_type);

	glShaderSource(shader_id, 1, &shader_code, NULL);
	glCompileShader(shader_id);

	int success;
	char infoLog[512];
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(shader_id, 512, NULL, infoLog);
		std::cout << "Shader Compliation Failed \n Shader_Type : " 
			<< shader_type << "\n info : " << infoLog << "\n";
		return -1;
	}

	return shader_id;
}
