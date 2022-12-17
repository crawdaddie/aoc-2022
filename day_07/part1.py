
def new_dir(c: str, dest: str):
    if dest == "/":
        return f'{dest}'
    if c == "/":
        return f'/{dest}'

    if dest == "..":
        return strip_last_token(c)

    return f'{c}/{dest}'


def strip_last_token(path: str, delimiter='/'):
    return delimiter.join(path.split(delimiter)[:-1])


small_dirs = []

with open("./test_input.txt", 'r') as f:
    c = ""
    fs = {"_size": 0}
    root = fs
    parent = root
    for line in f:
        line = line.strip()
        if line[:5] == "$ cd ":
            c = new_dir(c, line[5:])
            if c not in root and c != '':
                root[c] = {"_size": 0}
                parent = root
                root = root[c]
            continue
        if line[0].isdigit():
            size, name = line.split()
            size = int(size)
            # root['_size'] += size
            parent_size = parent[c]['_size'] + size
            parent[c]['_size'] = parent_size
            if parent_size < 100000:
                small_dirs.append(parent_size)

        if line[:4] == 'dir ':
            continue
    print(fs)
print(sum(small_dirs))
