#pragma once

#include "..\Render\Object3D.h"
#include "..\Materials\SimpleMaterial.h"

class LEDStripBackgroundWS35{
private:
	Vector3D basisVertices[4] = {Vector3D(400.0000f,-200.0000f,0.0000f),Vector3D(400.0000f,200.0000f,0.0000f),Vector3D(180.0000f,100.0000f,0.0000f),Vector3D(180.0000f,-100.0000f,0.0000f)};
	IndexGroup basisIndexes[2] = {IndexGroup(0, 1, 2), IndexGroup(0, 2, 3)};
	TriangleGroup triangleGroup = TriangleGroup(&basisVertices[0], &basisIndexes[0], 4, 2);
	SimpleMaterial simpleMaterial = SimpleMaterial(RGBColor(128, 128, 128));
	Object3D basisObj = Object3D(&triangleGroup, &simpleMaterial);

public:
	LEDStripBackgroundWS35(){}

	Object3D* GetObject(){
		return &basisObj;
	}
};
