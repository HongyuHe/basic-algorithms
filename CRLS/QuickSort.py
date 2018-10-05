def QuickSort(left, right):
	if left >= right:  #此处一定要>= 而不是 >, 在等于时就可返回，不必等到大于才返回，不然会拜拜多执行好几次
		global count
		count += 1
		return

	i = left
	j = i + 1
	pivot = i

	while j <= right:
		if sequence[pivot] > sequence[j]:
			i += 1
			sequence[i], sequence[j] = sequence[j], sequence[i]
		j += 1

	sequence[i], sequence[pivot] = sequence[pivot], sequence[i]
	count += 1
	QuickSort (left, i - 1)
	QuickSort (i + 1, right)

count = 0
total = (int)(input("Total: "))
sequence = list()
for i in range(0, total):
	sequence.append(input());

QuickSort (0, total - 1)
print(sequence)
print("Count: ", count)
