#include "nvm_struct.h"
#include "status.h"

#ifndef NVM_CACHE_H
#define NVM_CACHE_H

status_t nvm_instance_to_cache(nvm_cache_t *cache);
status_t nvm_cache_to_instance(nvm_cache_t *cache);

#endif
