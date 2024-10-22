#include "star.h"
#include <cmath>

Star::Star(const glm::vec2& position, float rotation, float radius, float aspect)
    : _position(position), _rotation(rotation), _radius(radius) {
    
    _vertices.reserve(15);

    for (int i=0;i<5;i++){
        float outPoint = i * 2.0f * M_PI / 5.0f + M_PI / 10.0f + _rotation;
        _vertices.push_back(glm::vec2(_position.x + cos(outPoint) * _radius, _position.y + sin(outPoint) * _radius * aspect));

        float inPoint_1 = outPoint + M_PI * 3.0f / 5.0f;
        float inPoint_2 = outPoint + M_PI * 7.0f / 5.0f;
        float inRadius = _radius / 3.0f;
        _vertices.push_back(glm::vec2(_position.x + cos(inPoint_1) * inRadius, _position.y + sin(inPoint_1) * inRadius * aspect));
        _vertices.push_back(glm::vec2(_position.x + cos(inPoint_2) * inRadius, _position.y + sin(inPoint_2) * inRadius * aspect));
    }
    glGenVertexArrays(1, &_vao);
    glGenBuffers(1, &_vbo);

    glBindVertexArray(_vao);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(
        GL_ARRAY_BUFFER, sizeof(glm::vec2) * _vertices.size(), _vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}

Star::Star(Star&& rhs) noexcept
    : _position(rhs._position), _rotation(rhs._rotation), _radius(rhs._radius), _vao(rhs._vao),
      _vbo(rhs._vbo) {
    rhs._vao = 0;
    rhs._vbo = 0;
}

Star::~Star() {
    if (_vbo) {
        glDeleteVertexArrays(1, &_vbo);
        _vbo = 0;
    }

    if (_vao) {
        glDeleteVertexArrays(1, &_vao);
        _vao = 0;
    }
}

void Star::draw() const {
    glBindVertexArray(_vao);
    glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(_vertices.size()));
}