7:
	cd day_07 && gcc part1.c ../common/*.c -o part1 && ./part1

test_common:
	gcc common/str_utils.c common/test/test_str_utils.c -o common/test/test_str_utils && ./common/test/test_str_utils

