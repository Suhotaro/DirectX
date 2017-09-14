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

void XM_CALLCONV FunctionArguments(FXMVECTOR v1, float f, FXMVECTOR v2, FXMVECTOR v3, GXMVECTOR v4,
								   HXMVECTOR v5, HXMVECTOR v6, CXMVECTOR v7, CXMVECTOR v8)
{
	cout << "v1 =" << v1 << endl;
	cout << "f ="  << f  << endl;
	cout << "v2 =" << v2 << endl;
	cout << "v3 =" << v3 << endl;
	cout << "v4 =" << v4 << endl;
	cout << "v5 =" << v5 << endl;
	cout << "v6 =" << v6 << endl;
	cout << "v7 =" << v7 << endl;
	cout << "v8 =" << v8 << endl;
}

void FunctionArguments()
{
	XMVECTOR v1 = XMVectorSet(1.0f, 1.0f, 1.0f, 0.0f);
	XMVECTOR v2 = XMVectorSet(2.0f, 2.0f, 2.0f, 0.0f);
	XMVECTOR v3 = XMVectorSet(3.0f, 3.0f, 3.0f, 0.0f);
	XMVECTOR v4 = XMVectorSet(4.0f, 4.0f, 4.0f, 0.0f);
	XMVECTOR v5 = XMVectorSet(5.0f, 5.0f, 5.0f, 0.0f);
	XMVECTOR v6 = XMVectorSet(6.0f, 6.0f, 6.0f, 0.0f);
	XMVECTOR v7 = XMVectorSet(7.0f, 7.0f, 7.0f, 0.0f);
	XMVECTOR v8 = XMVectorSet(8.0f, 8.0f, 8.0f, 0.0f);

	FunctionArguments(v1, 10.0f, v2, v3, v4, v5, v6, v7, v8);
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

class A
{
public:
	A() = default;

	void foo(FXMVECTOR _v)
	{
		XMStoreFloat3(&v1, _v);
		show(v1);
	}

private:
	void show(XMFLOAT3 v)
	{
		cout << "v1:(" << v.x << "," << v.y << "," << v.z << ")\n";
	}

	XMFLOAT3 v1;
	XMFLOAT3 v2;
};

void ClassMember()
{
	A a;
	a.foo(XMVectorSet(1.0f, 2.0f, 3.0f, 4.0f));
}

static const XMVECTORF32 g_Vector = { 1.0f, 2.0f, 3.0f, 0.0f };

void ConstInitializationSyntax()
{
	cout << "Global: " << g_Vector << endl;

	XMVECTORF32 Vector = { 4.0f, 5.0f, 6.0f, 0.0f };
	cout << "Global: " << Vector << endl;
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
	//FloatingPointError();
	//FunctionArguments();
	//ClassMember();
	ConstInitializationSyntax();

	return 0;
}
