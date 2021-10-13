//	stationaryorbit/mathematics/compensatedfloat
//	Copyright 2020-2021 zawa-ch.
//	GPLv3 (or later) license
//
//	This program is free software: you can redistribute it and/or modify
//	it under the terms of the GNU General Public License as published by
//	the Free Software Foundation, either version 3 of the License, or
//	any later version.
//
//	This program is distributed in the hope that it will be useful,
//	but WITHOUT ANY WARRANTY; without even the implied warranty of
//	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
//	See the GNU General Public License for more details.
//
//	You should have received a copy of the GNU General Public License
//	along with this program.
//	If not, see <http://www.gnu.org/licenses/>.
//
#ifndef __stationaryorbit_mathematics_compensatedfloat__
#define __stationaryorbit_mathematics_compensatedfloat__
#include "stationaryorbit/core.traits.hpp"
namespace zawa_ch::StationaryOrbit::Mathematics
{
	/// 計算時に誤差の補償が行われる数値を表します。
	///	@note
	///	正確な値を示す( @a std::numeric_limits<Tp>::is_exact が @a true である)型に対しては、この型を実体化するべきではありません。
	///	CompensatedFloat は加減算の際に発生する桁落ちによる誤差を補償するための型であり、桁落ちの発生しない型に対して使用する必要はないからです。
	template<class Tp>
	struct CompensatedFloat final
	{
		static_assert(NumericalTypeTraits::is_numericaltype<Tp>, "テンプレート引数 Tp は数値型である必要があります。");
	public:
		typedef Tp ValueType;
	private:
		///	このオブジェクトの値
		Tp value;
		///	計算時に発生した誤差
		Tp c;
	public:
		///	オブジェクトを既定の値で初期化します。
		CompensatedFloat() = default;
		///	指定された値でオブジェクトを初期化します。
		explicit constexpr CompensatedFloat(const Tp& value) : value(value), c() {}
	private:
		///	値からこのオブジェクトを直接構築します。
		constexpr CompensatedFloat(const Tp& value, const Tp& c) : value(value), c(c) {}
	public:
		///	このオブジェクトが指す値を取得します。
		constexpr ValueType Value() const noexcept { return value; }
		///	このオブジェクトの計算時に用いられる誤差の値を取得します。
		constexpr ValueType Error() const noexcept { return c; }

		[[nodiscard]] constexpr CompensatedFloat<Tp> operator+() const noexcept { return CompensatedFloat<Tp>(*this); }
		[[nodiscard]] constexpr CompensatedFloat<Tp> operator-() const noexcept { return CompensatedFloat<Tp>(-value, -c); }
		[[nodiscard]] constexpr CompensatedFloat<Tp> operator+(const Tp& other) const noexcept
		{
			ValueType comp = other - c;
			ValueType sum = value + comp;
			return CompensatedFloat<Tp>(sum, (sum - value) - comp);
		}
		[[nodiscard]] constexpr CompensatedFloat<Tp> operator-(const Tp& other) const noexcept
		{
			ValueType comp = other + c;
			ValueType sum = value - comp;
			return CompensatedFloat<Tp>(sum, (sum - value) + comp);
		}
		[[nodiscard]] constexpr CompensatedFloat<Tp> operator*(const Tp& other) const noexcept { return CompensatedFloat<Tp>(value * other, c * other); }
		[[nodiscard]] constexpr CompensatedFloat<Tp> operator/(const Tp& other) const noexcept { return CompensatedFloat<Tp>(value / other, c / other); }
		constexpr CompensatedFloat<Tp>& operator+=(const Tp& other) noexcept { return *this = *this + other; }
		constexpr CompensatedFloat<Tp>& operator-=(const Tp& other) noexcept { return *this = *this - other; }
		constexpr CompensatedFloat<Tp>& operator*=(const Tp& other) noexcept { return *this = *this * other; }
		constexpr CompensatedFloat<Tp>& operator/=(const Tp& other) noexcept { return *this = *this / other; }

		[[nodiscard]] constexpr bool Equals(const CompensatedFloat<Tp>& other) const noexcept { return Tp(*this) == Tp(other); }
		[[nodiscard]] constexpr bool operator==(const CompensatedFloat<Tp>& other) const noexcept { return Equals(other); }
		[[nodiscard]] constexpr bool operator!=(const CompensatedFloat<Tp>& other) const noexcept { return !Equals(other); }

		[[nodiscard]] constexpr bool operator<(const CompensatedFloat<Tp>& other) const noexcept { return Tp(*this) < Tp(other); }
		[[nodiscard]] constexpr bool operator>(const CompensatedFloat<Tp>& other) const noexcept { return Tp(*this) > Tp(other); }
		[[nodiscard]] constexpr bool operator<=(const CompensatedFloat<Tp>& other) const noexcept { return Tp(*this) <= Tp(other); }
		[[nodiscard]] constexpr bool operator>=(const CompensatedFloat<Tp>& other) const noexcept { return Tp(*this) >= Tp(other); }

		explicit constexpr operator ValueType() const { return value - c; }
	};

	/// 計算時に誤差の補償が行われる @a float を表します。
	typedef CompensatedFloat<float> CompensatedSingle;
	/// 計算時に誤差の補償が行われる @a double を表します。
	typedef CompensatedFloat<double> CompensatedDouble;
}
#endif // __stationaryorbit_mathematics_compensatedfloat__