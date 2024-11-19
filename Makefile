clang_format: src
	 find ./src -name '*.cpp' -o -name '*.hpp' | xargs clang-format -i
