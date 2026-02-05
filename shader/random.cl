// vim: ft=c

uint	hash(uint x)
{
	x ^= x >> 16;
	x *= 0x7feb352d;
	x ^= x >> 15;
	x *= 0x846ca68b;
	x ^= x >> 16;
	return x;
}

float	random01(uint seed)
{
	return (float)(hash(seed)) / (float)UINT_MAX;
}
