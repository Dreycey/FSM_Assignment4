/*
 * log.h
 *
 *  Created on: Feb 25, 2022
 *      Author: dreyceyalbin
 */

#ifndef LOG_H_
#define LOG_H_

#include <stdio.h>

#ifdef DEBUG
#    define LOG printf
#else
#    define LOG(...)
#endif

#endif /* LOG_H_ */
