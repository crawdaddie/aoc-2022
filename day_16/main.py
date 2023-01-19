valves = {}
with open("./test_input.txt", "r") as f:
    for line in f:
        line = line.strip()
        valve = line.split()[1]
        flow = int(line.split(";")[0].split("=")[1])
        targets = line.split("to ")[1].split(" ", 1)[1].split(", ")
        valves[valve] = targets
