import time
from age_cda import Graph
import networkx as nx

nodes = [0, 1, 2, 3, 4, 5]
edges = [[0, 1], [0, 2], [1, 2], [2, 3], [3, 4], [3, 5], [4, 5]]

G = nx.karate_club_graph()
nodes = [x for x in range(G.number_of_nodes())]
edges = [list(x) for x in G.edges]

start_time = time.time()

g = Graph.Graph()
g.createGraph(nodes, edges)
final= g.get_community()

print(final)

end_time = time.time()

print("Elapsed time: {} seconds".format(end_time - start_time))

# from collections import defaultdict
# mp = defaultdict(list)



# from age_dijkstra import Age_Dijkstra
# con = Age_Dijkstra()

# con.connect(
#     host="localhost",       # default is "172.17.0.2" 
#     port="5430",            # default is "5432"
#     dbname="postgresDB",    # default is "postgres"
#     user="postgresUser",    # default is "postgres"
#     password="postgresPW",  # default is "agens"
#     printMessage = False     # default is False
# )

# GRAPH_NAME = "karate"

# con.create_graph( graph_name = GRAPH_NAME)
# con.delete_graph( graph_name = GRAPH_NAME)
# con.create_graph( graph_name = GRAPH_NAME)

# def addToDb(final_community):
#     mp = {}
#     try:
#         for idx, xx in enumerate(final_community):
#             for x in xx:
#                 mp[x] = idx
#                 con.set_vertices(
#                 graph_name = GRAPH_NAME, 
#                 label= ("People_"+ str(idx)), 
#                 property={"name" : x,}
#                 )
#     except Exception as e :
#         print ("Nodes Creating error : ",e)

#     try:
#         for x in edges:
#             con.set_edge(
#                 graph_name = GRAPH_NAME, 
#                 label1=("People_"+ str(mp[x[0]]) ), 
#                 prop1={"name" : x[0],}, 
#                 label2=("People_"+ str(mp[x[1]]) ), 
#                 prop2={"name" : x[1]}, 
#                 edge_label = "Neighbour", 
#                 edge_prop = {"distance":"1"}
#             )
#     except Exception as e :
#         print ("Edges Creating error : ",e)
#     print(final_community)


# addToDb(final)