class Solution:
    def gridIllumination(self, N, lamps, queries):
        res = []
        
        diag0 = dict()
        diag1 = dict()
        row = dict()
        col = dict()
        lampDict = dict()

        for lamp in lamps:
            a = lamp[1] - lamp[0]
            b = lamp[1] + lamp[0]
            pair = (lamp[0], lamp[1])
            if a not in diag0:
                diag0[a] = dict()
            diag0[a][pair] = pair

            if b not in diag1:
                diag1[b] = dict()
            diag1[b][pair] = pair

            if lamp[0] not in row:
                row[lamp[0]] = dict()
            row[lamp[0]][pair] = pair

            if lamp[1] not in col:
                col[lamp[1]] = dict()
            col[lamp[1]][pair] = pair

        for query in queries:
            diff = query[1] - query[0]
            diff1 = query[1] + query[0]
            if query[0] in row or query[1] in col or diff in diag0 or diff1 in diag1:
                res.append(1)
                # turn of lamps
                for i in [-1,0,1]:
                    for j in [-1,0,1]:
                        pair = (query[0]+i, query[1]+j)
                        if pair[0] in row and pair in row[pair[0]]:
                            del row[pair[0]][pair]
                            if not row[pair[0]]:
                                del row[pair[0]]
                        if pair[1] in col and pair in col[pair[1]]:
                            del col[pair[1]][pair]
                            if not col[pair[1]]:
                                del col[pair[1]]
                        diff = pair[1] - pair[0]
                        if diff in diag0 and pair in diag0[diff]:
                            del diag0[diff][pair]
                            if not diag0[diff]:
                                del diag0[diff]
                        diff = pair[1] + pair[0]
                        if diff in diag1 and pair in diag1[diff]:
                            del diag1[diff][pair]
                            if not diag1[diff]:
                                del diag1[diff]
            else:
                res.append(0)

        return res
    