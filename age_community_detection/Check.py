from . import Exception

def Py1dList(data):
    if not isinstance(data, list):
        raise Exception.NotListException(data)

def Py2dList(data):
    if not isinstance(data, list) or any(not isinstance(sublist, list) for sublist in data):
        raise Exception.Not2DListException(data)

def EdgeArray(edges):
    for e in edges:
        if (len(e)!=2):
            raise Exception.NotAnEdgeException(e)

def EdgeExistInNodes(nodes, edges):
    for u,v in edges:
        if u not in nodes:
            raise Exception.NodeNotExist(u)
        if v not in nodes:
            raise Exception.NodeNotExist(v)