#pragma once
#include <tuple>

using namespace std;

template < typename T, size_t S >
struct Vector;

template < typename T, size_t S >
struct VectorBase
{
	inline T& operator[]( size_t a_Index )
	{
		return reinterpret_cast< T* >( this )[ a_Index ];
	}

	inline const T& operator[]( size_t a_Index ) const
	{
		return reinterpret_cast< const T* >( this )[ a_Index ];
	}

	template < typename U >
	Vector< T, S > operator+( const VectorBase< U, S >& a_Vector ) const
	{
		Vector< T, S > Result;

		for ( int i = 0; i < S; ++i )
		{
			Result[ i ] = operator[]( i ) + static_cast< T >( a_Vector[ i ] );
		}

		return Result;
	}

	template < typename U >
	Vector< T, S >& operator+=( const VectorBase< U, S >& a_Vector )
	{
		for ( int i = 0; i < S; ++i )
		{
			operator[]( i ) += static_cast< T >( a_Vector[ i ] );
		}

		return *reinterpret_cast< Vector< T, S >* >( this );
	}

	template < typename U >
	Vector< T, S > operator-( const VectorBase< U, S >& a_Vector ) const
	{
		Vector< T, S > Result;

		for ( int i = 0; i < S; ++i )
		{
			Result[ i ] = operator[]( i ) - static_cast< T >( a_Vector[ i ] );
		}

		return Result;
	}

	template < typename U >
	Vector< T, S >& operator-=( const VectorBase< U, S >& a_Vector )
	{
		for ( int i = 0; i < S; ++i )
		{
			operator[]( i ) -= static_cast< T >( a_Vector[ i ] );
		}

		return *reinterpret_cast< Vector< T, S >* >( this );
	}

	template < typename U >
	Vector< T, S > operator*( const VectorBase< U, S >& a_Vector ) const
	{
		Vector< T, S > Result;

		for ( int i = 0; i < S; ++i )
		{
			Result[ i ] = operator[]( i ) * static_cast< T >( a_Vector[ i ] );
		}

		return Result;
	}

	template < typename U >
	Vector< T, S >& operator*=( const VectorBase< U, S >& a_Vector )
	{
		for ( int i = 0; i < S; ++i )
		{
			operator[]( i ) *= static_cast< T >( a_Vector[ i ] );
		}

		return *reinterpret_cast< Vector< T, S >* >( this );
	}

	template < typename U >
	Vector< T, S > operator*( U a_Scalar ) const
	{
		Vector< T, S > Result;

		for ( int i = 0; i < S; ++i )
		{
			Result[ i ] *= a_Scalar;
		}

		return Result;
	}

	template < typename U >
	Vector< T, S >& operator*=( U a_Scalar )
	{
		for ( int i = 0; i < S; ++i )
		{
			operator[]( i ) *= a_Scalar;
		}

		return *reinterpret_cast< Vector< T, S >* >( this );
	}

	template < typename U >
	Vector< T, S > operator/( U a_Scalar ) const
	{
		Vector< T, S > Result;
		float Scalar = 1.0f / a_Scalar;

		for ( int i = 0; i < S; ++i )
		{
			Result[ i ] *= Scalar;
		}

		return Result;
	}

	template < typename U >
	Vector< T, S >& operator/=( U a_Scalar )
	{
		float Scalar = 1.0f / a_Scalar;

		for ( int i = 0; i < S; ++i )
		{
			operator[]( i ) *= Scalar;
		}

		return *reinterpret_cast< Vector< T, S >* >( this );
	}

};

template < typename T, size_t S >
struct Vector : public VectorBase< T, S > { };

template < typename T, size_t... I >
struct Swizzler : public VectorBase< T, sizeof...( I ) >
{
	T Data[ 1 ];

	template < typename U >
	operator Vector< U, sizeof...( I ) >()
	{
		Vector< U, sizeof...( I ) > Output;
		Repack< U, I... >( reinterpret_cast< U* >( &Output ), Data );
		return Output;
	}

private:

	template < typename U, size_t I0, size_t... I >
	inline constexpr void Repack( U* a_To, T* a_From )
	{
		a_To[ 0 ] = static_cast< U >( a_From[ I0 ] );

		if constexpr ( sizeof...( I ) != 0 )
		{
			Repack< U, I... >( a_To + 1, a_From );
		}
	}
};

template < typename T >
struct Vector< T, 2 > : public VectorBase< T, 2 >
{
	union
	{
		struct { T x; T y; };

		union
		{
			Swizzler< T, 0, 0 > xx;
			Swizzler< T, 0, 1 > xy;
			Swizzler< T, 1, 0 > yx;
			Swizzler< T, 1, 1 > yy;
		} swizzle;
	};

	Vector()
		: x( static_cast< T >( 0 ) )
		, y( static_cast< T >( 0 ) )
	{ }

	template < typename U >
	Vector( U a_X, U a_Y )
		: x( static_cast< T >( a_X ) )
		, y( static_cast< T >( a_Y ) )
	{ }

	template < typename U, size_t S >
	Vector( const Vector< U, S >& a_Vector )
		: x( static_cast< T >( a_Vector.x ) )
		, y( static_cast< T >( a_Vector.y ) )
	{ }

	inline Vector< T, 3 > ToVector3() const
	{
		return { x, y, static_cast< T >( 0 ) };
	}

	inline Vector< T, 4 > ToVector4() const
	{
		return { x, y, static_cast< T >( 0 ), static_cast< T >( 0 ) };
	}

	static const Vector< T, 2 > Zero;
	static const Vector< T, 2 > One;
};

template < typename T > const Vector< T, 2 > Vector< T, 2 >::Zero( 0, 0 );
template < typename T > const Vector< T, 2 > Vector< T, 2 >::One ( 1, 1 );

template < typename T >
struct Vector< T, 3 > : public VectorBase< T, 3 >
{
	union
	{
		struct { T x; T y; T z; };
		
		union
		{
			Swizzler< T, 0, 2 > xx;
			Swizzler< T, 0, 1 > xy;
			Swizzler< T, 0, 2 > xz;
			Swizzler< T, 1, 0 > yx;
			Swizzler< T, 1, 1 > yy;
			Swizzler< T, 1, 2 > yz;
			Swizzler< T, 2, 0 > zx;
			Swizzler< T, 2, 1 > zy;
			Swizzler< T, 2, 2 > zz;
			Swizzler< T, 0, 0, 2 > xxx;
			Swizzler< T, 0, 0, 1 > xxy;
			Swizzler< T, 0, 0, 2 > xxz;
			Swizzler< T, 0, 1, 0 > xyx;
			Swizzler< T, 0, 1, 1 > xyy;
			Swizzler< T, 0, 1, 2 > xyz;
			Swizzler< T, 0, 2, 0 > xzx;
			Swizzler< T, 0, 2, 1 > xzy;
			Swizzler< T, 0, 2, 2 > xzz;
			Swizzler< T, 1, 0, 2 > yxx;
			Swizzler< T, 1, 0, 1 > yxy;
			Swizzler< T, 1, 0, 2 > yxz;
			Swizzler< T, 1, 1, 0 > yyx;
			Swizzler< T, 1, 1, 1 > yyy;
			Swizzler< T, 1, 1, 2 > yyz;
			Swizzler< T, 1, 2, 0 > yzx;
			Swizzler< T, 1, 2, 1 > yzy;
			Swizzler< T, 1, 2, 2 > yzz;
			Swizzler< T, 2, 0, 2 > zxx;
			Swizzler< T, 2, 0, 1 > zxy;
			Swizzler< T, 2, 0, 2 > zxz;
			Swizzler< T, 2, 1, 0 > zyx;
			Swizzler< T, 2, 1, 1 > zyy;
			Swizzler< T, 2, 1, 2 > zyz;
			Swizzler< T, 2, 2, 0 > zzx;
			Swizzler< T, 2, 2, 1 > zzy;
			Swizzler< T, 2, 2, 2 > zzz;
		} swizzle;
	};

	Vector()
		: x( static_cast< T >( 0 ) )
		, y( static_cast< T >( 0 ) )
		, z( static_cast< T >( 0 ) )
	{ }

	template < typename U >
	Vector( U a_X, U a_Y, U a_Z )
		: x( static_cast< T >( a_X ) )
		, y( static_cast< T >( a_Y ) )
		, z( static_cast< T >( a_Z ) )
	{ }

	template < typename U, size_t S >
	Vector( const Vector< U, S >& a_Vector )
		: x( static_cast< T >( a_Vector.x ) )
		, y( static_cast< T >( a_Vector.y ) )
		, z( static_cast< T >( a_Vector.z ) )
	{ }

	inline Vector< T, 2 > ToVector2() const
	{
		return { x, y };
	}

	inline Vector< T, 4 > ToVector4() const
	{
		return { x, y, z, static_cast< T >( 0 ) };
	}

	static const Vector< T, 3 > Zero;
	static const Vector< T, 3 > One;
};

template < typename T > const Vector< T, 3 > Vector< T, 3 >::Zero( 0, 0, 0 );
template < typename T > const Vector< T, 3 > Vector< T, 3 >::One ( 1, 1, 1 );

template < typename T >
struct Vector< T, 4 > : public VectorBase< T, 4 >
{
	union
	{
		struct { T x; T y; T z; T w; };
		
		union
		{
			Swizzler< T, 0, 0 > xx;
			Swizzler< T, 0, 1 > xy;
			Swizzler< T, 0, 2 > xz;
			Swizzler< T, 0, 3 > xw;
			Swizzler< T, 1, 0 > yx;
			Swizzler< T, 1, 1 > yy;
			Swizzler< T, 1, 2 > yz;
			Swizzler< T, 1, 3 > yw;
			Swizzler< T, 2, 0 > zx;
			Swizzler< T, 2, 1 > zy;
			Swizzler< T, 2, 2 > zz;
			Swizzler< T, 2, 3 > zw;
			Swizzler< T, 3, 0 > wx;
			Swizzler< T, 3, 1 > wy;
			Swizzler< T, 3, 2 > wz;
			Swizzler< T, 3, 3 > ww;
			Swizzler< T, 0, 0, 0 > xxx;
			Swizzler< T, 0, 0, 1 > xxy;
			Swizzler< T, 0, 0, 2 > xxz;
			Swizzler< T, 0, 0, 3 > xxw;
			Swizzler< T, 0, 1, 0 > xyx;
			Swizzler< T, 0, 1, 1 > xyy;
			Swizzler< T, 0, 1, 2 > xyz;
			Swizzler< T, 0, 1, 3 > xyw;
			Swizzler< T, 0, 2, 0 > xzx;
			Swizzler< T, 0, 2, 1 > xzy;
			Swizzler< T, 0, 2, 2 > xzz;
			Swizzler< T, 0, 2, 3 > xzw;
			Swizzler< T, 0, 3, 0 > xwx;
			Swizzler< T, 0, 3, 1 > xwy;
			Swizzler< T, 0, 3, 2 > xwz;
			Swizzler< T, 0, 3, 3 > xww;
			Swizzler< T, 1, 0, 0 > yxx;
			Swizzler< T, 1, 0, 1 > yxy;
			Swizzler< T, 1, 0, 2 > yxz;
			Swizzler< T, 1, 0, 3 > yxw;
			Swizzler< T, 1, 1, 0 > yyx;
			Swizzler< T, 1, 1, 1 > yyy;
			Swizzler< T, 1, 1, 2 > yyz;
			Swizzler< T, 1, 1, 3 > yyw;
			Swizzler< T, 1, 2, 0 > yzx;
			Swizzler< T, 1, 2, 1 > yzy;
			Swizzler< T, 1, 2, 2 > yzz;
			Swizzler< T, 1, 2, 3 > yzw;
			Swizzler< T, 1, 3, 0 > ywx;
			Swizzler< T, 1, 3, 1 > ywy;
			Swizzler< T, 1, 3, 2 > ywz;
			Swizzler< T, 1, 3, 3 > yww;
			Swizzler< T, 2, 0, 0 > zxx;
			Swizzler< T, 2, 0, 1 > zxy;
			Swizzler< T, 2, 0, 2 > zxz;
			Swizzler< T, 2, 0, 3 > zxw;
			Swizzler< T, 2, 1, 0 > zyx;
			Swizzler< T, 2, 1, 1 > zyy;
			Swizzler< T, 2, 1, 2 > zyz;
			Swizzler< T, 2, 1, 3 > zyw;
			Swizzler< T, 2, 2, 0 > zzx;
			Swizzler< T, 2, 2, 1 > zzy;
			Swizzler< T, 2, 2, 2 > zzz;
			Swizzler< T, 2, 2, 3 > zzw;
			Swizzler< T, 2, 3, 0 > zwx;
			Swizzler< T, 2, 3, 1 > zwy;
			Swizzler< T, 2, 3, 2 > zwz;
			Swizzler< T, 2, 3, 3 > zww;
			Swizzler< T, 3, 0, 0 > wxx;
			Swizzler< T, 3, 0, 1 > wxy;
			Swizzler< T, 3, 0, 2 > wxz;
			Swizzler< T, 3, 0, 3 > wxw;
			Swizzler< T, 3, 1, 0 > wyx;
			Swizzler< T, 3, 1, 1 > wyy;
			Swizzler< T, 3, 1, 2 > wyz;
			Swizzler< T, 3, 1, 3 > wyw;
			Swizzler< T, 3, 2, 0 > wzx;
			Swizzler< T, 3, 2, 1 > wzy;
			Swizzler< T, 3, 2, 2 > wzz;
			Swizzler< T, 3, 2, 3 > wzw;
			Swizzler< T, 3, 3, 0 > wwx;
			Swizzler< T, 3, 3, 1 > wwy;
			Swizzler< T, 3, 3, 2 > wwz;
			Swizzler< T, 3, 3, 3 > www;
			Swizzler< T, 0, 0, 0, 0 > xxxx;
			Swizzler< T, 0, 0, 0, 1 > xxxy;
			Swizzler< T, 0, 0, 0, 2 > xxxz;
			Swizzler< T, 0, 0, 0, 3 > xxxw;
			Swizzler< T, 0, 0, 1, 0 > xxyx;
			Swizzler< T, 0, 0, 1, 1 > xxyy;
			Swizzler< T, 0, 0, 1, 2 > xxyz;
			Swizzler< T, 0, 0, 1, 3 > xxyw;
			Swizzler< T, 0, 0, 2, 0 > xxzx;
			Swizzler< T, 0, 0, 2, 1 > xxzy;
			Swizzler< T, 0, 0, 2, 2 > xxzz;
			Swizzler< T, 0, 0, 2, 3 > xxzw;
			Swizzler< T, 0, 0, 3, 0 > xxwx;
			Swizzler< T, 0, 0, 3, 1 > xxwy;
			Swizzler< T, 0, 0, 3, 2 > xxwz;
			Swizzler< T, 0, 0, 3, 3 > xxww;
			Swizzler< T, 0, 1, 0, 0 > xyxx;
			Swizzler< T, 0, 1, 0, 1 > xyxy;
			Swizzler< T, 0, 1, 0, 2 > xyxz;
			Swizzler< T, 0, 1, 0, 3 > xyxw;
			Swizzler< T, 0, 1, 1, 0 > xyyx;
			Swizzler< T, 0, 1, 1, 1 > xyyy;
			Swizzler< T, 0, 1, 1, 2 > xyyz;
			Swizzler< T, 0, 1, 1, 3 > xyyw;
			Swizzler< T, 0, 1, 2, 0 > xyzx;
			Swizzler< T, 0, 1, 2, 1 > xyzy;
			Swizzler< T, 0, 1, 2, 2 > xyzz;
			Swizzler< T, 0, 1, 2, 3 > xyzw;
			Swizzler< T, 0, 1, 3, 0 > xywx;
			Swizzler< T, 0, 1, 3, 1 > xywy;
			Swizzler< T, 0, 1, 3, 2 > xywz;
			Swizzler< T, 0, 1, 3, 3 > xyww;
			Swizzler< T, 0, 2, 0, 0 > xzxx;
			Swizzler< T, 0, 2, 0, 1 > xzxy;
			Swizzler< T, 0, 2, 0, 2 > xzxz;
			Swizzler< T, 0, 2, 0, 3 > xzxw;
			Swizzler< T, 0, 2, 1, 0 > xzyx;
			Swizzler< T, 0, 2, 1, 1 > xzyy;
			Swizzler< T, 0, 2, 1, 2 > xzyz;
			Swizzler< T, 0, 2, 1, 3 > xzyw;
			Swizzler< T, 0, 2, 2, 0 > xzzx;
			Swizzler< T, 0, 2, 2, 1 > xzzy;
			Swizzler< T, 0, 2, 2, 2 > xzzz;
			Swizzler< T, 0, 2, 2, 3 > xzzw;
			Swizzler< T, 0, 2, 3, 0 > xzwx;
			Swizzler< T, 0, 2, 3, 1 > xzwy;
			Swizzler< T, 0, 2, 3, 2 > xzwz;
			Swizzler< T, 0, 2, 3, 3 > xzww;
			Swizzler< T, 0, 3, 0, 0 > xwxx;
			Swizzler< T, 0, 3, 0, 1 > xwxy;
			Swizzler< T, 0, 3, 0, 2 > xwxz;
			Swizzler< T, 0, 3, 0, 3 > xwxw;
			Swizzler< T, 0, 3, 1, 0 > xwyx;
			Swizzler< T, 0, 3, 1, 1 > xwyy;
			Swizzler< T, 0, 3, 1, 2 > xwyz;
			Swizzler< T, 0, 3, 1, 3 > xwyw;
			Swizzler< T, 0, 3, 2, 0 > xwzx;
			Swizzler< T, 0, 3, 2, 1 > xwzy;
			Swizzler< T, 0, 3, 2, 2 > xwzz;
			Swizzler< T, 0, 3, 2, 3 > xwzw;
			Swizzler< T, 0, 3, 3, 0 > xwwx;
			Swizzler< T, 0, 3, 3, 1 > xwwy;
			Swizzler< T, 0, 3, 3, 2 > xwwz;
			Swizzler< T, 0, 3, 3, 3 > xwww;
			Swizzler< T, 1, 0, 0, 0 > yxxx;
			Swizzler< T, 1, 0, 0, 1 > yxxy;
			Swizzler< T, 1, 0, 0, 2 > yxxz;
			Swizzler< T, 1, 0, 0, 3 > yxxw;
			Swizzler< T, 1, 0, 1, 0 > yxyx;
			Swizzler< T, 1, 0, 1, 1 > yxyy;
			Swizzler< T, 1, 0, 1, 2 > yxyz;
			Swizzler< T, 1, 0, 1, 3 > yxyw;
			Swizzler< T, 1, 0, 2, 0 > yxzx;
			Swizzler< T, 1, 0, 2, 1 > yxzy;
			Swizzler< T, 1, 0, 2, 2 > yxzz;
			Swizzler< T, 1, 0, 2, 3 > yxzw;
			Swizzler< T, 1, 0, 3, 0 > yxwx;
			Swizzler< T, 1, 0, 3, 1 > yxwy;
			Swizzler< T, 1, 0, 3, 2 > yxwz;
			Swizzler< T, 1, 0, 3, 3 > yxww;
			Swizzler< T, 1, 1, 0, 0 > yyxx;
			Swizzler< T, 1, 1, 0, 1 > yyxy;
			Swizzler< T, 1, 1, 0, 2 > yyxz;
			Swizzler< T, 1, 1, 0, 3 > yyxw;
			Swizzler< T, 1, 1, 1, 0 > yyyx;
			Swizzler< T, 1, 1, 1, 1 > yyyy;
			Swizzler< T, 1, 1, 1, 2 > yyyz;
			Swizzler< T, 1, 1, 1, 3 > yyyw;
			Swizzler< T, 1, 1, 2, 0 > yyzx;
			Swizzler< T, 1, 1, 2, 1 > yyzy;
			Swizzler< T, 1, 1, 2, 2 > yyzz;
			Swizzler< T, 1, 1, 2, 3 > yyzw;
			Swizzler< T, 1, 1, 3, 0 > yywx;
			Swizzler< T, 1, 1, 3, 1 > yywy;
			Swizzler< T, 1, 1, 3, 2 > yywz;
			Swizzler< T, 1, 1, 3, 3 > yyww;
			Swizzler< T, 1, 2, 0, 0 > yzxx;
			Swizzler< T, 1, 2, 0, 1 > yzxy;
			Swizzler< T, 1, 2, 0, 2 > yzxz;
			Swizzler< T, 1, 2, 0, 3 > yzxw;
			Swizzler< T, 1, 2, 1, 0 > yzyx;
			Swizzler< T, 1, 2, 1, 1 > yzyy;
			Swizzler< T, 1, 2, 1, 2 > yzyz;
			Swizzler< T, 1, 2, 1, 3 > yzyw;
			Swizzler< T, 1, 2, 2, 0 > yzzx;
			Swizzler< T, 1, 2, 2, 1 > yzzy;
			Swizzler< T, 1, 2, 2, 2 > yzzz;
			Swizzler< T, 1, 2, 2, 3 > yzzw;
			Swizzler< T, 1, 2, 3, 0 > yzwx;
			Swizzler< T, 1, 2, 3, 1 > yzwy;
			Swizzler< T, 1, 2, 3, 2 > yzwz;
			Swizzler< T, 1, 2, 3, 3 > yzww;
			Swizzler< T, 1, 3, 0, 0 > ywxx;
			Swizzler< T, 1, 3, 0, 1 > ywxy;
			Swizzler< T, 1, 3, 0, 2 > ywxz;
			Swizzler< T, 1, 3, 0, 3 > ywxw;
			Swizzler< T, 1, 3, 1, 0 > ywyx;
			Swizzler< T, 1, 3, 1, 1 > ywyy;
			Swizzler< T, 1, 3, 1, 2 > ywyz;
			Swizzler< T, 1, 3, 1, 3 > ywyw;
			Swizzler< T, 1, 3, 2, 0 > ywzx;
			Swizzler< T, 1, 3, 2, 1 > ywzy;
			Swizzler< T, 1, 3, 2, 2 > ywzz;
			Swizzler< T, 1, 3, 2, 3 > ywzw;
			Swizzler< T, 1, 3, 3, 0 > ywwx;
			Swizzler< T, 1, 3, 3, 1 > ywwy;
			Swizzler< T, 1, 3, 3, 2 > ywwz;
			Swizzler< T, 1, 3, 3, 3 > ywww;
			Swizzler< T, 2, 0, 0, 0 > zxxx;
			Swizzler< T, 2, 0, 0, 1 > zxxy;
			Swizzler< T, 2, 0, 0, 2 > zxxz;
			Swizzler< T, 2, 0, 0, 3 > zxxw;
			Swizzler< T, 2, 0, 1, 0 > zxyx;
			Swizzler< T, 2, 0, 1, 1 > zxyy;
			Swizzler< T, 2, 0, 1, 2 > zxyz;
			Swizzler< T, 2, 0, 1, 3 > zxyw;
			Swizzler< T, 2, 0, 2, 0 > zxzx;
			Swizzler< T, 2, 0, 2, 1 > zxzy;
			Swizzler< T, 2, 0, 2, 2 > zxzz;
			Swizzler< T, 2, 0, 2, 3 > zxzw;
			Swizzler< T, 2, 0, 3, 0 > zxwx;
			Swizzler< T, 2, 0, 3, 1 > zxwy;
			Swizzler< T, 2, 0, 3, 2 > zxwz;
			Swizzler< T, 2, 0, 3, 3 > zxww;
			Swizzler< T, 2, 1, 0, 0 > zyxx;
			Swizzler< T, 2, 1, 0, 1 > zyxy;
			Swizzler< T, 2, 1, 0, 2 > zyxz;
			Swizzler< T, 2, 1, 0, 3 > zyxw;
			Swizzler< T, 2, 1, 1, 0 > zyyx;
			Swizzler< T, 2, 1, 1, 1 > zyyy;
			Swizzler< T, 2, 1, 1, 2 > zyyz;
			Swizzler< T, 2, 1, 1, 3 > zyyw;
			Swizzler< T, 2, 1, 2, 0 > zyzx;
			Swizzler< T, 2, 1, 2, 1 > zyzy;
			Swizzler< T, 2, 1, 2, 2 > zyzz;
			Swizzler< T, 2, 1, 2, 3 > zyzw;
			Swizzler< T, 2, 1, 3, 0 > zywx;
			Swizzler< T, 2, 1, 3, 1 > zywy;
			Swizzler< T, 2, 1, 3, 2 > zywz;
			Swizzler< T, 2, 1, 3, 3 > zyww;
			Swizzler< T, 2, 2, 0, 0 > zzxx;
			Swizzler< T, 2, 2, 0, 1 > zzxy;
			Swizzler< T, 2, 2, 0, 2 > zzxz;
			Swizzler< T, 2, 2, 0, 3 > zzxw;
			Swizzler< T, 2, 2, 1, 0 > zzyx;
			Swizzler< T, 2, 2, 1, 1 > zzyy;
			Swizzler< T, 2, 2, 1, 2 > zzyz;
			Swizzler< T, 2, 2, 1, 3 > zzyw;
			Swizzler< T, 2, 2, 2, 0 > zzzx;
			Swizzler< T, 2, 2, 2, 1 > zzzy;
			Swizzler< T, 2, 2, 2, 2 > zzzz;
			Swizzler< T, 2, 2, 2, 3 > zzzw;
			Swizzler< T, 2, 2, 3, 0 > zzwx;
			Swizzler< T, 2, 2, 3, 1 > zzwy;
			Swizzler< T, 2, 2, 3, 2 > zzwz;
			Swizzler< T, 2, 2, 3, 3 > zzww;
			Swizzler< T, 2, 3, 0, 0 > zwxx;
			Swizzler< T, 2, 3, 0, 1 > zwxy;
			Swizzler< T, 2, 3, 0, 2 > zwxz;
			Swizzler< T, 2, 3, 0, 3 > zwxw;
			Swizzler< T, 2, 3, 1, 0 > zwyx;
			Swizzler< T, 2, 3, 1, 1 > zwyy;
			Swizzler< T, 2, 3, 1, 2 > zwyz;
			Swizzler< T, 2, 3, 1, 3 > zwyw;
			Swizzler< T, 2, 3, 2, 0 > zwzx;
			Swizzler< T, 2, 3, 2, 1 > zwzy;
			Swizzler< T, 2, 3, 2, 2 > zwzz;
			Swizzler< T, 2, 3, 2, 3 > zwzw;
			Swizzler< T, 2, 3, 3, 0 > zwwx;
			Swizzler< T, 2, 3, 3, 1 > zwwy;
			Swizzler< T, 2, 3, 3, 2 > zwwz;
			Swizzler< T, 2, 3, 3, 3 > zwww;
			Swizzler< T, 3, 0, 0, 0 > wxxx;
			Swizzler< T, 3, 0, 0, 1 > wxxy;
			Swizzler< T, 3, 0, 0, 2 > wxxz;
			Swizzler< T, 3, 0, 0, 3 > wxxw;
			Swizzler< T, 3, 0, 1, 0 > wxyx;
			Swizzler< T, 3, 0, 1, 1 > wxyy;
			Swizzler< T, 3, 0, 1, 2 > wxyz;
			Swizzler< T, 3, 0, 1, 3 > wxyw;
			Swizzler< T, 3, 0, 2, 0 > wxzx;
			Swizzler< T, 3, 0, 2, 1 > wxzy;
			Swizzler< T, 3, 0, 2, 2 > wxzz;
			Swizzler< T, 3, 0, 2, 3 > wxzw;
			Swizzler< T, 3, 0, 3, 0 > wxwx;
			Swizzler< T, 3, 0, 3, 1 > wxwy;
			Swizzler< T, 3, 0, 3, 2 > wxwz;
			Swizzler< T, 3, 0, 3, 3 > wxww;
			Swizzler< T, 3, 1, 0, 0 > wyxx;
			Swizzler< T, 3, 1, 0, 1 > wyxy;
			Swizzler< T, 3, 1, 0, 2 > wyxz;
			Swizzler< T, 3, 1, 0, 3 > wyxw;
			Swizzler< T, 3, 1, 1, 0 > wyyx;
			Swizzler< T, 3, 1, 1, 1 > wyyy;
			Swizzler< T, 3, 1, 1, 2 > wyyz;
			Swizzler< T, 3, 1, 1, 3 > wyyw;
			Swizzler< T, 3, 1, 2, 0 > wyzx;
			Swizzler< T, 3, 1, 2, 1 > wyzy;
			Swizzler< T, 3, 1, 2, 2 > wyzz;
			Swizzler< T, 3, 1, 2, 3 > wyzw;
			Swizzler< T, 3, 1, 3, 0 > wywx;
			Swizzler< T, 3, 1, 3, 1 > wywy;
			Swizzler< T, 3, 1, 3, 2 > wywz;
			Swizzler< T, 3, 1, 3, 3 > wyww;
			Swizzler< T, 3, 2, 0, 0 > wzxx;
			Swizzler< T, 3, 2, 0, 1 > wzxy;
			Swizzler< T, 3, 2, 0, 2 > wzxz;
			Swizzler< T, 3, 2, 0, 3 > wzxw;
			Swizzler< T, 3, 2, 1, 0 > wzyx;
			Swizzler< T, 3, 2, 1, 1 > wzyy;
			Swizzler< T, 3, 2, 1, 2 > wzyz;
			Swizzler< T, 3, 2, 1, 3 > wzyw;
			Swizzler< T, 3, 2, 2, 0 > wzzx;
			Swizzler< T, 3, 2, 2, 1 > wzzy;
			Swizzler< T, 3, 2, 2, 2 > wzzz;
			Swizzler< T, 3, 2, 2, 3 > wzzw;
			Swizzler< T, 3, 2, 3, 0 > wzwx;
			Swizzler< T, 3, 2, 3, 1 > wzwy;
			Swizzler< T, 3, 2, 3, 2 > wzwz;
			Swizzler< T, 3, 2, 3, 3 > wzww;
			Swizzler< T, 3, 3, 0, 0 > wwxx;
			Swizzler< T, 3, 3, 0, 1 > wwxy;
			Swizzler< T, 3, 3, 0, 2 > wwxz;
			Swizzler< T, 3, 3, 0, 3 > wwxw;
			Swizzler< T, 3, 3, 1, 0 > wwyx;
			Swizzler< T, 3, 3, 1, 1 > wwyy;
			Swizzler< T, 3, 3, 1, 2 > wwyz;
			Swizzler< T, 3, 3, 1, 3 > wwyw;
			Swizzler< T, 3, 3, 2, 0 > wwzx;
			Swizzler< T, 3, 3, 2, 1 > wwzy;
			Swizzler< T, 3, 3, 2, 2 > wwzz;
			Swizzler< T, 3, 3, 2, 3 > wwzw;
			Swizzler< T, 3, 3, 3, 0 > wwwx;
			Swizzler< T, 3, 3, 3, 1 > wwwy;
			Swizzler< T, 3, 3, 3, 2 > wwwz;
			Swizzler< T, 3, 3, 3, 3 > wwww;
		} swizzle;
	};

	Vector()
		: x( static_cast< T >( 0 ) )
		, y( static_cast< T >( 0 ) )
		, z( static_cast< T >( 0 ) )
		, w( static_cast< T >( 0 ) )
	{ }

	template < typename U >
	Vector( U a_X, U a_Y, U a_Z, U a_W )
		: x( static_cast< T >( a_X ) )
		, y( static_cast< T >( a_Y ) )
		, z( static_cast< T >( a_Z ) )
		, w( static_cast< T >( a_W ) )
	{ }

	template < typename U, size_t S >
	Vector( const Vector< U, S >& a_Vector )
		: x( static_cast< T >( a_Vector.x ) )
		, y( static_cast< T >( a_Vector.y ) )
		, z( static_cast< T >( a_Vector.z ) )
		, w( static_cast< T >( a_Vector.w ) )
	{ }

	inline Vector< T, 2 > ToVector2() const
	{
		return { x, y };
	}

	inline Vector< T, 3 > ToVector3() const
	{
		return { x, y, z };
	}

	static const Vector< T, 4 > Zero;
	static const Vector< T, 4 > One;
};

template < typename T > const Vector< T, 4 > Vector< T, 4 >::Zero( 0, 0, 0, 0 );
template < typename T > const Vector< T, 4 > Vector< T, 4 >::One ( 1, 1, 1, 1 );

typedef Vector< float, 2 > Vector2;
typedef Vector< float, 3 > Vector3;
typedef Vector< float, 4 > Vector4;
typedef Vector< int, 2 > Vector2Int;
typedef Vector< int, 3 > Vector3Int;
typedef Vector< int, 4 > Vector4Int;

template < typename T, size_t X, size_t Y >
struct Matrix
{

};

class Math
{
public:

	template < typename T >
	static float Sqrt( T a_Scalar )
	{
		return sqrt( a_Scalar );
	}

	template < typename T, size_t S >
	static float Length( const Vector< T, S >& a_Vector )
	{
		const T* Data = reinterpret_cast< const T* >( &a_Vector );
		T Total = 0;

		for ( size_t Index = 0; Index < S; ++Index )
		{
			T Component = Data[ Index ];
			Total += Component * Component;
		}

		return sqrt( Total );
	}

	template < typename T, size_t S >
	static T LengthSqrd( const Vector< T, S >& a_Vector )
	{
		const T* Data = reinterpret_cast< const T* >( &a_Vector );
		T Total = 0;

		for ( size_t Index = 0; Index < S; ++Index )
		{
			T Component = Data[ Index ];
			Total += Component * Component;
		}

		return Total;
	}

	template < typename T, size_t S >
	static T Manhatten( const Vector< T, S >& a_Vector )
	{
		T Total = static_cast< T >( 0 );

		for ( int i = 0; i < S; ++i )
		{
			Total += a_Vector[ i ];
		}

		return Total;
	}

	template < typename T, size_t S >
	static T Dot( const Vector< T, S >& a_VectorA, const Vector< T, S >& a_VectorB )
	{
		Vector< T, S > Multiplied = a_VectorA * a_VectorB;
		return Manhatten( Multiplied );
	}

	template < typename T >
	static T Cross( const Vector< T, 3 >& a_VectorA, const Vector< T, 3 >& a_VectorB )
	{

	}
};