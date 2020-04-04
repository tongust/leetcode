import sys
import bisect
INT_MAX = sys.maxsize
class Solution:
    def getSkyline(self, buildings):
        if not buildings:
            return []
        if len(buildings) == 1:
            return [buildings[0][0:3:2], [buildings[0][1], 0]]
        
        # init
        lrh = dict()
        lrh[buildings[0][0]] = buildings[0][1:3]
        lrh[buildings[0][1]] = [INT_MAX, 0]
        head = [buildings[0][0], buildings[0][1]]

        for i in range(1, len(buildings)):
            b = buildings[i]
            left = b[0]
            right = b[1]
            hight = b[2]
            lo = bisect.bisect_left(head, left)
            if lo >= len(head) or head[lo] != left:
                lo -= 1
            hi = bisect.bisect_left(head, right)
            if hi >= len(head) or head[hi] != right:
                hi -= 1

            firstIndex = head[lo]
            lastIndex = head[hi]
            firstRight = lrh[head[lo]][0]
            firstHight = lrh[head[lo]][1]
            lastRight = lrh[head[hi]][0]
            lastHight = lrh[head[hi]][1]
            # __---__
            if lo == hi:
                if firstHight < hight:
                    lrh[right] = [firstRight, firstHight]
                    lrh[firstIndex] = [left,firstHight]
                    lrh[left] = [right, hight]
                    bisect.insort_left(head, left)
                    bisect.insort_left(head, right)
            else:
                jIndex = [head[j] for j in range(lo+1, hi)]
                # first
                if firstHight < hight and left < firstRight:
                    if firstIndex == left:
                        lrh[firstIndex] = [firstRight, hight]
                    else:
                        lrh[firstIndex] = [left,firstHight]
                        lrh[left] = [firstRight, hight]
                        bisect.insort_left(head, left)
                # last
                
                if lastHight < hight and lastIndex != right:
                    bisect.insort_left(head, right)
                    lrh[right] = [lastRight, lastHight]
                    lrh[lastIndex] = [right, hight]
                # lo+1 -- hi
                for j in jIndex:
                    bj = lrh[j]
                    if bj[1] < hight:
                        lrh[j] = [bj[0], hight]
        # concatenate
        pos_hight = [[k, lrh[k][1]] for k in lrh]
        key_points = []
        pos_hight.sort()
        for ph in pos_hight:
            if not key_points:
                key_points.append(ph)
            else:
                if key_points[-1][1] != ph[1]:
                    key_points.append(ph)
        
        return key_points
                    



if __name__ == "__main__":
    so = Solution()
    print(so.getSkyline([[2190,661048,758784],[9349,881233,563276],[12407,630134,38165],[22681,726659,565517],[31035,590482,658874],[41079,901797,183267],[41966,103105,797412],[55007,801603,612368],[58392,212820,555654],[72911,127030,629492],[73343,141788,686181],[83528,142436,240383],[84774,599155,787928],[106461,451255,856478],[108312,994654,727797],[126206,273044,692346],[134022,376405,472351],[151396,993568,856873],[171466,493683,664744],[173068,901140,333376],[179498,667787,518146],[182589,973265,394689],[201756,900649,31050],[215635,818704,576840],[223320,282070,850252],[252616,974496,951489],[255654,640881,682979],[287063,366075,76163],[291126,900088,410078],[296928,373424,41902],[297159,357827,174187],[306338,779164,565403],[317547,979039,172892],[323095,698297,566611],[323195,622777,514005],[333003,335175,868871],[334996,734946,720348],[344417,952196,903592],[348009,977242,277615],[351747,930487,256666],[363240,475567,699704],[365620,755687,901569],[369650,650840,983693],[370927,621325,640913],[371945,419564,330008],[415109,890558,606676],[427304,782478,822160],[439482,509273,627966],[443909,914404,117924],[446741,853899,285878],[480389,658623,986748],[545123,873277,431801],[552469,730722,574235],[556895,568292,527243],[568368,728429,197654],[593412,760850,165709],[598238,706529,500991],[604335,921904,990205],[627682,871424,393992],[630315,802375,714014],[657552,782736,175905],[701356,827700,70697],[712097,737087,157624],[716678,889964,161559],[724790,945554,283638],[761604,840538,536707],[776181,932102,773239],[855055,983324,880344]]))
    print(so.getSkyline([[2,13,10],[10,17,25],[12,20,14]]))
    print(so.getSkyline([[2,9,10],[3,7,15],[5,12,12],[15,20,10],[19,24,8]]))
    print(so.getSkyline([[1,2,1],[1,2,2],[1,2,3]]))
    



