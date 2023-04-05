from . import Check

class Graph:
    def __init__(self):
        self.nodes = None
        self.edges = None
    
    def createGraph(self, nodes, edges):
        Check.Py1dList(nodes)
        Check.Py2dList(edges)
        Check.EdgeArray(edges)
        Check.EdgeExistInNodes(nodes,edges)
        self.nodes = nodes
        self.edges = edges

    def __str__(self):
        return f"Graph with nodes : {self.nodes} edges : ({self.edges})"

