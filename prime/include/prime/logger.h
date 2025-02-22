
#pragma once

#include "defines.h"

#ifdef PCONFIG_DEBUG
#define PTRACE(message, ...)           
#define PINFO(message, ...)            
#define PWARN(message, ...)            
#define PERROR(message, ...)           
#define PFATAL(message, ...)           
#define PASSERT(expr)                  
#define PASSERT_MSG(expr, message)     
#else
#define PTRACE(message, ...)         
#define PDEBUG(message, ...)               
#define PINFO(message, ...)                
#define PWARN(message, ...)          
#define PERROR(message, ...)         
#define PFATAL(message, ...)        
#define PASSERT(expr)
#define PASSERT_MSG(expr, message)
#endif // PCONFIG_DEBUG