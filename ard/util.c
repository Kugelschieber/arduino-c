#include "util.h"

float map(float value, float fromLow, float fromHigh, float toLow, float toHigh) {
	return fromLow+((toHigh-toLow)/(fromHigh-fromLow))*(value-fromLow);
}
