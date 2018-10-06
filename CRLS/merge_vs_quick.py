import time
#QuickSort
def QuickSort(left, right):
    if left >= right:
        return

    i = left
    j = i + 1
    pivot = i

    while j <= right:
        if num_list[pivot] > num_list[j]:
            i += 1
            num_list[i], num_list[j] = num_list[j], num_list[i]
        j += 1

    num_list[i], num_list[pivot] = num_list[pivot], num_list[i]

    QuickSort (left, i - 1)
    QuickSort (i + 1, right)

#MergeSort:
def MergeSort(A):
    if len(A) < 2:
        return A

    mid = len(A) // 2
    l = MergeSort( A[:mid] )
    r = MergeSort(A[mid : (len(A)+1)])
    merged = Merge(l, r)
    return merged

def Merge(l, r):
    merged = []
    i, j = 0, 0

    while i < len(l) and j < len(r):
        if l[i] <= r[j]:
            merged.append(l[i])
            i += 1
        else:
            merged.append(r[j])
            j += 1
    for x in range(i, len(l)):
        merged.append(l[x])
    for y in range(j, len(r)):
        merged.append(r[y])

    return merged

try:
	fhand = open("500000number.txt")
except:
	print("Erro: File cannot be opened !")
	quit();
num_list = fhand.read().split();

start = time.clock()    #QuickSort
QuickSort (0, 500000 - 1)
end = time.clock()
print ("CPU execution time of Quick Sort (worst case): ", end-start, "sec")
start = time.clock()    #MergeSort:
MergeSort(num_list)
end = time.clock()
print ("CPU execution time of Merge Sort (worst case): ", end-start, "sec")
