#pragma once

#include <cstdint>
#include <immintrin.h>

#define xf(n) ::daum::xor_float::convert(n)
namespace daum
{
	namespace xor_float
	{
		constexpr uint32_t gen_key()
		{
			return (~(__TIME__[0] * 0xa24a7c) ^
				0xcfc9 ^
				(__TIME__[4] * 0x5a99) ^
				0x57f3aaa9 ^
				~(__TIME__[6] * 0x84575a) ^
				0x51f6 ^
				(__TIME__[3] * 0x1cd2) ^
				0x7dee4b90 ^
				~(__TIME__[7] * 0x38ab64) ^
				0x661198b);
		}

		constexpr uint32_t xor_key = ::daum::xor_float::gen_key();
		__forceinline float convert_back(const uint32_t val)
		{
			const auto xor_key_m128 = _mm_castsi128_ps(_mm_cvtsi32_si128(::daum::xor_float::xor_key));
			const auto val_m128 = _mm_castsi128_ps(_mm_cvtsi32_si128(val));
			const auto xored_val_m128 = _mm_xor_ps(val_m128, xor_key_m128);
			return _mm_cvtss_f32(xored_val_m128);
		}
		__forceinline float convert(float val)
		{
			uint32_t cache;
			reinterpret_cast<float&>(cache) = val;
			cache ^= ::daum::xor_float::xor_key;
			return xor_float::convert_back(cache);
		}
	}
}