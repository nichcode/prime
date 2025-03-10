
#pragma once

#ifdef PRIME_CONFIG_DEBUG
#define PRIME_TRACE(message, ...)           
#define PRIME_INFO(message, ...)            
#define PRIME_WARN(message, ...)            
#define PRIME_ERROR(message, ...)           
#define PRIME_ASSERT(expr)                  
#define PRIME_ASSERT_MSG(expr, message)     
#else
#define PRIME_TRACE(message, ...)         
#define PRIME_DEBUG(message, ...)         
#define PRIME_INFO(message, ...)         
#define PRIME_WARN(message, ...)          
#define PRIME_ERROR(message, ...)               
#define PRIME_ASSERT(expr)
#define PRIME_ASSERT_MSG(expr, message)
#endif // PRIME_CONFIG_DEBUG