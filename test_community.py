import unittest
from age_cda import Graph

class TestCommunity(unittest.TestCase):
    def test_community(self):
        """Test community detection"""
        nodes = [7, 1, 2, 3, 4, 5]
        edges = [[7, 1], [7, 2], [1, 2], [2, 3], [3, 4], [3, 5], [4, 5]]
        g = Graph.Graph()
        g.createGraph(nodes, edges)
        res = g.get_community()
        print(res)
        self.assertEqual(res,[[7, 1, 2], [3, 4, 5]])