import ctypes
import os
from collections import defaultdict


absolute_path = os.path.dirname(__file__)
absolute_path_ubuntu = os.path.join(absolute_path, "lib_ubuntu", "library.so")
absolute_path_windows32 = os.path.join(absolute_path, "lib_windows", 'x86', 'Release',  "lib_windows.dll")
absolute_path_windows64 = os.path.join(absolute_path, "lib_windows", 'x64', 'Release',  "lib_windows.dll")

# # Load the shared library
try:
    lib = ctypes.CDLL(absolute_path_ubuntu)
except:
    try:
        lib = ctypes.CDLL(absolute_path_windows32)
    except :
        lib = ctypes.CDLL(absolute_path_windows64)

get_community_assignment = lib.get_community_assignment
get_community_assignment.restype = ctypes.POINTER(ctypes.c_int)

def get_community(nodes, edges):
    nodeNum = 0
    mp_nodes={}
    new_nodes=[n for n in range(len(nodes))]
    new_edges=[]
    for n in nodes:
        mp_nodes[n] = nodeNum
        nodeNum+=1
    
    for e in edges:
        new_edges.append([ mp_nodes[e[0]], mp_nodes[e[1]] ])

    arr = (ctypes.c_int * (len(new_edges)*2))()
    for i,[u,v] in enumerate(new_edges):
        arr[(i*2)] = u
        arr[i*2+1] = v
    
    nrows = len(new_edges)
    nodeCount = len(new_nodes)

    res = get_community_assignment(
        arr,
        ctypes.c_int(nrows),
        ctypes.c_int(nodeCount))
    
    
    res = [res[i] for i in range(len(nodes))]
    com = defaultdict(list)
    for n in nodes:
        com[res[mp_nodes[n]]].append(n)
    final_com = []
    for x in com :
        final_com.append(com[x])
    
    return final_com




