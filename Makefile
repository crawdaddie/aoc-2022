# 7:
# 	cd day_07 && gcc part1.c ../common/*.c -o part1 && ./part1
#.

.PHONY: day%
	day%:
		echo "day_$@"

7:
	cd day_07 && python3 part1.py

8:
	cd day_08 && gcc part1.c ../common/*.c -o part1 && ./part1

9:
	cd day_09 && gcc part1.c ../common/*.c -o part1 && ./part1

10:
	cd "day_$@" && gcc part1.c ../common/*.c -o part1 && ./part1


10_2:
	cd "day_10" && gcc part2.c ../common/*.c -o part2 && ./part2
test_common:
	gcc common/str_utils.c common/test/test_str_utils.c -o common/test/test_str_utils && ./common/test/test_str_utils

