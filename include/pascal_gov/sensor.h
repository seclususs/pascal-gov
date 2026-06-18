// SPDX-License-Identifier: GPL-3.0-only
// Copyright (C) 2026 seclususs

#ifndef PASCAL_GOV_SENSOR_H
#define PASCAL_GOV_SENSOR_H

#include "pascal_gov/compiler.h"
#include <stdint.h>

typedef struct {
	int fd;
	uint8_t buffer[16];
	float default_val;
} pascal_gov_thermal_sensor;

typedef struct {
	int fd;
	uint8_t buffer[16];
} pascal_gov_battery_sensor;

void pascal_gov_sensor_init_thermal(
	pascal_gov_thermal_sensor *PASCAL_GOV_RESTRICT sensor, int fd,
	float default_val);

void pascal_gov_sensor_init_battery(
	pascal_gov_battery_sensor *PASCAL_GOV_RESTRICT sensor, int fd);

int pascal_gov_sensor_read_temp(
	pascal_gov_thermal_sensor *PASCAL_GOV_RESTRICT sensor,
	float *PASCAL_GOV_RESTRICT out_temp);

int pascal_gov_sensor_read_battery(
	pascal_gov_battery_sensor *PASCAL_GOV_RESTRICT sensor,
	float *PASCAL_GOV_RESTRICT out_capacity);

#endif // PASCAL_GOV_SENSOR_H
