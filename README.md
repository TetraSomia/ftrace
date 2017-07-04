# ftrace
Function call tracer

- Usage :
  `Usage : ./ftrace [-v] [-g] <commande>`
  ` -v  Disable verbose on stderr`
  ` -g  Enbale graph generation (.dot)`

- Graph generation :
  
  Generate a .dot file, you can use `xdot` to open it

- Call detected :
  
  - syscall
  
  - library function call
  
  - function call (if binary not stripped)
  
  - intra-library function call (but without symbols)
  
  
