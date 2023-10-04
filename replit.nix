{ pkgs }: {
	deps = [
		pkgs.cmake
  pkgs.valgrind
  pkgs.clang_12
		pkgs.ccls
		pkgs.gdb
		pkgs.gnumake
	];
}