#pragma once

#include "DeepMath.h"

#define Deep_Math_Vec3(...) DeepMath_Vector3_ctor(__VA_ARGS__)

typedef struct
{
	union
	{
		float xyz[3];
		struct
		{
			float x;
			float y;
			float z;
		};
	};
} Deep_Math_Vector3;

Deep_Inline Deep_Math_Vector3 DeepMath_Vector3_ctor(float x, float y, float z)
{
	Deep_Math_Vector3 v;
	v.x = x;
	v.y = y;
	v.z = z;
	return v;
}

Deep_Inline bool DeepMath_Vector3_Equal(Deep_Math_Vector3 v0, Deep_Math_Vector3 v1)
{
	return (v0.x == v1.x && v0.y == v1.y && v0.z == v1.z);
}

Deep_Inline Deep_Math_Vector3 DeepMath_Vector3_Add(Deep_Math_Vector3 v0, Deep_Math_Vector3 v1)
{
	return DeepMath_Vector3_ctor(v0.x + v1.x, v0.y + v1.y, v0.z + v1.z);
}

Deep_Inline Deep_Math_Vector3 DeepMath_Vector3_Sub(Deep_Math_Vector3 v0, Deep_Math_Vector3 v1)
{
	return DeepMath_Vector3_ctor(v0.x - v1.x, v0.y - v1.y, v0.z - v1.z);
}

Deep_Inline Deep_Math_Vector3 DeepMath_Vector3_Mul(Deep_Math_Vector3 v0, Deep_Math_Vector3 v1)
{
	return DeepMath_Vector3_ctor(v0.x * v1.x, v0.y * v1.y, v0.z * v1.z);
}

Deep_Inline Deep_Math_Vector3 DeepMath_Vector3_Div(Deep_Math_Vector3 v0, Deep_Math_Vector3 v1)
{
	return DeepMath_Vector3_ctor(v0.x / v1.x, v0.y / v1.y, v0.z / v1.z);
}

Deep_Inline Deep_Math_Vector3 DeepMath_Vector3_Scale(Deep_Math_Vector3 v, float scale)
{
	return DeepMath_Vector3_ctor(v.x * scale, v.y * scale, v.z * scale);
}

Deep_Inline void DeepMath_Vector3_Scale_InPlace(Deep_Math_Vector3* v, float scale)
{
	v->x *= scale;
	v->y *= scale;
	v->z *= scale;
}

Deep_Inline Deep_Math_Vector3 DeepMath_Vector3_Neg(Deep_Math_Vector3 v)
{
	return DeepMath_Vector3_Scale(v, -1.f);
}

Deep_Inline float DeepMath_Vector3_Dot(Deep_Math_Vector3 v0, Deep_Math_Vector3 v1)
{
	float dot = (float)((v0.x * v1.x) + (v0.y * v1.y) + v0.z * v1.z);
	return dot;
}

Deep_Inline float DeepMath_Vector3_Dist(Deep_Math_Vector3 a, Deep_Math_Vector3 b)
{
	float dx = (a.x - b.x);
	float dy = (a.y - b.y);
	float dz = (a.z - b.z);
	return (float)(sqrt(dx * dx + dy * dy + dz * dz));
}

Deep_Inline float DeepMath_Vector3_Mag(Deep_Math_Vector3 v)
{
	return (float)sqrt(DeepMath_Vector3_Dot(v, v));
}

Deep_Inline float DeepMath_Vector3_MagSqrt(Deep_Math_Vector3 v)
{
	return (float)(DeepMath_Vector3_Dot(v, v));
}

Deep_Inline Deep_Math_Vector3 DeepMath_Vector3_Norm(Deep_Math_Vector3 v)
{
	float len = DeepMath_Vector3_Mag(v);
	return len == 0.f ? v : DeepMath_Vector3_Scale(v, 1.f / len);
}
