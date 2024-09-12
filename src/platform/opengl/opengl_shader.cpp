
#include "opengl_shader.h"
#include "prime/prime_assert.h"
#include "platform/glad/glad.h"
#include "prime/prime_device.h"

#include <vector>
#include <format>
#include <fstream>

namespace prime {

	static GLuint CreateShader(i32 type, const str& shader_source)
	{
		int status = GL_FALSE;
		int maxLength = 0;

		GLuint shader = glCreateShader(type);
		const char* source = shader_source.c_str();
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

	OpenGLShader::OpenGLShader(Device* device, const str& vSource, const str& pSource, b8 load)
	{
		if (load) {
			m_VShader = CreateShader(GL_VERTEX_SHADER, ReadFile(vSource));
			m_PShader = CreateShader(GL_FRAGMENT_SHADER, ReadFile(pSource));
		}
		else {
			m_VShader = CreateShader(GL_VERTEX_SHADER, vSource);
			m_PShader = CreateShader(GL_FRAGMENT_SHADER, pSource);
		}

		int status = GL_FALSE;
		int maxLength = 0;

		m_ID = glCreateProgram();
		glAttachShader(m_ID, m_VShader);
		glAttachShader(m_ID, m_PShader);
		glLinkProgram(m_ID);

		glValidateProgram(m_ID);
		glGetProgramiv(m_ID, GL_LINK_STATUS, &status);
		glGetProgramiv(m_ID, GL_INFO_LOG_LENGTH, &maxLength);
		if (status != GL_TRUE)
		{
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(m_ID, maxLength, &maxLength, infoLog.data());

			str msg = std::format("shader link error : {}", infoLog.data());
			PERROR(msg);

			glDeleteProgram(m_ID);
			m_ID = 0;
			PASSERT(false);
		}
		glDeleteShader(m_VShader);
		glDeleteShader(m_PShader);

		m_Handle.Ptr = &m_ID;
		m_Device = device;
	}

	OpenGLShader::~OpenGLShader()
	{
		if (m_Handle.Ptr) {
			if (m_Device->IsActiveShader(m_Handle)) {
				m_Device->SetActiveShader(nullptr);
			}
			glDeleteProgram(m_ID);
			m_Handle.Ptr = nullptr;
			m_ID = 0;
		}
	}

	void OpenGLShader::Bind()
	{
		if (!m_Device->IsActiveShader(m_Handle)) {
			m_Device->SetActiveShader(&m_Handle);
			glUseProgram(m_ID);
		}
	}

	void OpenGLShader::Unbind()
	{
		m_Device->SetActiveShader(nullptr);
		glUseProgram(0);
	}

	void OpenGLShader::setInt(const str& name, i32 data)
	{
		GLint location = GetUniformLocation(name);
		glUniform1i(location, data);
	}

	void OpenGLShader::setIntArray(const str& name, i32* data, u32 count)
	{
		GLint location = GetUniformLocation(name);
		glUniform1iv(location, count, data);
	}

	void OpenGLShader::setFloat(const str& name, f32 data)
	{
		GLint location = GetUniformLocation(name);
		glUniform1f(location, data);
	}

	void OpenGLShader::setFloat2(const str& name, f32 data, f32 data2)
	{
		GLint location = GetUniformLocation(name);
		glUniform2f(location, data, data2);
	}

	void OpenGLShader::setFloat3(const str& name, f32 data, f32 data2, f32 data3)
	{
		GLint location = GetUniformLocation(name);
		glUniform3f(location, data, data2, data3);
	}

	void OpenGLShader::setFloat4(const str& name, f32 data, f32 data2, f32 data3, f32 data4)
	{
		GLint location = GetUniformLocation(name);
		glUniform4f(location, data, data2, data3, data4);
	}
	
	void OpenGLShader::setMat2(const str& name, f32* data)
	{
		GLint location = GetUniformLocation(name);
		glUniformMatrix2fv(location, 1, GL_FALSE, data);
	}

	void OpenGLShader::setMat3(const str& name, f32* data)
	{
		GLint location = GetUniformLocation(name);
		glUniformMatrix3fv(location, 1, GL_FALSE, data);
	}

	void OpenGLShader::setMat4(const str& name, f32* data)
	{
		GLint location = GetUniformLocation(name);
		glUniformMatrix4fv(location, 1, GL_FALSE, data);
	}

	i32 OpenGLShader::GetUniformLocation(const str& name)
	{
		auto it = m_UniformLocations.find(name);
		if (it == m_UniformLocations.end())
		{
			m_UniformLocations[name] = glGetUniformLocation(m_ID, name.c_str());
		}

		return m_UniformLocations[name];
	}
}