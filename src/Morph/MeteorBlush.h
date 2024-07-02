#pragma once

#include "Arduino.h"
#include "..\Math\Rotation.h"
#include "Morph.h"
#include "..\Materials\SimpleMaterial.h"
#include "..\Render\IndexGroup.h"
#include "..\Render\Object3D.h"

class MeteorBlush {
public:
    enum Morphs {
        blDefault,
        blMoveBlush,
    };

private:
Vector3D basisVertices[12] = { 
    Vector3D(-22.6342f,120.6927f-20,95.4003f), //0
    Vector3D(-15.7318f,136.4694f-20 ,95.4003f),
    Vector3D(-6.3644f,137.4555f-20,95.4003f),
    Vector3D(-8.8295f,110.0926f-20,95.4003f),
    Vector3D(0.5380f,108.1205f-20,95.4003f),
    Vector3D(3.4961f,136.2230f-20,95.4003f), //5
    Vector3D(18.2869f,132.5253f-20,95.4003f),
    Vector3D(5.7147f,106.8880f-20,95.4003f),
    Vector3D(14.0962f,105.4089f-20,95.4003f),
    Vector3D(27.1613f,128.8276f-20,95.4003f),
    Vector3D(33.3241f,126.1159f-20,95.4003f), //10
    Vector3D(31.5985f,107.1345f-20,95.4003f),
};
IndexGroup basisIndexes[6] = {
    IndexGroup(9,11,8),
    IndexGroup(7,4,6),
    IndexGroup(1,2,3),
    IndexGroup(0,1,3),
    IndexGroup(11,9,10),
    IndexGroup(6,4,5),
};

TriangleGroup triangleGroup = TriangleGroup(&basisVertices[0], &basisIndexes[0], 12, 6);
SimpleMaterial simpleMaterial = SimpleMaterial(RGBColor(128, 128, 128));
    Object3D basisObj = Object3D(&triangleGroup, &simpleMaterial);

static const byte morphCount = 2;

    
    int DefaultIndexes[12] = {0,1,2,3,4,5,6,7,8,9,10,11};
    int MoveBlushIndexes[6] = {0,3,4,7,8,11,};
    
    Vector3D DefaultVectors[12] = {Vector3D(0,0,0),Vector3D(0,0,0),Vector3D(0,0,0),Vector3D(0,0,0),Vector3D(0,0,0),Vector3D(0,0,0),Vector3D(0,0,0),Vector3D(0,0,0),Vector3D(0,0,0),Vector3D(0,0,0),Vector3D(0,0,0),Vector3D(0,0,0),/*Vector3D(0,0,0),Vector3D(0,0,0),Vector3D(0,0,0),Vector3D(0,0,0),Vector3D(0,0,0),Vector3D(0,0,0),Vector3D(0,0,0),Vector3D(0,0,0),Vector3D(0,0,0),Vector3D(0,0,0),Vector3D(0,0,0),Vector3D(0,0,0),Vector3D(0,0,0),Vector3D(0,0,0),Vector3D(0,0,0),Vector3D(0,0,0),Vector3D(0,0,0),Vector3D(0,0,0),*/};   
 
   Vector3D MoveBlushVectors[6] = {
Vector3D(6.90,15.78,0.00),//0
Vector3D(2.47,27.36,0.00),//3
Vector3D(2.96,28.10,0.00),//4
Vector3D(12.57,25.64,0.00),//7
Vector3D(13.07,23.42,0.00),//8
Vector3D(1.73,18.98,0.00),//11
   };
/*Vector3D BiggerNoseVectors[8] = {Vector3D(8.4117f,22.0785f,0.0000f),Vector3D(9.9468f,17.5824f,0.0000f),Vector3D(6.3111f,17.0042f,0.0000f),Vector3D(9.8417f,10.3621f,0.0000f),Vector3D(-1.1415f,23.0352f,0.0000f),Vector3D(-3.6689f,19.0258f,0.0000f),Vector3D(2.5732f,18.9604f,0.0000f),Vector3D(3.7327f,24.6146f,0.0000f)};
    Vector3D MoveEyeVectors[15] = {Vector3D(-6.2779f,4.9326f,0.0000f),Vector3D(-6.2779f,4.9326f,0.0000f),Vector3D(-6.2779f,4.9326f,0.0000f),Vector3D(-6.2779f,4.9326f,0.0000f),Vector3D(-6.2779f,4.9326f,0.0000f),Vector3D(-6.2779f,4.9326f,0.0000f),Vector3D(-6.2779f,4.9326f,0.0000f),Vector3D(-6.2779f,4.9326f,0.0000f),Vector3D(-6.2779f,4.9326f,0.0000f),Vector3D(-6.2779f,4.9326f,0.0000f),Vector3D(-6.2779f,4.9326f,0.0000f),Vector3D(-6.2779f,4.9326f,0.0000f),Vector3D(-6.2779f,4.9326f,0.0000f),Vector3D(-6.2779f,4.9326f,0.0000f),Vector3D(-6.2779f,4.9326f,0.0000f)};
    Vector3D HideBlushVectors[12] = {Vector3D(29.3262f,48.2032f,0.0000f),Vector3D(22.4307f,32.4422f,0.0000f),Vector3D(13.0726f,31.4571f,0.0000f),Vector3D(15.5353f,58.7927f,0.0000f),Vector3D(6.1772f,60.7628f,0.0000f),Vector3D(3.2220f,32.6885f,0.0000f),Vector3D(-11.5540f,36.3825f,0.0000f),Vector3D(1.0056f,61.9941f,0.0000f),Vector3D(-7.3674f,63.4717f,0.0000f),Vector3D(-20.4195f,40.0765f,0.0000f),Vector3D(-26.5762f,42.7854f,0.0000f),Vector3D(-24.8523f,61.7478f,0.0000f)};
*/
    Morph morphs[2] = {
        Morph(12, DefaultIndexes, DefaultVectors),
        Morph(6, MoveBlushIndexes, MoveBlushVectors),
    };
    

public:
    MeteorBlush(){}

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
