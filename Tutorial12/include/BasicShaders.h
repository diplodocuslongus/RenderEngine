#ifndef INCLUDE_BASIC_SHADERS_H
#define INCLUDE_BASIC_SHADERS_H

#include "VertexShader.h"
#include "FragmentShader.h"

class BasicVertexShader : public VertexShader {
    public:
        int locationProjectionMatrix;
        int locationViewMatrix;
        int locationTransformation;

        Matrix44 projectionMatrix, viewMatrix, transformation;
        Matrix44 finalMatrix;

        BasicVertexShader() :
            VertexShader(1000, 1000)
        {}

        virtual void initShader() {
            locationProjectionMatrix = uniforms.bind(projectionMatrix);
            locationViewMatrix = uniforms.bind(viewMatrix);
            locationTransformation = uniforms.bind(transformation);
        }

        virtual void prepare() {
            uniforms.get(locationProjectionMatrix, projectionMatrix);
            uniforms.get(locationViewMatrix, viewMatrix);
            uniforms.get(locationTransformation, transformation);

            finalMatrix = projectionMatrix * viewMatrix * transformation;
        }

        virtual void execute(DataList** attributesIn, DataList* attributesOut, int attributeLocation, Vector4& output) {
            //load attributes
            Vector3 pos, norm;
            Vector2 uv;

            attributesIn[0]->get(attributeLocation, pos);
            attributesIn[1]->get(attributeLocation, uv);
            attributesIn[2]->get(attributeLocation, norm);

            //calculate final vertex position
            output = finalMatrix * Vector4(pos.x, pos.y, pos.z, 1);
        }
};

class BasicFragmentShader : public FragmentShader {
    public:
        char shades[12] = "@#&%*+-'`. ";
        int shadesCount = sizeof(shades) / sizeof(shades[0]);

        BasicFragmentShader() :
            FragmentShader(1000)
        {}

        virtual void initShader() { 

        }

        virtual void prepare() {

        }

        virtual char execute(DataList* attributes, Vector4& output) {
            float brightness = 1;

            //convert brightness to shade
            brightness = 1 - brightness;
            brightness *= shadesCount;

            char character = shades[(int)brightness];
            return character;
        }
};

#endif