# [Largest Component Size by Common Factor](https://leetcode.com/problems/largest-component-size-by-common-factor/)
Given a non-empty array of unique positive integers A, consider the following graph:

- There are A.length nodes, labelled A[0] to A[A.length - 1];

- There is an edge between A[i] and A[j] if and only if A[i] and A[j] share a common factor greater than 1.

Return the size of the largest connected component in the graph.

# Solution
First of all, we should find all the factors of any number. Give array: [21, 22, 6], two dictionaries are created: *pri2num* and *num2pri*. The primes and numbers are linked to each other by those two maps. For this case, they are:

- *pri2num* = {3:[21, 6], 2:[6,22], 7:[21], 11:[22]}

- *num2pri* = {21:[3, 7], 22:[2,11], 6:[2,3]}

## Get primes
Below are the codes to calculate the primes.
```python
        for i in range(n):
            b = a = A[i]
            if a in PrimeNumSet:
                num2pri[b].add(a)
                addPri(a,b)
                continue
            ind = 0
            p = PrimeNum[ind]
            while p <= a:
                if a % p == 0:
                    num2pri[b].add(p)
                    addPri(p,b)
                    a = int(a/p) # here is the key to improve the performence
                    if a in PrimeNumSet:
                        num2pri[b].add(a)
                        addPri(a,b)
                        break
                else:
                    ind += 1
                    p = PrimeNum[ind]
```

## Find the largest set
Two tables are used to track the status of each element. This is to avoid visiting the element twice. For example, we start searching from prime: 3.

1) In the first search, we get two numbers {21,6} for the components. And get another two new prime for {21,6}: 2 and 7 (prime 3 is ignored since it has been visited).
2) In the second search, the 2 is poped out. And according to *pri2num*, its numbers are 6, 22. Since 6 has been visited (its status is tracked in *C*), 6 is added to the components.
3) End the searching because there are no new prime that is never visisted. The largest components are {21,6,22}

```py
        pri2num, num2pri = self.getGraph(A)
        n = len(A)
        B = dict()
        C = dict()
        for a in A:
            C[a] = False
        for a in pri2num:
            B[a] = False
        res = 1
        s = set()
        for a in pri2num:
            if B[a] or len(pri2num[a]) == 1:
                continue
            num_set = set()
            que = [a]
            while que:
                q = que.pop()
                B[q] = True
                adj = pri2num[q]
                for i in adj:
                    if C[i]:
                        continue
                    num_set.add(i)
                    C[i] = True
                    adj0 = num2pri[i]
                    for j in adj0:
                        if not B[j]:
                            B[j] = True
                            que.append(j)
            res1 = len(num_set)
            if res1 > res:
                res = res1
        return res
```