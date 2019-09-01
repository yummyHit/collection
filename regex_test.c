#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <regex.h>

int main() {
	regex_t regex;
	int reti;
	char msgbuf[100] = {0};
	/* Compile regular expression */
	reti = regcomp(&regex, "^a[[:alnum:]]", 0);
	if( reti ){ fprintf(stderr, "Could not compile regex\n"); exit(1); }
	/* Execute regular expression */
	reti = regexec(&regex, "abc", 0, NULL, 0);
	if( !reti ){
		puts("Match");
	}
	else if( reti == REG_NOMATCH ){
		puts("No match");
	}
	else{
		regerror(reti, &regex, msgbuf, sizeof(msgbuf));
		fprintf(stderr, "Regex match failed: %s\n", msgbuf);
		exit(1);
	}
	/* Free compiled regular expression if you want to use the regex_t again */
	regfree(&regex);
	/* The other examples */
	reti = regcomp(&regex, "\\([0-9]+ ms\\) no", REG_EXTENDED);
	if (reti)
	{
		fprintf(stderr, "Could not compile regex\n");
		return -1;
	}
	reti = regexec(&regex, "(4 ms) no", 0, NULL, 0);
	if (!reti)
		puts("Match again – 4 ms");
	else if (reti == REG_NOMATCH)
		puts("No match here – 4 ms?");
	reti = regexec(&regex, "(x ms) yes", 0, NULL, 0);
	if (reti == REG_NOMATCH)
		puts("No match here – x ms");
	reti = regexec(&regex, "(44 ms) no", 0, NULL, 0);
	if (!reti)
		puts("Match again – 44 ms");
	else if (reti == REG_NOMATCH)
		puts("No match here – 44 ms?");
	/* Yet another stupid example */
	regfree(&regex);
	reti = regcomp(&regex, "ab+c", REG_EXTENDED);
	if (reti)
	{
		fprintf(stderr, "Cound not compile regex\n");
		return -1;
	}
	reti = regexec(&regex, "abc", 0, NULL, 0);
	if (!reti)
		puts("match again – abc");
	reti = regexec(&regex, "abbbc", 0, NULL, 0);
	if (!reti)
		puts("match again – abbbc");
	reti = regexec(&regex, "ac", 0, NULL, 0);
	if (!reti)
		puts("match again – ac?");
	else if (reti == REG_NOMATCH)
		puts("no match here – ac");
	regfree(&regex);
	reti = regcomp(&regex, "[\x20-\x7E]", REG_EXTENDED);
	if (reti)
	{
		fprintf(stderr, "Could not compile regex\n");
		return -1;
	}
	reti = regexec(&regex, " ", 0, NULL, 0);
	if (!reti)
		puts("First");
	else if (reti == REG_NOMATCH)
		puts("Not First");
	reti = regexec(&regex, "a", 0, NULL, 0);
	if (!reti)
		puts("Second");
	else if (reti == REG_NOMATCH)
		puts("Not Second");
	reti = regexec(&regex, "1", 0, NULL, 0);
	if (!reti)
		puts("Third");
	else if (reti == REG_NOMATCH)
		puts("Not Third");
	reti = regexec(&regex, "(", 0, NULL, 0);
	if (!reti)
		puts("Fourth");
	else if (reti == REG_NOMATCH)
		puts("Not Fourth");
	return 0;
}
