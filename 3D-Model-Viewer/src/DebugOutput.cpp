#include <glad/glad.h>
#include <print>

#include "DebugOutput.h"

namespace {
	void GLAPIENTRY
		MessageCallback(GLenum /*source*/,
			GLenum type,
			GLuint /*id*/,
			GLenum severity,
			GLsizei /*length*/,
			const GLchar* message,
			const void* /*userParam*/)
	{
		std::println("GL CALLBACK : {} type = 0x{:x}, severity = 0x{:x}, message = {}",
			(type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
			type,
			severity,
			message);
	}
}

void DebugOutput::Enable()
{
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

	glDebugMessageCallback(MessageCallback, nullptr);
}