/* compile debug log */
#ifdef TEMO
	#define DEBUG(X) X
#else
	#define DEBUG(X)
#endif

/* time measure */
#define TM_INIT\
	struct timeval time_start, time_end; double time_taken;

#define TM_START(_log)\
	gettimeofday(&time_start, NULL); \
	printf("%s ...\n", _log);

#define TM_END(_log)\
	gettimeofday(&time_end, NULL); \
	time_taken = (time_end.tv_sec - time_start.tv_sec) * 1e6; \
	time_taken = (time_taken + (time_end.tv_usec - time_start.tv_usec)) * 1e-6; \
	printf("%s took(%f)\n", _log, time_taken);
