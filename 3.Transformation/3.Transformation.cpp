#include "stdafx.h"

#include <windows.h>
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <iostream>

using namespace std;
using namespace DirectX;
using namespace DirectX::PackedVector;

ostream& XM_CALLCONV operator<<(ostream& os, FXMVECTOR v)
{
	XMFLOAT3 dest;
	XMStoreFloat3(&dest, v);

	os << "(" << dest.x << "," << dest.y << "," << dest.z << ")";
	return os;
}

ostream& XM_CALLCONV operator << (ostream& os, FXMMATRIX m)
{
	for(int i = 0; i < 4; i++)
	{
		os << XMVectorGetX(m.r[i]) << "\t";
		os << XMVectorGetY(m.r[i]) << "\t";
		os << XMVectorGetZ(m.r[i]) << "\t";
		os << XMVectorGetW(m.r[i]) << "\t";
		os << endl;
	}
	return os;
}

int main()
{
	XMMATRIX A(1.0f, 0.0f, 0.0f, 0.0f,
			   0.0f, 2.0f, 0.0f, 0.0f,
			   0.0f, 0.0f, 4.0f, 0.0f,
			   1.0f, 2.0f, 3.0f, 1.0f);

	XMMATRIX B = XMMatrixScaling(1.0f, 2.0f, 0.5f);
	XMMATRIX C = XMMatrixScalingFromVector(XMVectorSet(1.0f, 1.0f, 1.0f, 0.0f));

	XMMATRIX D = XMMatrixRotationX(30.f);
	XMMATRIX E = XMMatrixRotationAxis(XMVectorSet(1.0f, 1.0f, 1.0f, 0.0f), 60.0f);

	XMMATRIX F = XMMatrixTranslation(2.0f, 0.0f, 0.0f);
	XMMATRIX G = XMMatrixTranslationFromVector(XMVectorSet(1.0f, 2.0f, 3.0f, 0.0f));

	XMVECTOR v = XMVector3TransformCoord(XMVectorSet(1.0f, 2.0f, 3.0f, 0.0f), A);
	XMVECTOR v2 = XMVector3TransformNormal(XMVectorSet(1.0f, 2.0f, 3.0f, 0.0f), A);

	cout << "A = " << endl << A << endl;
	cout << "B scaling = " << endl << B << endl;
	cout << "D rotation = " << endl << C << endl;
	cout << "E rotation axis = " << endl << E << endl;
	cout << "F translation = " << endl << F << endl;
	cout << "G translation from vector = " << endl << G << endl;

	cout << "v transform coord = " << endl << v << endl;
	cout << "v2 transform normal = " << endl << v2 << endl;

	return 0;
}
