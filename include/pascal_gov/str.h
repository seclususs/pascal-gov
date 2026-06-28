// SPDX-License-Identifier: GPL-3.0-only
// Copyright (C) 2026 seclususs

#ifndef PASCAL_GOV_STR_H
#define PASCAL_GOV_STR_H

#include "pascal_gov/compiler.h"
#include <stdbool.h>
#include <stddef.h>

static inline bool
pascal_gov_str_has_prefix(const char *PASCAL_GOV_RESTRICT str,
			  const char *PASCAL_GOV_RESTRICT prefix)
{
	while (*prefix)

		if (*prefix++ != *str++)
			return false;

	return true;
}

static inline bool
pascal_gov_str_contains(const char *PASCAL_GOV_RESTRICT str,
			const char *PASCAL_GOV_RESTRICT substr)
{
	if (!*substr)
		return true;

	const char *p1;
	const char *p2;

	for (const char *p1_adv = str; *p1_adv; ++p1_adv) {
		p1 = p1_adv;
		p2 = substr;

		while (*p1 && *p2 && *p1 == *p2) {
			p1++;
			p2++;
		}

		if (!*p2)
			return true;
	}

	return false;
}

static inline void pascal_gov_str_to_lower(char *str)
{
	for (; *str; ++str)

		if (*str >= 'A' && *str <= 'Z')
			*str += 32;
}

static inline void
pascal_gov_str_build_path(char *PASCAL_GOV_RESTRICT out, size_t max_len,
			  const char *PASCAL_GOV_RESTRICT dir,
			  const char *PASCAL_GOV_RESTRICT sub,
			  const char *PASCAL_GOV_RESTRICT file)
{
	size_t i = 0;

	while (*dir && i < max_len - 1)
		out[i++] = *dir++;

	if (i < max_len - 1)
		out[i++] = '/';

	while (*sub && i < max_len - 1)
		out[i++] = *sub++;

	if (i < max_len - 1)
		out[i++] = '/';

	while (*file && i < max_len - 1)
		out[i++] = *file++;

	out[i] = '\0';
}

#endif // PASCAL_GOV_STR_H
