#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "OTIO_internal.h"

#define OTIO_PRIME_COUNT 256
uint otio_primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 
						31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 
						73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 
						127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 
						179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 
						233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 
						283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 
						353, 359, 367, 373, 379, 383, 389, 397, 401, 409, 
						419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 
						467, 479, 487, 491, 499, 503, 509, 521, 523, 541, 
						547, 557, 563, 569, 571, 577, 587, 593, 599, 601, 
						607, 613, 617, 619, 631, 641, 643, 647, 653, 659, 
						661, 673, 677, 683, 691, 701, 709, 719, 727, 733, 
						739, 743, 751, 757, 761, 769, 773, 787, 797, 809, 
						811, 821, 823, 827, 829, 839, 853, 857, 859, 863, 
						877, 881, 883, 887, 907, 911, 919, 929, 937, 941, 
						947, 953, 967, 971, 977, 983, 991, 997, 1009, 1013,
						1019, 1021, 1031, 1033, 1039, 1049, 1051, 1061, 1063, 1069,
						1087, 1091, 1093, 1097, 1103, 1109, 1117, 1123, 1129, 1151,
						1153, 1163, 1171, 1181, 1187, 1193, 1201, 1213, 1217, 1223,
						1229, 1231, 1237, 1249, 1259, 1277, 1279, 1283, 1289, 1291,
						1297, 1301, 1303, 1307, 1319, 1321, 1327, 1361, 1367, 1373,
						1381, 1399, 1409, 1423, 1427, 1429, 1433, 1439, 1447, 1451,
						1453, 1459, 1471, 1481, 1483, 1487, 1489, 1493, 1499, 1511,
						1523, 1531, 1543, 1549, 1553, 1559, 1567, 1571, 1579, 1583,
						1597, 1601, 1607, 1609, 1613, 1619}; 

void otio_decial_remove_decimal(OTIOTime *time)
{
	uint i;
	for(i = 0; i < time->value.decimal; i++)
		time->rate.integer *= 10;
	for(i = 0; i < time->rate.decimal; i++)
		time->value.integer *= 10;
	time->rate.decimal = 0;
	time->value.decimal = 0;
}

void otio_decial_reduce(OTIOTime *time)
{
	uint i = 0;
	while(i < OTIO_PRIME_COUNT)
	{
		if(time->value.integer % otio_primes[i] == 0 && time->rate.integer % otio_primes[i] == 0)
		{
			time->value.integer /= otio_primes[i];
			time->rate.integer /= otio_primes[i];
			i = 0;
		}else
			i++;
	}
}

OTIOTime otio_time_add(OTIOTime time_a, OTIOTime time_b)
{
	OTIOTime t;
	uint i; 
	if(time_a.value.integer == 0)
		return time_b;
	if(time_b.value.integer == 0)
		return time_a;
	if(time_a.rate.integer == time_b.rate.integer && time_a.rate.decimal == time_b.rate.decimal)
	{
		if(time_a.rate.decimal < time_b.rate.decimal)
		{
			for(i = time_a.rate.decimal; i < time_b.rate.decimal; i++)
				time_a.rate.integer *= 10;
			time_a.rate.decimal = time_b.rate.decimal;
		}else
			for(i = time_b.rate.decimal; i < time_a.rate.decimal; i++)
				time_b.rate.integer *= 10;
		t.value.integer = time_a.rate.integer + time_b.rate.integer;
		t.value.decimal = time_a.rate.decimal;
		t.rate = time_a.rate;	
		return t;
	}
	otio_decial_remove_decimal(&time_a);
	otio_decial_reduce(&time_a);
	otio_decial_remove_decimal(&time_b);
	otio_decial_reduce(&time_b);
	t.rate.integer = time_a.rate.integer * time_b.rate.integer;
	t.rate.decimal = 0;
	t.value.integer = time_a.value.integer * time_b.rate.integer + time_b.value.integer * time_a.rate.integer;
	t.value.decimal = 0;
	otio_decial_reduce(&t);
	return t;
}

OTIOTime otio_time_subtract(OTIOTime time_a, OTIOTime time_b)
{
	OTIOTime t;
	uint i; 
	if(time_a.value.integer == 0)
	{
		time_b.value.integer = -time_b.value.integer;
		return time_b;
	}
	if(time_b.value.integer == 0)
		return time_a;
	if(time_a.rate.integer == time_b.rate.integer && time_a.rate.decimal == time_b.rate.decimal)
	{
		if(time_a.rate.decimal < time_b.rate.decimal)
		{
			for(i = time_a.rate.decimal; i < time_b.rate.decimal; i++)
				time_a.rate.integer *= 10;
			time_a.rate.decimal = time_b.rate.decimal;
		}else
			for(i = time_b.rate.decimal; i < time_a.rate.decimal; i++)
				time_b.rate.integer *= 10;
		t.value.integer = time_a.rate.integer - time_b.rate.integer;
		t.value.decimal = time_a.rate.decimal;
		t.rate = time_a.rate;	
		return t;
	}
	otio_decial_remove_decimal(&time_a);
	otio_decial_reduce(&time_a);
	otio_decial_remove_decimal(&time_b);
	otio_decial_reduce(&time_b);
	t.rate.integer = time_a.rate.integer * time_b.rate.integer;
	t.rate.decimal = 0;
	t.value.integer = time_a.value.integer * time_b.rate.integer - time_b.value.integer * time_a.rate.integer;
	t.value.decimal = 0;
	otio_decial_reduce(&t);
	return t;
}

OTIOTime otio_time_object_start_get(void *object)
{
	OTIOHeader *parent;
	OTIOTime time;
	parent = ((OTIOHeader *)object)->parent;
	if(parent == NULL)
	{	
		time.value.integer = 0;
		time.value.decimal = 0;
		time.rate.integer = 1;
		time.rate.decimal = 0;
		return time;
	}
	if(parent->type != ORIO_OT_SEQUENCE)
		return otio_time_object_start_get(parent);
	time = otio_time_object_start_get(parent);
	for(parent = parent->prev; parent != 0; parent = parent->prev)
		time = otio_time_add(((OTIOComposable *)parent)->duration_time, time);
	return time;
}

OTIOTime otio_time_object_end_get(void *object)
{
	uint type;
	type = ((OTIOHeader *)object)->type;
	if(type < ORIO_OT_COMPOSABLE_END)
		return otio_time_add(((OTIOComposable *)object)->duration_time, otio_time_object_start_get(object));
	else if(((OTIOHeader *)object)->parent != NULL)
		return otio_time_object_end_get(((OTIOHeader *)object)->parent);
	else
	{
		OTIOTime time;
		time.value.integer = 0;
		time.value.decimal = 0;
		time.rate.integer = 1;
		time.rate.decimal = 0;
		return time;
	}
}
/*
OTIOTime otio_time_get(void *object)
{
	OTIOHeader *parent;
	OTIOTime time;
	parent = ((OTIOHeader *)object)->parent;
	if(parent == NULL)
	{	
		time.value.integer = 0;
		time.value.decimal = 0;
		time.rate.integer = 1;
		time.rate.decimal = 0;
		return time;
	}
	if(parent->type != ORIO_OT_SEQUENCE)
		return otio_time_get(parent);
	time = otio_time_get(parent);
	for(parent = parent->prev; parent != 0; parent = parent->prev)
		time = otio_time_add(((OTIOComposable *)parent)->duration_time, time);
	return time;
}*/

void test()
{
	OTIOTime time_a, time_b, out;
	time_a.value.integer = 50;
	time_a.value.decimal = 0;
	time_a.rate.integer = 24;
	time_a.rate.decimal = 0;
	time_b.value.integer = 2;
	time_b.value.decimal = 0;
	time_b.rate.integer = 2997;
	time_b.rate.decimal = 2;
	out = otio_time_subtract(time_a, time_b);
	time_a.rate.decimal = 0;
}