#pragma once

namespace DeepEngine
{
	struct Vector3
	{
		float X = 0;
		float Y = 0;
		float Z = 0;

		Vector3() {};
		Vector3(float X, float Y, float Z);

		Vector3& operator +=(const Vector3& Other);
		Vector3& operator -=(const Vector3& Other);
		Vector3& operator *=(const float Other);
		Vector3& operator /=(const float Other);
		Vector3 operator +(const Vector3& Other);
		Vector3 operator -(const Vector3& Other);
		float operator *(const Vector3& Other);
		Vector3 operator *(const float Other);
		Vector3 operator /(const float Other);
	};
	inline bool operator ==(const Vector3& LHS, const Vector3& RHS);
	inline bool operator !=(const Vector3& LHS, const Vector3& RHS) { return !(LHS == RHS); }
}
