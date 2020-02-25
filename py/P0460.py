import collections
# ordered dictionary


class LFUCache:


    def __init__(self, capacity: int):
        self.cap = capacity
        self.min_time = 0
        self.dict_time = dict()#collections.OrderedDict()
        self.dict_key_value = dict()
        self.dict_key_time = dict()

    def get(self, key: int) -> int:
        if key in self.dict_key_value:
            self.touch(key)
            return self.dict_key_value[key]
        else:
            return -1

    def insert_ordered_dict(self, time, key):
        if time not in self.dict_time:
            self.dict_time[time] = collections.OrderedDict()
        self.dict_time[time][key] =  key

    def touch(self, key: int):
        time = self.dict_key_time[key]
        orderedKV = self.dict_time[time]
        del orderedKV[key]
        if not self.dict_time[time]:
            del self.dict_time[time]
        if not orderedKV and self.min_time == time:
            self.min_time += 1
        self.dict_key_time[key] += 1
        self.insert_ordered_dict(time+1, key)

    def put(self, key: int, value: int) -> None:
        if self.cap < 1:
            return
        if key in self.dict_key_value:
            self.dict_key_value[key] = value
            self.touch(key)
        else:
            if len(self.dict_key_value) >= self.cap:
                data = self.dict_time[self.min_time].popitem(last = False)
                del self.dict_key_time[data[0]]
                del self.dict_key_value[data[0]]
                if not self.dict_time[self.min_time]:
                    del self.dict_time[self.min_time]

            self.dict_key_value[key] = value
            self.dict_key_time[key] = 1
            self.insert_ordered_dict(1, key)
            self.min_time = 1
            

if __name__ == "__main__":
    cache = LFUCache(2)
    cache.put(3, 1)
    cache.put(2, 1)
    cache.put(2, 2)
    cache.put(4, 4)
    cache.get(2)
    cache.get(1)#       // returns 1
    cache.put(3, 3)#    // evicts key 2
    cache.get(2)#       // returns -1 (not found)
    cache.get(3)#       // returns 3.
    cache.put(4, 4)#    // evicts key 1.
    cache.get(1)#       // returns -1 (not found)
    cache.get(3)#       // returns 3
    cache.get(4)#       // returns 4