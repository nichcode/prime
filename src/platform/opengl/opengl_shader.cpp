
#include "opengl_shader.h"
#include "prime/prime_assert.h"
#include "platform/glad/glad.h"
#include "prime/prime_device.h"

#include <vector>
#include <format>
#include <fstream>

namespace prime {

	static GLuint CreateShader(i32 type, const str& shaderSource)
	{
		int status = GL_FALSE;
		int maxLength = 0;

		GLuint shader = glCreateShader(type);
		const char* source = shaderSource.c_str();
		glShaderSource(shader, 1, &source, NULL);
		glCompileShader(shader);
		glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

		if (status != GL_TRUE)
		{
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(shader, maxLength, &maxLength, infoLog.data());

			if (type == GL_VERTEX_SHADER)
			{
				str msg = std::format("Vertex shader compilation error : {}", infoLog.data());
				PERROR(msg);
			}
			else if (type == GL_FRAGMENT_SHADER)
			{
				str msg = std::format("Pixel shader compilation error : {}", infoLog.data());
				PERROR(msg);
			}
			PASSERT(false);
		}
		return shader;
	}

	static str ReadFile(const str& filepath)
	{
		str result;
		str msg = std::format("Could not read from file '{0}'", filepath);
		std::ifstream in(filepath, std::ios::in | std::ios::binary); // ifstream closes itself due to RAII
		if (in) {
			in.seekg(0, std::ios::end);
			size_t size = in.tellg();
			if (size != -1) {
				result.resize(size);
				in.seekg(0, std::ios::beg);
				in.read(&result[0], size);
			}
			else {
				PERROR(msg);
			}
		}
		else {
			PERROR(msg);
		}

		return result;
	}

	OpenGLShader::OpenGLShader(const str& vSource, const str& pSource, b8 load)
	{
		if (load) {
			m_vShader = CreateShader(GL_VERTEX_SHADER, ReadFile(vSource));
			m_pShader = CreateShader(GL_FRAGMENT_SHADER, ReadFile(pSource));
		}
		else {
			m_vShader = CreateShader(GL_VERTEX_SHADER, vSource);
			m_pShader = CreateShader(GL_FRAGMENT_SHADER, pSource);
		}

		int status = GL_FALSE;
		int maxLength = 0;

		m_id = glCreateProgram();
		glAttachShader(m_id, m_vShader);
		glAttachShader(m_id, m_pShader);
		glLinkProgram(m_id);

		glValidateProgram(m_id);
		glGetProgramiv(m_id, GL_LINK_STATUS, &status);
		glGetProgramiv(m_id, GL_INFO_LOG_LENGTH, &maxLength);
		if (status != GL_TRUE)
		{
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(m_id, maxLength, &maxLength, infoLog.data());

			str msg = std::format("shader link error : {}", infoLog.data());
			PERROR(msg);

			glDeleteProgram(m_id);
			m_id = 0;
			PASSERT(false);
		}
		glDeleteShader(m_vShader);
		glDeleteShader(m_pShader);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_id);
		m_id = 0;
	}

	void OpenGLShader::Bind()
	{
		glUseProgram(m_id);
	}

	void OpenGLShader::Unbind()
	{
		glUseProgram(0);
	}

	void OpenGLShader::SetInt(const str& name, i32 data)
	{
		GLint location = GetUniformLocation(name);
		glUniform1i(location, data);
	}

	void OpenGLShader::SetIntArray(const str& name, i32* data, u32 count)
	{
		GLint location = GetUniformLocation(name);
		glUniform1iv(location, count, data);
	}

	void OpenGLShader::SetFloat(const str& name, f32 data)
	{
		GLint location = GetUniformLocation(name);
		glUniform1f(location, data);
	}

	void OpenGLShader::SetFloat2(const str& name, f32 data, f32 data2)
	{
		GLint location = GetUniformLocation(name);
		glUniform2f(location, data, data2);
	}

	void OpenGLShader::SetFloat3(const str& name, f32 data, f32 data2, f32 data3)
	{
		GLint location = GetUniformLocation(name);
		glUniform3f(location, data, data2, data3);
	}

	void OpenGLShader::SetFloat4(const str& name, f32 data, f32 data2, f32 data3, f32 data4)
	{
		GLint location = GetUniformLocation(name);
		glUniform4f(location, data, data2, data3, data4);
	}
	
	void OpenGLShader::SetMat2(const str& name, f32* data)
	{
		GLint location = GetUniformLocation(name);
		glUniformMatrix2fv(location, 1, GL_FALSE, data);
	}

	void OpenGLShader::SetMat3(const str& name, f32* data)
	{
		GLint location = GetUniformLocation(name);
		glUniformMatrix3fv(location, 1, GL_FALSE, data);
	}

	void OpenGLShader::SetMat4(const str& name, f32* data)
	{
		GLint location = GetUniformLocation(name);
		glUniformMatrix4fv(location, 1, GL_FALSE, data);
	}

	i32 OpenGLShader::GetUniformLocation(const str& name)
	{
		auto it = m_uniformLocations.find(name);
		if (it == m_uniformLocations.end())
		{
			m_uniformLocations[name] = glGetUniformLocation(m_id, name.c_str());
		}

		return m_uniformLocations[name];
	}
}