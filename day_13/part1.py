from ast import literal_eval
from functools import cmp_to_key


def part1(puzzle_input):
    total = 0
    for i, (packet1, packet2) in enumerate(zip(*[iter(puzzle_input)] * 2)):
        if compare_lines(packet1, packet2) == 1:
            total += i + 1
    return total


def part2(puzzle_input):
    puzzle_input += [[[2]], [[6]]]
    puzzle_input = sorted(puzzle_input, key=cmp_to_key(
        compare_lines), reverse=True)
    return (puzzle_input.index([[2]]) + 1) * (puzzle_input.index([[6]]) + 1)


def compare_lines(p1, p2):
    if isinstance(p1, int) and isinstance(p2, int):
        return 1 if p1 <= p2 else -1

    elif isinstance(p1, int):
        p1 = [p1]

    elif isinstance(p2, int):
        p2 = [p2]

    if p1 == p2:
        return 0

    for i in range(0, max(len(p1), len(p2))):
        try:
            p1_el = p1[i]
        except IndexError:
            return 1
        try:
            p2_el = p2[i]
        except IndexError:
            return -1
        if p1_el != p2_el:
            return compare_lines(p1_el, p2_el)


if __name__ == "__main__":
    with open("input.txt", mode='rt') as f:
        puzzle_input = f.read().split("\n")
        puzzle_input = [literal_eval(l) for l in puzzle_input if l]
        print(f"part1: {part1(puzzle_input)}")
        print(f"part2: {part2(puzzle_input)}")
