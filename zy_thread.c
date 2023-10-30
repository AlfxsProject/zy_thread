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
#include "zy_thread.h"
#ifdef DO_PTHREAD
#include <errno.h>
#include <pthread.h>
#endif

struct zy_mutex_s
{
    const zy_alloc_t *alloc;
#ifdef DO_PTHREAD
    pthread_mutex_t mutex;
    pthread_mutexattr_t attr;
#endif
};

int zy_mutex_construct(zy_mutex_t **mutex, const zy_alloc_t *alloc)
{
#ifdef DO_MUTEX
    int r = zy_malloc(alloc, sizeof(zy_mutex_t), (void **)mutex);
    if (r == ZY_OK)
    {
        (*mutex)->alloc = alloc;
#ifdef DO_PTHREAD
        pthread_mutex_init(&(*mutex)->mutex, nullptr);
        pthread_mutexattr_init(&(*mutex)->attr);
        pthread_mutexattr_settype(&(*mutex)->attr, PTHREAD_MUTEX_ERRORCHECK);
#endif
    }
    return r;
#else
    return ZY_OK;
#endif
}
int zy_mutex_destruct(zy_mutex_t **mutex)
{
#ifdef DO_MUTEX
    if (*mutex != nullptr)
    {
#ifdef DO_PTHREAD
        int r = pthread_mutex_destroy(&(*mutex)->mutex);
        pthread_mutexattr_destroy(&(*mutex)->attr);
#else
        int r = 0;
#endif
        zy_free((*mutex)->alloc, (void **)mutex);

        switch (r)
        {
        case 0:
            return ZY_OK;
        case EBUSY:
            return ZY_E_BUSY;
        default:
            return ZY_E_UNKNOWN;
        }
    }
#else
    return ZY_OK;
#endif
}
int zy_mutex_lock(zy_mutex_t *mutex)
{
#ifdef DO_MUTEX
#ifdef DO_PTHREAD
    int r = pthread_mutex_lock(&mutex->mutex);
    switch (r)
    {
    case 0:
        return ZY_OK;
    case EDEADLK:
        return ZY_E_DEADLOCK;
    case EINVAL:
        return ZY_E_NOT_INITIALIZED;
    default:
        return ZY_E_UNKNOWN;
    }
#endif
#else
    return 0;
#endif
}

int zy_mutex_unlock(zy_mutex_t *mutex)
{
#ifdef DO_MUTEX
#ifdef DO_PTHREAD
    int r = pthread_mutex_unlock(&mutex->mutex);
    switch (r)
    {
    case 0:
        return ZY_OK;
    case EPERM:
        return ZY_E_PERM;
    case EINVAL:
        return ZY_E_NOT_INITIALIZED;
    default:
        return ZY_E_UNKNOWN;
    }
#endif
#else
    return 0;
#endif
}
