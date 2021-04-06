import fileinput


def fn(st, co):
    if st == [] and co == []:
        return True;
    elif st[0] == co[0]:
        return fn(st[1:], co[1:]);
    else:
        return False;
                


sl = [];
bol = False;

for line in fileinput.input():
    if bol and line == "XXXXXX\n":
        exit();
    elif line == "XXXXXX\n":
        bol = True;
    elif bol:
        found = False;
        l = [];
        for w in sl:
            if len(line) == len(w) and fn(sorted(list(line)), sorted(list(w))):
                found = True;
                l.append(w[:len(w)-1]);
        if not found:
            print("NOT A VALID WORD");
        else:
            l = sorted(l);
            for s in l:
                print(s);
        print("******");
    else:
        sl.append(line);
        
