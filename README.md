***2016-09-25***

Add an Anti-debug logic in native code, actually in JNI_OnLoad().
It works by checking `TracerPid` in `/proc/[pid]/status`.
If TracerPid is not 0, it will be recognised being attached and then kill the process.

***2016-09-28***

Add timeout checking logic to implement anti-debug. But it's not used widely, so that I comment this part.
