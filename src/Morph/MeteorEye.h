#pragma once

#include "Arduino.h"
#include "..\Math\Rotation.h"
#include "Morph.h"
#include "..\Materials\SimpleMaterial.h"
#include "..\Render\IndexGroup.h"
#include "..\Render\Object3D.h"

class MeteorEye{
public:
    enum Morphs {
    eBlink,
    eOpen,
    eClosed,
    };

private:
Vector3D basisVertices[30] = {Vector3D(-15.49+10, 67.01+80, 0), 
Vector3D(/*top*/-6.77+10, 81.56+30 +50,0),
Vector3D(1.47+10, 66.74+80, 0), 
Vector3D(/*top right*/18.43+10, 66.46+30 +50,0), 
Vector3D(9.71+10, 51.91+80 -5, 0), Vector3D(/*bottom right*/17.95+5, 37.09+20 +50,0),
Vector3D(0.99+10, 37.37+20 +50, 0),Vector3D(/*bottom*/-7.73+10, 22.82+15 +50,0),
Vector3D(-15.97+10, 37.64+20 +50, 0), Vector3D(/*bottom left*/-32.92+15, 37.92+20 +50,0),
Vector3D(-24.2 +10, 52.47+80 -5, 0), Vector3D(/*top left*/-32.44+10, 67.29+30 +50,0),
/*inside stuff*/Vector3D(-11.37+10, 59.6+80, 0), Vector3D(-7.01+10, 66.87+80, 0),
Vector3D(-2.89+10, 59.46+80, 0),  Vector3D(5.59+10, 59.32+80, 0),
Vector3D(1.23+10, 52.05+80, 0), Vector3D(5.35+10, 44.64+80, 0),
Vector3D(-3.13+10, 44.78+20 +50, 0), Vector3D(-7.49+10, 37.5+20 +50, 0),
Vector3D(-11.61+10, 44.92+20 +50, 0), Vector3D(-20.08+10, 45.05+20 +50, 0),
Vector3D(-15.73+10, 52.33+80, 0), Vector3D(-19.85+10, 59.74+80, 0),


Vector3D(25.95-5, 38.09+50 +55,0),
Vector3D(17.95 -5, 37.09+30 +25,0),
Vector3D(10.95+5, 39.09+20 +75,0),

Vector3D(25.95-55 +15, 38.09+1 +85,0),
Vector3D(17.95 -35 +10, 37.09+ +75,0),
Vector3D(10.95 -30+15, 39.09+2 +75,0),

};

IndexGroup basisIndexes[21] = {IndexGroup(0,1,2), IndexGroup(2,3,4), IndexGroup(4,5,6), IndexGroup(6,7,8), IndexGroup(8,9,10), IndexGroup(10,11,0), 
/*inside stuff*/ IndexGroup(0, 12, 13), IndexGroup(13,14,2), IndexGroup(2,14,15), IndexGroup(15,16,4), IndexGroup(4,16,17), IndexGroup(17,18,6), IndexGroup(6,18,19), IndexGroup(19,20,8), IndexGroup(8,20,21), IndexGroup(21,22,10), IndexGroup(10,22,23), IndexGroup(23,12,0),


IndexGroup(24,25,26), 

IndexGroup(27,28,29),
IndexGroup(31,33,34),

};

TriangleGroup triangleGroup = TriangleGroup(&basisVertices[0], &basisIndexes[0], 30, 21);

SimpleMaterial simpleMaterial = SimpleMaterial(RGBColor(128, 128, 128));

Object3D basisObj = Object3D(&triangleGroup, &simpleMaterial);

static const byte morphCount = 3;

    int BlinkIndexes[30] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,};
    int OpenIndexes[30] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,};
    int ClosedIndexes[30] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,};

    Vector3D BlinkVectors[30] = {
        Vector3D(7.39,-19.43,0.00), Vector3D(-6.40,-28.24,0.00), Vector3D(-4.88,-9.97,0.00),
        Vector3D(-7.92,-2.33,0.00), Vector3D(-2.24,6.15,0.00), Vector3D(-22.38,17.04,0.00),
        Vector3D(-1.90,17.83,0.00), Vector3D(0.75,39.09,0.00), Vector3D(3.22,17.49,0.00),
        Vector3D(2.07,23.44,0.00), Vector3D(-9.12,13.30,0.00), Vector3D(11.59,-12.69,0.00),
        Vector3D(0.02,-5.83,0.00), Vector3D(-0.77,-19.73,0.00), Vector3D(-0.27,-11.77,0.00),
        Vector3D(-5.59,-4.32,0.00), Vector3D(0.00,0.00,0.00), Vector3D(-4.58,6.35,0.00),
        Vector3D(-10.84,10.76,0.00), Vector3D(1.46,23.84,0.00), Vector3D(0.16,12.95,0.00),
        Vector3D(-0.53,11.46,0.00), Vector3D(0.00,0.00,0.00), Vector3D(-1.54,-3.71,0.00),
        Vector3D(-15.54,-8.99,0.00), Vector3D(-7.88,35.16,0.00), Vector3D(-5.02,0.41,0.00),
        Vector3D(-5.95,15.91,0.00), Vector3D(1.51,16.14,0.00), Vector3D(-7.91,20.14,0.00)
    };
    
    Vector3D OpenVectors[30] = {
        Vector3D(0,0,0),Vector3D(0,0,0),Vector3D(0,0,0),Vector3D(0,0,0),
        Vector3D(0,0,0),Vector3D(0,0,0),Vector3D(0,0,0),Vector3D(0,0,0),
        Vector3D(0,0,0),Vector3D(0,0,0),Vector3D(0,0,0),Vector3D(0,0,0),
        Vector3D(0,0,0),Vector3D(0,0,0),Vector3D(0,0,0),Vector3D(0,0,0),
        Vector3D(0,0,0),Vector3D(0,0,0),Vector3D(0,0,0),Vector3D(0,0,0),
        Vector3D(0,0,0),Vector3D(0,0,0),Vector3D(0,0,0),Vector3D(0,0,0),
        Vector3D(0,0,0),Vector3D(0,0,0),Vector3D(0,0,0),Vector3D(0,0,0),
        Vector3D(0,0,0),Vector3D(0,0,0),
    };   

    Vector3D ClosedVectors[30] = {
        Vector3D(7.39,-19.43,0.00), Vector3D(-6.40,-28.24,0.00), Vector3D(-4.88,-9.97,0.00), Vector3D(-7.92,-2.33,0.00), 

        Vector3D(-2.24,6.15,0.00), 
        Vector3D(-22.38,17.04,0.00), 
        Vector3D(-1.90,17.83,0.00), 
        Vector3D(0.75,39.09,0.00), 
        
        Vector3D(3.22,17.49,0.00), 
        Vector3D(2.07,23.44,0.00), 
        Vector3D(-9.12,13.30,0.00), 
        Vector3D(11.59,-12.69,0.00), 
        
        Vector3D(0.02,-5.83,0.00), 
        Vector3D(-0.77,-19.73,0.00), 
        Vector3D(-0.27,-11.77,0.00), 
        Vector3D(-5.59,-4.32,0.00),
        
        Vector3D(0.00,0.00,0.00), 
        Vector3D(-4.58,6.35,0.00), 
        Vector3D(-10.84,10.76,0.00), 
        Vector3D(1.46,23.84,0.00),
        
        Vector3D(0.16,12.95,0.00), 
        Vector3D(-0.53,11.46,0.00), 
        Vector3D(0.00,0.00,0.00), 
        Vector3D(-1.54,-3.71,0.00),
        
        Vector3D(-15.54,-8.99,0.00), 
        Vector3D(-7.88,35.16,0.00), 
        Vector3D(-5.02,0.41,0.00), 
        Vector3D(-5.95,15.91,0.00),
        
        Vector3D(1.51,16.14,0.00), Vector3D(-7.91,20.14,0.00)
    };

    Morph morphs[3] = {
        Morph(30, BlinkIndexes, BlinkVectors),
        Morph(30, OpenIndexes, OpenVectors),
        Morph(30, ClosedIndexes, ClosedVectors),
    };
    

public:
    MeteorEye(){}

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
