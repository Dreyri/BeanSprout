#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <OpenGL/gl.h>
#include <map>

namespace BS
{

class ShaderProgram
{
private:
    GLuint mProgramId;
    GLuint mVertexShaderId;
    GLuint mFragmentShaderId;

    std::map<std::string, int> mAttributeMap;
    std::map<std::string, int> mUniformMap;

    bool mInitialised;
public:
    ShaderProgram(const std::string& vsSource, const std::string& fsSource);
    ~ShaderProgram();

    void freeProgram();

    bool bind() const;
    void unbind() const;

    GLuint getProgramId() const;

    GLuint attribute(const std::string& attributeName) const;
    GLuint uniform(const std::string& uniformName) const;

    int addAttribute(const std::string& attributeName);
    int addUniform(const std::string& uniformName);

private:
    GLuint compileShader(const std::string& shaderSource, GLenum shaderType);
    void initialise(const std::string& vsSource, const std::string& fsSource);
};
}

#endif // SHADERPROGRAM_H
