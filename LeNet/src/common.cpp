#include "common.h"
#include "hls_math.h"

fixed_t sigmoid(fixed_t x)
{
	fixed_t neg_x = -x;
    return (1 / (1 + hls::expf(neg_x)));
}
