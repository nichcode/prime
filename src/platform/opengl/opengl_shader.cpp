
#include "opengl_shader.h"
#include "prime/assert.h"
#include "platform/glad/glad.h"

#include <vector>
#include <format>
#include <fstream>

namespace prime {

	static GLuint create_shader(i32 type, const str& shader_source)
	{
		int status = GL_FALSE;
		int max_length = 0;

		GLuint shader = glCreateShader(type);
		const char* source = shader_source.c_str();
		glShaderSource(shader, 1, &source, NULL);
		glCompileShader(shader);
		glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &max_length);

		if (status != GL_TRUE)
		{
			std::vector<GLchar> info_log(max_length);
			glGetShaderInfoLog(shader, max_length, &max_length, info_log.data());

			if (type == GL_VERTEX_SHADER)
			{
				str msg = std::format("Vertex shader compilation error : {}", info_log.data());
				PERROR(msg);
			}
			else if (type == GL_FRAGMENT_SHADER)
			{
				str msg = std::format("Pixel shader compilation error : {}", info_log.data());
				PERROR(msg);
			}
			PASSERT(false);
		}
		return shader;
	}

	static str read_file(const str& filepath)
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

	OpenGLShader::OpenGLShader(const str& v_source, const str& p_source, b8 load)
	{
		if (load) {
			m_v_shader = create_shader(GL_VERTEX_SHADER, read_file(v_source));
			m_p_shader = create_shader(GL_FRAGMENT_SHADER, read_file(p_source));
		}
		else {
			m_v_shader = create_shader(GL_VERTEX_SHADER, v_source);
			m_p_shader = create_shader(GL_FRAGMENT_SHADER, p_source);
		}

		int status = GL_FALSE;
		int max_length = 0;

		m_id = glCreateProgram();
		glAttachShader(m_id, m_v_shader);
		glAttachShader(m_id, m_p_shader);
		glLinkProgram(m_id);

		glValidateProgram(m_id);
		glGetProgramiv(m_id, GL_LINK_STATUS, &status);
		glGetProgramiv(m_id, GL_INFO_LOG_LENGTH, &max_length);
		if (status != GL_TRUE)
		{
			std::vector<GLchar> info_log(max_length);
			glGetProgramInfoLog(m_id, max_length, &max_length, info_log.data());

			str msg = std::format("shader link error : {}", info_log.data());
			PERROR(msg);

			glDeleteProgram(m_id);
			m_id = 0;
			PASSERT(false);
		}
		glDeleteShader(m_v_shader);
		glDeleteShader(m_p_shader);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_id);
		m_id = 0;
	}

	void OpenGLShader::bind()
	{
		glUseProgram(m_id);
	}

	void OpenGLShader::unbind()
	{
		glUseProgram(0);
	}

	void OpenGLShader::set_int(const str& name, i32 data)
	{
		GLint location = get_uniform_location(name);
		glUniform1i(location, data);
	}

	void OpenGLShader::set_int_array(const str& name, i32* data, u32 count)
	{
		GLint location = get_uniform_location(name);
		glUniform1iv(location, count, data);
	}

	void OpenGLShader::set_float(const str& name, f32 data)
	{
		GLint location = get_uniform_location(name);
		glUniform1f(location, data);
	}

	void OpenGLShader::set_float2(const str& name, f32 data, f32 data2)
	{
		GLint location = get_uniform_location(name);
		glUniform2f(location, data, data2);
	}

	void OpenGLShader::set_float3(const str& name, f32 data, f32 data2, f32 data3)
	{
		GLint location = get_uniform_location(name);
		glUniform3f(location, data, data2, data3);
	}

	void OpenGLShader::set_float4(const str& name, f32 data, f32 data2, f32 data3, f32 data4)
	{
		GLint location = get_uniform_location(name);
		glUniform4f(location, data, data2, data3, data4);
	}
	
	void OpenGLShader::set_mat2(const str& name, f32* data)
	{
		GLint location = get_uniform_location(name);
		glUniformMatrix2fv(location, 1, GL_FALSE, data);
	}

	void OpenGLShader::set_mat3(const str& name, f32* data)
	{
		GLint location = get_uniform_location(name);
		glUniformMatrix3fv(location, 1, GL_FALSE, data);
	}

	void OpenGLShader::set_mat4(const str& name, f32* data)
	{
		GLint location = get_uniform_location(name);
		glUniformMatrix4fv(location, 1, GL_FALSE, data);
	}

	i32 OpenGLShader::get_uniform_location(const str& name)
	{
		auto it = m_uniform_locations.find(name);
		if (it == m_uniform_locations.end())
		{
			m_uniform_locations[name] = glGetUniformLocation(m_id, name.c_str());
		}

		return m_uniform_locations[name];
	}
}