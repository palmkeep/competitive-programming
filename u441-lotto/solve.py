
#
#   powerset
#
#   Returns a list of all possible subsets of the original set
#   Includes the empty set and the original set itself
#
def powerset(orig_set):
    powerset = [[]]
    for i in range(1, 1 + len(orig_set)):
        powerset = unordered_choose(orig_set, i, powerset)
    return powerset
        



#
#   unordered_choose
#
#   Returns a list containing possible ways to choose elements from ListElements
#   Order is not taken into account
#   
#   cardinality = N : N elements are chosen
#
def unordered_choose(listElements, cardinality, listChosen=None, chosen=None):
    if listChosen is None:
        listChosen = []
    if chosen is None:
        chosen = []

    for i in range(1 + len(listElements) - cardinality):
        chosen.append(listElements[i])

        if cardinality == 1:
            listChosen.append(chosen[:])
        else:
            listChosen = unordered_choose(  listElements[i+1:], cardinality - 1,
                                            listChosen, chosen)
        chosen.pop()

    return listChosen

def testCase(line):
    line = [x for x in line.split()]
    N = int(line[0])

    numbers = line
    numbers = numbers[1:]
    numlist = unordered_choose(numbers, 6)
    for num in numlist:
        number = ""
        for x in num:
            number += x
            number += " "
        print(number.rstrip())



def main():
    line = input();
    while (line[0] != "0"):
        testCase(line)
        line = input()
        if (line[0] != "0"):
            print("")

if __name__ == "__main__":
    main()
