#include "./monkeys.h"
// Monkey 0:
//   Starting items: 79, 98
//   Operation: new = old * 19
//   Test: divisible by 23
//     If true: throw to monkey 2
//     If false: throw to monkey 3
void add_item(monkey *monkey, t_item *item) {
  monkey->last_item->next = item;
  monkey->last_item = item;
}

int perform_monkey_0(monkey **monkeys) {
  t_item *item = (monkeys[0]->items);
  int inspections = 0;
  while (item != NULL) {
    int worry_val = item->val * 19;
    worry_val = (int)worry_val / 3;
    if (worry_val % 23 == 0) {
      add_item(monkeys[2], item);
    } else {
      add_item(monkeys[3], item);
    }

    item = item->next;
    inspections++;
  }
  return inspections;
}

// Monkey 1:
//   Starting items: 54, 65, 75, 74
//   Operation: new = old + 6
//   Test: divisible by 19
//     If true: throw to monkey 2
//     If false: throw to monkey 0
int perform_monkey_1(monkey **monkeys) {
  t_item *item = (monkeys[1]->items);
  int inspections = 0;
  while (item != NULL) {
    int worry_val = item->val + 6;
    worry_val = (int)worry_val / 3;
    if (worry_val % 19 == 0) {
      add_item(monkeys[1], item);
    } else {
      add_item(monkeys[3], item);
    }

    item = item->next;
    inspections++;
  }
  return inspections;
}

// Monkey 2:
//   Starting items: 79, 60, 97
//   Operation: new = old * old
//   Test: divisible by 13
//     If true: throw to monkey 1
//     If false: throw to monkey 3
int perform_monkey_2(monkey **monkeys) {
  t_item *item = (monkeys[1]->items);
  int inspections = 0;
  while (item != NULL) {
    int worry_val = item->val * item->val;
    worry_val = (int)worry_val / 3;
    if (worry_val % 13 == 0) {
      add_item(monkeys[1], item);
    } else {
      add_item(monkeys[3], item);
    }

    item = item->next;
    inspections++;
  }
  return inspections;
}

// Monkey 3:
//   Starting items: 74
//   Operation: new = old + 3
//   Test: divisible by 17
//     If true: throw to monkey 0
//     If false: throw to monkey 1
int perform_monkey_3(monkey **monkeys) {
  t_item *item = (monkeys[1]->items);
  int inspections = 0;
  while (item != NULL) {
    int worry_val = item->val + 3;
    worry_val = (int)worry_val / 3;
    if (worry_val % 17 == 0) {
      add_item(monkeys[0], item);
    } else {
      add_item(monkeys[1], item);
    }

    item = item->next;
    inspections++;
  }
  return inspections;
}
