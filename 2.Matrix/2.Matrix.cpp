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
	if(!XMVerifyCPUSupport())
	{
		cout << "directx math not supported" << endl;
		return 0;
	}

	XMMATRIX A(1.0f, 0.0f, 0.0f, 0.0f,
			   0.0f, 2.0f, 0.0f, 0.0f,
			   0.0f, 0.0f, 4.0f, 0.0f,
			   1.0f, 2.0f, 3.0f, 1.0f);

	XMMATRIX B = XMMatrixIdentity();
	XMMATRIX C = A*B;
	XMMATRIX D = XMMatrixTranspose(A);
	XMVECTOR det = XMMatrixDeterminant(A);
	XMMATRIX E = XMMatrixInverse(&det, A);

	XMMATRIX F = A*E;

	cout << "A = "					 << endl << A   << endl;
	cout << "B = "					 << endl << B   << endl;
	cout << "C = A*B"				 << endl << C   << endl;
	cout << "D = transpose(A) ="	 << endl << D   << endl;
	cout << "det = determinant(A) =" << endl << det << endl;
	cout << "E = inverse(A) ="		 << endl << E   << endl;
	cout << "F = A*E ="				 << endl << F   << endl;

	return 0;
}
