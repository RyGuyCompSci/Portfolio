#N Partition of Even Sum Solution
# Coded for COS 320: Algorithm Design
# Author: Ryan Jones

#Contains main program loop
def main():
	while(True):
		v = input().split()
		if(int(v[0]) == 0): return
		numbers = input().split()
		numbers = [int(x) for x in numbers]
		reverseSort(numbers)

		sum = 0
		for i in numbers:
			sum += i
		divisions = int(v[1])
	
		#fail if sum doesn't evenly divide by the number of divisions
		# or if there are fewer values in the set than there are divisions
		if((sum % divisions) != 0 or int(v[0]) < divisions):
			print("Impossible")
		else:
			goal = int(sum / divisions)
			if(findPartition(numbers, goal, divisions)):
				print("Possible")
			else:
				print("Impossible")
			

#Sorts array in descending order (n^2 time)
# Necessary for correct ordering later
def reverseSort(array):
	for i in range(0, len(array)):
		for j in range(i, len(array)):
			if(array[j] > array[i]):
				temp = array[j]
				array[j] = array[i]
				array[i] = temp


#Uses bottom-up method of filling in sum array (n^2 time)
def findPartition(arr, goal, iterations):
	sum = 0
	n = len(arr)
	for i in arr:
		if(i > goal): return False #fail condition
		sum += i
	if(sum < goal): return False #fail condition
	if(sum == goal and iterations == 1): return True #ending condition
	
	computable = []
	min = arr[len(arr)-1]

	for i in range(0, goal+1):
		sub = []
		for j in range(0, n+1):
			if(i==0 or i==(min-1)): sub.append(True)
			else: sub.append(False)
		computable.append(sub)
	
	vals = []
	for i in range(0, goal+1): vals.append(None)

	#loop builder only starts from minimum value
	for i in range(min, goal+1):
		for j in range(1, n+1):
			computable[i][j] = computable[i][j-1]
			if(i >= arr[j-1]):
				truth = computable[i][j] or computable[i - arr[j-1]][j-1]
				if(truth and not(computable[i][j])): vals[i] = arr[j-1]
				computable[i][j] = truth
		
	if(computable[goal][n]): 
		if(not(removeElements(arr, goal, vals))): return False

	#and statement short-circuits if solution doesn't come on a subsequent check
	return computable[goal][n] and findPartition(arr, goal, iterations-1)


#Removes certain values from an array
# Also handles special cases where n-partition sum is impossible
def removeElements(array, goal, values):
	sum = goal
	while(sum != 0):
		val = values[sum]
		if(val==None): return False #needed for some 'impossible' cases where value subtracted doesn't exist
		array.remove(val)
		sum -= val
	return True


main()
