/* string-lib.h - headers for string-lib.c
   Eugene Kim, <eekim@eekim.com>
   $Id: string-lib.h,v 1.1.1.1 2004/02/13 07:21:11 hunter Exp $

   Copyright (C) 1996,1997 Eugene Eric Kim
   All Rights Reserved
*/

#ifndef __STRING_LIB_H__
#define __STRING_LIB_H__

char* newstr(char *str);
char* substr(char *str, int offset, int len);
char* replace_ltgt(char *str);
char* lower_case(char *buffer);

#endif
