/*
 * Copyright 2023 Alexandre Fernandez <alex@fernandezfamily.email>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#pragma once
#include <zy_alloc.h>

typedef struct zy_mutex_s zy_mutex_t;

#ifndef ZY_E_DEADLOCK
#define ZY_E_DEADLOCK (-2)
#endif

#ifndef ZY_E_NOT_INITIALIZED
#define ZY_E_NOT_INITIALIZED (-3)
#endif

#ifndef ZY_E_UNKNOWN
#define ZY_E_UNKNOWN (-4)
#endif

#ifndef ZY_E_BUSY
#define ZY_E_BUSY (-5)
#endif

#ifndef ZY_E_PERM
#define ZY_E_PERM (-6)
#endif

#ifdef __cplusplus
extern "C"
{
#endif

    int zy_mutex_construct(zy_mutex_t **mutex, const zy_alloc_t *alloc);
    int zy_mutex_destruct(zy_mutex_t **mutex);

    int zy_mutex_lock(zy_mutex_t *mutex);
    int zy_mutex_unlock(zy_mutex_t *mutex);

#ifdef __cplusplus
}
#endif