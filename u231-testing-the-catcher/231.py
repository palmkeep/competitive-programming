import fileinput

def ans(mi, co):
    #sorted_mi = sorted(mi);
    if mi == []:
        return 0;
    if co == -1:
        return max(1+ans(mi[1:], mi[0]), ans(mi[1:], -1));
    else:
        if mi[0] < co:
            return max(1+ans(mi[1:], mi[0]), ans(mi[1:], co));
        else:
            return ans(mi[1:], co);
        



mi = [];

test = 1;

first = True;
for line in fileinput.input():
    if int(line) == -1:
        if prev == -1:
            exit();
        else:
            if not first:
                print("");
            print("Test #{0}:".format(test));
            print("  maximum possible interceptions: {0}".format(ans(mi, -1)));
            mi = [];
            first = False;
            test += 1;
    else:
        mi.append(int(line));

    prev = int(line);
