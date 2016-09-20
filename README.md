# multifunge interpreter

A funge is a programming language.

It looks like this:

```befunge
>v
^<
```

Which means:

```c
int main(argc, char **argv)
{
	for(;;;)
		;
}
```

Or this:

```befunge
25*"!dlroW ,olleH">:#,_@
```

Which means:

```c
#include <stdio.h>
int main()
{
	printf("Hello, World!\n");
}
```

This project includes a very fast interpreter capable of executing these programs.  Future work _might_ include building a compiler as well!
