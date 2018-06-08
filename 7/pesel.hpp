#include <cstdint>

inline
bool checkPesel(uint64_t pesel) {
	const uint8_t f[11] = { 1, 3, 7, 9, 1, 3, 7, 9, 1, 3, 1 };
	uint64_t d = 1;
	uint16_t c = 0;
	int i = 11;
	while (i-- > 0) {
		c += f[i] * ((pesel / d) % 10);
		d *= 10;
	}
	return !(c % 10);
}