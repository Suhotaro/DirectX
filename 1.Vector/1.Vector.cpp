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

const float Epsilon = 0.001f;

bool Equals(float lhs, float rhs)
{
	return fabs(lhs - rhs) < Epsilon ? true : false;
}

void SetterFunctions()
{
	XMVECTOR p = XMVectorZero();
	XMVECTOR q = XMVectorSplatOne();
	XMVECTOR u = XMVectorSet(1.0f, 2.0f, 3.0f, 0.0f);
	XMVECTOR v = XMVectorReplicate(-2.0f);
	XMVECTOR w = XMVectorSplatZ(u);

	cout << "p : " << p << endl;
	cout << "q : " << q << endl;
	cout << "u : " << u << endl;
	cout << "v : " << v << endl;
	cout << "w : " << w << endl;
}

void VectorFunctions()
{
	XMVECTOR n = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
	XMVECTOR u = XMVectorSet(1.0f, 2.0f, 3.0f, 0.0f);
	XMVECTOR v = XMVectorSet(-2.0f, 1.0f, -3.0f, 0.0f);
	XMVECTOR w = XMVectorSet(0.707f, 0.707f, 0.0f, 0.0f);

	XMVECTOR a = u + v;
	XMVECTOR b = u - v;
	XMVECTOR c = 10.0f*u;

	XMVECTOR L = XMVector3Length(u);
	XMVECTOR d = XMVector3Normalize(u);
	float len_x = XMVectorGetX(d);
	float len_y = XMVectorGetY(d);
	float len_z = XMVectorGetZ(d);
	float len_a = XMVectorGetZ(d);

	float len_d = sqrt(len_x*len_x + len_y*len_y + len_z*len_z);

	XMVECTOR s = XMVector3Dot(u, v);
	XMVECTOR e = XMVector3Cross(u, v);

	XMVECTOR projW;
	XMVECTOR perpW;
	XMVector3ComponentsFromNormal(&projW, &perpW, w, n);

	bool equal = XMVector3Equal(projW + perpW, w) != 0;
	bool notEqual = XMVector3NotEqual(projW + perpW, w) != 0;

	XMVECTOR angleVec = XMVector3AngleBetweenVectors(projW, perpW);
	float angleRadius = XMVectorGetX(angleVec);
	float angleDegree = XMConvertToDegrees(angleRadius);

	cout << "u                  : " << u << endl;
	cout << "v                  : " << v << endl;
	cout << "w                  : " << w << endl;
	cout << "n                  : " << n << endl;
	cout << "a = u + v          : " << a << endl;
	cout << "b = u - v          : " << b << endl;
	cout << "c = 10 * u         : " << c << endl;
	cout << "d = u / |u|        : " << d << endl;
	cout << "e = u x v          : " << e << endl;
	cout << "L = |u|            : " << L << endl;
	cout << "s = u.v            : " << L << endl;
	cout << "projW              : " << projW << endl;
	cout << "perpW              : " << perpW << endl;
	cout << "projW + perpW == w : " << equal << endl;
	cout << "projW + perpW != w : " << notEqual << endl;
	cout << "angle              : " << angleDegree << endl;
}

void FloatingPointError()
{
	cout.precision(8);

	XMVECTOR u = XMVectorSet(1.0f, 1.0f, 1.0f, 0.0f);
	XMVECTOR n = XMVector3Normalize(u);

	XMVECTOR u2 = XMVectorSet(1.0f, 0.00009f, 1.0f, 0.0f);
	XMVECTOR n2 = XMVector3Normalize(u);

	float LU = XMVectorGetX(XMVector3Length(n));
	cout << LU << endl;
	if (LU == 1.0f)
		cout << "Length 1\n";
	else
		cout << "Length not 1\n";

	float LU2 = XMVectorGetX(XMVector3Length(n2));

	float powLU = powf(LU, 1.0e6f);
	cout << "LU^(10^6) =" << powLU << endl;

	cout << "Equals: " << Equals(LU, LU2) << endl;
}

int main()
{
	cout.setf(ios_base::boolalpha);

	if(!XMVerifyCPUSupport())
	{
		cout << "direct x math not supported\n";
		return 0;
	}

	//SetterFunctions();
	//VectorFunctions();
	FloatingPointError();

	return 0;
}
