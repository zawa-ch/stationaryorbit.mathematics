//	stationaryorbit.mathematics:/integral
//	Copyright 2020 zawa-ch.
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
#include "stationaryorbit/mathematics/compensatedfloat.hpp"
#include "stationaryorbit/mathematics/integral.hpp"
using namespace zawa_ch::StationaryOrbit;
using namespace zawa_ch::StationaryOrbit::Mathematics;

MidpointIntegral::MidpointIntegral(const IMathematicFunction<double>& function, const Range<double, true, true>& integrationrange)
	: _func(function), _irange(integrationrange)
{
	if (
		!(
			(std::numeric_limits<double>::lowest() <= integrationrange.bottom())
			&&(integrationrange.bottom() <= std::numeric_limits<double>::max())
			&&(std::numeric_limits<double>::lowest() <= integrationrange.top())
			&&(integrationrange.top() <= std::numeric_limits<double>::max())
		)
	)
	{ throw std::invalid_argument("引数 integrationrange として指定可能な範囲は有限な実数である必要があります。"); }
}
const IMathematicFunction<double>& MidpointIntegral::Function() const { return _func; }
Range<double, true, true> MidpointIntegral::getIntegrationRange() const { return _irange; }
double MidpointIntegral::Calc(const double& value) const { return _irange.length() * _func.Calc((_irange.bottom() + _irange.top()) / 2); }
double MidpointIntegral::Calc(const double& value, size_t div) const
{
	auto result = CompensatedDouble(0.0);
	auto length = _irange.length();
	for (size_t i = 0; i < div; i++)
	{
		result += _func.Calc(_irange.bottom() + (((length * i) + (length * (i + 1)) / div / 2)));
	}
	return result.Value();
}

TrapeziumIntegral::TrapeziumIntegral(const IMathematicFunction<double>& function, const Range<double, true, true>& integrationrange)
	: _func(function), _irange(integrationrange)
{
	if (
		!(
			(std::numeric_limits<double>::lowest() <= integrationrange.bottom())
			&&(integrationrange.bottom() <= std::numeric_limits<double>::max())
			&&(std::numeric_limits<double>::lowest() <= integrationrange.top())
			&&(integrationrange.top() <= std::numeric_limits<double>::max())
		)
	)
	{ throw std::invalid_argument("引数 integrationrange として指定可能な範囲は有限な実数である必要があります。"); }
}
const IMathematicFunction<double>& TrapeziumIntegral::Function() const { return _func; }
Range<double, true, true> TrapeziumIntegral::getIntegrationRange() const { return _irange; }
double TrapeziumIntegral::Calc(const double& value) const { return (_func.Calc(_irange.bottom()) + _func.Calc(_irange.top())) * _irange.length() / 2; }
double TrapeziumIntegral::Calc(const double& value, size_t div) const
{
	auto result = CompensatedDouble(0.0);
	auto length = _irange.length();
	for (size_t i = 0; i < div; i++)
	{
		result += (_func.Calc(length * i) + _func.Calc(length * (i + 1))) * length / div / 2;
	}
	return result.Value();
}

SimpsonIntegral::SimpsonIntegral(const IMathematicFunction<double>& function, const Range<double, true, true>& integrationrange)
	: _func(function), _irange(integrationrange)
{
	if (
		!(
			(std::numeric_limits<double>::lowest() <= integrationrange.bottom())
			&&(integrationrange.bottom() <= std::numeric_limits<double>::max())
			&&(std::numeric_limits<double>::lowest() <= integrationrange.top())
			&&(integrationrange.top() <= std::numeric_limits<double>::max())
		)
	)
	{ throw std::invalid_argument("引数 integrationrange として指定可能な範囲は有限な実数である必要があります。"); }
}
const IMathematicFunction<double>& SimpsonIntegral::Function() const { return _func; }
Range<double, true, true> SimpsonIntegral::getIntegrationRange() const { return _irange; }
double SimpsonIntegral::Calc(const double& value) const
{
	auto mresult = MidpointIntegral(_func, _irange).Calc(value);
	auto tresult = SimpsonIntegral(_func, _irange).Calc(value);
	return (mresult * 2 + tresult) / 3;
}
double SimpsonIntegral::Calc(const double& value, size_t div) const
{
	auto mresult = MidpointIntegral(_func, _irange).Calc(value, div);
	auto tresult = SimpsonIntegral(_func, _irange).Calc(value, div);
	return (mresult * 2 + tresult) / 3;
}
