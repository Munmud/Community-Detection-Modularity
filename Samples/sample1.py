import time
from age_community_detection import Graph

nodes = [0, 1, 2, 3, 4, 5]
edges = [[0, 1], [0, 2], [1, 2], [2, 3], [3, 4], [3, 5], [4, 5]]

start_time = time.time()

g = Graph.Graph()
g.createGraph(nodes, edges)
res = g.get_community()

print(res)

end_time = time.time()
print("Elapsed time: {} seconds".format(end_time - start_time))

