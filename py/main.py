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
    
    def isOn(lamp, query):
        if lamp[0] == query[0] or lamp[1] == query[1]:
            return True
        if lamp[0] - query[0] == lamp[1] - query[1]:
            return True
        return False

if __name__ == "__main__":

    so = Solution()
    lamps = [[7,55],[53,61],[2,82],[67,85],[81,75],[38,91],[68,0],[60,43],[40,19],[12,75],[26,2],[24,89],[42,81],[60,58],[77,72],[33,24],[19,93],[7,16],[58,54],[78,57],[97,49],[65,16],[42,75],[90,50],[89,34],[76,97],[58,23],[62,47],[94,28],[88,65],[3,87],[81,10],[12,81],[44,81],[54,92],[90,54],[17,54],[27,82],[48,15],[8,46],[4,99],[15,13],[90,77],[2,87],[18,33],[52,90],[4,95],[57,61],[31,22],[32,8],[49,26],[24,65],[88,55],[88,38],[64,76],[94,76],[59,12],[41,46],[80,28],[38,36],[65,67],[75,37],[56,97],[83,57],[2,4],[44,43],[71,90],[62,40],[79,94],[81,11],[96,34],[38,11],[22,3],[54,96],[78,33],[54,54],[79,98],[1,28],[0,32],[37,11]]
    queries = [[85,29],[24,84],[95,68],[80,35],[31,53],[69,45],[85,29],[87,25],[42,47],[7,59],[99,3],[31,70],[64,62],[44,91],[55,25],[15,52],[95,33],[21,29],[61,34],[93,34],[79,27],[30,86],[52,0],[18,10],[5,1],[40,21],[11,48],[55,94],[22,42],[81,0],[39,43],[5,25],[43,29],[45,47],[83,93],[77,70],[22,63],[30,73],[18,48],[39,88],[91,47]]
    res = so.gridIllumination(5, lamps, queries)
    for r in res:
        pass
