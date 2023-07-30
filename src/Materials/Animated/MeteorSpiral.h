#pragma once

#include "AnimatedMaterial.h"
#include "..\..\Signals\FunctionGenerator.h"
#include "..\..\Materials\SpiralMaterial.h"

class RainbowSpiral : public AnimatedMaterial{
private:
    FunctionGenerator fGenMatBend = FunctionGenerator(FunctionGenerator::Sine, 0.8f, 0.9f, 6.7f);
     RGBColor rainbowSpectrum[6] = {RGBColor(252, 3, 98), RGBColor(112, 146, 190), RGBColor(181, 230, 29), RGBColor(166, 75, 168), RGBColor(23, 255, 243), RGBColor(255, 255, 128)};
    SpiralMaterial spiralMaterial = SpiralMaterial(6, rainbowSpectrum, 3.0f, 7.0f);

public:
    RainbowSpiral(){}

    void Update(float ratio){
        spiralMaterial.SetBend(fGenMatBend.Update());
        spiralMaterial.SetRotationAngle((1.0f - ratio) * 360.0f);
        spiralMaterial.SetPositionOffset(Vector2D(0.0f, 75.0f));
    }

    Material* GetMaterial(){
        return &spiralMaterial;
    }

    RGBColor GetRGB(Vector3D position, Vector3D normal, Vector3D uvw) override{
        return spiralMaterial.GetRGB(position, normal, uvw);
    }
};
