#include "shader.h"

#define GLOBAL_FILE_DIR "../data"
#define LOCAL_FILE_DIR "data/"

GLuint Shader::loadShader(GLenum eShaderType, const std::string &fileName){
    std::string strFilename = FindFileOrThrow(fileName);
    std::ifstream shaderFile(strFilename.c_str());
    std::stringstream shaderData;
    shaderData << shaderFile.rdbuf();
    shaderFile.close();
    
    GLuint shader = glCreateShader(eShaderType);
    std::string shaderString = shaderData.str();
    const char *strFileData = shaderString.c_str();
    glShaderSource(shader, 1, &strFileData, NULL);
    glCompileShader(shader);

    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if(status == GL_FALSE){
        GLint infoLogLength;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

        GLchar *strInfoLog = new GLchar[infoLogLength + 1];
        glGetShaderInfoLog(shader, infoLogLength, NULL, strInfoLog);

        const char * strShaderType = NULL;
        switch(eShaderType){
            case GL_VERTEX_SHADER: strShaderType = "vertex"; break;
            case GL_FRAGMENT_SHADER: strShaderType = "fragment"; break;
        }

        fprintf(stderr, "Compile failure in %s shader:\n%s\n", strShaderType, strInfoLog);
        delete[] strInfoLog;

    }

    return shader;
}

GLuint Shader::createProgram(const std::vector<GLuint> &shaderList){
    GLuint program = glCreateProgram();

    for(size_t iLoop = 0; iLoop < shaderList.size(); iLoop++){
        glAttachShader(program, shaderList[iLoop]);
    }
    glLinkProgram(program);
    GLint status;
    glGetProgramiv(program, GL_LINK_STATUS, &status);

    if(status == GL_FALSE){
        GLint infoLogLength;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);
        
        GLchar *strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(program, infoLogLength, NULL, strInfoLog);
		fprintf(stderr, "Linker failure: %s\n", strInfoLog);
		delete[] strInfoLog;
    }

    setUniformsCache(program);

    for(size_t iLoop = 0; iLoop < shaderList.size(); iLoop++){
        glDetachShader(program, shaderList[iLoop]);
    }
    return program;
}

void Shader::load(const std::string &vShaderFilename, const std::string &fShaderFilename){
    std::vector<GLuint> shaders;
    shaders.push_back(loadShader(GL_VERTEX_SHADER, vShaderFilename));
    shaders.push_back(loadShader(GL_FRAGMENT_SHADER, fShaderFilename));

    program = createProgram(shaders);
    std::for_each(shaders.begin(), shaders.end(), glDeleteShader);
}

void Shader::setUniformsCache(GLuint &prog){
    GLint numUniforms = 0;
    glGetProgramiv(prog, GL_ACTIVE_UNIFORMS, &numUniforms);
    std::cout << numUniforms << std::endl;
    GLint uniformMaxLength = 0;
    glGetProgramiv(prog, GL_ACTIVE_UNIFORM_MAX_LENGTH, &uniformMaxLength);
    
    GLint count = -1;
    GLenum type = 0;
    GLsizei length ;
    GLint location;
    std::vector<GLchar> uniformName(uniformMaxLength);

    for(GLint i = 0; i < numUniforms; i++){
        glGetActiveUniform(prog, i,uniformMaxLength, &length, &count, &type, uniformName.data());
        std::string name(uniformName.begin(), uniformName.begin()+length);
        location = glGetUniformLocation(prog, name.c_str());
        uniformsCache[name] = location;
        std::cout << name << std::endl;
        auto arrayPos = name.find('[');
        if(arrayPos != std::string::npos){
            name = name.substr(0, arrayPos);
            uniformsCache[name] = location;
        }
    }
    for ( auto it = uniformsCache.begin(); it != uniformsCache.end(); ++it ){
        std::cout << " " << it->first << ":" << it->second;
        std::cout << std::endl;
    }
}

GLint Shader::getUniformLocation(const std::string &name) const{
    auto it = uniformsCache.find(name);
    
    if(it == uniformsCache.end()){
        return -1;
    } else {
        return it->second;
    }
}

void Shader::setUniform1i(const std::string &name, int v1) const {
   int loc = getUniformLocation(name);
   if(loc != -1) glUniform1i(loc, v1);
}

void Shader::setUniform1f(const std::string &name, float v1) const {
    int loc = getUniformLocation(name);
    if(loc != -1) glUniform1f(loc, v1);
}

void Shader::setUniformTexture(const std::string &name, const GLuint &texId, int slot) const{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, texId);
    setUniform1i(name, slot);
    glActiveTexture(GL_TEXTURE0);
}

std::string Shader::FindFileOrThrow(const std::string &strBasename){
    std::string strFilename = LOCAL_FILE_DIR + strBasename;
    std::ifstream testFile(strFilename.c_str());
    if(testFile.is_open()){
        return strFilename;
    }
    strFilename = GLOBAL_FILE_DIR + strBasename;
    testFile.open(strFilename.c_str());
    if(testFile.is_open()){
        return strFilename;
    }
    throw std::runtime_error("Could not find the file " + strBasename);

}
