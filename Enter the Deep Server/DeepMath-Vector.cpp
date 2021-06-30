#include "DeepMath.h"

//TODO:: implement ExpressionTemplates (to make code cache friendly)

namespace DeepEngine
{
	inline bool operator ==(const Vector3& LHS, const Vector3& RHS)
	{
		return (LHS.X == RHS.X && LHS.Y == RHS.Y && LHS.Z == RHS.Z);
	}
	
	Vector3::Vector3(float X, float Y, float Z)
	{
		this->X = X;
		this->Y = Y;
		this->Z = Z;
	}

	Vector3& Vector3::operator +=(const Vector3& Other)
	{
		X += Other.X;
		Y += Other.Y;
		Z += Other.Z;
		return *this;
	}
	Vector3& Vector3::operator -=(const Vector3& Other)
	{
		X -= Other.X;
		Y -= Other.Y;
		Z -= Other.Z;
		return *this;
	}
	Vector3& Vector3::operator *=(const float Other)
	{
		X *= Other;
		Y *= Other;
		Z *= Other;
		return *this;
	}
	Vector3& Vector3::operator /=(const float Other)
	{
		X /= Other;
		Y /= Other;
		Z /= Other;
		return *this;
	}
	Vector3 Vector3::operator +(const Vector3& Other)
	{
		Vector3 Temp(X, Y, Z);
		Temp.X += Other.X;
		Temp.Y += Other.Y;
		Temp.Z += Other.Z;
		return Temp;
	}
	Vector3 Vector3::operator -(const Vector3& Other)
	{
		Vector3 Temp(X, Y, Z);
		Temp.X -= Other.X;
		Temp.Y -= Other.Y;
		Temp.Z -= Other.Z;
		return Temp;
	}
	float Vector3::operator *(const Vector3& Other)
	{
		return X * Other.X + Y * Other.Y + Z * Other.Z;
	}
	Vector3 Vector3::operator *(const float Other)
	{
		Vector3 Temp(X, Y, Z);
		Temp.X *= Other;
		Temp.Y *= Other;
		Temp.Z *= Other;
		return Temp;
	}
	Vector3 Vector3::operator /(const float Other)
	{
		Vector3 Temp(X, Y, Z);
		Temp.X /= Other;
		Temp.Y /= Other;
		Temp.Z /= Other;
		return Temp;
	}
}