>  *    *      s@
   v<   v<
   .    ,
   >^   >^

   "A"  "B"

"This program implements a multithreaded cat program."
"Thread "A" (forks with the "*" symbol) reads single characters from stdin."
"Thread "B" (forks on the next "*") outputs single characters from stdin."
"The "s" on the main thread synchronizes it, preventing it from terminating."
"It hangs when it is finished outputting characters."