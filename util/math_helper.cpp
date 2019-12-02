//
// C++ Implementation by Ajay Bhaga
//
// Modified Genetic Algorithm
// Based on design of Samuel Arzt (March 2017)
//

#include "math_helper.h"

MathHelper::MathHelper() {
}

MathHelper::~MathHelper() {
}

// The standard sigmoid function.
double MathHelper::sigmoidFunction(double xValue) {

    if (xValue > 10) return 1.0;
    else if (xValue < -10) return 0.0;
    else return 1.0 / (1.0 + exp(-xValue));

}

// The standard TanH function.
double MathHelper::tanHFunction(double xValue) {

    if (xValue > 10) return 1.0;
    else if (xValue < -10) return -1.0;
    else return tanh(xValue);

}

// The SoftSign function as proposed by Xavier Glorot and Yoshua Bengio (2010):
// "Understanding the difficulty of training deep feed-forward neural networks."
double MathHelper::softSignFunction(double xValue) {

    return xValue / (1 + abs(xValue));

}

cyclone::Vector3 MathHelper::translateGLToWindowCoordinates(GLdouble x, GLdouble y, GLdouble z)
{
    GLdouble modelview[16];
    GLdouble projection[16];
    GLint viewport[4];

    glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
    glGetDoublev(GL_PROJECTION_MATRIX, projection);
    glGetIntegerv(GL_VIEWPORT, viewport);

    cyclone::Vector3 outputCoord = cyclone::Vector3(0.0, 0.0, 0.0);

    gluProject(x, y, z, modelview, projection, viewport, &outputCoord.x, &outputCoord.y, &outputCoord.z);

    return outputCoord;
}

