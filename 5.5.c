/*
 * Exercise 5-5.  Write versions of the library functions strncpy,
 * strncat, strncmp, which operate on at most the first n characters
 * of their argument strings.  For example, strncpy(s,t,n) copies
 * at most n characters of t to s. 
 */

#include <stdio.h>

char *mstrncpy(char *, char *, size_t);
char *mstrncat(char *, char *, size_t);
int mstrncmp(char *, char *, size_t);

/* 
 * Copy at most n characters of string t to s.  Pad with '\0' if t has
 * fewer than n characters.  
 */
char * 
mstrncpy(char *s, char *t, size_t n) 
{
	int i;
	for (i = 0; *s && *t && (i < n); i++) {
		*s++ = *t++;
	}
	*s = '\0';
        return s - i;
}

/*
 * Concatenate at most n characters of string t to string s.
 * Terminate s with '\0' and then return s.
 */
char *
mstrncat(char *s, char *t, size_t n)
{
	int i;
	char *p = s;
	
	while (*p)
		p++;
	for (i = 0; *t && (i < n); i++) {
		*p++ = *t++;
	}
	*p = '\0';
	return s;
}

/*
 * Compare at most n characters of string s to string t.
 * Return <0 if s<t, 0 if s==t, or >0 if s>t.
 */
int
mstrncmp(char *s, char *t, size_t n)
{
	int i;
	
	for (i = 1; (i < n) && *s && *t && (*s++ == *t++); i++) {
		if ((*t == '\0') && (*s == '\0'))
			return 0;
		if (*s == '\0')
			return -1;
		if (*t == '\0')
			return 1;
	}
	return 0;
}

/* Test mstrncpy, mstrncat and mstrncmp.  */
int
main() {
	char a[10];
	char b[] = "abcd";
	char c[] = "abc";
	char d[] = "abc";
	printf("%s\n", mstrncpy(a, b, 10)); /* abcd */
	printf("%s\n", mstrncpy(a, b, 2));  /* ab */
	printf("%s\n", mstrncat(a, b, 10)); /* ababcd */
	printf("%s\n", mstrncat(a, b, 2));  /* ababcdab */
	printf("%d\n", mstrncmp(c, d, 4));  /* 0 */
	printf("%d\n", mstrncmp(c, b, 3));  /* 0 */
	printf("%d\n", mstrncmp(c, b, 8));  /* -1 */
	printf("%d\n", mstrncmp(b, c, 8));  /* 1 */
        return 0;
}
