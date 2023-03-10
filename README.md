  Etapas de instalação

  Tenha um MINGW GCC instalado, e nas variaviaveis da ambiente um path para ele
  
  abrir o code blocks e clicar em "open project"
  
  
  selecionar o arquivo .cbp deste repositorio
  
  logo em seguida clicar em 
  
  Build options
  
	-(NOME_DO_PROJETO), search directories, add pasta include
  
	-Debug, Linker settings, add liballegro_font-5.0.10-static-mt-debug
  
	- release, Linker settings, add allegro-5.0.10-mingw-4.7.0\lib\liballegro-5.0.10-monolith-mt.a;
