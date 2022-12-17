#include "./monkeys.h"

// Monkey 0:
//   Starting items: 79, 98
//   Operation: new = old * 19
//   Test: divisible by 23
//     If true: throw to monkey 2
//     If false: throw to monkey 3
void init_monkey_0(monkey *monkey, int *items, int num_items) {
  monkey->items = items;
}
void init_monkey_1(monkey *monkey) {
  // Monkey 1:
  //   Starting items: 54, 65, 75, 74
  //   Operation: new = old + 6
  //   Test: divisible by 19
  //     If true: throw to monkey 2
  //     If false: throw to monkey 0
}
void init_monkey_2(monkey *monkey) {
  // Monkey 2:
  //   Starting items: 79, 60, 97
  //   Operation: new = old * old
  //   Test: divisible by 13
  //     If true: throw to monkey 1
  //     If false: throw to monkey 3
}
void init_monkey_3(monkey *monkey) {
  // Monkey 3:
  //   Starting items: 74
  //   Operation: new = old + 3
  //   Test: divisible by 17
  //     If true: throw to monkey 0
  //     If false: throw to monkey 1
}
