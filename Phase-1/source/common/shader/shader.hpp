#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>

#include <glad/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace our
{

    class ShaderProgram
    {

    private:
        // Shader Program Handle
        GLuint program;

    public:
        void create();
        void destroy();

        ShaderProgram() { program = 0; }
        ~ShaderProgram() { destroy(); }

        bool attach(const std::string &filename, GLenum type) const;

        bool link() const;

        // ================ < --- TODOes --- > ================ //

        void use()
        {
            // TODO: call opengl to use the program identified by this->program

            //==// Installs The Program object to the current state
            glUseProgram(program);
        }

        GLuint getUniformLocation(const std::string &name)
        {
            // TODO: call opengl to get the uniform location for the uniform defined by name from this->program

            return glGetUniformLocation(program, name.c_str());
        }

        void set(const std::string &uniform, GLfloat value)
        {
            // TODO: call opengl to set the value to the uniform defined by name

            //==// Set Val To The Uniform That Specified By Location
            glUniform1f(getUniformLocation(uniform), value);
        }

        void set(const std::string &uniform, glm::vec2 value)
        {
            // TODO: call opengl to set the value to the uniform defined by name

            //==// Set Val To Uniform Specified By Its Location
            glUniform2f(getUniformLocation(uniform), value.x, value.y);
        }

        void set(const std::string &uniform, glm::vec3 value)
        {
            // TODO: call opengl to set the value to the uniform defined by name

            //==// Set Val To Uniform Specified By Its Location
            glUniform3f(getUniformLocation(uniform), value.x, value.y, value.z);
        }

        void set(const std::string &uniform, glm::vec4 value)
        {
            // TODO: call opengl to set the value to the uniform defined by name

            //==// Set Val To Uniform Specified By Its Location
            glUniform4f(getUniformLocation(uniform), value.x, value.y, value.z, value.w);
        }

        // TODO: Delete the copy constructor and assignment operator

        ShaderProgram(const our::ShaderProgram &) = delete;
        ShaderProgram &operator=(const our::ShaderProgram &) = delete;

        //==// Question: Why do we do this? Hint: Look at the deconstructor
        /*
                Ans: Because if the ShaderProgram gets copied to another ShaderProgram,
                the "program" handler (ID) (Data member) would be copied. So now we have
                like two pointers point to the same data, and then when
                the destructor of the copied ShaderProgram calls openGL function to destroy
                the program, there will be nothing left to delete because it would be already
                deleted by the original program.
            */
    };

    // ================ < --- End --- > ================ //

}

#endif