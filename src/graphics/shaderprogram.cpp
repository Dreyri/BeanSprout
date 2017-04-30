#include "shaderprogram.h"
#include <string>
#include <iostream>
#include <OpenGL/gl.h>

namespace BS
{
ShaderProgram::ShaderProgram(const std::string& vsSource, const std::string& fsSource)
    : mInitialised(false)
{
    mProgramId = glCreateProgram();
    glUseProgram(mProgramId);
    initialise(vsSource, fsSource);
}

ShaderProgram::~ShaderProgram()
{
    freeProgram();
}

void ShaderProgram::freeProgram()
{
    unbind();
    glDeleteProgram(mProgramId);
}

bool ShaderProgram::bind() const
{
    if(mInitialised)
    {
        glUseProgram(mProgramId);
        return true;
    }
    else
    {
        std::cout << "W: couldn't bind program, shader not initialised!" << std::endl;
        return false;
    }
}
void ShaderProgram::unbind() const
{
    glUseProgram(0);
}

GLuint ShaderProgram::getProgramId() const
{
    return mProgramId;
}

GLuint ShaderProgram::compileShader(const std::string& shaderSource, GLenum shaderType)
{
    std::string shaderTypeString;

    switch(shaderType)
    {
    case GL_VERTEX_SHADER:
        shaderTypeString = "GL_VERTEX_SHADER";
        break;
    case GL_FRAGMENT_SHADER:
        shaderTypeString = "GL_FRAGMENT_SHADER";
        break;
    default:
        std::cout << "E: Shader type not support or bad shader!" << std::endl;
        break;
    }

    GLuint shaderId = glCreateShader(shaderType);
    if(shaderId == 0)
    {
        std::cout << "E: could not create shader of type " << shaderTypeString << std::endl;
        return 0;
    }
    const char* shaderSourceCstr = shaderSource.c_str();

    glShaderSource(shaderId, 1, &shaderSourceCstr, NULL);
    glCompileShader(shaderId);

    GLint shaderStatus;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &shaderStatus);

    if(shaderStatus == GL_FALSE)
    {
        std::cout << "E: Compilation failed!" << std::endl;
        return 0;
    }
    else
    {
        std::cout << "Shader compilation successful!" << std::endl;
    }

    return shaderId;
}

void ShaderProgram::initialise(const std::string& vsSource, const std::string& fsSource)
{
    mVertexShaderId = compileShader(vsSource, GL_VERTEX_SHADER);
    mFragmentShaderId = compileShader(fsSource, GL_FRAGMENT_SHADER);

    if(mVertexShaderId == 0 || mFragmentShaderId == 0)
    {
        std::cout << "E: Could not initialise shader!" << std::endl;
    }

    glAttachShader(mProgramId, mVertexShaderId);
    glAttachShader(mProgramId, mFragmentShaderId);

    glLinkProgram(mProgramId);

    //can detach now as no longer required
    glDetachShader(mProgramId, mVertexShaderId);
    glDetachShader(mProgramId, mFragmentShaderId);

    GLint programLinkSuccess = GL_FALSE;
    glGetProgramiv(mProgramId, GL_LINK_STATUS, &programLinkSuccess);
    if(programLinkSuccess == GL_TRUE)
    {
        std::cout << "Shader program link successful!" << std::endl;
    }
    else
    {
        std::cout << "E: Shader program link failed!" << std::endl;
        return;
    }

    glValidateProgram(mProgramId);

    GLint programValidationStatus;
    glGetProgramiv(mProgramId, GL_VALIDATE_STATUS, &programValidationStatus);
    if(programValidationStatus == GL_TRUE)
    {
        std::cout << "Shader program validation successful!" << std::endl;
    }
    else
    {
        std::cout << "E: Shader program validation failed!" << std::endl;
    }

    mInitialised = true;
}
}
