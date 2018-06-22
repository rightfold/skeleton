#pragma once

#define SK_LIKELY(  cond) __builtin_expect(cond, true)
#define SK_UNLIKELY(cond) __builtin_expect(cond, false)
