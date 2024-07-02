#pragma once

#include "Arduino.h"
#include "..\Math\Rotation.h"
#include "Morph.h"
#include "..\Materials\SimpleMaterial.h"
#include "..\Render\IndexGroup.h"
#include "..\Render\Object3D.h"

class MeteorBrow {
public:
    enum Morphs {
        bDefault,
        bAngry,
        bSurprise,
        bSad,
    };

private:
    Vector3D basisVertices[14] = {
        Vector3D(30.98-5, 193.19-5, 0), Vector3D(60.03-5, 189.49-5, 0),Vector3D(74.95-5, 174.71-5, 0),Vector3D(68.16-5, 155.68-5, 0),
        Vector3D(10.87-5, 185.05-5, 0), Vector3D(15.08-5, 178.44-5, 0),Vector3D(21.32-5, 192.08-5, 0),Vector3D(47.31-5, 194.02-5, 0),
        Vector3D(68.1-5, 184.2-5, 0), Vector3D(78.46-5, 161.9, 0),Vector3D(27.35-5, 178.09-5, 0),Vector3D(42.87-5, 177.55-5, 0),
        Vector3D(57.87-5, 170.05-5, 0), Vector3D(77.3-5, 151.72-5, 0)
    };

    IndexGroup basisIndexes[12] = {
        IndexGroup(4,5,6), IndexGroup(6,0,10), IndexGroup(5,6,10), IndexGroup(10,0,7), 
        IndexGroup(7,10,11), IndexGroup(7,11,1), IndexGroup(1,11,8), IndexGroup(8,11,12), 
        IndexGroup(8,12,2), IndexGroup(12,2,3), IndexGroup(2,3,9), IndexGroup(9,3,13)
    };

    TriangleGroup triangleGroup = TriangleGroup(&basisVertices[0], &basisIndexes[0], 14, 12);

    SimpleMaterial simpleMaterial = SimpleMaterial(RGBColor(128, 128, 128));

    Object3D basisObj = Object3D(&triangleGroup, &simpleMaterial);

    static const byte morphCount = 4;

    
    int DefaultIndexes[14] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,};
    int AngryIndexes[14] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,};
    int SurprisedIndexes[14] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,};
    int SadIndexes[14] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,};

    Vector3D DefaultVectors[14] = {
        Vector3D(0,0,0),Vector3D(0,0,0),Vector3D(0,0,0),Vector3D(0,0,0),
        Vector3D(0,0,0),Vector3D(0,0,0),Vector3D(0,0,0),Vector3D(0,0,0),
        Vector3D(0,0,0),Vector3D(0,0,0),Vector3D(0,0,0),Vector3D(0,0,0),
        Vector3D(0,0,0),Vector3D(0,0,0),
    };   
 
    Vector3D AngryVectors[14] = {
        Vector3D(-8.72,-14.46+5,0.00),Vector3D(-19.67,-6.98+5,0.00),Vector3D(-16.54,8.26+5,0.00),Vector3D(-18.16,14.32+5,0.00),
        Vector3D(-1.66,-11.52+5,0.00),Vector3D(-5.01,-15.45+5,0.00),Vector3D(-5.39,-14.68+5,0.00),Vector3D(-16.36,-12.93+5,0.00),
        Vector3D(-19.56,-1.61+5,0.00),Vector3D(-14.20,18.08+5,0.00),Vector3D(-12.14,-14.60+5,0.00),Vector3D(-15.83,-10.21+5,0.00),
        Vector3D(-17.87,-0.05+5,0.00),Vector3D(-16.37,18.32+5,0.00)
    };

    Vector3D SurprisedVectors[14] = {
        Vector3D(0+5,0+5,0),Vector3D(0+5,0+5,0),Vector3D(0+5,0+5,0),Vector3D(0,0,0),Vector3D(0,0,0),
        Vector3D(0,0+5,0),Vector3D(0+5,0+5,0),Vector3D(0+5,0+5,0),Vector3D(0+5,0+5,0),Vector3D(0+5,0+5,0),
        Vector3D(0,0,0),Vector3D(0,0,0),Vector3D(0,0,0),Vector3D(0+5,0,0),
    };

    Vector3D SadVectors[14] = {
        Vector3D(-8.34,-22.68,0.00),Vector3D(-21.01,-24.14,0.00),Vector3D(-19.35,-13.27,0.00),Vector3D(-12.62,-9.02,0.00),
        Vector3D(-1.25,-17.59,0.00),Vector3D(-5.08,-18.44,0.00),Vector3D(-5.39,-19.68,0.00),Vector3D(-16.31,-26.47,0.00),
        Vector3D(-21.37,-21.47,0.00),Vector3D(-13.46,-1.90,0.00),Vector3D(-12.35,-23.09,0.00),Vector3D(-14.36,-28.25,0.00),
        Vector3D(-18.55,-23.21,0.00),Vector3D(-13.13,-2.32,0.00)
    };

    Morph morphs[4] = {
       Morph(14, DefaultIndexes, DefaultVectors),
       Morph(14, AngryIndexes, AngryVectors),
       Morph(14, SurprisedIndexes, SurprisedVectors),
       Morph(14, SadIndexes, SadVectors)
        
        
    };
    

public:

    MeteorBrow(){}

    Object3D* GetObject(){
        return &basisObj;
    }

    void SetMorphWeight(Morphs morph, float weight){
        morphs[morph].Weight = weight;
    }

    float* GetMorphWeightReference(Morphs morph){
        return &morphs[morph].Weight;
    }

    void Reset(){
        for(int i = 0; i < morphCount; i++){
            morphs[i].Weight = 0.0f;
        }
    }

    void Update(){
        basisObj.ResetVertices();

        for(int i = 0; i < morphCount; i++){
            if(morphs[i].Weight > 0.0f){
                morphs[i].MorphObject3D(basisObj.GetTriangleGroup());
            }
        }

    }
};
